/*
 * Copyright 2010-2015 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include <aws_iot_mqtt_client_interface.h>
#include <aws_iot_shadow_interface.h>
#include "aws_iot_error.h"
#include "aws_iot_log.h"
#include "aws_iot_shadow_actions.h"
#include "aws_iot_shadow_json.h"
#include "aws_iot_shadow_key.h"
#include "aws_iot_shadow_records.h"

const ShadowInitParameters_t ShadowInitParametersDefault = {
		.pHost = AWS_IOT_MQTT_HOST,
		.port = AWS_IOT_MQTT_PORT,
		.pRootCA = NULL,
		.pClientCRT = NULL,
		.pClientKey = NULL
};

const ShadowConnectParameters_t ShadowConnectParametersDefault = {
		.pMyThingName = AWS_IOT_MY_THING_NAME,
		.pMqttClientId = AWS_IOT_MQTT_CLIENT_ID
};

void aws_iot_shadow_reset_last_received_version(void) {
	shadowJsonVersionNum = 0;
}

uint32_t aws_iot_shadow_get_last_received_version(void) {
	return shadowJsonVersionNum;
}

void aws_iot_shadow_enable_discard_old_delta_msgs(void) {
	shadowDiscardOldDeltaFlag = true;
}

void aws_iot_shadow_disable_discard_old_delta_msgs(void) {
	shadowDiscardOldDeltaFlag = false;
}

IoT_Error_t aws_iot_shadow_init(AWS_IoT_Client *pClient, ShadowInitParameters_t *pParams) {
	if (pClient == NULL) {
		return NULL_VALUE_ERROR;
	}

	IoT_Client_Init_Params mqttInitParams;
	mqttInitParams.enableAutoReconnect = pParams->enableAutoReconnect;
	mqttInitParams.pHostURL =  pParams->pHost;
	mqttInitParams.port = pParams->port;
	mqttInitParams.pRootCALocation = pParams->pRootCA;
	mqttInitParams.pDeviceCertLocation = pParams->pClientCRT;
	mqttInitParams.pDevicePrivateKeyLocation = pParams->pClientKey;
	mqttInitParams.mqttCommandTimeout_ms = 2000;
	mqttInitParams.tlsHandshakeTimeout_ms = 10000;
	mqttInitParams.isSSLHostnameVerify = true;
	mqttInitParams.disconnectHandler = pParams->disconnectHandler;

	IoT_Error_t rc = aws_iot_mqtt_init(pClient, &mqttInitParams);
	if(SUCCESS != rc) {
		return rc;
	}

	resetClientTokenSequenceNum();
	aws_iot_shadow_reset_last_received_version();
	initDeltaTokens();
	return SUCCESS;
}

IoT_Error_t aws_iot_shadow_connect(AWS_IoT_Client *pClient, ShadowConnectParameters_t *pParams) {
	if(NULL == pClient || NULL == pParams || NULL == pParams->pMqttClientId) {
		return NULL_VALUE_ERROR;
	}

	IoT_Error_t rc = SUCCESS;
	IoT_Client_Connect_Params ConnectParams = iotClientConnectParamsDefault;

	snprintf(myThingName, MAX_SIZE_OF_THING_NAME, "%s", pParams->pMyThingName);
	snprintf(mqttClientID, MAX_SIZE_OF_UNIQUE_CLIENT_ID_BYTES, "%s", pParams->pMqttClientId);

	DEBUG("Thing Name %s", myThingName);
	DEBUG("MQTT Client ID %s", mqttClientID);

	ConnectParams.keepAliveIntervalInSec = 60;
	ConnectParams.MQTTVersion = MQTT_3_1_1;
	ConnectParams.isCleanSession = true;
	ConnectParams.isWillMsgPresent = false;
	ConnectParams.pClientID = pParams->pMqttClientId;
	ConnectParams.pPassword = NULL;
	ConnectParams.pUsername = NULL;

	rc = aws_iot_mqtt_connect(pClient, &ConnectParams);

	if(SUCCESS == rc) {
		initializeRecords(pClient);
	}

	return rc;
}

IoT_Error_t aws_iot_shadow_register_delta(AWS_IoT_Client *pMqttClient, jsonStruct_t *pStruct) {
	if(NULL == pMqttClient || NULL == pStruct) {
		return NULL_VALUE_ERROR;
	}

	if(!aws_iot_mqtt_is_client_connected(pMqttClient)) {
		return MQTT_CONNECTION_ERROR;
	}

	return registerJsonTokenOnDelta(pStruct);
}

IoT_Error_t aws_iot_shadow_yield(AWS_IoT_Client *pClient, uint32_t timeout) {
	HandleExpiredResponseCallbacks();
	return aws_iot_mqtt_yield(pClient, timeout);
}

IoT_Error_t aws_iot_shadow_disconnect(AWS_IoT_Client *pClient) {return aws_iot_mqtt_disconnect(pClient);
}

IoT_Error_t aws_iot_shadow_update(AWS_IoT_Client *pClient, const char *pThingName, char *pJsonString,
									fpActionCallback_t callback, void *pContextData, uint8_t timeout_seconds,
								  	bool isPersistentSubscribe) {
	if(NULL == pClient) {
		return NULL_VALUE_ERROR;
	}

	if(!aws_iot_mqtt_is_client_connected(pClient)) {
		return MQTT_CONNECTION_ERROR;
	}

	return iot_shadow_action(pThingName, SHADOW_UPDATE, pJsonString, callback, pContextData,
			timeout_seconds, isPersistentSubscribe);
}

IoT_Error_t aws_iot_shadow_delete(AWS_IoT_Client *pClient, const char *pThingName, fpActionCallback_t callback,
									void *pContextData, uint8_t timeout_seconds, bool isPersistentSubscribe) {
	if(NULL == pClient) {
		return NULL_VALUE_ERROR;
	}

	if (!aws_iot_mqtt_is_client_connected(pClient)) {
		return MQTT_CONNECTION_ERROR;
	}

	char deleteRequestJsonBuf[MAX_SIZE_CLIENT_TOKEN_CLIENT_SEQUENCE];
	iot_shadow_delete_request_json(deleteRequestJsonBuf);
	return iot_shadow_action(pThingName, SHADOW_DELETE, deleteRequestJsonBuf, callback, pContextData,
			timeout_seconds, isPersistentSubscribe);
}

IoT_Error_t aws_iot_shadow_get(AWS_IoT_Client *pClient, const char *pThingName, fpActionCallback_t callback,
								void *pContextData, uint8_t timeout_seconds, bool isPersistentSubscribe) {
	if(NULL == pClient) {
		return NULL_VALUE_ERROR;
	}

	if (!aws_iot_mqtt_is_client_connected(pClient)) {
		return MQTT_CONNECTION_ERROR;
	}

	char getRequestJsonBuf[MAX_SIZE_CLIENT_TOKEN_CLIENT_SEQUENCE];

	iot_shadow_get_request_json(getRequestJsonBuf);

	return iot_shadow_action(pThingName, SHADOW_GET, getRequestJsonBuf, callback, pContextData,
			timeout_seconds, isPersistentSubscribe);
}

IoT_Error_t aws_iot_shadow_set_autoreconnect_status(AWS_IoT_Client *pClient, bool newStatus) {
	return aws_iot_mqtt_autoreconnect_set_status(pClient, newStatus);
}


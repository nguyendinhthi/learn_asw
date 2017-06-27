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

/**
* @file subscribe_publish_sample.c
* @brief simple MQTT publish and subscribe on the same topic
*
* This example takes the parameters from the aws_iot_config.h file and establishes a connection to the AWS IoT MQTT Platform.
* It subscribes and publishes to the same topic - "sdkTest/sub"
*
* If all the certs are correct, you should see the messages received by the application in a loop.
*
* The application takes in the certificate path, host name , port and the number of times the publish should happen.
*
*/

/*******************************************************************************
* @file    sub_pub_nucleo.c
* @author  Central LAB
* @version V2.0.0
* @date    22-June-2016
* @brief   simple MQTT publish and subscribe implementation for sample on Nucleo.
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of STMicroelectronics nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************
*/


//#include "stdio.h"
//#include "stdlib.h"
#include "ctype.h"
#include "string.h"
//#include <unistd.h>

//#include <signal.h>
//#include <memory.h>
//#include <sys/time.h>
//#include <limits.h>
#include "timer_interface.h"

#include "aws_iot_log.h"
#include "aws_iot_version.h"
#include "aws_iot_mqtt_client_interface.h"
#include "aws_iot_config.h"
#include "sub_pub_nucleo.h"
#include "sensors_data.h"

#define PATH_MAX 800

extern char rootCA[];
extern char clientCRT[];
extern char clientKey[];
extern volatile uint32_t BpushButtonState;

char *optarg;
int optind, opterr, optopt;


/**
* @brief MQTT subscriber callback hander
*
* called when data is received from AWS IoT Thing (message broker)
* @param MQTTCallbackParams type parameter
* @return no return
*/
//void MQTTcallbackHandler(AWS_IoT_Client *pClient, char *topicName, uint16_t topicNameLen,
//IoT_Publish_Message_Params *params, void *pData) {
//    INFO("\r\nSubscribe MQTT Packet......\r\n");
//    INFO("%.*s:\t%.*s\r\n", topicNameLen, topicName, (int)params->payloadLen, params->payload);
//}

void MQTTcallbackHandler(AWS_IoT_Client *pClient, char *topicName, uint16_t topicNameLen,
IoT_Publish_Message_Params *params, void *pData) {
    INFO("\r\nSubscribe MQTT Packet......\r\n");
    INFO("%.*s\r\n", (int)params->payloadLen, params->payload);
}

/**
* @brief MQTT disconnect callback hander
*
* @param no parameter
* @return no return
*/

void disconnectCallbackHandler(AWS_IoT_Client *pClient, void *data) {
    WARN("MQTT Disconnect\r\n");
    IoT_Error_t rc = FAILURE;
    if(NULL == data) {
        return;
    }

    AWS_IoT_Client *client = (AWS_IoT_Client *)data;
    if(aws_iot_is_autoreconnect_enabled(client)){
        INFO("Auto Reconnect is enabled, Reconnecting attempt will start now\r\n");
    }else{
        WARN("Auto Reconnect not enabled. Starting manual reconnect...\r\n");
        rc = aws_iot_mqtt_attempt_reconnect(client);
        if(NETWORK_RECONNECTED == rc){
            WARN("Manual Reconnect Successful\r\n");
        }else{
            WARN("Manual Reconnect Failed - %d\r\n", rc);
        }
    }
}



//int getopt(int argc, char** argv, const char *optstring) {return 0;}
//char* getcwd( char* buffer, size_t size ) {return 0;}


/**
* @brief Default cert location
*/
//char certDirectory[PATH_MAX + 1] = "../../certs";

/**
* @brief Default MQTT HOST URL is pulled from the aws_iot_config.h
*/
char HostAddress[255] = AWS_IOT_MQTT_HOST;

/**
* @brief Default MQTT port is pulled from the aws_iot_config.h
*/
uint32_t port = AWS_IOT_MQTT_PORT;

/**
* @brief This parameter will avoid infinite loop of publish and exit the program after certain number of publishes
*/
uint32_t publishCount = 0;

//char CurrentWD[PATH_MAX + 1];
char cafileName[] = AWS_IOT_ROOT_CA_FILENAME;
char clientCRTName[] = AWS_IOT_CERTIFICATE_FILENAME;
char clientKeyName[] = AWS_IOT_PRIVATE_KEY_FILENAME;


/**
* @brief main entry function to AWS IoT code
*
* @param no parameter
* @return IoT_Error_t status return
*/

int aws_main(void) {
    IoT_Error_t rc = FAILURE;
    int32_t i = 0;
    bool infinitePublishFlag = true;

    AWS_IoT_Client client;

    INFO("\nAWS IoT SDK Version %d.%d.%d-%s\r\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_TAG);


    //	getcwd(CurrentWD, sizeof(CurrentWD));
    //	sprintf(rootCA, "%s/%s/%s", CurrentWD, certDirectory, cafileName);
    //	sprintf(clientCRT, "%s/%s/%s", CurrentWD, certDirectory, clientCRTName);
    //	sprintf(clientKey, "%s/%s/%s", CurrentWD, certDirectory, clientKeyName);



    //	DEBUG("rootCA %s", rootCA);
    //	DEBUG("clientCRT %s", clientCRT);
    //	DEBUG("clientKey %s", clientKey);

    IoT_Client_Init_Params mqttInitParams;
    mqttInitParams.enableAutoReconnect = false; // enabled later below
    mqttInitParams.pHostURL =  HostAddress;
    mqttInitParams.port = port;
    mqttInitParams.pRootCALocation = rootCA;
    mqttInitParams.pDeviceCertLocation = clientCRT;
    mqttInitParams.pDevicePrivateKeyLocation = clientKey;
    mqttInitParams.mqttCommandTimeout_ms = NUCLEO_mqttCommandTimeout_ms;  //STM Modified this value
    mqttInitParams.tlsHandshakeTimeout_ms = NUCLEO_tlsHandshakeTimeout_ms;//STM Modified this value
    mqttInitParams.isSSLHostnameVerify = true;
    mqttInitParams.disconnectHandler = disconnectCallbackHandler;
    mqttInitParams.disconnectHandlerData = (void *)&client;	
    
    rc = aws_iot_mqtt_init(&client, &mqttInitParams);
    if(SUCCESS != rc) {
        ERROR("aws_iot_mqtt_init returned error : %d\r\n", rc);
        return rc;
    }
    
    IoT_Client_Connect_Params connectParams = iotClientConnectParamsDefault;
    connectParams.keepAliveIntervalInSec = NUCLEO_keepAliveIntervalInSec; //10;
    //< MQTT clean session.  True = this session is to be treated as clean.  
    //  Previous server state is cleared and no stated is retained from this connection.>
    connectParams.isCleanSession = true;						
    connectParams.MQTTVersion = MQTT_3_1_1;
    connectParams.pClientID = AWS_IOT_MQTT_CLIENT_ID;
    connectParams.isWillMsgPresent = false;

    INFO("Connecting...\r\n");
    rc = aws_iot_mqtt_connect(&client, &connectParams);
    if(SUCCESS != rc) {
        ERROR("Error(%d) connecting to %s:%d\r\n", rc, mqttInitParams.pHostURL, mqttInitParams.port);
        return rc;
    }
    else
    {
        DEBUG("aws_iot_mqtt_connect: connected to %s:%d", mqttInitParams.pHostURL, mqttInitParams.port);
    }
    
    /*
    * Enable Auto Reconnect functionality. Minimum and Maximum time of Exponential backoff are set in aws_iot_config.h
    *  #AWS_IOT_MQTT_MIN_RECONNECT_WAIT_INTERVAL
    *  #AWS_IOT_MQTT_MAX_RECONNECT_WAIT_INTERVAL
    */
    rc = aws_iot_mqtt_autoreconnect_set_status(&client, true);
    if(SUCCESS != rc) {
        ERROR("Unable to set Auto Reconnect to true - %d\r\n", rc);
        return rc;
    }

    
    INFO("Subscribing...\r\n");
    rc = aws_iot_mqtt_subscribe(&client, "stm/noida/tp1", 11, QOS0, MQTTcallbackHandler, NULL);
    if(SUCCESS != rc) {
        ERROR("Error subscribing : %d\r\n", rc);
        return rc;
    }
    
    char cPayload[AWS_IOT_MQTT_TX_BUF_LEN];
    sprintf(cPayload, "%s : %d ", "hello from STM", i);
    
    IoT_Publish_Message_Params paramsQOS0;
    paramsQOS0.qos = QOS0;
    paramsQOS0.payload = (void *) cPayload;

    IoT_Publish_Message_Params paramsQOS1;
    paramsQOS1.qos = QOS1;
    paramsQOS1.payload = (void *) cPayload;
    


    if(publishCount != 0){
        infinitePublishFlag = false;
    }

    while((NETWORK_ATTEMPTING_RECONNECT == rc || NETWORK_RECONNECTED == rc || SUCCESS == rc)
    && (publishCount > 0 || infinitePublishFlag)) {
        
        //Max time the yield function will wait for read messages
        rc = aws_iot_mqtt_yield(&client, NUCLEO_YIELD_MAX_WAIT_MSEC_READ); //100
        if(NETWORK_ATTEMPTING_RECONNECT == rc){		
            INFO("-->sleep\r\n");
            fsleep(NUCLEO_YIELD_SLEEP_MSEC);
            // If the client is attempting to reconnect we will skip the rest of the loop.
            continue;
        }
        INFO("-->sleep\r\n");
        fsleep(NUCLEO_YIELD_SLEEP_MSEC);

        
        if(BpushButtonState)
        {
            INFO("\r\nPublish MQTT Packet......\r\n");
            
            BpushButtonState = 0;
            PrepareMqttPayload(cPayload, sizeof(cPayload));
            
            
            
            paramsQOS1.payloadLen = strlen(cPayload) + 1;
            
            
            do {
                rc = aws_iot_mqtt_publish(&client, "stm/noida/tp1", 11, &paramsQOS1);
                if (publishCount > 0) {
                    publishCount--;
                }
            } while(MQTT_REQUEST_TIMEOUT_ERROR == rc && (publishCount > 0 || infinitePublishFlag));
            
        }
        else
        {
            INFO(".......Push User Button to Publish Sensors Data...\r\n");
        }
    }//End of while

    //Reach here only if reconnect fails which is an error or we hit publishing limit which is OK case. 
    if(SUCCESS != rc){
        ERROR("An error occurred in the loop.\r\n");
    }
    else{
        INFO("Publish done\r\n");
    }

    DeInitTimer(&(client.pingTimer));           // STM	
    DeInitTimer(&(client.reconnectDelayTimer)); // STM	
    
    return rc;
}




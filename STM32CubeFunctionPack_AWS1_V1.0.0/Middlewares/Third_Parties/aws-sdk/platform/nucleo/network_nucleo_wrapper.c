
#include "network_interface.h"
#include "timer_interface.h"
#include "wifi_module.h"
#include "aws_iot_log.h"
#include "aws_iot_config.h"
#include "app_wifi_read.h"


#if   defined ( __CC_ARM )
#define __nop() __nop()
#elif defined ( __GNUC__ )
#define __nop() asm("nop")
#elif defined ( __ICCARM__ )
#define __nop() __no_operation()
#endif


extern void (*p_ind_wifi_socket_data_received)(uint8_t * data_ptr, uint32_t message_size, uint32_t chunck_size);
extern void (*p_ind_wifi_socket_client_remote_server_closed)(uint8_t * socket_closed_id);

void data_ind_wifi_socket_data_received(uint8_t * data_ptr, uint32_t message_size, uint32_t chunck_size);
void data_ind_wifi_socket_client_remote_server_closed(uint8_t * socket_closed_id);

extern int32_t last_ticks;


int32_t  AwsConnected = 0; 
int8_t my_socket = -1;	


/**
* @brief Initialize the TLS implementation
*
* Perform any initialization required by the TLS layer.
* Connects the interface to implementation by setting up
* the network layer function pointers to platform implementations.
*
* @param pNetwork - Pointer to a Network struct defining the network interface.
* @return integer defining successful initialization or TLS error
*/
IoT_Error_t iot_tls_init(Network *pNetwork, char *pRootCALocation, char *pDeviceCertLocation,
char *pDevicePrivateKeyLocation, char *pDestinationURL,
uint16_t DestinationPort, uint32_t timeout_ms, bool ServerVerificationFlag)
{

    pNetwork->connect = iot_tls_connect;
    pNetwork->read = iot_tls_read;
    pNetwork->write = iot_tls_write;
    pNetwork->disconnect = iot_tls_disconnect;
    pNetwork->isConnected = iot_tls_is_connected;
    pNetwork->destroy = iot_tls_destroy;
    
    pNetwork->tlsConnectParams.DestinationPort = DestinationPort;
    pNetwork->tlsConnectParams.pDestinationURL = pDestinationURL;
    pNetwork->tlsConnectParams.pDeviceCertLocation = pDeviceCertLocation;
    pNetwork->tlsConnectParams.pDevicePrivateKeyLocation = pDevicePrivateKeyLocation;
    pNetwork->tlsConnectParams.pRootCALocation = pRootCALocation;
    pNetwork->tlsConnectParams.ServerVerificationFlag = ServerVerificationFlag;
    pNetwork->tlsConnectParams.timeout_ms = timeout_ms;
    
    
    p_ind_wifi_socket_data_received = data_ind_wifi_socket_data_received;
    p_ind_wifi_socket_client_remote_server_closed = data_ind_wifi_socket_client_remote_server_closed;
    
    
    return SUCCESS;
}

/**
* @brief Create a TLS socket and open the connection
*
* Creates an open socket connection including TLS handshake.
*
* @param pNetwork - Pointer to a Network struct defining the network interface.
* @param TLSParams - TLSConnectParams defines the properties of the TLS connection.
* @return integer - successful connection or TLS error
*/
IoT_Error_t iot_tls_connect(Network *pNetwork, TLSConnectParams *TLSParams)
{
    uint32_t retrycount = 5;	

    
    if ( wifi_socket_client_security(
                (uint8_t *)"m", //o->one-way Auth, m-> mutual Auth
                (uint8_t *)pNetwork->tlsConnectParams.pRootCALocation,
                (uint8_t *)pNetwork->tlsConnectParams.pDeviceCertLocation,
                (uint8_t *)pNetwork->tlsConnectParams.pDevicePrivateKeyLocation,
                (uint8_t *)pNetwork->tlsConnectParams.pDestinationURL,  //"SERVER"
                last_ticks
                ) != WiFi_MODULE_SUCCESS)
    {
        ERROR("wifi_socket_client_security FAIL\r\n");
        return NETWORK_SSL_CERT_ERROR;
    }
    

    label_client_open:	
    if ( wifi_socket_client_open(
                (uint8_t *)pNetwork->tlsConnectParams.pDestinationURL,				//hostname
                pNetwork->tlsConnectParams.DestinationPort,				//port_number
                "s", 															//protocol 
                (uint8_t *)&my_socket 	//sock_id
                ) != WiFi_MODULE_SUCCESS)
    {
        ERROR("wifi_socket_client_open FAIL\r\n");
        retrycount --;
        if(retrycount) goto label_client_open;
        
        return SSL_CONNECTION_ERROR;
    }
    INFO("wifi_socket_client_open PASS\r\n");
    
    AwsConnected = 1;

    return SUCCESS;

}

/**
* @brief Write bytes to the network socket
*
* @param Network - Pointer to a Network struct defining the network interface.
* @param unsigned char pointer - buffer to write to socket
* @param integer - number of bytes to write
* @param integer - write timeout value in milliseconds
* @return integer - number of bytes written or TLS error
*/
IoT_Error_t iot_tls_write(Network* pNetwork, unsigned char* writebuffer, size_t bytestowrite, Timer * timeout, size_t * byteswritten)

{
    WiFi_Status_t status = WiFi_MODULE_SUCCESS;
    

    
    if ( (status = wifi_socket_client_write(my_socket, bytestowrite, (char *)writebuffer)) == WiFi_MODULE_SUCCESS)
    {
        
        *byteswritten = bytestowrite;

        return SUCCESS;
    }
    else
    {
        ERROR("+iot_tls_write failed");
        return FAILURE;
    }
}

/**
* @brief Read bytes from the network socket
*
* @param Network - Pointer to a Network struct defining the network interface.
* @param unsigned char pointer - pointer to buffer where read bytes should be copied
* @param integer - number of bytes to read
* @param integer - read timeout value in milliseconds
* @return integer - number of bytes read or TLS error
*/

IoT_Error_t iot_tls_read(Network* pNetwork, unsigned char* readbuffer,  size_t bytestoread, Timer * timeout, size_t * bytesread)
{
    uint32_t i = 0;
    
    int timeout_ms = 1000; //bug
    
    uint32_t tickstart = 0;
    tickstart = HAL_GetTick();


    while(i < bytestoread )
    {
        if(DequeueRx(&readbuffer[i]))
        {
            i++;
        }
        
        __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
        if((HAL_GetTick() - tickstart) > timeout_ms)
        {
            break;
        }
        
    }
    
    *bytesread = i;

    
    if(i)
    {
        return SUCCESS;
    }
    else
    { // when timed out and no data return this
        return NETWORK_SSL_NOTHING_TO_READ;
    }
    
}


/**
* @brief Disconnect from network socket
*
* @param Network - Pointer to a Network struct defining the network interface.
*/
IoT_Error_t iot_tls_disconnect(Network *pNetwork)
{
    wifi_socket_client_close(my_socket);
    return SUCCESS;
}

/**
* @brief Perform any tear-down or cleanup of TLS layer
*
* Called to cleanup any resources required for the TLS layer.
*
* @param Network - Pointer to a Network struct defining the network interface.
* @return integer - successful cleanup or TLS error
*/
IoT_Error_t iot_tls_destroy(Network *pNetwork)
{
    my_socket = -1;
    pNetwork->read = NULL;
    pNetwork->write = NULL;
    pNetwork->disconnect = NULL;
   
    return SUCCESS;
}


/**
* @brief Check if TLS layer is still connected
*
* Called to check if the TLS layer is still connected or not.
*
* @param Network - Pointer to a Network struct defining the network interface.
* @return int - integer indicating status of network physical layer connection
*/
IoT_Error_t iot_tls_is_connected(Network *pNetwork)
{
    if (AwsConnected)
    {
        return SUCCESS;
    }
    else
    {
        return FAILURE; 
    }
}	

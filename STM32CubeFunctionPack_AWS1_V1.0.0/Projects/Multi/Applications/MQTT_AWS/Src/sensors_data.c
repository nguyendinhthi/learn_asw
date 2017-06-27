/**
******************************************************************************
* @file    sensors_data.c
* @author  Central LAB
* @version V2.0.0
* @date    22-June-2016
* @brief   This file provides One routine to read all Sensor Data and 
*          One routine to initialize all sensors.
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
*
* Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
* You may not use this file except in compliance with the License.
* You may obtain a copy of the License at:
*
*        http://www.st.com/software_license_agreement_liberty_v2
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


#include "stdint.h"
#include "stdio.h"


/* IKS x-cube related section    ---------------------------------------------------*/
#ifdef __IKS01A1
#include "x_nucleo_iks01a1.h"
#include "x_nucleo_iks01a1_accelero.h"
#include "x_nucleo_iks01a1_gyro.h"
#include "x_nucleo_iks01a1_magneto.h"
#include "x_nucleo_iks01a1_humidity.h"
#include "x_nucleo_iks01a1_temperature.h"
#include "x_nucleo_iks01a1_pressure.h"
#else
#include "x_nucleo_iks01a2.h"
#include "x_nucleo_iks01a2_accelero.h"
#include "x_nucleo_iks01a2_gyro.h"
#include "x_nucleo_iks01a2_magneto.h"
#include "x_nucleo_iks01a2_humidity.h"
#include "x_nucleo_iks01a2_temperature.h"
#include "x_nucleo_iks01a2_pressure.h"
#endif

/* define sensors depending on whether we are using X-NUCLEO-IKS01A1 or X-NUCLEO-IKS01A2 */
#ifdef __IKS01A1
#define ACCELERO_SENSORS_AUTO (LSM6DS3_X_0)
#define LSM_SENSORS_AUTO (LSM6DS0_X_0)
#else
#define ACCELERO_SENSORS_AUTO (LSM303AGR_X_0)
#define LSM_SENSORS_AUTO (LSM6DSL_X_0)
#endif


typedef enum  { 
  MODULE_SUCCESS                 = 1,
  MODULE_ERROR                   = -1,
  MODULE_NO_USER_PARAMS_ON_FLASH = -2,
  MODULE_NO_USER_PARAMS_ON_NFC   = -3,
  MODULE_NFC_NOT_PRESENT         = -4,
  MODULE_NFC_NOT_USED            = -5,
  MODULE_NFC_IN_USE              = 100,  
} System_Status_t;

float TEMPERATURE_Value;
float HUMIDITY_Value;
float PRESSURE_Value;
SensorAxes_t ACC_Value;
SensorAxes_t GYR_Value;
SensorAxes_t MAG_Value;

void *ACCELERO_handle    = NULL;
void *GYRO_handle        = NULL;
void *MAGNETO_handle     = NULL;
void *HUMIDITY_handle    = NULL;
void *TEMPERATURE_handle = NULL;
void *PRESSURE_handle    = NULL;


int PrepareMqttPayload(char * PayloadBuffer, int PayloadSize)
{
  char * Buff = PayloadBuffer;
  int BuffSize = PayloadSize;
  
    int snprintfreturn = 0;
    if(BSP_TEMPERATURE_Get_Temp(TEMPERATURE_handle,(float *)&TEMPERATURE_Value) != COMPONENT_OK)
    {
        printf("Temperature reading error\r\n");
    }

    if(BSP_HUMIDITY_Get_Hum(HUMIDITY_handle,(float *)&HUMIDITY_Value) != COMPONENT_OK)
    {
        printf("Humidity reading error\r\n");
    }

    if(BSP_PRESSURE_Get_Press(PRESSURE_handle,(float *)&PRESSURE_Value) != COMPONENT_OK)
    {
        printf("Pressure reading error\r\n");
    }
    BSP_ACCELERO_Get_Axes(ACCELERO_handle,&ACC_Value);
    BSP_GYRO_Get_Axes(GYRO_handle,&GYR_Value);
    BSP_MAGNETO_Get_Axes(MAGNETO_handle,&MAG_Value);

    snprintfreturn = snprintf(Buff, BuffSize, "%-11s%.2s% 05.2f\r\n","Temperature",": ", TEMPERATURE_Value);
    Buff += snprintfreturn; BuffSize -=snprintfreturn;
    snprintfreturn = snprintf(Buff, BuffSize, "%-11s%.2s% 05.2f\r\n","Humidity"   ,": ", HUMIDITY_Value);
    Buff += snprintfreturn; BuffSize -=snprintfreturn;
    snprintfreturn = snprintf(Buff, BuffSize, "%-11s%.2s% 05.2f\r\n","Pressure"   ,": ", PRESSURE_Value);
    Buff += snprintfreturn; BuffSize -=snprintfreturn;
    
    
    snprintfreturn = snprintf(Buff, BuffSize,"%-11s%.2s%4d\t","ACC-X",": ",ACC_Value.AXIS_X);
    Buff += snprintfreturn; BuffSize -=snprintfreturn;
    snprintfreturn = snprintf(Buff, BuffSize, "%-5s%.2s%4d\t"  ,"ACC-Y",": ",ACC_Value.AXIS_Y);
    Buff += snprintfreturn; BuffSize -=snprintfreturn;
    snprintfreturn = snprintf(Buff, BuffSize,"%-5s%.2s%4d\r\n","ACC-Z",": ",ACC_Value.AXIS_Z);
    Buff += snprintfreturn; BuffSize -=snprintfreturn;
    
    snprintfreturn = snprintf(Buff, BuffSize, "%-11s%.2s%4d\t","GYR-X",": ",GYR_Value.AXIS_X);
    Buff += snprintfreturn; BuffSize -=snprintfreturn;
    snprintfreturn = snprintf(Buff, BuffSize, "%-5s%.2s%4d\t"  ,"GYR-Y",": ",GYR_Value.AXIS_Y);
    Buff += snprintfreturn; BuffSize -=snprintfreturn;
    snprintfreturn = snprintf(Buff, BuffSize, "%-5s%.2s%4d\r\n","GYR-Z",": ",GYR_Value.AXIS_Z);
    Buff += snprintfreturn; BuffSize -=snprintfreturn;

    snprintfreturn = snprintf(Buff, BuffSize, "%-11s%.2s%4d\t","MAG-X",": ",MAG_Value.AXIS_X);
    Buff += snprintfreturn; BuffSize -=snprintfreturn;
    snprintfreturn = snprintf(Buff, BuffSize, "%-5s%.2s%4d\t"  ,"MAG-Y",": ",MAG_Value.AXIS_Y);
    Buff += snprintfreturn; BuffSize -=snprintfreturn;
    snprintfreturn = snprintf(Buff, BuffSize, "%-5s%.2s%4d\r\n","MAG-Z",": ",MAG_Value.AXIS_Z);
    
    printf("%s",PayloadBuffer);
    
    if (snprintfreturn >= 0 && snprintfreturn < PayloadSize)
    {
        return 0;
    }
    else if(snprintfreturn >= PayloadSize)
    {
        printf("Data Pack truncated\r\n");			
        return 0;
    }
    else
    {
        printf("Data Pack Error\r\n");			
        return 1;
    }
    
}


int InitSensors(void)
{
   System_Status_t status = MODULE_ERROR;
 
   /* Try to use LSM6DS3 DIL24 if present */
   if(BSP_ACCELERO_Init( ACCELERO_SENSORS_AUTO, &ACCELERO_handle)!=COMPONENT_OK){        
   /* otherwise try to use LSM6DS on board */
     if(BSP_ACCELERO_Init(LSM_SENSORS_AUTO, &ACCELERO_handle)!=COMPONENT_OK){
       return status;
     }
   }

   /* Try to use LSM6DS3 if present, otherwise use LSM6DS0 */
   if(BSP_GYRO_Init( GYRO_SENSORS_AUTO, &GYRO_handle )!=COMPONENT_OK){
     return status;
   }

#ifdef __IKS01A1
   if(BSP_MAGNETO_Init( LIS3MDL_0, &MAGNETO_handle )!=COMPONENT_OK){
     return status;
   }
#else
   /* Force to use LIS3MDL */
   if(BSP_MAGNETO_Init( LSM303AGR_M_0, &MAGNETO_handle )!=COMPONENT_OK){
     return status;
   }
#endif      

   /* Force to use HTS221 */
   if(BSP_HUMIDITY_Init( HTS221_H_0, &HUMIDITY_handle )!=COMPONENT_OK){
     return status;
   }

   /* Force to use HTS221 */
   if(BSP_TEMPERATURE_Init( HTS221_T_0, &TEMPERATURE_handle )!=COMPONENT_OK){
     return status;
   }

   /* Try to use LPS25HB DIL24 if present, otherwise use LPS25HB on board */
   if(BSP_PRESSURE_Init( PRESSURE_SENSORS_AUTO, &PRESSURE_handle )!=COMPONENT_OK){
     return status;
   }
      
   /*  Enable all the sensors */
   BSP_ACCELERO_Sensor_Enable( ACCELERO_handle );
   BSP_GYRO_Sensor_Enable( GYRO_handle );
   BSP_MAGNETO_Sensor_Enable( MAGNETO_handle );
   BSP_HUMIDITY_Sensor_Enable( HUMIDITY_handle );
   BSP_TEMPERATURE_Sensor_Enable( TEMPERATURE_handle );
   BSP_PRESSURE_Sensor_Enable( PRESSURE_handle );

   status = MODULE_SUCCESS;
   return status;      

}

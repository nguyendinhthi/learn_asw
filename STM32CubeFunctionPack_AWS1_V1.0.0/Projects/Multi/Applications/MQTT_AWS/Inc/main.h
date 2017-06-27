/* ----------------------------------------------------------------------
******************************************************************************
* @file    main.h
* @author  Central LAB
* @version V2.0.0
* @date    22-June-2016
* @brief   Header for main.c module
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
 * -------------------------------------------------------------------- */

/**
   \mainpage STM32 Cube Function Pack for AWs IoT Solution
   *
   * Introduction
   * ------------
   *
   * FP-CLD-AWS1 is an STM32 ODE function pack. Thanks to this package you can directly connect your
   * IoT node to the Amazon AWS IoT platform, transmit and receive sensor data and commands to and 
   * from AWS services. This package can jump-start any end-to-end IoT development, saving your time in 
   * the integration of the different basic functions needed for a sensor-to-cloud development environment.
   * 
   * This software package implements application level functions based on the MQTT protocol and enables 
   * communication with the Amazon AWS IoT platform. Developers can use it to prototype end-to-end IoT 
   * applications together with Amazon AWS cloud services, to easily transmit and receive real time sensor data.   
   *
   *
   * Using the Package
   * -----------------
   * Before using the STM32CubeFunctionPack_AWS1_V1.0.0 package, it is necessary
   * to set up the Thing Configuration in Amazon AWS IoT Console and update the source code in this package.
   * The package needs the Device Certificate, Private Key, Thing Name, Cleint ID and MQTT Host value. 
   * Without these additions the package will NOT build.
   *
   * How to set up the Thing Configuration in Amazon AWS IoT Console and update the source code 
   * are described the Quick Start Guide that can be downloaded by clicking on the QSG.htm file 
   * present in the Documentation folder. 
   *
   * It is recommended to read the Quick Start Guide before using this package.
   *
   *
   * Examples
   * --------
   *
   * The Packge ships with a basic example called "Subscribe and Publish Sample"
   * This Example demonstrate how to Send Data to AWS cloud and how to get back the data from cloud.
   *
   *
   * Building the Package
   * --------------------
   *
   * The Package contains a project files to build Project.
   * On MDK-ARM Tool chain the project file is in <code>STM32CubeFunctionPack_AWS1_V1.0.0\\Projects\\Multi\\Applications\\MQTT_AWS\\MDK-ARM\\STM32F401RE-Nucleo</code> folder.
   * - Project.uvprojx
   * On IAR Embedded Workbench Tool chain the project file is in <code>STM32CubeFunctionPack_AWS1_V1.0.0\\Projects\\Multi\\Applications\\MQTT_AWS\\EWARM\\STM32F401RE-Nucleo</code> folder.
   * - Project.eww
   * On System Workbench Tool chain the project file is in <code>STM32CubeFunctionPack_AWS1_V1.0.0\\Projects\\Multi\\Applications\\MQTT_AWS\\SW4STM32\\STM32F401RE_Nucleo\\STM32F4xx-Nucleo-MQTT_AWS</code> folder.
   * - .project
   *
   * Pre-processor Macros
   * --------------------
   *
   * Each Package project have differant pre-processor macros.
   *
   * - USART_PRINT_MSG
   * Define macro USART_PRINT_MSG, If you want to receive print messages on UART
   *
   * - IOT_INFO
   * Define macro IOT_INFO, If you want to receive print messages on UART from AWS IoT part of module of generic Information type
   * - IOT_ERROR
   * Define macro IOT_ERROR, If you want to receive print messages on UART from AWS IoT part of module of Error type
   * - IOT_WARN
   * Define macro IOT_WARN, If you want to receive print messages on UART from AWS IoT part of module of Warning type
   * - IOT_DEBUG
   * Define macro IOT_DEBUG, If you want to receive print messages on UART from AWS IoT part of module of Extended Information type
   * - IOT_TRACE
   * Define macro IOT_TRACE, If you want to receive print messages on UART from AWS IoT part of module of all Trace type
   *
   *
   * <hr>
   * STM32 Cube Function Pack for AWs IoT 
   * -----------------------------
   * 
   * The following files relevant to Package are present in the <b>STM32CubeFP_AWS_V2.0.0</b> Pack directories:
   * |File/Folder                   |Content                                                                 |
   * |------------------------------|------------------------------------------------------------------------|
   * |\b Documentation              | This documentation                                                     |
   * |\b Drivers                    | BSP Drivers                                                            |
   * |\b Middlewares                | WIFI, FreeRTOS and AWS IOT source code                                 |
   * |\b Projects                   | Source files for rebuilding the Package                                |
   * 
   * <hr>
   * Revision History of STM32 Cube Function Pack for AWs IoT
   * ------------
   * Version 1.0.0 
   *
   * Copyright Notice
   * ------------
   *
   * COPYRIGHT(c) 2015 STMicroelectronics.
   */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/

#include <stdio.h>

#ifdef USE_STM32L0XX_NUCLEO
#include "stm32l0xx_hal.h"
#include "stm32l0xx_nucleo.h"
#include "stm32l0xx_hal_rcc.h"
#include "stm32l0xx_hal_rcc_ex.h"
#endif
#ifdef USE_STM32F1xx_NUCLEO
#include "stm32f1xx_hal.h"
#include "stm32f1xx_nucleo.h"
#include "stm32f1xx_hal_rcc.h"
#endif
#ifdef USE_STM32F4XX_NUCLEO
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_rcc_ex.h"
#endif  



#include "wifi_interface.h"
#include "wifi_main.h"
#include "user_button.h"
#include "sensors_data.h"
#include "freertos_main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define USART_PRINT_MSG_BAUDRATE 460800
/* Exported functions ------------------------------------------------------- */


#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

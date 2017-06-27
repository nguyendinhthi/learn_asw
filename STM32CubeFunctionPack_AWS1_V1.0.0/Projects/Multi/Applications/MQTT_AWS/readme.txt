/**
  @page AWS IoT Cloud Application
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    readme.txt  
  * @version V1.0.0
  * @date    15-03-2017
  * @brief   This application contains an example showing how to connect a Nucleo 
based microsystem to Amazon Cloud 

  ******************************************************************************
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
  @endverbatim

@par Example Description 

STM32CubeFunctionPack_AWS1 provides a software running on STM32 which offers a complete middleware to build applications based on 
WiFi connectivity (SPW01SA) and to connect STM32 Nucleo boards with Amazon AWS Cloud based services. The software leverages 
functionalities provided by the following expansion boards:
   -X-NUCLEO-IKS01A1 featuring temperature, humidity, pressure and motion MEMS sensors
   -X-NUCLEO-IKS01A2 featuring temperature, humidity, pressure and motion MEMS sensors
   -X-NUCLEO-IDW01M1 a Wi-Fi evaluation board based on the SPWF01SA module

FP-CLD-STM32CubeFunctionPack_AWS1 is an expansion software package for STM32Cube. The software runs on the STM32 micro-controller and 
includes drivers that recognize WiFi module (SPWF01SA), and sensor devices (HTS221, LPS25HB, LSM6DS0, LIS3MDL, LSM6DSL and LSM303AGR). 
It also includes a middleware package implementing the MQTT protocol for easy interaction of 
STM32 Nucleo based microsystem with Amazon AWS Cloud services. The expansion software is built on STM32Cube software technology 
to ease portability across different STM32 microcontrollers. The software comes with examples for registering the 
device and sending sensors data to the Amazon AWS Cloud service.
  
@par Hardware and Software environment

HW setup for running the application is composed by the following boards:
	- STM32F401RE-Nucleo RevC 
	- X-NUCLEO-IDW01M1
	- X-NUCLEO-IKS01A1
	- X-NUCLEO-IKS01A2
The Wi-Fi expansion board X-NUCLEO-IDW01M1 can be connected to the STM32 Nucleo motherboard through the Morpho extension connector.
The sensors board X-NUCLEO-IKS01A1 or X-NUCLEO-IKS01A2 can be easily connected to X-NUCLEO-IDW01M1 expansion board through the Arduino UNO R3 
extension connector.

MQTT_AWS application works with default subscribe_publish_sample application. In its default configuration, the application publishes all
sensor data to AWS Cloud and subscribes back those data. The published and subscribed data can be visualized through a Hyper Terminal running
on a PC connected to Nucleo baord through the USB emulated UART interface.
User can switch between the X-NUCLEO-IKS01A1 or X-NUCLEO-IKS01A2 by switching the project settings of the Build Toolset selected. 
For more details on how to use registered mode please refer to User Manual.
    
The first step of using the Package is to Complete the  AWS Management Console Setup as described in User Manual. 
After completing the AWS Setup update the Source Code with Device Certificate, Private Key and AWS Configuration Data as described in User Manual.
It is very Critical to follow the Steps described in User Manual genrate the Device Certificate, Private Key for your Thing.
 - WARNING: This package will NOT work with Default AWS Create Device Certificate process.
 You have to follow "View other options" and use a CSR to Create Device Certificate process.
 - WARNING: This package will NOT work with Default AWS Created RSA-2048 Key.
 This package will ONLY work with ECC-256 Key.

	
@par How to use it? 

This package contains projects for 3 IDEs IAR, µVision and System Workbench. 

In order to make the  program work, you must do the following:
 - WARNING: before opening the project with any toolchain be sure your folder
   installation path is not too in-depth since the toolchain may report errors
   after building.
   
For IAR:
 - Open IAR toolchain (this firmware has been successfully tested with
   Embedded Workbench V7.70).
 - Open one of the IAR project file EWARM\STM32F401RE-Nucleo\Project.eww
 - Update the Source Code with Device Certificate, Private Key and AWS Configuration Data as described in User Manual
 - Rebuild all files and load your image into target memory.
 - Connect a Hyper Terminal running on PC to Nucleo Device connected to the PC
 - Run the example.

For µVision:
 - Open µVision V5.10.0.2 toolchain (this firmware has been 
   successfully tested with MDK-ARM Professional Version: 5.10.0.2).
 - Open one of the µVision project files MDK-ARM\STM32F401RE-Nucleo\Project.uvprojx
 - Update the Source Code with Device Certificate, Private Key and AWS Configuration Data as described in User Manual
 - Rebuild all files and load your image into target memory.
 - Connect a Hyper Terminal running on PC to Nucleo Device connected to the PC
 - Run the example.
 
For System Workbench:
 - Open System Workbench for STM32 (this firmware has been successfully tested with System Workbench for STM32 Version 1.8.0). 
 - Set the default workspace proposed by the IDE (please be sure that there are not spaces in the workspace path).
 - Press "File" -> "Import" -> "Existing Projects into Workspace"; press "Browse" in the "Select root directory" and choose the path where the System
   Workbench project is located (it should be SW4STM32\STM32F401RE-Nucleo). 
 - Update the Source Code with Device Certificate, Private Key and AWS Configuration Data as described in User Manual
 - Rebuild all files and load your image into target memory.
 - Connect a Hyper Terminal running on PC to Nucleo Device connected to the PC
 - Run the example.

Once run the application, follow the instructions visible on serial interface to configure access to WiFi network and to visualize data on the
Serial Interface.


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */





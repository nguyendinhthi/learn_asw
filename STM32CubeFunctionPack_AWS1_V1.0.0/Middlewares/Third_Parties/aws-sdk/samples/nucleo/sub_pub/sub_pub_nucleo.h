/**
******************************************************************************
* @file    sub_pub_nucleo.h
* @author  Central LAB
* @version V2.0.0
* @date    22-June-2016
* @brief   Header file for sub_pub_nucleo.c
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


#ifndef _NUCLEO_SUBSCRIBE_PUBLISH_SAMPLE_H_
#define _NUCLEO_SUBSCRIBE_PUBLISH_SAMPLE_H_

#include "aws_iot_error.h"


#define NUCLEO_mqttCommandTimeout_ms 	15000 //2000 //STM Modified this value
#define NUCLEO_tlsHandshakeTimeout_ms 15000 //2000 //STM Modified this value
#define NUCLEO_keepAliveIntervalInSec 30 		//10 //STM Modified this value
#define NUCLEO_YIELD_MAX_WAIT_MSEC_READ			2000
#define NUCLEO_YIELD_SLEEP_MSEC							1000

int aws_main(void);	
int create_global_timers( void );
#endif

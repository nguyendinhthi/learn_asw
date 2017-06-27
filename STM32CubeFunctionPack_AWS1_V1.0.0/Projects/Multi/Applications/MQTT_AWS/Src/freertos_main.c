/**
******************************************************************************
* @file    freertos_main.c
* @author  Central LAB
* @version V2.0.0
* @date    22-June-2016
* @brief   Freertos Main program body.
*          Provides FreeRTOS entry routine and Thread Routines
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

/* Includes ------------------------------------------------------------------*/
#include "cmsis_os.h"
#include "sub_pub_nucleo.h"
#include "stm32f4xx_nucleo.h" 


/* USER CODE BEGIN Includes */


/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/


TaskHandle_t xIotTaskHandle = NULL;


/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void AwsIotTask(void * pvParameters);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
* @brief FreeRTOS entry function.
* @param None
* @return 0 (Zero) on Success and 1(One) on Error
*/


int freertos_main(void)
{

    /* USER CODE BEGIN 1 */
    /* USER CODE END 1 */


    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* Create the thread(s) */
    /* definition and creation of defaultTask */
    
    
    if (pdPASS != xTaskCreate( AwsIotTask, "AwsIoT Task", (configMINIMAL_STACK_SIZE * 10), NULL, configTIMER_TASK_PRIORITY - 2, &xIotTaskHandle ))
    {
        return 1;
    }

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */
    /* Start scheduler */
    osKernelStart();

    return 0;

}

/* USER CODE BEGIN 4 */


/**
* @brief FreeRTOS task entry function for AWS IoT task.
*
*  Task entry function. Tasks must be implemented to never return (i.e. continuous loop).
*
* @param pvParameters - Void pointer to parameter being passed to the task being created
* @return - no return values
*/



void AwsIotTask(void * pvParameters)
{

    while (create_global_timers()) //If there is error in Creating Timers try again
    {
        BSP_LED_On(LED2);
    }

    while(aws_main()) //If there is error in Connecting to AWS try again
    {
        BSP_LED_On(LED2);
        osDelay(10000); //Delay 10 Sec
    }
    
    while (1)
    {
    }
}

/* USER CODE END 4 */



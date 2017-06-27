#include "timer_interface.h"
#include "cmsis_os.h"
#include <stdio.h>


//Create Global Timers

#define MAX_NUM_TIMERS 10

typedef struct st_TimerHandle{
    
    TimerHandle_t xTimer;
    uint32_t TimeToExpire;
    uint32_t Allocated;
    
}st_TimerHandle_t, *pst_TimerHandle_t;

/* An array to hold handles to the created timers. */
st_TimerHandle_t stTimers[MAX_NUM_TIMERS]; 
static int32_t AllocatedTimerIndex = -1;

void vTimerCallback( TimerHandle_t pxTimer )
{
}



/* ...    Create before creating tasks     ... */
int create_global_timers( void )
{
    uint32_t x;

    /* Create some timers.  Don't start them. Starting the timers before the RTOS
    scheduler has been started means the timers will start running
    immediately that the RTOS scheduler starts. Starting will be done inside code */

    for( x = 0; x < MAX_NUM_TIMERS; x++ )
    {
        stTimers[x].xTimer = xTimerCreate
        (  /* Just a text name, not used by the RTOS kernel. */
        "Timer",
        /* The timer period in ticks, must be greater than 0 */
        2000,
        /* The timers will auto-reload themselves when they expire. */
        pdFALSE,
        /* Assign each timer a unique id equal to its array index. */
        ( void * ) x,
        /* Each timer calls the same callback when it expires. */
        vTimerCallback
        );

        if( stTimers[x].xTimer == NULL )
        {
            /* The timer was not created. */
            return 1; //Failure
        }
    }
    return 0; //Success
}


/**
 * @brief Initialize a timer
 *
 * Performs any initialization required to the timer passed in.
 *
 * @param Timer - pointer to the timer to be initialized
 */


void init_timer(Timer* timer)
{
    uint32_t i = 0;
    AllocatedTimerIndex++;

    
    for(i=0; i < MAX_NUM_TIMERS; i++)
    {
        if(!stTimers[i].Allocated)
        {
            stTimers[i].Allocated = 1;
            *timer = &stTimers[i];
            goto exit;
        }
    }

exit:	
    ;
}

void DeInitTimer(Timer* timer)
{

    AllocatedTimerIndex--;
    xTimerStop( ((pst_TimerHandle_t)*timer)->xTimer, 0 );
    ((pst_TimerHandle_t)*timer)->TimeToExpire = 0;
    ((pst_TimerHandle_t)*timer)->Allocated = 0;
}








/**
* @brief Check if a timer is expired
*
* Call this function passing in a timer to check if that timer has expired.
*
* @param Timer - pointer to the timer to be checked for expiration
* @return bool - true = timer expired, false = timer not expired
*/
bool has_timer_expired(Timer* timer)
{

    if( xTimerIsTimerActive(((pst_TimerHandle_t)*timer)->xTimer) != pdFALSE )// active means not expired
    {
        return pdFALSE; //0 = timer not expired
    }
    else
    {
        ((pst_TimerHandle_t)*timer)->TimeToExpire = 0;

        return !pdFALSE;//1 = timer expired
    }
}

/**
* @brief Create a timer (milliseconds)
*
* Sets the timer to expire in a specified number of milliseconds.
*
* @param Timer - pointer to the timer to be set to expire in milliseconds
* @param unsigned int - set the timer to expire in this number of milliseconds
*/
void countdown_ms(Timer* timer, unsigned int time_ms)
{

    if( xTimerChangePeriod( ((pst_TimerHandle_t)*timer)->xTimer, time_ms / portTICK_PERIOD_MS, 0 ) == pdPASS )
    {
        ((pst_TimerHandle_t)*timer)->TimeToExpire = xTaskGetTickCount();;
    }
    else
    {
    }
    
}

/**
* @brief Create a timer (seconds)
*
* Sets the timer to expire in a specified number of seconds.
*
* @param Timer - pointer to the timer to be set to expire in seconds
* @param unsigned int - set the timer to expire in this number of seconds
*/
void countdown_sec(Timer* timer, unsigned int time_s)
{
    countdown_ms(timer, time_s * 1000);
}

/**
* @brief Check the time remaining on a give timer
*
* Checks the input timer and returns the number of milliseconds remaining on the timer.
*
* @param Timer - pointer to the timer to be set to checked
* @return int - milliseconds left on the countdown timer
*/
uint32_t left_ms(Timer* timer)
{
    unsigned int time_s = 0; 
    if( xTimerIsTimerActive(((pst_TimerHandle_t)*timer)->xTimer ) != pdFALSE )
    {
        //Active
        time_s = xTimerLeftMs(((pst_TimerHandle_t)*timer)->xTimer);
        time_s = time_s - ((xTaskGetTickCount()) - ((pst_TimerHandle_t)*timer)->TimeToExpire);
    }
    else
    {
        //Not active
        time_s = 0;
    }
    
    return time_s;
}

/**
* @brief   Wait for Timeout (Time Delay)
* @param   millisec      time delay value
* @retval  status code that indicates the execution status of the function.
*/

void fsleep(int parm) 
{
    
#if INCLUDE_vTaskDelay
    TickType_t ticks = parm / portTICK_PERIOD_MS;

    vTaskDelay(ticks ? ticks : 1);          /* Minimum delay = 1 tick */

#else
    (void) parm;

#endif
    
}

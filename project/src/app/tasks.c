/* Free RTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "../middleware/middleware.h" // @todo Remove!
#include "../drivers/dio.h"
#include "../drivers/pwm.h"
#include "Emios_Mcl_Ip.h"

uint32_t tasks_pwm_counter;

/* Dimensions of the buffer that the task being created will use as its stack.
NOTE:  This is the number of words the stack will hold, not the number of
bytes.  For example, if each stack item is 32-bits, and this is set to 100,
then 400 bytes (100 * 32-bits) will be allocated. */
#define STACK_SIZE 2000

/* Structure that will hold the TCB of the task being created. */
StaticTask_t xTaskBuffer;

/* Buffer that the task being created will use as its stack.  Note this is
an array of StackType_t variables.  The size of StackType_t is dependent on
the RTOS port. */
StackType_t xStack[STACK_SIZE];

/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
 * implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
 * used by the Idle task. */
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    uint32_t * pulIdleTaskStackSize )
{
    /* If the buffers to be provided to the Idle task are declared inside this
     * function then they must be declared static - otherwise they will be allocated on
     * the stack and so not exists after this function exits. */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[ /*configMINIMAL_STACK_SIZE*/ STACK_SIZE ];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle
     * task's state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
     * Note that, as the array is necessarily of type StackType_t,
     * configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = STACK_SIZE; /*configMINIMAL_STACK_SIZE;*/
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook(void) {
	for (int i = 0; 1; ++i) {
		if (middleware_step() < 0) return -2;
	}
}

static void _busy_delay(int us) {
	for (int i = 0; i < (us * 80); ++i) {
		__asm("nop");
	}
}

static int cycle = 0;

/* Function that implements the task being created. */
void vTaskCode( void * pvParameters )
{
	/* The parameter value is expected to be 1 as 1 is passed in the
	pvParameters value in the call to xTaskCreateStatic(). */
	configASSERT( ( uint32_t ) pvParameters == 1UL );

	 TickType_t xLastWakeTime;
	 const TickType_t xFrequency = 2;

     // Initialise the xLastWakeTime variable with the current time.
     xLastWakeTime = xTaskGetTickCount();

	for( ;; )
	{
        //taskENTER_CRITICAL();

        if (cycle == 0) Emios_Mcl_Ip_Init(0, &Emios_Mcl_Ip_0_Config_BOARD_INITPERIPHERALS);
        ++cycle;

        tasks_pwm_counter = IP_EMIOS_0->CH.UC[23].CNT;

        // Perform action here.
        dio_write(&dio_out_44, 1);
        _busy_delay(30);
        dio_write(&dio_out_44, 0);

        //taskEXIT_CRITICAL();

        // Wait for the next cycle.
        xTaskDelayUntil( &xLastWakeTime, xFrequency );
	}
}

void tasks_init(void) {
    TaskHandle_t xHandle = NULL;

    /* Create the task without using any dynamic memory allocation. */
    xHandle = xTaskCreateStatic(
                  vTaskCode,       /* Function that implements the task. */
                  "NAME",          /* Text name for the task. */
                  STACK_SIZE,      /* Number of indexes in the xStack array. */
                  ( void * ) 1,    /* Parameter passed into the task. */
                  tskIDLE_PRIORITY + 1,/* Priority at which the task is created. */
                  xStack,          /* Array to use as the task's stack. */
                  &xTaskBuffer );  /* Variable to hold the task's data structure. */
}

void tasks_start(void) {
	vTaskStartScheduler();
}

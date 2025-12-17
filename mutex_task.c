#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "mutex_task.h"

static SemaphoreHandle_t xMutex;
static int sharedCounter = 0;

static void vMutexTask1(void *pvParameters)
{
    for (;;)
    {
        xSemaphoreTake(xMutex, portMAX_DELAY);
        printf("Task 1 entered critical section\n");
        sharedCounter++;
        printf("Task 1 counter = %d\n", sharedCounter);
        vTaskDelay(pdMS_TO_TICKS(200));
        printf("Task 1 leaving critical section\n");
        xSemaphoreGive(xMutex);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

static void vMutexTask2(void *pvParameters)
{
    for (;;)
    {
        xSemaphoreTake(xMutex, portMAX_DELAY);
        printf("Task 2 entered critical section\n");
        sharedCounter++;
        printf("Task 2 counter = %d\n", sharedCounter);
        vTaskDelay(pdMS_TO_TICKS(200));
        printf("Task 2 leaving critical section\n");
        xSemaphoreGive(xMutex);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void createMutexDemoTasks(void)
{
    xMutex = xSemaphoreCreateMutex();
    configASSERT(xMutex != NULL);

    xTaskCreate(
        vMutexTask1,
        "MutexT1",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 2,
        NULL
    );

    xTaskCreate(
        vMutexTask2,
        "MutexT2",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 1,
        NULL
    );
}


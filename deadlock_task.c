#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "deadlock_task.h"

static SemaphoreHandle_t xMutexA;
static SemaphoreHandle_t xMutexB;

static void vDeadlockTask1(void *pvParameters)
{
    for (;;)
    {
        printf("Task 1 trying to lock Mutex A\n");
        xSemaphoreTake(xMutexA, portMAX_DELAY);
        printf("Task 1 locked Mutex A\n");

        vTaskDelay(pdMS_TO_TICKS(500)); // force overlap

        printf("Task 1 trying to lock Mutex B\n");
        xSemaphoreTake(xMutexB, portMAX_DELAY);
        printf("Task 1 locked Mutex B\n");

        /* Never reached in deadlock */
        xSemaphoreGive(xMutexB);
        xSemaphoreGive(xMutexA);
    }
}

static void vDeadlockTask2(void *pvParameters)
{
    for (;;)
    {
        printf("Task 2 trying to lock Mutex B\n");
        xSemaphoreTake(xMutexB, portMAX_DELAY);
        printf("Task 2 locked Mutex B\n");

        vTaskDelay(pdMS_TO_TICKS(500)); // force overlap

        printf("Task 2 trying to lock Mutex A\n");
        xSemaphoreTake(xMutexA, portMAX_DELAY);
        printf("Task 2 locked Mutex A\n");

        /* Never reached in deadlock */
        xSemaphoreGive(xMutexA);
        xSemaphoreGive(xMutexB);
    }
}

void createDeadlockDemoTasks(void)
{
    xMutexA = xSemaphoreCreateMutex();
    xMutexB = xSemaphoreCreateMutex();

    configASSERT(xMutexA);
    configASSERT(xMutexB);

    xTaskCreate(
        vDeadlockTask1,
        "DeadlockT1",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 2,
        NULL
    );

    xTaskCreate(
        vDeadlockTask2,
        "DeadlockT2",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 2,
        NULL
    );
}


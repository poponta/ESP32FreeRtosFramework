//
//  Copyright (c) 2021 Hirotaka Yuno <create.future.technology@gmail.com>.  All right reserved.
//

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "EspFreeRtos.h"

void EspFreeRtos::CreateTask(TaskFunction pvTaskCode,
                             const char *pcName,
                             uint32_t usStackDepth,
                             void *pvParameters,
                             uint32_t uxPriority,
                             TaskHandle *pvCreatedTask,
                             int32_t xCoreID) {
  xTaskCreatePinnedToCore(pvTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pvCreatedTask, xCoreID);
}

void EspFreeRtos::DelayTask(uint32_t time_ms) {
  vTaskDelay(time_ms);
}

void EspFreeRtos::DelayTaskUntil(uint32_t last_wake_time_ms, uint32_t interval_ms) {
  TickType_t tmp = last_wake_time_ms;
  vTaskDelayUntil(&tmp, interval_ms);
}

void EspFreeRtos::SuspendTask(TaskHandle xTaskToSuspend) {
  vTaskSuspend(xTaskToSuspend);
}

uint32_t EspFreeRtos::GetTickCount() {
  return xTaskGetTickCount();
}
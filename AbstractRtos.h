//
//  Copyright (c) 2021 Hirotaka Yuno <create.future.technology@gmail.com>.  All right reserved.
//

#ifndef ABSTRACT_RTOS_H_
#define ABSTRACT_RTOS_H_ 

#include <stdint.h>

using TaskFunction = void (*)(void *arg);
using TaskHandle = void*;

class AbstractRtos {
 public:
  AbstractRtos() = default;
  virtual ~AbstractRtos() = default;
  virtual void CreateTask(TaskFunction pvTaskCode,
                          const char *pcName,
                          uint32_t usStackDepth,
                          void *pvParameters,
                          uint32_t uxPriority,
                          TaskHandle *pvCreatedTask,
                          int32_t xCoreID) = 0;
  virtual void DelayTask(uint32_t time_ms) = 0;
  virtual void DelayTaskUntil(uint32_t last_wake_time_ms, uint32_t interval_ms) = 0;
  virtual void SuspendTask(TaskHandle xTaskToSuspend) = 0;
  virtual uint32_t GetTickCount() = 0;
};
#endif
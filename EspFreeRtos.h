//
//  Copyright (c) 2021 Hirotaka Yuno <create.future.technology@gmail.com>.  All right reserved.
//

#ifndef ESP_FREE RTOS_H_
#define ESP_FREE RTOS_H_

#include "AbstractRtos.h"

class EspFreeRtos : public AbstractRtos {
 public:
  EspFreeRtos() = default;
  virtual ~EspFreeRtos() = default;
  virtual void CreateTask(TaskFunction pvTaskCode,
                          const char *pcName,
                          uint32_t usStackDepth,
                          void *pvParameters,
                          uint32_t uxPriority,
                          TaskHandle *pvCreatedTask,
                          int32_t xCoreID) final;
  virtual void DelayTask(uint32_t time_ms) final;
  virtual void DelayTaskUntil(uint32_t last_wake_time_ms, uint32_t interval_ms) final;
  virtual uint32_t GetTickCount() final;
};
#endif
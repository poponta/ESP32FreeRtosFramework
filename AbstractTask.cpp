//
//  Copyright (c) 2021 Hirotaka Yuno <create.future.technology@gmail.com>.  All right reserved.
//

#include <limits>
#include <Arduino.h>
#include "AbstractTask.h"
#include "AbstractRtos.h"
#include "RtosFactory.h"

AbstractTask::TaskContainer AbstractTask::task_container_;

AbstractTask::AbstractTask(char *name, uint32_t cycle, uint16_t stack, uint32_t priority, CpuCore core) :
  cycle_(cycle),
  stack_(stack),
  priority_(priority),
  core_(core)
{
  memset(name_, 0, sizeof(name_));
  strncpy(name_, name, (sizeof(name_) - 1));
  task_container_.PushBack(this);
  // Select RTOS
  rtos_ = RtosFactory::Create(RtosFactory::RtosKind::EspFreeRtos);
}

void AbstractTask::Start() {
  rtos_->CreateTask(RepriseWrapper, name_, stack_, this, priority_, &handle_, static_cast<int32_t>(core_));
}

void AbstractTask::Reprise() {
  constexpr auto timer_limit = std::numeric_limits<decltype(rtos_->GetTickCount())>::max();

  while(1) {
    uint32_t start_time = rtos_->GetTickCount();

    // Cycle processing
    PreMain();
    Main();
    PostMain();

    // Transition to Blocked State
    rtos_->DelayTaskUntil(start_time, cycle_);
  }
}

void AbstractTask::Stop() {
  
}

AbstractTask::TaskContainer& AbstractTask::GetTaskContainer() {
  return task_container_;
}

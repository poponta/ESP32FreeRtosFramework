#include <limits>
#include <Arduino.h>
#include "AbstractTask.h"
#include "AbstractRtos.h"
#include "RtosFactory.h"

AbstractTask::TaskContainer AbstractTask::task_container_;

AbstractTask::AbstractTask(char *name, uint32_t cycle, uint16_t stack, uint32_t priority, CpuCore core, bool is_cyclic) :
  cycle_(cycle),
  stack_(stack),
  priority_(priority),
  core_(core),
  is_suspend_req_(false)
{
  memset(name_, 0, sizeof(name_));
  strncpy(name_, name, (sizeof(name_) - 1));
  if (is_cyclic == true) {
    task_container_.PushBack(this);
  }
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

    if(is_suspend_req_ == true) {
      Suspend();
    }

    // Cycle processing
    Loop();

    // Transition to Blocked State
    rtos_->DelayTaskUntil(start_time, cycle_);
  }
}

void AbstractTask::Suspend() {
  rtos_->SuspendTask(handle_);
}

void AbstractTask::Resume() {
  rtos_->ResumeTask(handle_);
  is_suspend_req_ = false;
}

void AbstractTask::SuspendRequest() {
  is_suspend_req_ = true;
}

AbstractTask::TaskContainer& AbstractTask::GetTaskContainer() {
  return task_container_;
}

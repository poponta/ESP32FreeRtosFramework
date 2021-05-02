//
//  Copyright (c) 2021 Hirotaka Yuno <create.future.technology@gmail.com>.  All right reserved.
//

#ifndef ABSTRACT_TASK_H_
#define ABSTRACT_TASK_H_

#include <string.h>
#include "AbstractRtos.h"
#include "ArrayContainer.h"

enum class CpuCore {
  kSystemCore = 0,
  kAppCore = 1
};
  
class AbstractTask {
 public:
  static const uint32_t kMaxCyclicTaskNum = 16;
  using TaskContainer = ArrayContainer<AbstractTask*, kMaxCyclicTaskNum, std::true_type>;

  AbstractTask(char *name, uint32_t cycle, uint16_t stack, uint32_t priority, CpuCore core);
  virtual ~AbstractTask() = default;
  AbstractTask (const AbstractTask &obj) = delete;
  AbstractTask& operator=(const AbstractTask &obj) = delete;

  void Start();
  void Reprise();
  virtual void Initialize() = 0;
  virtual void PreMain() = 0;
  virtual void Main() = 0;
  virtual void PostMain() = 0;
  virtual void Finalize() = 0;
  void Stop();

  // For C language Interface (ex. FreeRTOS API)
  static void RepriseWrapper(void* _this) {
    static_cast<AbstractTask*>(_this)->Reprise();
  }

  // For Observer pattern
  static TaskContainer& GetTaskContainer();
  
 protected:
  static const uint32_t kTaskNameMaxSize = 256;
  static TaskContainer task_container_;  // For Observer pattern
  char name_[kTaskNameMaxSize];
  uint32_t cycle_;
  uint16_t stack_;
  /*UBaseType_t */ uint32_t priority_;
  /*TaskHandle_t*/ void *handle_;
  CpuCore core_;
  AbstractRtos *rtos_;
};
#endif

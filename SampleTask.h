//
//  Copyright (c) 2021 Hirotaka Yuno <create.future.technology@gmail.com>.  All right reserved.
//

#ifndef SAMPLE_TASK_
#define SAMPLE_TASK_

#include "AbstractTask.h"

class SampleTask : public AbstractTask {
 public:
  SampleTask(char *name, uint32_t cycle, uint16_t stack, uint32_t priority, CpuCore core);
  virtual ~SampleTask() = default;
  SampleTask (const SampleTask &obj) = delete;
  SampleTask& operator=(const SampleTask &obj) = delete;

  virtual void Initialize() final;
  virtual void PreMain() final;
  virtual void Main() final;
  virtual void PostMain() final;
  virtual void Finalize() final;
};
#endif

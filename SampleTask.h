#ifndef SAMPLE_TASK_
#define SAMPLE_TASK_

#include "AbstractTask.h"

class SampleTask : public AbstractTask {
 public:
  SampleTask(char *name, uint32_t cycle, uint16_t stack, uint32_t priority, CpuCore core);
  virtual ~SampleTask() = default;
  SampleTask (const SampleTask &obj) = delete;
  SampleTask& operator=(const SampleTask &obj) = delete;

  virtual void Setup() final;
  virtual void Loop() final;
};
#endif  // SAMPLE_TASK_

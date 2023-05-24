#include <Arduino.h>
#include "AbstractTask.h"
#include "LoopMain.h"
#include "SampleTask.h"

// Instantiate Concrete task here
// AbstractTask(char *name, uint32_t cycle_ms, uint16_t stack_byte, uint32_t priority, CpuCore core);
SampleTask sample_task1("sample1", 3000, 4096, 5, CpuCore::kSystemCore);
SampleTask sample_task2("sample2", 3000, 4096, 5, CpuCore::kAppCore);

void LoopMain::Init() {
  auto &tasks = AbstractTask::GetTaskContainer();
  uint32_t task_num = tasks.Size();
  int i = 0;

  Serial.begin(115200);
  Serial.println("# System Start");
  log_i("num of tasks : %d", task_num);

  for (auto &e : tasks) {
    e->Setup();
    e->Start();
    i++;

    if (i >= task_num) {
      break;
    }
  }
}

void LoopMain::Loop() {

}

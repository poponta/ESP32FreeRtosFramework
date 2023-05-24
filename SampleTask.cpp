#include <Arduino.h>
#include "RtosUtility.h"
#include "SampleTask.h"

SampleTask::SampleTask(char *name, uint32_t cycle, uint16_t stack, uint32_t priority, CpuCore core) :
  AbstractTask(name, cycle, stack, priority, core) {
}

void SampleTask::Setup() {
  // タスク起動時に1度だけコールされます

}

void SampleTask::Loop() {
  // 周期的にコールされます
  auto tm = millis();
  log_i("test : %d", tm);
  RtosUtility::ScopedCriticalSection lock;
}


#include <Arduino.h>
#include "SampleTask.h"

SampleTask::SampleTask(char *name, uint32_t cycle, uint16_t stack, uint32_t priority, CpuCore core) :
  AbstractTask(name, cycle, stack, priority, core) {
}

void SampleTask::Setup() {

}

void SampleTask::Loop() {
  auto tm = millis();
  log_i("test : %d", tm);
}


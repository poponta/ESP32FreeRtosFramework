//
//  Copyright (c) 2021 Hirotaka Yuno <create.future.technology@gmail.com>.  All right reserved.
//

#include <Arduino.h>
#include "SampleTask.h"

SampleTask::SampleTask(char *name, uint32_t cycle, uint16_t stack, uint32_t priority, CpuCore core) :
  AbstractTask(name, cycle, stack, priority, core) {
}

void SampleTask::Initialize() {
}

void SampleTask::PreMain() {
  
}

void SampleTask::Main() {
  auto tm = millis();
  log_i("test : %d", tm);
}

void SampleTask::PostMain() {

}

void SampleTask::Finalize() {

}

#include <Arduino.h>
#include "AbstractTask.h"
#include "LoopMain.h"
#include "SampleTask.h"
#include "BatteryMonitorTask.h"
// #include "BoxTask.h"
#include "BoxControlTask.h"
#include "DeviceScanTask.h"

// Instantiate Concrete task here
// AbstractTask(char *name, uint32_t cycle_ms, uint16_t stack_byte, uint32_t priority, CpuCore core);
//BoxTask box_task("box", 100, 8192, 5, CpuCore::kSystemCore);
BatteryMonitorTask battery_monitor_task("batmontsk", 100, 8192, 5, CpuCore::kSystemCore);
BoxControlTask box_control_task("boxctrltsk", 100, 8192, 5, CpuCore::kSystemCore);
DeviceScanTask device_scan_task("devicescantsk", 200, 8192, 5, CpuCore::kSystemCore);

SampleTask sample_task1("sample1", 1000, 4096, 1, CpuCore::kAppCore);

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

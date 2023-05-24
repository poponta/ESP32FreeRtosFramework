#include "AbstractTask.h"
#include "RtosFactory.h"
#include "RtosUtility.h"

bool RtosUtility::DelayTask(uint32_t time_ms) {
  auto rtos = RtosFactory::Get();
  if (rtos) {
      rtos->DelayTask(time_ms);
      return true;
  }
  return false;
}

void RtosUtility::EnterCriticalSection() {
  auto rtos = RtosFactory::Get();
  if (rtos) {
    rtos->EnterCriticalSection();
  }
}

void RtosUtility::LeaveCriticalSection() {
  auto rtos = RtosFactory::Get();
  if (rtos) {
    rtos->LeaveCriticalSection();
  }
}

RtosUtility::ScopedCriticalSection::ScopedCriticalSection() {
  EnterCriticalSection();
};

RtosUtility::ScopedCriticalSection::~ScopedCriticalSection() {
  LeaveCriticalSection();
};
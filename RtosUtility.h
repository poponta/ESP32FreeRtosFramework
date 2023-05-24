#ifndef RTOS_UTILITY_H 
#define RTOS_UTILITY_H 

namespace RtosUtility{
  bool DelayTask(uint32_t time_ms);
  void EnterCriticalSection();
  void LeaveCriticalSection();
  class ScopedCriticalSection {
   public:
    ScopedCriticalSection();
    virtual ~ScopedCriticalSection();
  };
}
#endif
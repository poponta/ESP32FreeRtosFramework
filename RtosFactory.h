#ifndef RTOS_FACTORY_H 
#define RTOS_FACTORY_H 

class AbstractRtos;
namespace RtosFactory{
  enum class RtosKind {
    EspFreeRtos,
  };
  AbstractRtos* Create(RtosKind rtos);
  AbstractRtos* Get();
};

#endif
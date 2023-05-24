#include "EspFreeRtos.h"
#include "RtosFactory.h"

namespace {
  AbstractRtos *instance = nullptr;
}

AbstractRtos* RtosFactory::Create(RtosKind rtos) {
  switch (rtos) {
    case RtosFactory::RtosKind::EspFreeRtos:
      {
        static EspFreeRtos esp_free_rtos;
        instance =  &esp_free_rtos;
      }
      break;

    default:
      break;
  }
  return instance;
}

AbstractRtos* RtosFactory::Get() {
  return instance;
}
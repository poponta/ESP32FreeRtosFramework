//
//  Copyright (c) 2021 Hirotaka Yuno <create.future.technology@gmail.com>.  All right reserved.
//

#include "EspFreeRtos.h"
#include "RtosFactory.h"

AbstractRtos* RtosFactory::Create(RtosKind rtos) {
  AbstractRtos *ret = nullptr;

  switch (rtos) {
    case RtosFactory::RtosKind::EspFreeRtos :
      {
        static EspFreeRtos esp_free_rtos;
        ret =  &esp_free_rtos;
      }
      break;

    default :
      break;
  }
  return ret;
}
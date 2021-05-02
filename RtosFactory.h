//
//  Copyright (c) 2021 Hirotaka Yuno <create.future.technology@gmail.com>.  All right reserved.
//

#ifndef RTOS_FACTORY_H 
#define RTOS_FACTORY_H 

#include "AbstractRtos.h"

namespace RtosFactory{
  enum class RtosKind {
    EspFreeRtos,
  };
  AbstractRtos* Create(RtosKind rtos);
};

#endif
//
//  Copyright (c) 2021 Hirotaka Yuno <create.future.technology@gmail.com>.  All right reserved.
//

#include "LoopMain.h"

static LoopMain loop_main;

void setup() {
  // put your setup code here, to run once:
  loop_main.Init();
}

void loop() {
  // put your main code here, to run repeatedly:
  loop_main.Loop();
}

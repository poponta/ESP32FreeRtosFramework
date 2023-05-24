#ifndef LOOP_MAIN_H_
#define LOOP_MAIN_H_

class LoopMain {
 public:
  LoopMain() = default;
  virtual ~LoopMain() = default;
  LoopMain(const LoopMain&) = delete;
  LoopMain& operator=(const LoopMain&) = delete;

  void Init();
  void Loop();
};
#endif

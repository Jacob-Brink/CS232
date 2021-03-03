#include "prompt.h"

class Shell {
 public:
  Shell();
  void run();
 private:
  Prompt prompt;
};

#include "prompt.h"
#include "commandline.h"

class Shell {
 public:
  Shell();
  void run();
 private:
  void handleCommand(CommandLine commandLine);
  Prompt prompt;
};

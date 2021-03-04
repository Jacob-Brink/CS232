#include "command.h"
#include <vector>

class SysCommand: public Command {
 public:
  SysCommand(CommandLine &commandLine);
 protected:
  bool isValidCount(int count);
  void run(char** args);
};

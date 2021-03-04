#include "command.h"

class PwdCommand: public Command {
 public:
  PwdCommand(CommandLine &commandLine);
 protected:
  void run(char** args);
};

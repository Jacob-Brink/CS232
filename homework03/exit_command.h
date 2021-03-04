#include "command.h"

class ExitCommand: public Command {
 public:
  ExitCommand(CommandLine &commandLine);
 protected:
  void run(char** args);
};

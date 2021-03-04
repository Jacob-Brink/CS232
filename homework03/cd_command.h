#include "command.h"

class CdCommand: public Command {
 public:
  CdCommand(CommandLine &commandLine);
 protected:
  void run(char** args);
  bool isValidParam(char** args);
};

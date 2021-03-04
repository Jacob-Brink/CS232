#include "command.h"

class ExitCommand: public Command {
 public:
  ExitCommand(vector<string> args, bool blocking);
 protected:
  void run(vector<string> args);
};

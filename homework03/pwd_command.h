#include "command.h"

class PwdCommand: public Command {
 public:
  PwdCommand(vector<string> args, bool blocking);
 protected:
  void run(vector<string> args);
};

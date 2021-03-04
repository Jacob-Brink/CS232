#include "command.h"

class CdCommand: public Command {
 public:
  CdCommand(vector<string> args, bool blocking);
 protected:
  void run(vector<string> args);
  bool isValidParam(vector<string> args);
};
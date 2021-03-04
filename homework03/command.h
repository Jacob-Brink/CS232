#include "commandline.h"
#include <vector>

#ifndef COMMAND_H
#define COMMAND_H

class Command {
 public:
  Command() {};
  Command(vector<int> argCount, vector<string> args, bool blocking);
  void execute();
 protected:
  virtual void run(vector<string> args) {
  cout << "Command::run() not implemented" << endl;
  };

  virtual bool isValidParam(vector<string> args);
 private:
  bool isValidCount();
  bool isValid();
  vector<int> argCount;
  vector<string> args;
  bool blocking;
};

#endif

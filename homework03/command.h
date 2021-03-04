#include "commandline.h"
#include <vector>

#ifndef COMMAND_H
#define COMMAND_H

class Command {
 public:
  Command() {};
  Command(vector<int> argCount, bool builtin, CommandLine &commandLine);
  void execute();
 protected:
  virtual void run(char** args) = 0;
  virtual bool isValidParam(char** args);
  virtual bool isValidCount(int count);
 private:
  bool isValid();
  bool builtin;
  
  vector<int> requiredArgCount;
  vector<string> args;
  int argCount;
  char** c_args;
  bool blocking;
};

#endif

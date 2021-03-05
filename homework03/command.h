/* command.h
*
* @instructor: Professor Norman
*
* @Date: 03/04/2021
* @assignment: homework03
* @student: Jacob Brink
*
* Description:
* declaration of Command class, which contains common parameter checking, blocking and nonblocking execution of commands, and etc
*/

#include <unistd.h>
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
  virtual string validParamError();
  virtual string paramCountError();
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

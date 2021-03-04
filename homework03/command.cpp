/* command.cpp
*
* @instructor: Professor Norman
*
* @Date: 03/04/2021
* @assignment: homework03
* @student: Jacob Brink
*
* Description:
* definitions of Command class; provides both blocking and nonblocking execution of code along with parameter validation functions
*/


#include <iostream>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include "command.h"
#include "commandline.h"

using namespace std;

Command::Command(vector<int> argCountParam, bool builtinParam, CommandLine &commandLine) {
  requiredArgCount = argCountParam;
  builtin = builtinParam;
  
  argCount = commandLine.getArgCount();
  blocking = commandLine.noAmpersand();
  c_args = commandLine.getArgVector();
  
  vector<string> temp(commandLine.getArgVector(), commandLine.getArgVector()+commandLine.getArgCount());
  args = temp;
};

bool Command::isValidCount(int count) {
  int realArgCount = count - 1;
  for (int i : requiredArgCount) {
    if (realArgCount == i) {
      return true;
    }
  }
  return false;
};

bool Command::isValidParam(char** args) {
  return true; //should be overriden
};

bool Command::isValid() {
  if (!this->isValidCount(argCount)) {
    cout << "Given wrong number of parameters" << endl;
    return false;
  } else if (!this->isValidParam(c_args)) {
    cout << "Parameters are of incorrect type" << endl;
    return false;
  }
  return true;
}

void Command::execute() {
  if (!this->isValid()) {
    cout << "Please try again!" << endl;
    return;
  }

  if (builtin) {
    // for builtin commands such as exit or cd, we want to run them on the main thread
    this->run(c_args);
    
  } else {
  
    pid_t pid = fork();

    if (pid == 0) {
      this->run(c_args);
      exit(0); //exit out of thread
    } else if (pid > 0) {
    
      if (blocking) {
	int status;
	waitpid(pid, &status, 0);
      }
    
    } else {
      cout << "An error occurred executing the program" << endl;
    }
  }
};


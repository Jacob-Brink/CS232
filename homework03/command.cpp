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
#include <sched.h>
#include "command.h"
#include "commandline.h"

using namespace std;

/* Sets up the parameters and setting for the command
 */
Command::Command(vector<int> argCountParam, bool builtinParam, CommandLine &commandLine) {
  requiredArgCount = argCountParam;
  builtin = builtinParam;
  
  argCount = commandLine.getArgCount();
  blocking = commandLine.noAmpersand();
  c_args = commandLine.getArgVector();
  
  vector<string> temp(commandLine.getArgVector(), commandLine.getArgVector()+commandLine.getArgCount());
  args = temp;
};

// function that can be overriden that checks if given parameters are correct
bool Command::isValidCount(int count) {
  int realArgCount = count - 1;
  for (int i : requiredArgCount) {
    if (realArgCount == i) {
      return true;
    }
  }
  return false;
};

// function that checks if parameters are valid
bool Command::isValidParam(char** args) {
  return true; // default to true if not overriden
};

// error messages that can be overriden
string Command::paramCountError() {
  return "Given wrong number of parameters.";
};

string Command::validParamError() {
  return "Given parameters are not valid";
};

bool Command::isValid() {
  if (!this->isValidCount(argCount)) {
    cout << this->paramCountError() << endl;
    return false;
  } else if (!this->isValidParam(c_args)) {
    cout << this->validParamError() << endl;
    return false;
  }
  return true;
}

// handles executing programs, including programs to be run in the background or not
void Command::execute() {
  if (!this->isValid()) {
    cout << "Please try again!" << endl;
    return;
  }

  if (builtin) {
    // for builtin commands such as exit or cd, we want to run them on the main thread
    this->run(c_args);
    
  } else {
    // for non builtin commands

    // create a new child process
    pid_t pid = fork();

    if (pid == 0) { // if child process, execute the code

      this->run(c_args);
      exit(0); //exit out of thread
      
    } else if (pid > 0) { // if parent process and blocking, wait, else do nothing
    
      if (blocking) {
	int status;
	waitpid(pid, &status, 0);
      } 
    
    } else {
      perror("Error in creating child process");
    }
  }
};


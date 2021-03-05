/* shell.cpp
*
* @instructor: Professor Norman
*
* @Date: 03/04/2021
* @assignment: homework03
* @student: Jacob Brink
*
* Description:
* definitions of Shell class, emulates a basic shell
*/


#include "shell.h"
#include "prompt.h"
#include "command.h"
#include "exit_command.h"
#include "cd_command.h"
#include "sys_command.h"
#include "pwd_command.h"
#include "commandline.h"
#include <iostream>
#include <sstream>

using namespace std;

// Shell constructor sets up prompt instance
Shell::Shell() {
  prompt = Prompt();
  prompt.set();
};

// creates a basic shell like program
void Shell::run() {

  while (true) {

    // display updated prompt to user
    prompt.set();
    cout << prompt.get();

    // since commandline assumes that given input is non empty string
    string input;
    getline(cin, input);
    if (input.empty()) {
      continue;
    }

    // if not empty, then give CommandLine the user input
    stringstream ss;
    ss << input;
    CommandLine commandLine = CommandLine(ss);

    // use polymorphism to create commands
    Command *commandObj = NULL;

    string command(commandLine.getCommand());
    
    if (command == "cd") {
      commandObj = new CdCommand(commandLine);
    } else if (command == "exit") {
      commandObj = new ExitCommand(commandLine);
    } else if (command == "pwd") {
      commandObj = new PwdCommand(commandLine);
    } else {
      commandObj = new SysCommand(commandLine);
    }

    commandObj->execute(); // run command
    delete commandObj; // free memory
    
  };
}

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

Shell::Shell() {
  prompt = Prompt();
  prompt.set();
};

void Shell::run() {

  bool running = true;

  while (running) {

    // display updated prompt to user
    prompt.set();
    cout << prompt.get();

    // since commandline assumes that given input is non empty string
    string input;
    getline(cin, input);
    if (input.empty()) {
      continue;
    }

    stringstream ss;
    ss << input;
    
    CommandLine commandLine = CommandLine(ss);
    string command(commandLine.getCommand());
    
    Command *commandObj = NULL;

    
    if (command == "cd") {
      commandObj = new CdCommand(commandLine);
    } else if (command == "exit") {
      commandObj = new ExitCommand(commandLine);
    } else if (command == "pwd") {
      commandObj = new PwdCommand(commandLine);
    } else {
      commandObj = new SysCommand(commandLine);
    }

    if (commandObj != NULL) {
      commandObj->execute();
      delete commandObj;
    }   
    
  };
}

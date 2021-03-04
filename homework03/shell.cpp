#include "shell.h"
#include "prompt.h"
#include "command.h"
#include "exit_command.h"
#include "cd_command.h"
#include "pwd_command.h"
#include "commandline.h"
#include <iostream>

using namespace std;

Shell::Shell() {
  prompt = Prompt();
  prompt.set();
};

void Shell::run() {

  bool running = true;

  while (running) {

    prompt.set();
    cout << prompt.get();
    
    CommandLine commandLine = CommandLine(cin);
    string command(commandLine.getCommand());
    
    Command *commandObj = NULL;
    vector<string> argVector(commandLine.getArgVector(), commandLine.getArgVector()+commandLine.getArgCount());

    
    if (command == "cd") {
      commandObj = new CdCommand(argVector, commandLine.noAmpersand());
    } else if (command == "exit") {
      commandObj = new ExitCommand(argVector, commandLine.noAmpersand());
    } else if (command == "pwd") {
      commandObj = new PwdCommand(argVector, commandLine.noAmpersand());
    } else {
      //commandObj = new SysCommand(argVector, commandLine.noAmpersand());
    }

    if (commandObj != NULL) {
      commandObj->execute();
      delete commandObj;
    }   
    
  };
}

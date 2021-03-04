#include <iostream>
#include <unistd.h>
#include "pwd_command.h"

using namespace std;

PwdCommand::PwdCommand(CommandLine &commandLine): Command({0}, false, commandLine) {
};

// courtesy of prompt.cpp developed by professor Norman
void PwdCommand::run(char** args) {
    char *tcwd = getcwd(NULL, 0);
    string cwd = string(tcwd);
    free(tcwd);

    cout << cwd << endl;

};

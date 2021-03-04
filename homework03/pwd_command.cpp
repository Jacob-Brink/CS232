#include <iostream>
#include <unistd.h>
#include "pwd_command.h"

using namespace std;

PwdCommand::PwdCommand(vector<string> args, bool blocking): Command({0}, args, blocking) {
};

// courtesy of prompt.cpp developed by professor Norman
void PwdCommand::run(vector<string> args) {
    char *tcwd = getcwd(NULL, 0);
    string cwd = string(tcwd);
    free(tcwd);

    cout << cwd << endl;

};

#include "exit_command.h"
#include <stdio.h>

ExitCommand::ExitCommand(vector<string> args, bool blocking): Command({0}, args, blocking) {

}

void ExitCommand::run(vector<string> args) {
  exit(0);
}

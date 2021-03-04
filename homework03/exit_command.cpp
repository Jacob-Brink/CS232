#include "exit_command.h"
#include <stdio.h>

ExitCommand::ExitCommand(CommandLine &commandLine): Command({0}, true, commandLine) {

}

void ExitCommand::run(char** args) {
  exit(0);
}

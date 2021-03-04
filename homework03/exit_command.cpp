/* exit_command.cpp
*
* @instructor: Professor Norman
*
* @Date: 03/04/2021
* @assignment: homework03
* @student: Jacob Brink
*
* Description:
* definition of ExitCommand class; simply exits program when run
*/


#include "exit_command.h"
#include <stdio.h>

ExitCommand::ExitCommand(CommandLine &commandLine): Command({0}, true, commandLine) {

}

void ExitCommand::run(char** args) {
  exit(0);
}

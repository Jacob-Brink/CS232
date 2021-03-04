/* sys_command.cpp
*
* @instructor: Professor Norman
*
* @Date: 03/04/2021
* @assignment: homework03
* @student: Jacob Brink
*
* Description:
* definition of SysCommand class; handles searching for program and executing that program
*/


#include "path.h"
#include "sys_command.h"
#include <unistd.h>

SysCommand::SysCommand(CommandLine &commandLine): Command({0}, false, commandLine) {
  
}

bool SysCommand::isValidCount(int count) {
  return count >= 1;
}

void SysCommand::run(char** args) {
  string commandName(args[0]);
  Path path = Path();

  int dir = path.find(commandName);

  if (dir == -1) {
    cout << "No such program was found" << endl;
  }

  string directory = path.getDirectory(dir);

  int errcode = execve((directory + "/" + commandName).c_str(), args, NULL);
  if (errcode == -1) {
    perror("Error: ");
  }

  
}

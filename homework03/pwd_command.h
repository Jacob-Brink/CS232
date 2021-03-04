/* pwd_command.h
*
* @instructor: Professor Norman
*
* @Date: 03/04/2021
* @assignment: homework03
* @student: Jacob Brink
*
* Description:
* declaration of PwdCommand; child of Command class; simply prints current working directory
*/


#include "command.h"

class PwdCommand: public Command {
 public:
  PwdCommand(CommandLine &commandLine);
 protected:
  void run(char** args);
};

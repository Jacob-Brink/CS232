/* cd_command.h
*
* @instructor: Professor Norman
*
* @Date: 03/04/2021
* @assignment: homework03
* @student: Jacob Brink
*
* Description:
* declaration of CdCommand; child of Command class; changes to user specified directory
*/


#include "command.h"

class CdCommand: public Command {
 public:
  CdCommand(CommandLine &commandLine);
 protected:
  void run(char** args);
  bool isValidParam(char** args);
};

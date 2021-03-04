/* sys_command.h
*
* @instructor: Professor Norman
*
* @Date: 03/04/2021
* @assignment: homework03
* @student: Jacob Brink
*
* Description:
* declaration of SysCommand class; child of Command class; used for all commands other than those built in to the Shell program (such as ExitCommand, etc)
*/


#include "command.h"
#include <vector>

class SysCommand: public Command {
 public:
  SysCommand(CommandLine &commandLine);
 protected:
  bool isValidCount(int count);
  void run(char** args);
};

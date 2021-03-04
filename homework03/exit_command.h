/* exit_command.h
*
* @instructor: Professor Norman
*
* @Date: 03/04/2021
* @assignment: homework03
* @student: Jacob Brink
*
* Description:
* declaration of ExitCommand; subclass of Command; when run, exits program
*/


#include "command.h"

class ExitCommand: public Command {
 public:
  ExitCommand(CommandLine &commandLine);
 protected:
  void run(char** args);
};

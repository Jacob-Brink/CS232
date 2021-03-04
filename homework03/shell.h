/* shell.h
*
* @instructor: Professor Norman
*
* @Date: 03/04/2021
* @assignment: homework03
* @student: Jacob Brink
*
* Description:
* declaration of Shell class; run function should be called to initiate a shell like program
*/


#include "prompt.h"
#include "commandline.h"

class Shell {
 public:
  Shell();
  void run();
 private:
  void handleCommand(CommandLine commandLine);
  Prompt prompt;
};

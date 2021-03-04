/* cd_command.cpp
*
* @instructor: Professor Norman
*
* @Date: 03/04/2021
* @assignment: homework03
* @student: Jacob Brink
*
* Description:
* definition of CdCommand class; changes current working directory and handles errors
*/


#include "cd_command.h"
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>

using namespace std;

CdCommand::CdCommand(CommandLine &commandLine): Command({1}, true, commandLine) {

}

//https://stackoverflow.com/questions/146924/how-can-i-tell-if-a-given-path-is-a-directory-or-a-file-c-c 
bool CdCommand::isValidParam(char** args) {
  struct stat s;
  if ( stat(args[1], &s) == 0 ) {
    if ( s.st_mode & S_IFDIR ) {
      return true;
    }
  } 
  return false;
}

void CdCommand::run(char** args) {
  int err = chdir(args[1]);
  if (err != 0) {
    cout << "An error occurred while changing directories" << endl;
  }
}

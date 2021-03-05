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

// set Command accepted argument count to just 1 and true for builtin command
CdCommand::CdCommand(CommandLine &commandLine): Command({1}, true, commandLine) {

}

string CdCommand::validParamError() {
  return "Given path does not exist";
}

string CdCommand::paramCountError() {
  return "Requires one argument that specifies what directory to change to\nUsing cd & to run in the background is not allowed.";
}

//https://stackoverflow.com/questions/146924/how-can-i-tell-if-a-given-path-is-a-directory-or-a-file-c-c
// checks that parameter is a directory
bool CdCommand::isValidParam(char** args) {
  struct stat s;
  if ( stat(args[1], &s) == 0 ) {
    if ( s.st_mode & S_IFDIR ) {
      return true;
    }
  }
  return false;
}

// tries changing directory
void CdCommand::run(char** args) {
  int err = chdir(args[1]);
  if (err != 0) {
    cout << "An error occurred while changing directories" << endl;
  }
}

#include "cd_command.h"
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>

using namespace std;

CdCommand::CdCommand(vector<string> args, bool blocking): Command({1}, args, blocking) {

}

//https://stackoverflow.com/questions/146924/how-can-i-tell-if-a-given-path-is-a-directory-or-a-file-c-c 
bool CdCommand::isValidParam(vector<string> args) {
  struct stat s;
  if ( stat((args[1]).c_str(), &s) == 0 ) {
    if ( s.st_mode & S_IFDIR ) {
      return true;
    }
  } 
  return false;
}

void CdCommand::run(vector<string> args) {
  int err = chdir((args[1]).c_str());
  if (err != 0) {
    cout << "An error occurred while changing directories" << endl;
  }
}

/* path.cpp
*
* @instructor: Professor Norman
*
* @Date: 03/04/2021
* @assignment: homework03
* @student: Jacob Brink
*
* Description:
* definitions of Path class; enables basic file searching
*/


#include <iostream>
#include <sstream>
#include "path.h"
#include <dirent.h>
#include <sys/types.h>

// https://stackoverflow.com/questions/11295019/environment-path-directories-iteration

// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
Path::Path() {
  
  string PATH = getenv("PATH");
  char delimiter = ':';
  
  stringstream ss (PATH);
  string dir;
  
  while (getline(ss, dir, delimiter)) {
    directories.push_back(dir);
  }
  
};

int Path::find(const string& program) {
  
  DIR *d;
  struct dirent *inf;

  int i = 0;
  
  for ( string dir : directories ) {
    // get a pointer to the directory
    d = opendir(dir.c_str());

    // search for directory that holds program
    if (d) {
      while ((inf = readdir(d))) {
	if (program == inf->d_name) {
	  return i;
	}
      }
      closedir(d);
    }
    
    i++; 
  }

  // return -1 when program is not found
  return -1;
  
};

string Path::getDirectory(int i) const {
  return directories[i];
};

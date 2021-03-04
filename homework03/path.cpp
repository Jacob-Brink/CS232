#include <iostream>
#include <sstream>
#include "path.h"


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
  
};

string Path::getDirectory(int i) const {
  
};

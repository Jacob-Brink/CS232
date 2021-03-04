#include <iostream>
#include "command.h"
#include "commandline.h"

using namespace std;

Command::Command(vector<int> argCountParam, vector<string> argsParam, bool blockingParam) {
  argCount = argCountParam;
  args = argsParam;
  blocking = blockingParam;
};

bool Command::isValidCount() {
  for (int i : argCount) {
    if ((args.size()-1) == i) {
      return true;
    }
  }
  return false;
}

bool Command::isValidParam(vector<string> args) {
  return true; //should be overriden
}

bool Command::isValid() {
  if (!isValidCount()) {
    cout << "Given wrong number of parameters" << endl;
    return false;
  } else if (!isValidParam(args)) {
    cout << "Parameters are of incorrect type" << endl;
    return false;
  }
  return true;
}

void Command::execute() {
  if (!isValid()) {
    cout << "Please try again!" << endl;
    return;
  }

  if (blocking) {
    this->run(args);
  } else {
    // fork then run
  }
};


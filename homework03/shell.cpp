#include "shell.h"
#include "prompt.h"
#include <iostream>

using namespace std;

Shell::Shell() {
  prompt = Prompt();
  prompt.set();
};

void Shell::run() {
  while (true) {
    string command;
    cout << prompt.get();
    getline(cin, command);
  }
};

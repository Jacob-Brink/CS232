//
//  main.cpp
//  CS232 Command Shell
//
//  Created by Victor Norman on 1/20/15.
//  Copyright (c) 2015 Victor Norman. All rights reserved.
//

#include <iostream>
#include "shell.h"
#include "path.h"

int main(int argc, const char *argv[])
{
  Path path = Path();
  
    Shell myShell;
    myShell.run();
}

#include <iostream>

using namespace std;

class Path {
 public:
  Path();
  int find(const string& program);
  string getDirectory(int i) const;
};

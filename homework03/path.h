#include <iostream>
#include <vector>

using namespace std;

class Path {
 public:
  Path();
  int find(const string& program);
  string getDirectory(int i) const;
 private:
  vector<string> directories;
};

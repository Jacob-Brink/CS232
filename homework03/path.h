/* path.h
*
* @instructor: Professor Norman
*
* @Date: 03/04/2021
* @assignment: homework03
* @student: Jacob Brink
*
* Description:
* declaration of Path class; enables file search features
*/


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

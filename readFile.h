#include <map>
#include <string>
using namespace std;

string readFileFromTxt(string filename, map<string, int> &map1, map<int, string> &map2);
void preHandleStr(string &str);
void showMap1(map<string, int> &_map);
void showMap2(map<int, string> &_map);
void test();
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
using namespace std;

void preHandleStr(string &str) {
    int len = str.size();
    for (int i = 0; i < len; i++) {
        if ((str[i] < 'A' || str[i] > 'Z') && (str[i] < 'a' || str[i] > 'z') && str[i] != ' ') {
            str[i] = '.';
        }
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 'a' - 'A';
        }
    }
    char target = '.';
    str.erase(remove(str.begin(), str.end(), target), str.end());
}

string readFileFromTxt(string filename, map<string, int> &map1, map<int, string> &map2) {
    ifstream INFILE;
    INFILE.open(filename);
    if (!INFILE.is_open()) {
        exit(EXIT_FAILURE);
    }
    string temp_str;
    string str;
    int i = 0;
    while ((INFILE >> temp_str)) {
        preHandleStr(temp_str);
        if (temp_str != "") {
            if (map1.find(temp_str) == map1.end()) {
                map1[temp_str] = i;
                map2[i] = temp_str;
                i++;
            }
            str = str + " " + temp_str;
        }
    }
    cout << str << endl;
    return str;
}

void showMap1(map<string, int> &_map) {
    map<string, int>::iterator end = _map.end();
    for (map<string, int>::iterator it = _map.begin(); it != end; it++) {
        cout << it->first << ":" << it->second << endl;
    }
}
void showMap2(map<int, string> &_map) {
    map<int, string>::iterator end = _map.end();
    for (map<int, string>::iterator it = _map.begin(); it != end; it++) {
        cout << it->first << ":" << it->second << endl;
    }
}
void test() {
    map<string, int> map1;
    map<int, string> map2;
    readFileFromTxt("./text.txt", map1, map2);
    showMap1(map1);
    showMap2(map2);
}
// int main(int argc, char const *argv[]) {
//     test();
//     return 0;
// }

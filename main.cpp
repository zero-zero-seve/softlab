#include <iostream>

#include "graph.h"
#include "readFile.h"
using namespace std;
void test1();
int main(int argc, char const *argv[]) {
    test1();
    return 0;
}

void test1() {
    map<string, int> map1;
    map<int, string> map2;
    string str = readFileFromTxt("./text.txt", map1, map2);
    Graph graph = Graph(str, map1, map2);
    graph.initGraph();
    graph.showStr();
    graph.showGraph();
    // str = graph.queryBridgeWords("exciting", "excg");
    // cout << str << endl;
    // str = graph.generateNewText("Seek to explore new and exciting synergies");
    // cout << str << endl;
    // str = graph.calcShortestPath("out", "seek");
    // cout << str << endl;
    showMap2(map2);
    str = graph.randomWalk();
    cout << str << endl;
}

#include "graph.h"

#include <limits.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>

#include "readFile.h"
using std::cout;
using std::endl;
// 构造函数
Graph::Graph(string str, map<string, int> _map1, map<int, string> _map2) {
    len = 0;
    map1 = _map1;
    map2 = _map2;
    std::stringstream STR(str);
    string word;
    while (STR >> word) {
        this->str[len++] = map1[word];
    }
    this->size = map1.size();
    initGraph();
}

void Graph::showStr() {
    for (int i = 0; i < len; i++) {
        cout << this->str[i] << " ";
    }
    cout << endl;
}
void Graph::showGraph() {
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            cout << this->graph[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::initGraph() {
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            this->graph[i][j] = 0;
        }
    }
    for (int i = 0; i < this->len - 1; i++) {
        int index1 = this->str[i];
        int index2 = this->str[i + 1];
        this->graph[index1][index2] += 1;
    }
}

Graph::~Graph() {}

string Graph::queryBridgeWords(string word1, string word2) {
    int flag1 = 1;
    int flag2 = 1;
    if (map1.find(word1) == map1.end()) {
        flag1 = 0;
    }
    if (map1.find(word2) == map1.end()) {
        flag2 = 0;
    }
    string s = "";
    if (flag1 == 0 && flag2 == 0) {
        s = s + "No" + " \"" + word1 + "\" and \"" + word2 + "\" in the graph!";
    } else if (flag1 == 0) {
        s = s + "No" + " \"" + word1 + "\" in the graph!";
    } else if (flag2 == 0) {
        s = s + "No" + " \"" + word2 + "\" in the graph!";
    } else {
        // 存在word1与word2，查询图
        s = findMiddleWord(map1[word1], map1[word2], 0);
    }
    return s;
}
string Graph::findMiddleWord(int firstword, int secondword, int choice) {
    string str = "";
    int flag = 0;
    for (int middleword = 0; middleword < size; middleword++) {
        if (graph[firstword][middleword] != 0) {
            if (graph[middleword][secondword] != 0) {
                flag = 1;
                str = str + map2[middleword] + ",";
            }
        }
    }
    switch (choice) {
        case 0: {
            if (flag == 0) {
                str = str + "No bridge words from " + "\"" + map2[firstword] + " \"to \"" + map2[secondword] +
                      "\"!";
            } else {
                str[str.size() - 1] = '.';
                string s = "";
                str = s + "The bridge words from " + "\"" + map2[firstword] + " \"to \"" + map2[secondword] +
                      "\" are:" + str;
            }
            break;
        }
        // 返回中间词或者空
        case 1: {
            if (flag == 0) {
                str = " ";
            } else {
                int count = 0;
                for (int i = 0; i < str.size(); i++) {
                    if (str[i] == ',') {
                        str[i] = ' ';
                        count++;
                    }
                }
                // 选择一个桥接词
                str = chooseOne(str, count);
            }
            break;
        }
    }
    return str;
}
string Graph::chooseOne(string str, int len) {
    srand(static_cast<unsigned int>(time(nullptr)));
    int random_number = (rand() * 1000) % len;
    // 选择合适的一个桥接词
    std::stringstream STR(str);
    string word;
    for (int i = 0; i <= random_number; i++) {
        STR >> word;
    }
    return word;
}

string Graph::generateNewText(string inputText) {
    // 已经获得用户输入文本，对文本做处理
    preHandleStr(inputText);
    std::stringstream STR(inputText);
    string word1;
    string word2;
    string str = "";
    int step = 0;
    // 读取第一个存在word1
    while (STR >> word1) {
        str = str + word1 + ' ';
        if (map1.find(word1) != map1.end()) {
            break;
        }
    }
    string temp_str;
    while (STR >> word2) {
        // str+=word2;
        if (map1.find(word2) == map1.end()) {
            str = str + word2 + ' ';
            step = 1;
            continue;
        }
        if (step != 0) {
            str = str + word2 + ' ';
            step = 0;
            word1 = word2;
            continue;
        }
        temp_str = findMiddleWord(map1[word1], map1[word2], 1);
        str = temp_str == " " ? str + word2 + ' ' : str + temp_str + ' ' + word2 + ' ';
        word1 = word2;
    }
    return str;
}

// 最短路径计算
string Graph::calcShortestPath(string word1, string word2) {
    string str = "";
    if (map1.find(word1) == map1.end() || map1.find(word2) == map1.end()) {
        str = str + "There is no word named " + word1 + " or " + word2;
    } else {
        vector<int> ans;
        dijkstra(map1[word1], map1[word2], ans);
        if (ans.size() == 0) {
            str = "Do not have a path from " + word1 + " to " + word2;
        } else {
            int _size = ans.size();

            // 从最后一个元素开始向前访问
            for (int i = _size - 1; i >= 0; --i) {
                str = str + map2[ans[i]] + "->";
            }
            str = str + word2;
        }
    }
    return str;
}

int Graph::minDistance(int dist[], int sptSet[]) {
    // 初始化最小距离为无穷大
    int min = INT_MAX, min_index;

    for (int v = 0; v < size; v++)
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    return min_index;
}

void Graph::dijkstra(int src, int dest, vector<int>& ans) {
    int dist[size - 1];  // dist[i]将保存从源点到顶点i的最短路径长度
    int sptSet[size - 1];  // sptSet[i]为真，如果顶点i包含在最短路径树中或最短路径已被确定
    int preNode[size - 1];
    for (int i = 0; i <= size - 1; i++) {
        if (graph[src][i] == 0) {
            dist[i] = INT_MAX;
            preNode[i] = -1;
        } else {
            dist[i] = graph[src][i];
            preNode[i] = src;
        }
        sptSet[i] = 0;
    }
    dist[src] = 0;
    sptSet[src] = true;

    for (int count = 0; count <= size - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = 1;
        for (int v = 0; v < size; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                preNode[v] = u;
            }
        }
    }
    // 根据每个节点前驱节点得到从src到dest最短路径
    if (dist[dest] != INT_MAX) {
        int i = dest;
        while (preNode[i] != src) {
            ans.push_back(preNode[i]);
            i = preNode[i];
        }
        ans.push_back(src);
    }
}
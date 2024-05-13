#include <map>
#include <string>
#include <vector>
using namespace std;
#define SIZE 20
#define LEN 30
class Graph {
   private:
    int graph[SIZE][SIZE];
    int size;  // graph真实大小
    int str[LEN];
    int len;  // 字符串长度
    map<string, int> map1;
    map<int, string> map2;
    string findMiddleWord(int firstword, int secondword, int choice);
    string chooseOne(string str, int len);
    void dijkstra(int src, int dest, vector<int>& ans);
    int minDistance(int dist[], int sptSet[]);
    void scan(vector<int>& path, int src);

   public:
    // 构造函数
    Graph(string str, map<string, int> _map1, map<int, string> _map2);
    // 析构函数
    ~Graph();
    // 其他函数
    void showStr();
    void showGraph();
    void initGraph();
    string queryBridgeWords(string word1, string word2);
    string generateNewText(string inputText);
    string calcShortestPath(string word1, string word2);
    string randomWalk();
};

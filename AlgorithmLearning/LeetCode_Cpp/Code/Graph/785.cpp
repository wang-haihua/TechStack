#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        if(graph.empty()){
            return false;
        }
        vector<int> color(graph.size(),0);
        queue<int> q;
        for(int i=0;i<graph.size();++i){
            if(!color[i]){
                q.push(i);
                color[i] = 1;
            }
            while(!q.empty()){
                int node = q.front();
                q.pop();
                for(const auto& j: graph[node]){
                    if(!color[j]){
                        q.push(j);
                        color[j] = color[node] == 2?1:2;
                    }else if(color[j] == color[node]){
                        return false;
                    }
                }
            }
        }
        return true;
    }
};

int main(){
    vector<vector<int>> graph{{},{3},{},{1},{}};
    Solution s;
    s.isBipartite(graph);
    return 0;
}
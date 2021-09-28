#include<iostream>
#include<vector>
#include<string>

using namespace std;

const int infinity = 99999;

void dijkstra(vector<vector<int>> G, vector<int>& res){
    int points = G.size();
    vector<int> dist(points);
    vector<bool> flag(points,false);
    res = dist;
    // 起点 初始化被选集
    flag[0] = true;
    for(int i=0;i<points;++i){
        dist[i] = G[0][i];
    }
    // 寻找最短路径
    for(int i=1;i<points-1;++i){
        int min = infinity;
        int u = -1;
        for(int j=0;j<points;++j){
            // 比较离原点最近的点
            if(!flag[j]&&dist[j]<min){
                u = j;
                min = dist[j];
            }
        }
        // 找出最近点之后，更新最短距离
        flag[u] = true;
        for(int j=1;j<points;++j){
            if(!flag[j]&&(dist[u]+G[u][j]<dist[j])){
                dist[j] = dist[u] + G[u][j];
                res[j] = u;
            }
        }
    }
}

string toNode(int n){
    switch (n)
    {
    case 0:
        return "A";
        break;
    case 1:
        return "B";
        break;
    case 2:
        return "C";
        break;
    case 3:
        return "D";
        break;
    case 4:
        return "E";
        break;
    case 5:
        return "F";
        break;
    default:
        return "";
        break;
    }
}

int main(){
    int A[6] = {0,7,12,infinity,infinity,infinity};
    int B[6] = {infinity,0,2,9,infinity,infinity};
    int C[6] = {infinity,infinity,0,infinity,10,infinity};
    int D[6] = {infinity,infinity,infinity,0,infinity,1};
    int E[6] = {infinity,infinity,infinity,4,0,5};
    int F[6] = {infinity,infinity,infinity,infinity,infinity,0};
    vector<vector<int>> G;
    G.push_back(vector<int>(A,A+6));
    G.push_back(vector<int>(B,B+6));
    G.push_back(vector<int>(C,C+6));
    G.push_back(vector<int>(D,D+6));
    G.push_back(vector<int>(E,E+6));
    G.push_back(vector<int>(F,F+6));
    vector<int> res;
    dijkstra(G,res);
    int i = res.size()-1;
    cout<<'F'<<',';
    while(i>0){
        cout<<toNode(res[i])<<',';
        i = res[i];
    }
    return 0;   
}
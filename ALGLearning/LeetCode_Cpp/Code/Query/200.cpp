#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//Code Content
vector<int> direction{-1,0,1,0,-1};
int dfs(vector<vector<char>>& grid, int row, int clom){
    if(grid[row][clom]=='0'){
        return 0;
    }
    grid[row][clom]='0';
    int x,y;
    for(int i=0;i<4;++i){
        x = row + direction[i];
        y = clom + direction[i+1];
        if(x>=0&&x<grid.size()&&y>=0&&y<grid[0].size()){
            dfs(grid,x,y);
        }
    }
    return 1;
}

int numIslands(vector<vector<char>>& grid) {
    if(grid.empty()||grid[0].empty()){
        return 0;
    }
    int res = 0;
    for(int i=0;i<grid.size();++i){
        for(int j=0;j<grid[0].size();++j){
            if(grid[i][j]=='1'){
                res += dfs(grid,i,j);
            }
        }
    }
    return res;
}

int main(){

    return 0;
}
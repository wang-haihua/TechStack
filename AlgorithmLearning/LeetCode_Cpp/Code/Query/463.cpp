#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//Code Content
vector<int> direction{-1,0,1,0,-1};
int dfs(vector<vector<int>>& grid, int row, int clom){
    if(!(row>=0&&row<grid.size()&&clom>=0&&clom<grid[0].size())){
        return 1;
    }
    if(grid[row][clom]==0){
        return 1;
    }
    if(grid[row][clom]==2){
        return 0;
    }
    grid[row][clom] = 2;
    int x,y,len=0;
    for(int i=0;i<4;++i){
        x = row + direction[i];
        y = clom + direction[i+1];
        len += dfs(grid,x,y);
    }
    return len;
}

int islandPerimeter(vector<vector<int>>& grid) {
    if(grid.empty()||grid[0].empty()){
        return 0;
    }
    int ans = 0;
    for(int i=0;i<grid.size();++i){
        for(int j=0;j<grid[0].size();++j){
            if(grid[i][j]==1){
                ans = max(ans,dfs(grid,i,j));
            }
        }
    }
    return ans;
}


class Solution {
    vector<int> direction={-1,0,1,0,-1};
public:
    int dfs(vector<vector<int>>& grid, int i, int j){
        if(grid[i][j]==0) return 1;
        if(grid[i][j]==2) return 0;
        grid[i][j] = 2;
        int x, y, perimeter = 0;
        for(int s=0;s<4;++s){
            int x = i+direction[s];
            int y = j+direction[s+1];
            if(x>=0 && x<grid.size() && y>=0 && y<grid[0].size()){
                perimeter += dfs(grid,x,y);
            }else{
                ++perimeter;
            }
        }
        return perimeter;
    }

    int islandPerimeter(vector<vector<int>>& grid) {
        if(grid.empty() || grid[0].empty()){
            return 0;
        }
        int ans = 0;
        for(int i=0;i<grid.size();++i){
            for(int j=0;j<grid[0].size();++j){
                if(grid[i][j]==1){
                    ans += dfs(grid,i,j);
                }
            }
        }
        return ans;
    }
};

int main(){
    vector<vector<int>> grid = {{0,1,0,0},{1,1,1,0},{0,1,0,0},{1,1,0,0}};
    // int ans = islandPerimeter(grid);
    Solution s;
    s.islandPerimeter(grid);
    return 0;
}
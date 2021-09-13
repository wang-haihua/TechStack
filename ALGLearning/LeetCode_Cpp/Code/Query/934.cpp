#include<iostream>
#include<vector>
#include<algorithm>
#include<deque>

using namespace std;

//Code Content
class Solution {
public:

    vector<int> direction{-1,0,1,0,-1};
    typedef pair<int,int> point;

    void dfs(vector<vector<int>>& grid, deque<point>& points, int row, int colu){
        if(grid[row][colu]==2){
            return;
        }
        if(grid[row][colu]==0){
            points.push_back(make_pair(row,colu));
            return;
        }
        grid[row][colu] = 2;
        int x,y;
        for(int i=0;i<4;++i){
            x = row + direction[i];
            y = colu + direction[i+1];
            if(x>=0&&x<grid.size()&&y>=0&&y<grid[0].size()){
                dfs(grid,points,x,y);
            }
        }
    }

    int shortestBridge(vector<vector<int>>& grid) {
        int ans = 0;
        if(grid.empty()||grid[0].empty()){
            return ans;
        }

        deque<point> points;
        bool found = false;
        for(int i=0;i<grid.size();++i){
            if(found){
                break;
            }
            for(int j=0;j<grid[0].size();++j){
                if(grid[i][j]==1){
                    dfs(grid,points,i,j);
                    found = true;
                    break;
                }
            }
        }

        while(!points.empty()){
            int pLen = points.size();
            ++ans;
            for(int i=0;i<pLen;++i){
                auto p = points.front();
                points.pop_front();
                int x,y;
                for(int j=0;j<4;++j){
                    x = p.first + direction[j];
                    y = p.second + direction[j+1];
                    if(x>=0&&x<grid.size()&&y>=0&&y<grid[0].size()){
                        if(grid[x][y]==0){
                            points.push_back(make_pair(x,y));
                            grid[x][y] = 2;
                        }
                        if(grid[x][y]==2){
                            continue;
                        }
                        if(grid[x][y]==1){
                            return ans;
                        }
                    }
                }
            }
        }
        return ans;
    }
};

int main(){
    vector<vector<int>> grid{{0,1,0},{0,0,0},{0,0,1}};
    Solution s;
    int ans = s.shortestBridge(grid);
    return 0;
}
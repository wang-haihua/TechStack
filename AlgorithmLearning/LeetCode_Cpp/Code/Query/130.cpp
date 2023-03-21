#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>

using namespace std;

//Code Content
class Solution {
public:

    vector<int> direction{-1,0,1,0,-1};

    void dfs(vector<vector<char>>& board, unordered_multimap<int,int>& output, int row, int colu){
        if(board[row][colu]=='X'){
            return;
        }
        output.insert(make_pair(row,colu));
        board[row][colu] = 'X';
        int x,y;
        for(int i=0;i<4;++i){
            x = row + direction[i];
            y = colu + direction[i+1];
            if(x>=0&&x<board.size()&&y>=0&&y<board[0].size()){
                dfs(board,output,x,y);
            }
        }
    }

    void solve(vector<vector<char>>& board) {
        if(board.empty()||board[0].empty()){
            return;
        }
        
        unordered_multimap<int,int> edge;
        int m = board.size(), n = board[0].size();
        for(int i=0;i<m;++i){
            dfs(board,edge,i,0);
            dfs(board,edge,i,n-1);
        }
        for(int j=1;j<n-1;++j){
            dfs(board,edge,0,j);
            dfs(board,edge,m-1,j);
        }
        unordered_multimap<int,int> output;
        for(int i=1;i<m-1;++i){
            for(int j=1;j<n-1;++j){
                if(board[i][j]=='O'){
                    dfs(board,output,i,j);
                }
            }
        }
        for(const auto p: edge){
            board[p.first][p.second] = 'O';
        }
    }
};


int main(){
    vector<vector<char>> board;
    int m,n;
    cin >> m >> n;
    cout<<"m:"<<m<<",n:"<<n<<endl;
    for(int i=0;i<m;++i){
        vector<char> tmp;
        for(int j=0;j<n;++j){
            char ch;
            cin >> ch;
            tmp.push_back(ch);
        }
        board.push_back(tmp);
    }
    Solution s;
    s.solve(board);
    return 0;
}
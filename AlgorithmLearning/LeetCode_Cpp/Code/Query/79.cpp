#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//Code Content
class Solution {
public:

    vector<int> direction{-1,0,1,0,-1};
    void backTracking(vector<vector<char>>& board, string word, vector<vector<bool>> visited, int row, int colu, bool& find, int len){
        if(visited[row][colu] || find || board[row][colu] != word[len]){
            return;
        }
        if(len == word.length()){
            find = true;
            return;
        }

        visited[row][colu] = true;
        int x,y;
        for(int i=0;i<4;++i){
            x = row+direction[i];
            y = colu+direction[i+1];
            if(x>=0&&x<board.size()&&y>=0&&y<board[0].size()){
                backTracking(board,word,visited,x,y,find,len+1);
            }
        }
        visited[row][colu] = false;
    }

    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> visited(m,vector<bool>(n,false));
        bool find = false;
        for(int i=0;i<m;++i){
            for(int j=0;j<n;++j){
                if(board[i][j]==word[0]){
                    backTracking(board,word,visited,i,j,find,0);
                }
            }
        }
        return find;
    }
};

int main(){
    vector<vector<char>> board;
    /*
    {{"A","B","C","E"},
    {"S","F","C","S"},
    {"A","D","E","E"}};
    */
    int m,n;
    cout<< "input m,n:"<<endl;
    cin>>m>>n;
    cout<<"m:"<<m<<",n:"<<n<<endl;
    for(int i=0;i<m;++i){
        vector<char> tmp;
        for(int j=0;j<n;++j){
            char ch;
            cin>>ch;
            tmp.push_back(ch);
        }
        board.push_back(tmp);
    }
    Solution s;
    s.exist(board,"ABCCED");
    return 0;
}
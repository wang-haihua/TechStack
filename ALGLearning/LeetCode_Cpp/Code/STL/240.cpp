#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int head = 0, tail = matrix[0].size()-1;
        while(head<tail){
            int mid = head+(tail-head)/2;
            if(matrix[0][mid]==target){
                return true;
            }else if(matrix[0][mid] > target){
                tail = mid;
            }else{
                head = mid + 1;
            }
        }
        int col = head-1;
        head = 0, tail = matrix.size()-1;
        while(head<tail){
            int mid = head+(tail-head)/2;
            if(matrix[mid][col]==target){
                return true;
            }else if(matrix[mid][col] > target){
                tail = mid;
            }else{
                head = mid + 1;
            }
        }
        return false;
    }
};

int main(){

    vector<vector<int>> matrix{{1,4,7,11,15},
                               {2,5,8,12,19},
                               {3,6,9,16,22},
                               {10,13,14,17,24},
                               {18,21,23,26,30}};

    Solution s;
    s.searchMatrix(matrix,5);

    return 0;
}
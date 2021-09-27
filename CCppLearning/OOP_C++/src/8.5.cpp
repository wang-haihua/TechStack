#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<vector<int>> arr(3); // arr中有 3 个元素，每个元素都是 vector<int> 容器
    for(int i=0; i<arr.size(); ++i){
        for(int j=0; j<3; ++j){
            arr[i].push_back(j);
        }
    }
    for(int i=0; i<arr.size(); ++i){
        for(int j=0; j<3; ++j){
            cout << arr[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}

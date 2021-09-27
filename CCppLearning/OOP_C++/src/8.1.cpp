#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> v; // 空数组
    v.push_back(1); v.push_back(2); v.push_back(3); v.push_back(4);
    vector<int>::const_iterator cit; // const 迭代器
    for(cit = v.begin(); cit != v.end(); ++cit){
        cout << *cit << ',';
    }
    cout << endl;

    vector<int>::reverse_iterator rit; // 反向迭代器
    for(rit = v.rbegin(); rit != v.rend(); ++rit){
        cout << *rit << ',';
    }
    cout << endl;

    vector<int>::iterator it; // 非 const 迭代器
    for(it = v.begin(); it != v.end(); ++it){
        *it += 1;
        cout << *it << ',';
    }
    cout << endl;
    return 0;
}
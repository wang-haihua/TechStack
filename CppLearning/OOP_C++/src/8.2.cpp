#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){

    int array[10] = {10,20,30,40};
    vector<int> v;
    v.push_back(1); v.push_back(2); v.push_back(3); v.push_back(4);
    vector<int>::iterator it;
    it = find(v.begin(), v.end(), 3);
    if(it != v.end()){
        cout << *it << endl;
    }
    // find() 没有找到元素时，返回容器末尾迭代器
    it = find(v.begin(), v.end(), 9);
    if(it == v.end()){
        cout << "not found" << endl;
    }
    it = find(v.begin()+1,v.end()-2,2);
    if(it != v.end()){
        cout << *it << endl;
    }
    // 算法操作普通数组
    int *parr = find(array,array+4,20);
    cout<< *parr << endl;
    return 0;
}
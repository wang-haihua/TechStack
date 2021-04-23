#include <iostream>
#include <vector>
using namespace std;
template<class T>
void printVector(T s, T e){
    for(;s != e; ++s){
        cout << *s << ' ';
    }
    cout << endl;
}

int main(){

    int a[5] = {1,2,3,4,5};
    vector<int> v(a,a+5);
    cout << "1)" << v.end() - v.begin() << endl;
    cout << "2)";
    printVector(v.begin(), v.end());
    v.insert(v.begin()+3, 100); // insert()函数插入元素
    cout << "3)";
    printVector(v.begin(), v.end());

    vector<int> v2(5,0);
    v2.insert(v2.begin()+2,v.begin(),v.end()); // insert() 函数数据块插入  
    cout << "4)";
    printVector(v2.begin(), v2.end());
    
    v.erase(v.begin()+3); // erase() 函数删除元素 
    cout << "5)";
    printVector(v.begin(), v.end());
    v.erase(v.begin()+2,v.begin()+4); // erase() 函数删除数据块
    cout << "6)";
    printVector(v.begin(), v.end());
 
    return 0;
}
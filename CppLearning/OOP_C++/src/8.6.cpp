#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

class A{
    private:
        int n;
    public:
        A(int n_){n = n_;}
        friend bool operator<(const A & a1, const A & a2);
        friend bool operator==(const A & a1, const A & a2);
        friend ostream& operator<<(ostream & o, const A & a2);
};

bool operator<(const A & a1, const A & a2){
    return a1.n < a2.n;
}

bool operator==(const A & a1, const A & a2){
    return a1.n == a2.n;
}

ostream& operator<<(ostream & o, const A & a2){
    o << a2.n;
    return o;
}

template <class T>
void printList(T start, T end){
    for(;start != end; ++start){
        cout << *start << ',';
    }
    cout << endl;
}

int main(){
    list<A> lst1, lst2;
    lst1.push_back(1); lst1.push_back(3);
    lst1.push_back(2); lst1.push_back(4);
    lst1.push_back(2);
    lst2.push_back(10); lst2.push_back(50);
    lst2.push_back(30); lst2.push_back(30);  
    lst2.push_back(40); lst2.push_back(40); 
    lst2.push_back(30); lst2.push_back(20);
    cout << "1) ";
    printList(lst1.begin(),lst1.end());
    cout << "2) ";
    printList(lst2.begin(),lst2.end());
    lst2.sort(); // 调用 sort 成员函数进行 lst2 排序
    cout << "3) ";
    printList(lst2.begin(),lst2.end());
    lst2.unique(); // 删除 lst2 中所有和前一个元素相等的元素
    cout << "4) ";
    printList(lst2.begin(),lst2.end());
    lst2.pop_front(); // 将 lst2 的第一个元素删除
    cout << "5) ";
    printList(lst2.begin(),lst2.end());
    lst1.remove(2); // 删除 lst1 中所有值为 2 的元素
    cout << "6) ";
    printList(lst1.begin(),lst1.end());
    lst2.merge(lst1); // 将 lst1 中的元素合并到 lst2 并将 lst1 清空
    cout << "7) ";
    printList(lst2.begin(),lst2.end());
    lst2.reverse(); // 颠倒 lst2
    cout << "8) ";
    printList(lst2.begin(),lst2.end());
    
    lst1.push_back(100); lst1.push_back(200); 
    lst1.push_back(300); lst1.push_back(400);
    cout<<"9) ";
    printList(lst1.begin(),lst1.end());
    // 找到列表中的指定元素
    list<A>::iterator p1,p2,p3;
    p1 = find(lst2.begin(),lst2.end(),4);
    p2 = find(lst1.begin(),lst1.end(),200);
    p3 = find(lst1.begin(),lst1.end(),400);
    lst2.splice(p1,lst1,p2,p3); // 将 lst1 中 [p2,p3) 区间内的元素插入到 lst2 中 p1 位置之前，并将这些元素从 lst1 中删除
    cout<<"10) ";
    printList(lst1.begin(),lst1.end());
    cout<<"11) ";
    printList(lst2.begin(),lst2.end());
    
    return 0;
}
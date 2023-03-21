#include<iostream>
using namespace std;

void hanoi(int n, char src, char mid, char dest){
    if(n == 1){
        cout << src << "->" << dest << endl;
        return; // 终止条件
    }
    hanoi(n-1, src, dest, mid); // 将 n-1 个盘子从 src 移到 mid 柱
    cout << src << "->" << dest << endl; // 将 src 柱的最大盘移到 dest 柱
    hanoi(n-1, mid, src, dest); // 将 n-1 个盘子从 mid 移到 dest 柱
}

int main(){
    int n = 3;
    hanoi(n,'A','C','B');
    return 0;
}
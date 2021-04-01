#include <iostream>
using namespace std;

void outRedirect(int x, int y){
    freopen("test.txt","w",stdout); // 将标准输出重定向到 test.txt 文件
    if( 0 == y){
        cerr<<"error."<<endl;
    }else{
        cout << x / y ;
    }
}

void inRedirect(){
    int y;
    freopen("test.txt","r",stdin); // 将标准输入重定向为 test.txt 输入
    cin >> y;
    cout << "cinRe:" << y <<endl;
}

int main(){
    int m = 5;
    int n = 2;
    outRedirect(m,n);
    inRedirect();
    return 0;
}

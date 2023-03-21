#include<iostream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

//Code Content

int main(){
    multiset<string> s;
    s.insert("SFO");
    s.insert("ALT");
    s.insert("JFK");
    for(auto elem: s){
        cout<<elem<<endl;
    }
    return 0;
}
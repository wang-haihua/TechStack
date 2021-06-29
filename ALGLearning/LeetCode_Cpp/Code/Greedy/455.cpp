#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// 贪心思想 最小的饼干满足胃口最小的孩子
int findContentChildren(vector<int>& g, vector<int>& s) {
    int pg = 0, ps = 0;
    int lg = g.size(), ls = s.size();
    int count = 0;
    sort(g.begin(),g.end());
    sort(s.begin(),s.end());
    while(pg < lg && ps < ls){
        if(g[pg] <= s[ps]){
            count++;
            pg++;
            ps++;
        }else{
            ps++;
        }
    }
    return count;
}

// 代码优化
int findContentChildren(vector<int>& g, vector<int>& s) {
    int pg = 0, ps = 0;
    int lg = g.size(), ls = s.size();
    sort(g.begin(),g.end());
    sort(s.begin(),s.end());
    while(pg < lg && ps < ls){
        if(g[pg] <= s[ps])
            pg++;
        ps++;
    }
    return pg;
}

int main(){
    vector<int> g{1,2};
    vector<int> s{1,2,3};
    int count = findContentChildren(g,s);
    cout << count <<endl;
    return 0;
}
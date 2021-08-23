#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//Code Content
vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    vector<vector<int>> ans(people.size());
    sort(people.begin(),people.end(),[](vector<int>& a, vector<int>& b){
        return a[0] < b[0];
    });
    int curHei = people[0][0];
    ans[people[0][1]] = people[0];
    vector<int> index;
    for(int i=0;i<people.size();++i){
        if(i==people[0][1]){
            index.push_back(-1);
        }else{
            index.push_back(i);
        }
    }
    int i=1;
    while(i<people.size()){
        vector<int> tmp = index;
        while(i<people.size()&&people[i][0]==curHei){
            ans[index[people[i][1]]] = people[i];
            tmp[people[i][1]] = -1;
            ++i;        
        }
        if(i>=people.size()) break;
        curHei = people[i][0];
        int count = 0;
        for(int j=0;j<tmp.size();++j){
            if(tmp[j]>=0){
                index[count++] = tmp[j];
            }
        }
    }
    return ans;
}

// 代码优化
vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    sort(people.begin(), people.end(), [](const vector<int>& u, const vector<int>& v) {
        return u[0] < v[0] || (u[0] == v[0] && u[1] > v[1]);
    });
    int n = people.size();
    vector<vector<int>> ans(n);
    for (const vector<int>& person: people) {
        int spaces = person[1] + 1;
        for (int i = 0; i < n; ++i) {
            if (ans[i].empty()) {
                --spaces;
                if (!spaces) {
                    ans[i] = person;
                    break;
                }
            }
        }
    }
    return ans;
}

int main(){
    int n;
    cout<<"input num size"<<endl;
    cin >> n;
    vector<vector<int>> people(n);
    cout<<"input elem"<<endl;
    for(int i=0;i<n;++i){
        for(int j=0;j<2;++j){
            int input;
            cin>>input;
            people[i].push_back(input);
        }
    }
    vector<vector<int>> ans = reconstructQueue(people);
    return 0;
}
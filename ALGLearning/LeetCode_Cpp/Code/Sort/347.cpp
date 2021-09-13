#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;

//Code Content

vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int,int> counts;
    for(const int& elem:nums){
        ++counts[elem];
    }
    typedef pair<int,int> PAIR;
    vector<PAIR> counts_vec(counts.begin(),counts.end());
    sort(counts_vec.begin(),counts_vec.end(),[](PAIR x, PAIR y){
        return x.second > y.second;
    });

    vector<int> res;
    for(int i=0;i<k;++i){
        res.push_back(counts_vec[i].first);
    }

    return res;
}

int main(){
    vector<int> nums{1,1,1,2,2,3};
    int k = 2;
    vector<int> res;
    res = topKFrequent(nums,k);
    return 0;
}
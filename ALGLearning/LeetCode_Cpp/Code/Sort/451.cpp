#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;

//Code Content 这种直接将map转化为vector的方法会超出时限
string frequencySort(string s) {
    unordered_map<char,int> counts;
    for(const auto& c: s){
        ++counts[c];
    }

    typedef pair<char,int> PAIR;
    vector<PAIR> counts_vec(counts.begin(),counts.end());
    sort(counts_vec.begin(),counts_vec.end(),[](PAIR x, PAIR y){
        return x.second > y.second;
    });

    string res = "";
    for(const auto& elem: counts_vec){
        for(int i=0;i<elem.second;++i){
            res = res + elem.first;
        }
    }
    return res;
}

string frequencySort(string s){
    //1. 遍历字符串，统计每个字符出现的频率，同时记录最高频率 maxFreq；
    unordered_map<char,int> counts;
    int maxFreq = 0;
    for(const auto& ch:s){
        maxFreq = max(maxFreq,++counts[ch]);
    }

    //2. 创建桶，存储从 11 到 \textit{maxFreq}maxFreq 的每个出现频率的字符；
    vector<string> buckets(maxFreq + 1);
    for (const auto& p: counts) {
        buckets[p.second].push_back(p.first);
    }

    //3. 按照出现频率从大到小的顺序遍历桶，对于每个出现频率，获得对应的字符，然后将每个字符按照出现频率拼接到排序后的字符串。
    string res;
    for (int i = maxFreq; i > 0; i--) {
        string &bucket = buckets[i];
        for (auto &ch : bucket) {
            for (int k = 0; k < i; k++) {
                res.push_back(ch);
            }
        }
    }
    return res;
}

int main(){

    return 0;
}
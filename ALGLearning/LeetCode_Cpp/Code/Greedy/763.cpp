#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<string>

using namespace std;

//Code Content
vector<int> partitionLabels(string s) {
    vector<int> ans;
    // 统计字符串中字符出现的第一个位置和最后一个位置
    std::vector<vector<int>> charIntervals;
    /*
    map<int,vector<int>> map;
    for(int i=0;i<s.size();++i){
        if(map.find((int)s[i])==map.end()){ //Map.find(key)会返回迭代器的地址，key不存在的话迭代器的值为Map.end()
            map[(int)s[i]][0]=i; 
        }else{
            map[(int)s[i]][1]=i; 
        }
    }
    std::map<int,vector<int>>::iterator it;
    for(it = map.begin();it!=map.end();++it){
        charIntervals.push_back(it->second);
    }
    */
   vector<int> startInd(256,-1);
   vector<int> endInd(256,-1);
   for(int i=0;i<s.size();++i){
       if(startInd[(int)s[i]]==-1){
            startInd[(int)s[i]]= i;
            endInd[(int)s[i]]= i;
       }else{
           endInd[(int)s[i]] = i;
       }
   }
   for(int i=0;i<startInd.size();++i){
       if(startInd[i]!=-1){
           charIntervals.push_back(vector<int> {startInd[i],endInd[i]});
       }
   }

    // 排序区间
    sort(charIntervals.begin(),charIntervals.end(),[](vector<int>& a,vector<int>& b){
        return a[0]<b[0];
    });
    // 相交区间并集
    int preStart = charIntervals[0][0];
    int preEnd = charIntervals[0][1];
    for(int i=1;i<charIntervals.size();++i){
        if(charIntervals[i][1]>preEnd){
            if(charIntervals[i][0]>preEnd){
                ans.push_back(preEnd-preStart+1);
                preStart = charIntervals[i][0];
            }
            preEnd = charIntervals[i][1];
        }
    }
    ans.push_back(preEnd-preStart+1);
    return ans;
}

int main(){
    string s = "ababcbacadefegdehijhklij";
    vector<int> ans;
    ans = partitionLabels(s);
    return 0;
}

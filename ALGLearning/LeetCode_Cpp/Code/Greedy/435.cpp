#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//Code Content
void sortIntervalsByEnd(vector<vector<int>>& internals){
    vector<int> tmp;
    int len = internals.size();
    for(int i = 0;i<len;++i){
        for(int j = i+1;j<len;++j){
            if(internals[i][1]>internals[j][1]){
                tmp = internals[i];
                internals[i] = internals[j];
                internals[j] = tmp;
            }
        }
    }
}

int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    int len = intervals.size();
    if(len<2) return 0;
    sortIntervalsByEnd(intervals);
    vector<vector<int>> sort_intervals;
    sort_intervals.push_back(intervals[0]);
    int preVal = intervals[0][1];
    for(int i =1; i<intervals.size();++i){
        if(preVal<=intervals[i][0]){
            sort_intervals.push_back(intervals[i]);
            preVal = intervals[i][1];
        }
    }
    return intervals.size() - sort_intervals.size();
}

// 代码优化
int eraseOverlapIntervals_v2(vector<vector<int>>& internals){
    if(internals.empty()){ // 使用empty成员函数判空
        return 0;
    }
    int len = internals.size();
    // 使用Lambda表达式，结合std::sort()函数自定义区间排序
    sort(internals.begin(),internals.end(),[](vector<int> a,vector<int> b){
        return a[1] < b[1];
    });
    int total = 0, preVal = internals[0][1];
    for(int i=1;i<len;++i){
        if(internals[i][0]<preVal){
            ++total;
        }else{
            preVal = internals[i][1];
        }
    }
    return total;
}

int main(){
    int n;
    cout<<"input num size"<<endl;
    cin >> n;
    vector<vector<int>> intervals(n);
    cout<<"input elem"<<endl;
    for(int i=0;i<n;++i){
        for(int j=0;j<2;++j){
            int input;
            cin>>input;
            intervals[i].push_back(input);
        }
    }
    int res = eraseOverlapIntervals(intervals);
    cout << res << endl;
    return 0;
}
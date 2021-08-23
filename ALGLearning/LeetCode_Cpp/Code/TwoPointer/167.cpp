#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//Code Content
vector<int> twoSum(vector<int>& numbers, int target) {
    int head = 0, tail = numbers.size()-1;
    vector<int> ans;
    while(head < tail){
        int sum = numbers[head]+numbers[tail];
        if(sum==target){
            ans.push_back(head+1);
            ans.push_back(tail+1);
            return ans;
        }else if(sum<target){
            ++head;
        }else{
            --tail;
        }
    }
    return ans;
}

// 代码优化
vector<int> twoSum(vector<int>& numbers, int target) {
    int head = 0, tail=numbers.size(), sum;
    while (head<tail)
    {
        sum = numbers[head] + numbers[tail];
        if(sum==tail){
            break;
        }else if(sum<target){
            ++head;
        }else{
            --tail;
        }
    }
    return vector<int> {head+1,tail+1};
}

int main(){
    vector<int> nums;
    int n;
    cin >> n;
    for(int i=0;i<n;++i){
        int input;
        cin>>input;
        nums.push_back(input);
    }
    int target;
    cin>>target;
    vector<int> ans = twoSum(nums,target);
    return 0;
}
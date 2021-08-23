#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//Code Content
bool subCheck(vector<int> nums, int start, int end){
    for(int i=start;i<end-1;++i){
        if(nums[i]>nums[i+1]){
            return false;
        }
    }
    return true;
}

bool checkPossibility(vector<int>& nums) {
    int len = nums.size();
    if(len<=1) return true;
    int i=0;
    while(i<len-1&&nums[i]<=nums[i+1]){
        ++i;
    }
    if(i==len-1) return true;
    int tmp = nums[i];
    nums[i] = nums[i+1];
    bool prechg = subCheck(nums,0,i+1)&&subCheck(nums,i+1,len);
    nums[i] = tmp, nums[i+1] = tmp; 
    bool tailchg =  subCheck(nums,0,i+1)&&subCheck(nums,i+1,len);
    return prechg||tailchg;
}

//  代码优化
bool checkPossibility(vector<int>& nums) {
    for(int i=0;i<nums.size()-1;++i){
        int x = nums[i], y = nums[i+1];
        if(x>y){
            nums[i] = y;
            if(is_sorted(nums.begin(),nums.end())){
                return true;
            }
            nums[i] = x;
            nums[i+1] = x;
            return is_sorted(nums.begin(),nums.end());
        }
    }
    return true;
}

int main(){
    int n;
    cout<<"input num size"<<endl;
    cin >> n;
    vector<int> nums;
    cout<<"input elem"<<endl;
    for(int i=0;i<n;++i){
        int input;
        cin>>input;
        nums.push_back(input);
    }
    bool ans = checkPossibility(nums);
    return 0;
}
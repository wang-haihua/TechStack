#include <iostream>
using namespace std;
#include <vector>

class Solution {
public:
    int removeElement(vector<int>& nums, int val){
        int pointer1 = 0, pointer2 = 0;
        int nums_len = nums.size();
        while(pointer1 < nums_len){
            if(nums[pointer1] == val){
                nums[pointer2] = val;
                ++pointer2;
            }
            ++pointer1;
        }
        return pointer2;
    }
};

int main(){

    Solution s;
    vector<int> nums = {3,2,2,3};
    int val = 3;
    cout<<s.removeElement(nums, 3)<<endl;

    return 0;
}
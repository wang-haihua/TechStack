#include<iostream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

class Solution {
public:
    void replacementCandidate(vector<int>& major, vector<int>& count, int candidate){
        for(int i=0;i<major.size();++i){
            if(count[i] == 0){
                major[i] = candidate;
            }
        }
    }

    void voteCount(vector<int>& major, vector<int>& count, int candidate){
        for(int i=0;i<major.size();++i){
            if(major[i] == candidate){
                ++count[i];
            }else{
                --count[i];
            }
        }
    }

    bool checkVote(int majorElem, vector<int> nums, double rate){
        int count = 0;
        for(const auto elem: nums){
            if(majorElem == elem){
                ++count;
            }
        }
        return count > rate;
    }

    bool removeElem(vector<int>& major, int val){
        auto it = major.begin();
        while(it!=major.end()){
            if(*it==val){
                major.erase(it);
                return true;
            }else{
                ++it;
            }
        }
        return false;
    }

    vector<int> majorityElement(vector<int>& nums) {
        int len = nums.size();
        vector<int> major(2,nums[0]);
        vector<int> count(2,0);
        if(len<=2){
            major.assign(nums.begin(),nums.end());
        }else{
            for(int i=0;i<len;++i){
                voteCount(major,count,nums[i]);
                replacementCandidate(major,count,nums[i]);
            }
        }
        set<int> majorSet(major.begin(),major.end());
        major.assign(majorSet.begin(),majorSet.end());
        for(const auto majorElem:major){
            if(!checkVote(majorElem,nums,(double)len/3)){
                removeElem(major,majorElem);
            }
        }
        return major;
    }

};

int main(){
    vector<int> nums{0,3,4,0};
    Solution s;
    vector<int> ans = s.majorityElement(nums);
    return 0;
}
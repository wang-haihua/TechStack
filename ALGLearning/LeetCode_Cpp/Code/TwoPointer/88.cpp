#include <iostream>
using namespace std;
#include <vector>

class Solution{
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n){
        int tail1 = m-1, tail2 = n-1, tail = m+n-1;
        if(-1 == tail1){
            nums1 = nums2;
        }
        while(tail2 >= 0){
            if(tail1 < 0){
                nums1[tail--] = nums2[tail2--];
                continue;
            }
            if(nums1[tail1] < nums2[tail2]){
                nums1[tail--] = nums2[tail2--];
            }else{
                nums1[tail--] = nums1[tail1--];
            }
        }
        for(int i =0; i< m+n; i++){
            cout<<nums1[i]<<' ';
        }
        cout<<endl;
    }
};

int main(){
    Solution s;
    vector<int> nums1 = {1,5,0,0,0}; // {1,2,3,0,0,0};
    vector<int> nums2 = {2,4,6}; //{4,5,6};
    int m = nums1.size() - nums2.size(), n = nums2.size();
    cout << m << n <<endl;
    s.merge(nums1, m, nums2, n);
    return 0;
}

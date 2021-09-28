#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int integerPairBinarySearch(vector<int> arr, int sum, vector<int>& res){
    sort(arr.begin(),arr.end());
    vector<int>::const_iterator cit;
    for(cit = arr.begin(); cit!=arr.end(); ++cit){
        int target = *cit;
        int left = 0;
        int right = arr.size() - 1;
        while (left <= right)
        {
            int mid = left + (right-left)/2;
            if(target == (sum-arr[mid])){
                res.push_back(target);
                res.push_back(arr[mid]);
                return 1;
            }
            else if (target > (sum-arr[mid]))
            {
                right = mid - 1;
            }
            else if (target < (sum-arr[mid]))
            {
                left = mid + 1;
            }
        }
    }
    return 0;
}

int integerPairTwoPointer(vector<int> arr, int sum, vector<int>& res){
    sort(arr.begin(),arr.end());
    int head = 0;
    int tail = arr.size()-1;
    while(head <= tail){
        if(arr[head]+arr[tail] == sum){
            res.push_back(arr[head]);
            res.push_back(arr[tail]);
            return 1;
        }
        else if(arr[head]+arr[tail] < sum){
            head++;
        }
        else if(arr[head]+arr[tail] > sum){
            tail--;
        }
    }
    return 0;
}

int main(){
    int a[10] = {1,3,4,6,7,8,9,1,4,5};
    vector<int> res1,res2;
    vector<int> arr(a,a+10);
    integerPairBinarySearch(arr,14,res1);
    integerPairTwoPointer(arr,14,res2);
    cout << res1[0] << ',' << res1[1] << endl;
    cout << res2[0] << ',' << res2[1] << endl;
    return 0;
}
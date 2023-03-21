#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//Code Content
int findMinArrowShots(vector<vector<int>>& points) {
    if(points.empty()){
        return 0;
    }
    sort(points.begin(),points.end(),[](vector<int>& a, vector<int>& b){
        return a[1]<b[1];
    });
    int preVal = points[0][1];
    int arrows = 1;
    for(int i=1;i<points.size();++i){
        if(points[i][0]>preVal){
            ++arrows;
            preVal = points[i][1];
        }
    }
    return arrows;
}

int main(){

    return 0;
}
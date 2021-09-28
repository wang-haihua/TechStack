#include<iostream>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

class job{
    public:    
    int id;
    int startT;
    int endT;
    job(int i=0,int s=0 , int e=0){id=i;startT=s;endT=e;}
    friend void jobSche(vector<job> arr, vector<int>& res);
    friend void jobSortByEndT(vector<job>& arr, int start, int end);
    friend void swap(job& ja, job& jb);
};

void swap(job& ja, job& jb){
    job tmp;
    tmp.id = ja.id;tmp.startT=ja.startT;tmp.endT=ja.endT;
    ja.id = jb.id;ja.startT=jb.startT;ja.endT=jb.endT;
    jb.id = tmp.id;jb.startT=tmp.startT;jb.endT=tmp.endT;
}

void jobSortByEndT(vector<job>& arr, int start, int end){
    if(start>=end) return;
    int pHead=start; int pTail=end;
    int key=arr[start].endT;
    while(pHead<pTail){
        while (pTail>pHead&&arr[pTail].endT>=key)
        {
            pTail--;
        }
        swap(arr[pHead],arr[pTail]);
        while (pHead<pTail&&arr[pHead].endT<=key)
        {
            pHead++;
        }
        swap(arr[pHead],arr[pTail]);
    }
    jobSortByEndT(arr,start,pHead-1);
    jobSortByEndT(arr,pTail+1,end);
}

void jobSche(vector<job> jobs, vector<int>& res){
    jobSortByEndT(jobs,0,jobs.size()-1);
    res.push_back(jobs[0].id);
    int target = jobs[0].endT;
    for(int i=1;i<jobs.size();++i){
        if(jobs[i].startT>=target){
            res.push_back(jobs[i].id);
            target = jobs[i].endT;
        }
    }
}

int main(){
    vector<int> startTime{6,1,2,3,5,3,0,5,8,8,12};
    vector<int> endTime{11,4,14,5,7,9,6,9,10,12,16};
    vector<job> jobs;
    for(int i=1;i<=endTime.size();++i){
        job j(i,startTime[i-1],endTime[i-1]);
        jobs.push_back(j);
    }
    /*
    jobSortByEndT(jobs,0,jobs.size()-1);
    for(int i=0;i<jobs.size();++i){
        cout << jobs[i].id <<',' <<jobs[i].endT << endl;
    }
    */
    vector<int> res;
    jobSche(jobs,res);
    for(int i=0;i<res.size();++i){
        cout << res[i] << ',';
    }
    return 0;
}
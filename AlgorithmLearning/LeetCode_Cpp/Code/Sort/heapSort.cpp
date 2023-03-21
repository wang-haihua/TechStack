#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

/***************
* 完全二叉树顺序存储：
* 传入的数组起始节点从0开始，对于下标为k的节点来说：
* 左孩子位置：2k + 1
* 右孩子位置：2k + 2
* 父亲节点位置：(k - 1) / 2
****************/

/*
* 上浮操作，比较节点与其父节点，满足条件则交换子和父的值
* a > b ，建立大根堆，升序排序
* a < b ，建立小根堆，降序排序
*/
void swim(vector<int> &nums, int i){
    int parent = (i-1)/2;
    if(parent<0 || nums.empty()) return;
    if(nums[i] > nums[parent]){
        swap(nums[i],nums[parent]);
        swim(nums,parent); // 递归调整
    }
}

/*
* 下沉操作，比较节点与其子节点，满足条件则交换子和父的值
* 如果是大根堆，节点应该与值大的子节点交换
* 如果是小根堆，节点应该与值小的子节点交换
*/
void sink(vector<int> &nums, int i,int heapSize){
    if(heapSize==0 || nums.empty()) return;

    // 找到当前节点、左节点、右节点中较大的一个节点索引
    int bigger = i;
    int leftChild = 2*i+1;
    if(leftChild < heapSize){
        bigger = nums[leftChild] > nums[i] ? leftChild:i;
    }
    int rightChild = 2*i+2;
    if(rightChild < heapSize){
        bigger = nums[rightChild] > nums[bigger] ? rightChild:bigger;
    }

    // 如果较大节点是左右节点中的一个，交换当前节点和较大节点
    if(bigger!=i){
        swap(nums[i],nums[bigger]);
        sink(nums,bigger,heapSize); // 递归调整
    }
}


/*
* 每一个叶子节点可以看成一个大小唯一的堆
* 从最后一个非叶子节点(即最后一个节点的父节点)开始，对每一个节点进行下沉操作
* 这样以当前节点为根节点的树就变成堆了
*/
void buildHeap(vector<int> &nums, int heapSize){
    // 从最后一个非叶子节点开始构造
    int i=(heapSize-1)/2;
    for(i;i>=0;--i){
        sink(nums,i,heapSize);
    }
}

/*
* 删除堆根节点时，先与最后一个节点进行交换，交换后，堆大小减1，并对根节点进行下沉调整
*/
void sort(vector<int> &nums, int &heapSize){
	swap(nums[0], nums[heapSize - 1]);
	--heapSize;
	sink(nums,0,heapSize);
}

void heapSort(vector<int> &nums){
    int heapSize = nums.size();
    buildHeap(nums,heapSize);
    for(int i=0;i<nums.size()-1;++i){
        sort(nums,heapSize);
    }
}

int main(){
    vector<int> arr{29,10,14,37,14,25,10};
    heapSort(arr);
    return 0;
}
#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:

    TreeNode* helper(unordered_map<int,int> hash, vector<int>& preorder, int preStart, int preEnd, vector<int>& postorder,int postStart, int postEnd){
        if(preStart > preEnd){
            return nullptr;
        }
  
        int rootVal = preorder[preStart];
        TreeNode* node = new TreeNode(rootVal);
        if(preStart+1>preEnd){
            return node;
        }

        int leftChildPostIndex = hash[preorder[preStart+1]];
        // int leftLen = leftChildPostIndex - leftBound + 1;
        int leftLen = leftChildPostIndex - postStart + 1;

        node->left = helper(hash,preorder,preStart+1,preStart+leftLen,postorder,postStart,leftLen);
        node->right = helper(hash,preorder,preStart+leftLen+1,preEnd,postorder,leftChildPostIndex+1,postEnd-1);
        return node;
    }

    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        int len = preorder.size();
        if(len == 0){
            return nullptr;
        }
        
        if(len == 1){
            TreeNode* root = new TreeNode(preorder[0]);
            return root;
        }

        unordered_map<int,int> hash;
        for(int i=0;i<len-1;++i){
            hash[postorder[i]] = i;
        }

        return helper(hash,preorder,0,len-1,postorder,0,len-1);
    }
};

void printTree(TreeNode* root){
    if(!root){
        return;
    }
    cout<<root->val<<',';
    printTree(root->left);
    printTree(root->right);
}

int main(){
    vector<int> pre={2,1}, post={1,2};
    Solution s;
    TreeNode* root = s.constructFromPrePost(pre,post);
    printTree(root);
    cout<<endl;
    return 0;
}
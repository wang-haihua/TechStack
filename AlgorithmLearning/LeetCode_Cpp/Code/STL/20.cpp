#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for(const auto c: s){
            if(c=='(' || c=='[' || c=='{'){
                st.push(c);
            }else if(c==')' && st.top()=='('){
                st.pop();
            }else if(c==']' && st.top()=='['){
                st.pop();
            }else if(c=='}' && st.top()=='{'){
                st.pop();
            }
        }
        return st.empty();
    }
};

int main(){
    string s = "(}";
    Solution so;
    bool ans = so.isValid(s);
    return 0;
}
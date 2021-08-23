#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

/* 算法效率低下，超长字符串处理会超时
vector<int> countChar(string s){
    int slen = s.size();
    vector<int> count(256,0);
    for(int i=0;i<slen;++i){
        count[int(s[i])]++;
    }
    return count;
}

bool ifContant(string s, string t){
    vector<int> countS = countChar(s);
    vector<int> countT = countChar(t);
    for(int i=0;i<countS.size();++i){
        if(countS[i]<countT[i]){
            return false;
        }
    }
    return true;
}

string minWindow(string s, string t){
    vector<int> countT = countChar(t);
    bool found = false;
    int left = 0, right = 0;
    string res = "";
    while(left<s.size()){
        for(right;right<s.size();++right){
            string tmp = s.substr(left,right-left+1);
            if(ifContant(tmp,t)){
                if(res==""||res.size()>tmp.size()){
                    res = tmp;
                }
                break;
            }
        }
        if(right==s.size()) return res;
        for(left;left<=right;++left){
            string tmp = s.substr(left,right-left+1);
            if(!ifContant(tmp,t)){
                break;
            }
            if(res==""||res.size()>tmp.size()){
                res = tmp;
            }
        }
        right++;
    }
    return res;
}
*/
string minWindow(string s, string t){
    vector<int> tFreq(128,0), winFreq(128,0);
    for(int i=0;i<t.size();++i){
        tFreq[t[i]]++;
    }

    int distance = 0; // 用于判断窗口内的字符串是否包含t
    int minLen = s.size()+1;
    int pLeft = 0, pRight = 0; 
    int begin;
    while (pRight<s.size())
    {
        // 先移动右指针找到包含t的字串
        if(tFreq[s[pRight]]==0){
            pRight++;
            continue;
        }

        if(winFreq[s[pRight]]<tFreq[s[pRight]]){
            distance++;
        }
        winFreq[s[pRight++]]++;

        //移动左指针缩小窗口
        while (distance==t.size())
        {
            //更新最小窗口大小，和窗口起点
            if(pRight-pLeft < minLen){
                minLen = pRight-pLeft;
                begin = pLeft;
            }

            if(tFreq[s[pLeft]]==0){
                pLeft++;
                continue;
            }

            if(winFreq[s[pLeft]]==tFreq[s[pLeft]]){
                distance--;
            }
            winFreq[s[pLeft++]]--;
        }
    }

    if(minLen == s.size()+1){
        return "";
    }

    return s.substr(begin,minLen);
    
}

int main(){
    string s = "cabwefgewcwaefgcf";
    string t = "cae";
    string ans = minWindow(s,t);
    cout<<ans<<endl;
    return 0;
}
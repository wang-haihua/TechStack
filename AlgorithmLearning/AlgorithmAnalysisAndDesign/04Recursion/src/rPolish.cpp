#include<iostream>
#include<vector>
#include<string>
#include<cstring>
using namespace std;

double exp(vector<string>& notaion){
    string term = notaion.back();
    notaion.pop_back();
    const char* c = term.data();
    switch (c[0])
    {
    case '+':
        return exp(notaion) + exp(notaion);
    case '-':
        return exp(notaion) - exp(notaion);
    case '*':
        return exp(notaion) * exp(notaion);
    case '/':
        return exp(notaion) / exp(notaion);
    default:
        return atof(c);
    }
}

// 字符串分割函数
vector<string> split(const string& str, const string& delim){
    vector<string> res;
    if(""==str) return res;
    // 先将 string 转化为 char*
    char* strs = new char[str.length()+1];
    strcpy(strs,str.c_str());
    const char* dl = delim.c_str();
    char *tokenPtr = strtok(strs,dl); // 使用 strtok() 函数分割字符串
    while(tokenPtr){
        string s = tokenPtr;
        res.push_back(s);
        tokenPtr = strtok(NULL,dl);
    }

    return res;
}

int main(){
    string strNon = "35.0 24.0 + 12.0 11.0 + *";
    vector<string> notation;
    notation = split(strNon," ");
    cout<< strNon << " = " << exp(notation) << endl;

    return 0;
}
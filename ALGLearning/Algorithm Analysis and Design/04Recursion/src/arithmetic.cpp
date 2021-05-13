#include<iostream>
#include<deque>
#include<string>
#include<cstring>
using namespace std;

int factor_value(deque<string>& exp);
int term_value(deque<string>& exp);

// 求一个表达式的值
int expression_value(deque<string>& exp){
    int result = term_value(exp);
    while (true)
    {
        string op = exp.front(); // 查看下一个字符
        if(op =="+" || op == "-"){
            exp.pop_front();
            int value = term_value(exp);
            if(op == "+"){
                result += value;
            }else{
                result -= value;
            }
        }else{
            break;
        }
    }

    return result;
}

// 求一个项的值
int term_value(deque<string>& exp){
    int result = factor_value(exp);
    while(true){
        string op = exp.front(); // 查看下一个字符
        if(op =="*" || op == "/"){
            exp.pop_front();
            int value = factor_value(exp);
            if(op == "*"){
                result *= value;
            }else{
                result /= value;
            }
        }else{
            break;
        }
    }
    return result;
}

// 求一个因子的值
int factor_value(deque<string>& exp){
    int result = 0;
    string c = exp.front(); // 查看下一个字符
    if(c == "("){
        exp.pop_front();
        result = expression_value(exp);
        exp.pop_front();
    }else{
        const char* vc = c.data();
        result += atoi(vc);
        exp.pop_front();
    }
    return result;
}

// 字符串分割函数
deque<string> split(const string& str, const string& delim){
    deque<string> res;
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
    string expStr = "( 2 + 3 ) * ( 5 + 7 ) + 9 / 3";
    deque<string> expDe = split(expStr," ");
    cout << expression_value(expDe) << endl;
    return 0;
}
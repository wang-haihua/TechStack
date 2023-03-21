#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
struct Student
{
    char name[20];
    int score;
};

int main(){
    // 二进制文件写入
    ofstream outFile("students.dat", ios::out|ios::binary);
    Student s;
    while(cin >> s.name >> s.score){
        outFile.write((char *)& s, sizeof(s));
    }
    outFile.close();
    
    // 二进制文件读取
    ifstream inFile("students.dat", ios::in|ios::binary);
    if(!inFile){
        cout << "error" << endl;
        return 0;
    }
    while(inFile.read((char*)& s, sizeof(s))){
        int readedBytes = inFile.gcount(); // 查看本次读取了多少个字节
        cout << s.name << " " << s.score << endl;
    }
    inFile.close();

    // 二进制文件读写（修改）
    fstream ioFile("student.dat", ios::in|ios::out|ios::binary);
    if(!ioFile){
        cout << "error";
        return 0;
    }
    ioFile.seekp(2 * sizeof(s), ios::beg); // 将写指针定位到要被修改的内容首部
    ioFile.write("Mike", strlen("Mike")+1); // +1 的目的是也将 '\0' 写入到末尾
    ioFile.seekg(0, ios::beg);
    while (ioFile.read((char*)& s, sizeof(s)))
    {
        cout << s.name << " " << s.score << endl;
    }
    ioFile.close();
    
    return 0;
}

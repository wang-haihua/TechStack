#include <iostream>
#include <iomanip> // 流操纵算子头文件
using namespace std;

int main(){

    // 分别以十六进制、十进制、八进制先后输出 n
    int n = 141;
    cout << "1) " << hex << n << " ";
    cout << dec << n << " ";
    cout << oct << n <<endl;

    // 保留 5 位有效数字
    double x = 1234567.89, y = 12.34567;
    cout << "2) " << setprecision(5) << x << " " << y <<endl;

    // 保留小数点后 5 位 定点输出浮点数
    cout << "3) " << fixed << setprecision(5) << x << " " << y <<endl;

    // 科学计数法输出，且保留小数点后 5 位
    cout << "4) " << scientific << setprecision(5) << x << " " << y <<endl;

    // 非负数要显示正号，输出宽度为 12 字符， 宽度不足则用 * 号填补
    cout << "5) " << showpos << fixed << setw(12) << setfill('*') << 12.1 <<endl;

    // 非负数不显示正号，输出宽度为 12 字符， 左对齐 宽度不足则右边用填充字符填补
    cout << "6) " << noshowpos << setw(12) << left << 12.1 <<endl;

    // 输出宽度为 12 字符，右对齐 宽度不足则左边用填充字符填补
    cout << "7) " << setw(12) << right << 12.1 << endl;

    // 宽度不足时，符号和数值分列左右，中间用填充字符填补
    cout << "8) " << setw(12) << internal << -12.1 <<endl;
    cout << "9) " << 12.1 <<endl;

    return 0;
}
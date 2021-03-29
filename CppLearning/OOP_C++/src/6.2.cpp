#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

class Shape{
    public:
        virtual double area() = 0; // 纯虚函数 Shape 无法计算面积 没有信息
        virtual void printInfo() = 0;
};

class Rectangle:public Shape{
    public:
        int width, height;
        virtual double area();
        virtual void printInfo();
};

class Circle:public Shape{
    public:
        int radius;
        virtual double area();
        virtual void printInfo();
};

class Triangle:public Shape{
    public:
        int a, b, c;
        virtual double area();
        virtual void printInfo();
};

double Rectangle::area(){
    return width*height;
}

double Circle::area(){
    return 3.14*pow(radius,2);
}

double Triangle::area(){
    double temp = (a+b+c)/2.0;
    return sqrt(temp*(temp-a)*(temp-b)*(temp-c));
}

void Rectangle::printInfo(){
    cout << "Rectangle:" << area() << endl;
}

void Circle::printInfo(){
    cout << "Circle:" << area() << endl;
}

void Triangle::printInfo(){
    cout << "Triangle:" << area() << endl;
}

Shape* pShape[100];
int compare(const void * s1, const void * s2){
    Shape** p1;
    Shape** p2; // p1 p2 都是指向指针的指针
    p1 = (Shape**)s1; // 从 pShape 中取几何形体都是指向该几何形体 Shape* 类型 所以要用 * 号取值
    p2 = (Shape**)s2;
    double a1,a2;
    a1 = (*p1)->area(); // p1 p2 是基类指针，被调用的 area() 取决与 p1 p2 指向的派生类， 所以此处是多态
    a2 = (*p2)->area();
    if(a1 < a2){
        return -1;
    }
    else if (a2 < a1)
    {
        return 1;
    }
    else{
        return 0;
    }
    
} 

int main(){

    int n;
    cin >> n;
    for(int index = 0; index < n; index++){
        char c;
        cin >> c;
        switch (c)
        {
        case 'R':
            Rectangle* pr;
            pr = new Rectangle();
            cin >> pr->width >> pr->height;
            pShape[index] = pr;
            break;
        case 'C':
            Circle* pc;
            pc = new Circle();
            cin >> pc->radius;
            pShape[index]= pc;
            break;
        case 'T':
            Triangle* pt;
            pt = new Triangle();
            cin >> pt->a >> pt->b >> pt->c;
            pShape[index] = pt;
            break;
        default:
            break;
        }
    }

    qsort(pShape,n,sizeof(Shape*),compare);
    for(int i=0; i<n; i++){
        pShape[i]->printInfo();
    }

    return 0;
}
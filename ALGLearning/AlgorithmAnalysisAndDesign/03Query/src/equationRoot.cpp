#include<iostream>
#include<cmath>

using namespace std;

double f(double x){
    return pow(x,3) - 5*pow(x,2) + 10*x - 80;
}

double equationRoot(double lower, double upper){
    double EPS = 1e-6;
    while(lower <= upper){
        double root = lower + (upper-lower)/2;
        double f_root = f(root);
        if(fabs(f_root) < EPS){
            return root;
        }
        else if(f_root > 0){
            upper = root;
        }
        else if(f_root < 0){
            lower = root;
        }
    }
    return 0;
}

int main(){
    double root = equationRoot(0,100);
    cout << root << endl;
    return 0;
}
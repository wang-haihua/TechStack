#include <iostream>
using namespace std;

template <class T>
T maxElement(T a[], int size){
    T tempMax = a[0];
    for(int i=1; i<size; ++i){
        if(tempMax < a[i]){
            tempMax = a[i];
        }
    }
    return tempMax;
}

int main(){
    int arr1[] = {1,2,3,4,5};
    double arr2[] = {1.1,2.2,3.3,4.4,5.5};
    cout << maxElement(arr1, 5);
    cout << maxElement<double>(arr2, 5);
    return 0;
}
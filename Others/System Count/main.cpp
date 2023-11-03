#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    int start_sys, sys, num2 = 0, char0;
    string result, num;
    string a[16] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
    cout<<"Введите стартовую систему: ";
    cin>>start_sys;
    cout<<"Введите число: ";
    cin>>num;
    cout<<"Введите конечную систему исчисления: ";
    cin>>sys;
    for (int i = 0; i < num.length(); i += 1) {
        char0 = stoi(to_string(num[num.length()-1-i]))-48;
        num2 = num2 + char0 * pow(start_sys, i);
    }
    while (num2 != 0) {
        result = a[num2%sys] + result;
        num2 = num2/sys;
    }
    cout<<result;

    return 0;
}
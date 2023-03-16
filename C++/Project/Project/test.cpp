#include<iostream>
#include<string>
#include<nlohmann/json.hpp>
#include<fstream>
#include<ctime>
#include<stdlib.h>

using namespace std;
using json= nlohmann::json;

void find(string* arr, int& count){
    //read
    string str;
    ifstream in("/Users/macos/C++/Project/Project/seri.txt");
    while(!in.eof()) {
        getline(in,str);
        arr[count]=str;
        count++;
    }
}

void xuat(string*arr, int& count){
    for (int i=0; i<count-1;i++) {
        cout << arr[i] << endl;
    }
}

void findseri(string* arr, int& count){
    string seri;
    cout << "Nhap ma: ";
    getline(cin,seri);
    bool flag=false;
    for (int i=0; i<count-1; i++) {
        if (arr[i]==seri) {
            flag=true;
        }
    }
    if (flag == true) cout << "Ton tai sp" << endl;
    if (flag == false) cout << "Khong ton tai sp" << endl;
}

int main2() {
    int count=0;
    string* arr = new string;
    find(arr,count);
    xuat(arr,count);
    findseri(arr,count);
    return 0;
}



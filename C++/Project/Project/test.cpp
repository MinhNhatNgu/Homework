#include<iostream>
#include<string>
#include<nlohmann/json.hpp>
#include<fstream>
#include<ctime>
#include<stdlib.h>
#include<vector>

using namespace std;
using json= nlohmann::json;

string getquan(string s, string result="") {
    char key='/';
    bool flag=false;
    for (int i=(unsigned int)s.size()-1; i>=0; i--) {
        if (s[i]!=key && flag==false) {
            result+=s[i];
        } else {
            flag=true;
        }
    }
    return result;
}

void kho(string s) {
    
    cout << setw(30) << s;
}

int main2() {
    
    return 0;
}

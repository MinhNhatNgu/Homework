#include<iostream>
#include<string>
#include<nlohmann/json.hpp>
#include<fstream>
#include<ctime>
#include<stdlib.h>
#include<vector>

using namespace std;
using json= nlohmann::json;

string outquantity(string s , char key) {
    string quantity="";
    bool flag=false;
    for (int i=(unsigned int)s.size()-1; i>=0; i--) {
        if (s[i]!=key && flag==false) {
            quantity+=s[i];
        } else {
            flag=true;
        }
    }
    return quantity;
}
int main2() {
    string s="Mac-MacAir-gold-08GB (SL:99)";
    string temp= s.substr(s.length()-5,5);
    string p="0123456789";
    string result;
    for (int i=0; i<temp.size(); i++) {
        if (p.find(temp[i])!=string::npos) {
            cout << temp[i] << endl;
            result+=temp[i];
        }
    }
    cout << result;
    return 0;
}

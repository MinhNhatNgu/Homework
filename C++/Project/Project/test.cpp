#include<iostream>
#include<string>
#include<nlohmann/json.hpp>
#include<fstream>
#include<ctime>
#include<stdlib.h>

using namespace std;
using json= nlohmann::json;


int main2() {
    //int count=0;
    //string* arr = new string;
    //find(arr,count);
    //xuat(arr,count);
    //findseri(arr,count);
    ifstream ifs("/Users/macos/C++/Project/Project/data.json");
    json j = json::parse(ifs);
    ifs.close();
    
    
    ofstream ofs("/Users/macos/C++/Project/Project/data.json");
    ofs << j.dump(4);
    ofs.close();
    return 0;
}

#include<iostream>
#include<string>
#include<nlohmann/json.hpp>
#include<fstream>
#include<ctime>
#include<stdlib.h>
#include<vector>

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


void getinfo(json& data, string& fkey1,const string& path){
    if (data.is_object()) {
        for (auto it=data.begin(); it!=data.end(); it++) {
            if (it.key()==fkey1) {
                cout << path << "/" << it.key() << "/" << it.value() << endl;
            } else {
                getinfo(it.value(),fkey1,path+"/"+it.key());
            }
        }
    }
}

void print (json& data, const string& path) {
    if (data.is_object()) {
        for (auto it=data.begin() ; it!=data.end() ; it++) {
            if (it.key()=="02GB" || it.key()=="04GB") {
                ofstream of("/Users/macos/C++/Project/Project/textdata.txt",ios::app);
                of << path << "/" + it.key() << "/" << it.value()<< endl;
                of.close();
                
            } else {
                print(it.value(),path+"/"+it.key());
            }
        }
    }
    
}

void locsp(){
    ifstream in("/Users/macos/C++/Project/Project/textdata.txt");
    string* arr = new string;
    string temp;
    int count=0;
    while(!in.eof()) {
        getline(in,temp);
        arr[count]=temp;
        count++;
    }
    in.close();
    
    int chooseDevice, chooseType, chooseColor, chooseRam;
    int quantity;
    string device,type,color,ram;
    cout << "1.IP   2.Mac  3.Boqua";
    cin >> chooseDevice;
    if (chooseDevice==1) {
        device="IP";
        cout << "1.IP13  2.IPX  3.IP7  4.Boqua";
        cin >> chooseType;
        if (chooseType==1) type="IP13";
        if (chooseType==2) type="IPX";
        if (chooseType==3) type="IP7";
        if (chooseType==4) type="";
        cout << "1.black   2.purple  3.white  4.boqua";
        cin >> chooseColor;
        if (chooseColor==1) color="black";
        if (chooseColor==2) color="purplr";
        if (chooseColor==3) color="white";
        if (chooseColor==4) color="";
        cout << "1. 2GB   2. 4GB   3.Boqua";
        cin >> chooseRam;
        if (chooseRam==1) ram="02GB";
        if (chooseRam==2) ram="04GB";
        if (chooseRam==3) ram="";
        //slove
        
        for (int i=1; i<count ; i++) {
            if (arr[i].find(device)!=string::npos && arr[i].find(type)!=string::npos && arr[i].find(color)!=string::npos && arr[i].find(ram)!=string::npos) {
                cout << arr[i] << endl;
            }
        }
        
    }
    if (chooseDevice==2) {
        
    }
}

int main2() {
    //int count=0;
    //string* arr = new string;
    //find(arr,count);
    //xuat(arr,count);
    //findseri(arr,count);
    ifstream ifs("/Users/macos/C++/Project/Project/data.json");
    json j = json::parse(ifs);
    ifs.close();
    
    string path="";
    ofstream cls("/Users/macos/C++/Project/Project/textdata.txt",ios::out);
    cls << endl;
    cls.close();
    print(j,path);
    locsp();
    
    
    ofstream ofs("/Users/macos/C++/Project/Project/data.json");
    ofs << j.dump(4);
    ofs.close();
    return 0;
}

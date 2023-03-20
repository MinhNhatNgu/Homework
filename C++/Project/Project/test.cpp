#include<iostream>
#include<string>
#include<nlohmann/json.hpp>
#include<fstream>
#include<ctime>
#include<stdlib.h>
#include<vector>

using namespace std;
using json= nlohmann::json;

void xem(vector<string>& listsp){
    cout << "San pham ban da lua chon: " << endl;
    for (int i=0,count=1; i<listsp.size();i++,count++) {
        cout << count << ". " << listsp[i] << endl;
    }
}

void them(vector<string>& listsp){
    int chooseDevice, chooseType, chooseColor, chooseRam;
    string device,type,color,ram;
    
    cout << "Chon thiet bi: " << endl;
    cout << "1.IPhone\t" << "2.Macbook\t" << endl;
    cin >> chooseDevice;
    if (chooseDevice==1) {
        device="IP";
        cout << "Chon dong san pham:" << endl;
        cout << "1.IPhone13\t" << "2.IPX\t" << "3.IP7\t" << endl;
        cin >> chooseType;
        if (chooseType==1) type="IP13";
        if (chooseType==2) type="IPX";
        if (chooseType==3) type="IP7";
        cout << "Chon mau:" << endl;
        cout << "1.Black\t\t" << "2.Purple\t" << "3.White\t\t" << endl;
        cin >> chooseColor;
        if (chooseColor==1) color="black";
        if (chooseColor==2) color="purple";
        if (chooseColor==3) color="white";
        cout << "Chon dung luong ram:" << endl;
        cout << "1. 2GB\t\t" << "2. 4GB\t\t" << endl;
        cin >> chooseRam;
        if (chooseRam==1) ram="02GB";
        if (chooseRam==2) ram="04GB";
    }
    if (chooseDevice==2) {
        device="Mac";
        cout << "1.Macbook Air\t\t" << "2.Macbook Pro\t\t" << endl;
        cin >> chooseType;
        if (chooseType==1) type="MacAir";
        if (chooseType==2) type="MacPro";
        cout << "1.Gold\t\t" << "2.Gray\t" << endl;
        cin >> chooseColor;
        if (chooseColor==1) color="gold";
        if (chooseColor==2) color="gray";
        cout << "1. 8GB\t\t" << "2. 16GB\t\t" << endl;
        cin >> chooseRam;
        if (chooseRam==1) ram="08GB";
        if (chooseRam==2) ram="16GB";
    }
    
    string info= device + "-" + type + "-" + color + "-" + ram;
    listsp.push_back(info);
    
    
}

void xoa(vector<string>& listsp){
    
    cout << endl << "Nhap so muon xoa: ";
    int dele;
    cin >> dele;
    listsp.erase(listsp.begin()+dele-1);
}

void out (vector<string>& listsp) {
    
}

int main2() {
    vector<string> listsp;
    cout << "1.Xem   2.Them   3.Xoa" << endl;
    them(listsp);
    them(listsp);
    them(listsp);
    out(listsp);
    return 0;
}

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <ctime>
#include <stdlib.h>

using namespace std;
using json = nlohmann::json;

//static variable

//int num;
string seri;
int chooseColor;
int chooseRam;
int quantity;
string device,type,color,ram;


//Cap phat dong


//sub function
int random(int a, int b);
int getChoose(int a, int b);
void clear(int n);

//function
void getQuantity(string device, string type, string color, string ram, int quantity);
string getChar(string str, int start, int end);
void getInfoIP(string nameType, string name);
void getInfoMac(string nameType, string name);
void writeSeriIP(string device, string type, string color, string ram, int quantity);
void writeSeriMac(string device, string type, string color, string ram, int quantity);
void getSeriFromFile(string* arrSeri, int& countSeri);
void findBySeri(string* arrSeri, int& countSeri);

//main function
void menu();
void choose_menu();
void nhapsp();
void kiemsp();

//main
int main() {
    srand((unsigned int)time(NULL));
    
    menu();
    choose_menu();
    
    return 0;
}

//define sub-function
int random(int a, int b) {
    return a + rand() % (b - a + 1);
}

int getChoose(int a, int b) {
    int num;
    string input;
    bool valid=false;
    while(valid!=true) {
        cout << "Lua chon cua ban (" << a << "-" << b << "):";
        cin >> input;
        if (input.find_first_not_of("0123456789")==string::npos) {
            num = stoi(input);
            if (num==0) {
                clear(2);
                menu();
                choose_menu();
            }
            if (num >= a && num <= b) {
                valid = true;
            } else cout << "Khong hop le! Vui long nhap lai" << endl;
        } else cout << "Khong hop le! Vui long nhap lai" << endl;
    }
    return num;
}

void clear(int n) {
    for (int i=0; i<n ;i++) {
        cout << endl;
    }
}

//define function
void menu() {
    cout << "======== MENU ========" << endl;
    cout << "1. Nhap san pham" << endl;
    cout << "2. Tim kiem san pham" << endl;
    cout << "3. Xoa san pham" << endl;
    cout << "4. Xuat don hang" << endl;
    cout << "5. Kiem tra kho" << endl;
    cout << "6. thoat" << endl;
}

void choose_menu() {
    int choose;
    choose = getChoose(1,6);
    if (choose==1) {
        nhapsp();
    }
    if (choose==2) {
        kiemsp();
    }
}
    

void nhapsp() {
    //Local Variable
    int choose;
    
    clear(2);
    cout << "--------Nhap san pham--------" << endl;
    cout << "1. Iphone" << "\t\t\t" << "2. Macbook" << endl;
    cout << "[0] tro ve menu" << endl;
    choose = getChoose(1,2);
    
    //Iphone
    if (choose == 1) {
        device="IP";
        clear(1);
        cout << "-----------Iphone-----------" << endl;
        cout << "1. Iphone7\t" << "2. IphoneX\t" << "3. Iphone13"<<  endl;
        cout << "[0] tro ve menu" << endl;
        choose=getChoose(1,3);
        if (choose==1) {
            getInfoIP("IP7","Iphone7");
        }
        if (choose==2) {
            getInfoIP("IPX","IphoneX");
        }
        if (choose==3) {
            getInfoIP("IP13","Iphone13");
        }
        
    }
    
    //Macbook
    if (choose == 2) {
        device="Mac";
        clear(1);
        cout << "-----------Macbook-----------" << endl;
        cout << "1. Macbook Air" << endl;
        cout << "2. Macbook Pro" << endl;
        cout << "[0] tro ve menu" << endl;
        choose=getChoose(1,2);
        if (choose==1) {
            getInfoMac("MacAir","Macbook Air");
        }
        if (choose==2) {
            getInfoMac("MacPro","Macbook Pro");
        }
    }
}



void getQuantity(string device, string type, string color, string ram, int quantity){
    ifstream ifs("/Users/macos/C++/Project/Project/data.json");
    json j = json::parse(ifs);
    ifs.close();
    int store = j[device][type][color][ram];
    j[device][type][color][ram]=quantity + store;
    ofstream ofs("/Users/macos/C++/Project/Project/data.json");
    ofs << j.dump(4);
    ofs.close();
}

string getChar(string str, int start, int end){
    return str.substr(start, end);
}

void getInfoIP (string nameType, string name){
    string hold;
    type=nameType;
    clear(1);
    cout << "-----------" << name << "-----------" << endl;
    cout << "~Chon mau:" << endl;
    cout << "1. black\t\t" << "2. White\t" << "3. Purple" << endl;
    cout << "[0] tro ve menu" << endl;
    cout << "Lua chon cua ban: ";
    chooseColor=getChoose(1, 3);
    if (chooseColor==1) color="black";
    if (chooseColor==2) color="white";
    if (chooseColor==3) color="purple";
    cout << "~Chon dung luong ram:" << endl;
    cout << "1. 2GB" << "\t\t\t" << "2. 4GB" << endl;
    cout << "[0] tro ve menu" << endl;
    cout << "Lua chon cua ban: ";
    chooseRam=getChoose(1, 2);
    if (chooseRam==1) ram="02GB";
    if (chooseRam==2) ram="04GB";
    cout << "~Nhap so luong san pham (toi da 999) " << endl;
    quantity=getChoose(1, 999);
    getQuantity(device, type, color, ram, quantity);
    writeSeriIP(device, type, color, ram, quantity);
    cout << "~~~Nhap san pham thanh cong~~~" << endl;
    cout << "Nhan [0] de tro lai menu" << endl;
    cout << "Nhan [Enter] de tiep tuc" << endl;
    cin.get();
    cin.get();
    nhapsp();
}

void getInfoMac (string nameType, string name){
    string hold;
    type=nameType;
    clear(1);
    cout << "-----------" << name << "-----------" << endl;
    cout << "~Chon mau:" << endl;
    cout << "1. Gold" << "\t\t\t" << "2. Gray" << endl;
    cout << "[0] tro ve menu" << endl;
    cout << "Lua chon cua ban: ";
    chooseColor=getChoose(1, 2);
    if (chooseColor==1) color="gold";
    if (chooseColor==2) color="gray";
    cout << "~Chon dung luong ram:" << endl;
    cout << "1. 8GB" << "\t\t\t" << "2. 16GB" << endl;
    cout << "[0] tro ve menu" << endl;
    cout << "Lua chon cua ban: ";
    chooseRam=getChoose(1, 2);
    if (chooseRam==1) ram="08GB";
    if (chooseRam==2) ram="16GB";
    cout << "Nhap so luong san pham (toi da 999) " << endl;
    quantity=getChoose(1, 999);
    getQuantity(device, type, color, ram, quantity);
    writeSeriMac(device, type, color, ram, quantity);
    cout << "~~~Nhap san pham thanh cong~~~" << endl;
    cout << "Nhan [0] de tro lai menu" << endl;
    cout << "Nhan [Enter] de tiep tuc" << endl;
    cin.get();
    cin.get();
    nhapsp();
}

void writeSeriIP(string device, string type, string color, string ram, int quantity) {
    ofstream write("/Users/macos/C++/Project/Project/seri.txt",ios::app);
    for (int i=0; i<quantity ; i++) {
        seri = getChar(device,0,1) + getChar(type,2,1) + getChar(color,0,3) + getChar(ram,0,2) + to_string(random(10000,32767));
        write << seri << endl;
    }
    write.close();
}

void writeSeriMac(string device, string type, string color, string ram, int quantity) {
    ofstream write("/Users/macos/C++/Project/Project/seri.txt",ios::app);
    for (int i=0; i<quantity ; i++) {
        seri = getChar(device,0,1) + getChar(type,3,1) + getChar(color,0,3) + getChar(ram,0,2) + to_string(random(10000,32767));
        write << seri << endl;
    }
    write.close();
}

void kiemsp() {
    int choose;
    int countSeri=0;
    string* arrSeri = new string;
    clear(2);
    cout << "--------Tim SP--------" << endl;
    cout << "1. Tim san pham bang ma sp" << endl;
    cout << "2.Loc san pham" << endl;
    choose=getChoose(1, 2);
    if (choose==1) {
        getSeriFromFile(arrSeri, countSeri);
        findBySeri(arrSeri, countSeri);
    }
    if (choose==2) {
        
    }
}

void getSeriFromFile (string* arrSeri, int& countSeri) {
    string str;
    ifstream inFile("/Users/macos/C++/Project/Project/seri.txt");
    while(!inFile.eof()) {
        getline(inFile,str);
        arrSeri[countSeri] = str;
        countSeri++;
    }
}

void findBySeri (string* arrSeri, int& countSeri) {
    string strSeri;
    cout << "Nhap CHINH XAC ma san pham: ";
    cin >> strSeri;
    bool findFlags=false;
    for (int i=0; i<countSeri-1; i++) {
        if (arrSeri[i]==strSeri) findFlags=true;
    }
    if (findFlags==true) {
        cout << "Ton tai san pham" << endl;
    }
    if (findFlags==false) {
        cout << "Khong tim thay san pham" << endl;
    }
}

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <vector>

using namespace std;
using json = nlohmann::json;

//static variable

//sub function
int random(int a, int b);
int getChoose(int a, int b);
void clear(int n);
int continuee();

//function
void getQuantity(string& device, string& type, string& color, string& ram, int& quantity);
string getChar(string str, int start, int end);
void getInfoIP(string nameType, string name,string& device, string&type , string& color, string& ram);
void getInfoMac(string nameType, string name,string& device, string&type , string& color, string& ram);
void writeSeriIP(string& device, string& type, string& color, string& ram, int& quantity);
void writeSeriMac(string& device, string& type, string& color, string& ram, int& quantity);
void getSeriFromFile(string*& arrSeri, int& countSeri);
void findBySeri(string*& arrSeri, int& countSeri);
void decodeSeri(string& seri, string& deviceData, string& typeData, string& colorData, string& ramData);
void textData(json& data, const string& path);
void findByFilter();
void deleteSeri(string* arr,int& count, string& deviceData, string& typeData, string&colorData, string& ramData);
void deleteProduct();
void updateJson (string& deviceData, string& typeData, string& colorData, string& ramData);
void viewcart (vector<string>& list);
void addcart (vector<string>& list);
void deletecart (vector<string>& list);
string outQuantity(string s);
void orderOut (vector<string>& list);

//main function
void menu();
void choose_menu();
void nhapsp();
void kiemsp();
void xoasp();
void kho();
void giohang(vector<string> list);

vector<string> list;
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
        cout << "--> Lua chon cua ban (" << a << "-" << b << "): ";
        cin >> input;
        if (input.find_first_not_of("-0123456789")==string::npos) {
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

int continuee(){
    cout << "[0] Tro ve menu" << endl;
    cout << "[phim bat ki] Tiep tuc" << endl;
    cout << "--> Lua chon cua ban: ";
    string choose;
    cin >> choose;
    if (choose=="0") {
        clear(2);
        menu();
        choose_menu();
        return 0;
    } else return 1;
}

//define function
void menu() {
    cout << "======== MENU ========" << endl;
    cout << "1. Nhap san pham" << endl;
    cout << "2. Tim kiem san pham" << endl;
    cout << "3. Xoa san pham" << endl;
    cout << "4. Gio Hang" << endl;
    cout << "5. Kiem tra kho" << endl;
    cout << "6. thoat" << endl;
}

void choose_menu() {
    int chooseMenu;
    chooseMenu = getChoose(1,6);
    switch(chooseMenu) {
        case 1: nhapsp();
            break;
        case 2: kiemsp();
            break;
        case 3: xoasp();
            break;
        case 4: giohang(list);
            break;
        case 5: kho();
            break;
        case 6: break;
    }
}

void nhapsp() {
    //Local Variable
    int choose;
    string device,type,color,ram;
    
    clear(2);
    cout << "--------NHAP SAN PHAM--------" << endl;
    cout << "1. Iphone" << "\t\t\t" << "2. Macbook" << endl;
    cout << "[0] Tro ve menu" << endl;
    choose = getChoose(1,2);
    
    //Iphone
    if (choose == 1) {
        device="IP";
        clear(1);
        cout << "-----------IPHONE-----------" << endl;
        cout << "1. Iphone7\t" << "2. IphoneX\t" << "3. Iphone13"<<  endl;
        cout << "[0] Tro ve menu" << endl;
        choose=getChoose(1,3);
        if (choose==1) {
            getInfoIP("IP7","IPHONE 7",device,type,color,ram);
        }
        if (choose==2) {
            getInfoIP("IPX","IPHONE X",device,type,color,ram);
        }
        if (choose==3) {
            getInfoIP("IP13","IPHONE 13",device,type,color,ram);
        }
    }
    
    //Macbook
    if (choose == 2) {
        device="Mac";
        clear(1);
        cout << "-----------MACBOOK-----------" << endl;
        cout << "1. Macbook Air" << endl;
        cout << "2. Macbook Pro" << endl;
        cout << "[0] Tro ve menu" << endl;
        choose=getChoose(1,2);
        if (choose==1) {
            getInfoMac("MacAir","MACBOOK AIR",device,type,color,ram);
        }
        if (choose==2) {
            getInfoMac("MacPro","MACBOOK PRO",device,type,color,ram);
        }
    }
}

void getQuantity(string& device, string& type, string& color, string& ram, int& quantity){
    string path="";
    //open - read json file
    ifstream ifs("/Users/macos/C++/Project/Project/data.json");
    json j = json::parse(ifs); //convert json object to string
    ifs.close();
    //add data
    int store = j[device][type][color][ram];
    j[device][type][color][ram]=quantity + store;
    //write json file
    ofstream ofs("/Users/macos/C++/Project/Project/data.json");
    ofs << j.dump(4);
    ofs.close();
    //clear file textdata
    ofstream cls("/Users/macos/C++/Project/Project/textdata.txt",ios_base::trunc);
    cls.close();
    //update file textdata
    textData(j,path);
}

string getChar(string str, int start, int end){
    return str.substr(start, end);
}

void getInfoIP (string nameType, string name,string& device, string&type , string& color, string& ram){
    int quantity;
    int chooseRam;
    int chooseColor;
    type=nameType; //Type
    clear(1);
    cout << "-----------" << name << "-----------" << endl;
    cout << "Chon mau:" << endl;
    cout << "1. Black\t\t" << "2. White\t" << "3. Purple" << endl;
    cout << "[0] Tro ve menu" << endl;
    chooseColor=getChoose(1, 3);
    if (chooseColor==1) color="black";
    if (chooseColor==2) color="white";
    if (chooseColor==3) color="purple";
    clear(1);
    cout << "Chon dung luong ram:" << endl;
    cout << "1. 2GB" << "\t\t\t" << "2. 4GB" << endl;
    cout << "[0] Tro ve menu" << endl;
    chooseRam=getChoose(1, 2);
    if (chooseRam==1) ram="02GB";
    if (chooseRam==2) ram="04GB";
    clear(1);
    cout << "Nhap so luong san pham (toi da 999) " << endl;
    quantity=getChoose(1, 999);
    //add quantity - create seri
    getQuantity(device, type, color, ram, quantity);
    writeSeriIP(device, type, color, ram, quantity);
    clear(1);
    cout << "~~~~~Nhap san pham thanh cong~~~~~" << endl;
    clear(1);
    if (continuee()==1) nhapsp();
}

void getInfoMac (string nameType, string name,string& device, string&type , string& color, string& ram){
    int quantity;
    int chooseRam;
    int chooseColor;
    type=nameType; //Type
    clear(1);
    cout << "-----------" << name << "-----------" << endl;
    cout << "Chon mau:" << endl;
    cout << "1. Gold" << "\t\t\t" << "2. Gray" << endl;
    cout << "[0] Tro ve menu" << endl;
    chooseColor=getChoose(1, 2);
    if (chooseColor==1) color="gold";
    if (chooseColor==2) color="gray";
    clear(1);
    cout << "Chon dung luong ram:" << endl;
    cout << "1. 8GB" << "\t\t\t" << "2. 16GB" << endl;
    cout << "[0] Tro ve menu" << endl;
    chooseRam=getChoose(1, 2);
    if (chooseRam==1) ram="08GB";
    if (chooseRam==2) ram="16GB";
    clear(1);
    cout << "Nhap so luong san pham (toi da 999) " << endl;
    quantity=getChoose(1, 999);
    // add quantity - create seri
    getQuantity(device, type, color, ram, quantity);
    writeSeriMac(device, type, color, ram, quantity);
    clear(1);
    cout << "~~~~~Nhap san pham thanh cong~~~~~" << endl;
    clear(1);
    if (continuee()==1) nhapsp();
}

void writeSeriIP(string& device, string& type, string& color, string& ram, int& quantity) {
    string seri;
    ofstream write("/Users/macos/C++/Project/Project/seri.txt",ios::app);
    // Create seri
    for (int i=0; i<quantity ; i++) {
        seri = getChar(device,0,1) + getChar(type,2,1) + getChar(color,0,3) + getChar(ram,0,2) + to_string(random(10000,32767));
        write << seri << endl;
    }
    write.close();
}

void writeSeriMac(string& device, string& type, string& color, string& ram, int& quantity) {
    string seri;
    ofstream write("/Users/macos/C++/Project/Project/seri.txt",ios::app);
    // Create seri
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
    cout << "--------TIM SAN PHAM--------" << endl;
    cout << "1. Tim sp bang ma sp" << endl;
    cout << "2. Loc sp" << endl;
    cout << "[0] Tro ve menu" << endl;
    choose=getChoose(1, 2);
    if (choose==1) {
        clear(2);
        getSeriFromFile(arrSeri, countSeri);
        findBySeri(arrSeri, countSeri);
    }
    if (choose==2) {
        clear(2);
        findByFilter();
    }
    delete arrSeri;
}

void getSeriFromFile (string*& arrSeri, int& countSeri) {
    string str;
    ifstream inFile("/Users/macos/C++/Project/Project/seri.txt");
    while(!inFile.eof()) {   //check end file?
        getline(inFile,str);
        arrSeri[countSeri] = str;
        countSeri++;
    }
    inFile.close();
}

void findBySeri (string*& arrSeri, int& countSeri) {
    cout << "-------TIM SP BANG MA-------" << endl;
    string strSeri;
    string deviceData,typeData,colorData,ramData;
    cout << "--> Nhap CHINH XAC ma san pham: ";
    cin >> strSeri;
    bool findFlags=false;
    // check seri
    for (int i=0; i<countSeri; i++) {
        if (arrSeri[i]==strSeri) findFlags=true;
    }
    if (findFlags==true) {
        clear(1);
        cout << "~~~Da tim thay san pham~~~" << endl;
        cout << "Thong tin san pham: ";
        // decode seri
        decodeSeri(strSeri,deviceData,typeData,colorData,ramData);
        cout << deviceData << " - " << typeData << " - " << colorData << " - " << ramData << endl;
        clear(1);
        if (continuee()==1) {
            findBySeri(arrSeri,countSeri);
        }
    }
    if (findFlags==false) {
        clear(1);
        cout << "!!! Khong tim thay san pham !!!" << endl;
        clear(1);
        if (continuee()==1) {
            findBySeri(arrSeri,countSeri);
        }
    }
}

void decodeSeri(string& seri, string& deviceData, string& typeData, string& colorData, string& ramData) {
    if (seri!="") {
        deviceData=seri.substr(0,1);
        typeData=seri.substr(1,1);
        colorData=seri.substr(2,3);
        ramData=seri.substr(5,2);
        if ((deviceData=="I")) deviceData="IP";
        if (deviceData=="M") deviceData="Mac";
        if (typeData=="7") typeData="IP7";
        if (typeData=="X") typeData="IPX";
        if (typeData=="1") typeData="IP13";
        if (typeData=="A") typeData="MacAir";
        if (typeData=="P") typeData="MacPro";
        if (colorData=="bla") colorData="black";
        if (colorData=="pur") colorData="purple";
        if (colorData=="whi") colorData="white";
        if (colorData=="gra") colorData="gray";
        if (colorData=="gol") colorData="gold";
        if (ramData=="02") ramData="02GB";
        if (ramData=="04") ramData="04GB";
        if (ramData=="08") (ramData="08GB");
        if (ramData=="16") ramData="16GB";
    }
}

void textData(json& data, const string& path) {
    if (data.is_object()) {   // check is json object?
        for (auto it=data.begin() ; it!=data.end() ; it++) {   // for loop
            if (it.key()=="02GB" || it.key()=="04GB" || it.key()=="08GB" || it.key()=="16GB") {
                ofstream outfile("/Users/macos/C++/Project/Project/textdata.txt",ios::app);
                outfile << path << "/" + it.key() << "/" << it.value()<< endl;
                outfile.close();
                
            } else {
                textData(it.value(),path+"/"+it.key());   // recursion
            }
        }
    }
}

void findByFilter() {
    cout << "--------LOC SP--------" << endl;
    // get data from file textdata to array
    ifstream infile("/Users/macos/C++/Project/Project/textdata.txt");
    string* arr = new string;
    string str;
    int count=0;
    while(!infile.eof()) {   // check end of file?
        getline(infile,str);
        arr[count]=str;
        count++;
    }
    infile.close();
    
    int chooseDevice, chooseType, chooseColor, chooseRam;
    string device,type,color,ram;
    clear(1);
    cout << "Chon thiet bi: " << endl;
    cout << "1.IPhone\t" << "2.Macbook\t" << "3.Bo qua" << endl;
    cout << "[0] Tro ve menu" << endl;
    chooseDevice=getChoose(1,3);
    if (chooseDevice==1) {
        device="IP";
        clear(1);
        cout << "Chon dong san pham:" << endl;
        cout << "1.IPhone7\t" << "2.IPhoneX\t" << "3.IPhone13\t" << "4.Bo qua" << endl;
        cout << "[0] Tro ve menu" << endl;
        chooseType=getChoose(1,4);
        if (chooseType==1) type="IP7";
        if (chooseType==2) type="IPX";
        if (chooseType==3) type="IP13";
        if (chooseType==4) type="";
        clear(1);
        cout << "Chon mau:" << endl;
        cout << "1.Black\t\t" << "2.White\t" << "3.Purple\t\t" << "4.Bo qua" << endl;
        cout << "[0] Tro ve menu" << endl;
        chooseColor=getChoose(1,4);
        if (chooseColor==1) color="black";
        if (chooseColor==2) color="white";
        if (chooseColor==3) color="purple";
        if (chooseColor==4) color="";
        clear(1);
        cout << "Chon dung luong ram:" << endl;
        cout << "1. 2GB\t\t" << "2. 4GB\t\t" << "3.Bo qua" << endl;
        cout << "[0] Tro ve menu" << endl;
        chooseRam=getChoose(1,3);
        if (chooseRam==1) ram="02GB";
        if (chooseRam==2) ram="04GB";
        if (chooseRam==3) ram="";
    }
    if (chooseDevice==2) {
        device="Mac";
        clear(1);
        cout << "1.Macbook Air\t\t" << "2.Macbook Pro\t\t" << "3.Bo qua" << endl;
        cout << "[0] Tro ve menu" << endl;
        chooseType=getChoose(1,3);
        if (chooseType==1) type="MacAir";
        if (chooseType==2) type="MacPro";
        if (chooseType==3) type="";
        clear(1);
        cout << "1.Gold\t\t" << "2.Gray\t" << "3.Bo qua" << endl;
        cout << "[0] Tro ve menu" << endl;
        chooseColor=getChoose(1,3);
        if (chooseColor==1) color="gold";
        if (chooseColor==2) color="gray";
        if (chooseColor==3) color="";
        clear(1);
        cout << "1. 8GB\t\t" << "2. 16GB\t\t" << "3.Bo qua" << endl;
        cout << "[0] Tro ve menu" << endl;
        chooseRam=getChoose(1,3);
        if (chooseRam==1) ram="08GB";
        if (chooseRam==2) ram="16GB";
        if (chooseRam==3) ram="";
    }
    if (chooseDevice==3) device="";
    bool flags=false;
    vector<string> listAvaiable;
    
    //find by filter
    for (int i=0; i<count ; i++) {
        if (outQuantity(arr[i])!="0") {
            if (arr[i].find(device)!=string::npos && arr[i].find(type)!=string::npos && arr[i].find(color)!=string::npos && arr[i].find(ram)!=string::npos) {
                listAvaiable.push_back(arr[i]);
                flags=true;
            }
        }
    }
    if (flags==true) {
        clear(1);
        cout << "Nhung san pham thoa man dieu kien:" << endl;
        cout << "(/ThietBi/DongSP/Mau/Ram/SoLuong)" << endl << endl;
        for (int i=0; i<listAvaiable.size();i++) {
            cout << listAvaiable[i] << endl;
        }
    } else {
        cout << "!!! Khong co SP nao phu hop thoa man !!!" << endl;
    }
    delete arr;  // detele array
    clear(1);
    if (continuee()==1) {
        findByFilter();
    }
}

void xoasp() {
    int choose;
    string deviceData,typeData,colorData,ramData;
    string* arr = new string;
    int count=0;
    clear(2);
    cout << "--------XOA SP--------" << endl;
    cout << "1. Xoa sp theo ma sp" << endl;
    cout << "2. Xoa nhieu sp ( xoa theo dong sp )" << endl;
    cout << "[0] Tro ve menu" << endl;
    choose=getChoose(1, 2);
    if (choose==1) {
        deleteSeri(arr,count,deviceData,typeData,colorData,ramData);
    }
    if (choose==2) {
        deleteProduct();
    }
    delete arr;
}

void deleteSeri(string* arr,int& count, string& deviceData, string& typeData, string&colorData, string& ramData){
    string str;
    string seriDelete;
    // check and get seri from user
    do {
        clear(1);
        cout << "Nhap ma sp can xoa:";
        cin >> seriDelete;
        if (seriDelete.size()<12 || seriDelete.size()>12) {
            cout << "!!! Ma SP khong ton tai !!!" << endl;
            clear(1);
            cout << "[Nhan bat ki] Tiep tuc" << endl;
            cout << "[0] Tro ve menu" << endl;
            string back;
            cin >> back;
            if (back=="0") {
                clear(2);
                menu();
                choose_menu();
            }
        }
    } while (seriDelete.size()<12 || seriDelete.size()>12);
    
    decodeSeri(seriDelete,deviceData,typeData,colorData,ramData);
    // get seri from file to array
    ifstream inFile("/Users/macos/C++/Project/Project/seri.txt");
    while(!inFile.eof()) {
        getline(inFile,str);
        arr[count] = str;
        count++;
    }
    inFile.close();
    // delete
    bool flags=false;
    ofstream write("/Users/macos/C++/Project/Project/export.txt",ios::app);
    for (int i=0; i<count;i++) {
        if (arr[i]==seriDelete) {
            flags=true;
            write << seriDelete << "-D" << endl;
            arr[i]="";
        }
    }
    write.close();
    // write to file after delete
    ofstream ofs("/Users/macos/C++/Project/Project/seri.txt",ios::ate);
    ofs << endl;
    for (int i=0; i<count; i++) {
        if (arr[i]!="") {
            ofs << arr[i] << endl;
        }
    }
    ofs.close();
    // check flags
    if (flags==true) {
        cout << "~~~~~Xoa thanh cong~~~~~" << endl;
        updateJson(deviceData,typeData,colorData,ramData);
        cout << "[Phim bat ki] Tro ve menu: ";
        string hold;
        cin >> hold;
        if (hold!="") {
            clear(2);
            menu();
            choose_menu();
        }
    } else {
        cout << "!!! Ma SP khong ton tai !!!" << endl;
        cout << "[Phim bat ki] Tro ve menu: ";
        string hold;
        cin >> hold;
        if (hold!="") {
            clear(2);
            menu();
            choose_menu();
        }
    }
}

void deleteProduct() {
    int chooseDevice, chooseType, chooseColor, chooseRam;
    string device,type,color,ram;
    string deviceData,typeData,colorData,ramData;
    clear(1);
    cout << "-------XOA SP-------" << endl;
    cout << "Chon thiet bi: " << endl;
    cout << "1.IPhone\t" << "2.Macbook\t" << endl;
    cout << "[0] Tro ve menu" << endl;
    chooseDevice=getChoose(1,2);
    if (chooseDevice==1) {
        device="IP";
        clear(1);
        cout << "Chon dong san pham:" << endl;
        cout << "1.IPhone7\t" << "2.IPhoneX\t" << "3.IPhone13\t" << endl;
        cout << "[0] Tro ve menu" << endl;
        chooseType=getChoose(1,3);
        if (chooseType==1) type="IP7";
        if (chooseType==2) type="IPX";
        if (chooseType==3) type="IP13";
        clear(1);
        cout << "Chon mau:" << endl;
        cout << "1.Black\t\t" << "2.White\t" << "3.Purple\t\t" << endl;
        cout << "[0] Tro ve menu" << endl;
        chooseColor=getChoose(1,3);
        if (chooseColor==1) color="black";
        if (chooseColor==2) color="white";
        if (chooseColor==3) color="purple";
        clear(1);
        cout << "Chon dung luong ram:" << endl;
        cout << "1. 2GB\t\t" << "2. 4GB\t\t" << endl;
        cout << "[0] Tro ve menu" << endl;
        chooseRam=getChoose(1,2);
        if (chooseRam==1) ram="02GB";
        if (chooseRam==2) ram="04GB";
    }
    if (chooseDevice==2) {
        device="Mac";
        clear(1);
        cout << "1.Macbook Air\t\t" << "2.Macbook Pro\t\t" << endl;
        cout << "[0] Tro ve menu" << endl;
        chooseType=getChoose(1,2);
        if (chooseType==1) type="MacAir";
        if (chooseType==2) type="MacPro";
        clear(1);
        cout << "1.Gold\t\t" << "2.Gray\t" << endl;
        cout << "[0] Tro ve menu" << endl;
        chooseColor=getChoose(1,2);
        if (chooseColor==1) color="gold";
        if (chooseColor==2) color="gray";
        clear(1);
        cout << "1. 8GB\t\t" << "2. 16GB\t\t" << endl;
        cout << "[0] Tro ve menu" << endl;
        chooseRam=getChoose(1,2);
        if (chooseRam==1) ram="08GB";
        if (chooseRam==2) ram="16GB";
    }
    ifstream ifs("/Users/macos/C++/Project/Project/data.json");
    json j = json::parse(ifs);
    if (j[device][type][color][ram]==0) {
        cout << "!!! Khong ton tai SP !!!" << endl;
        if (continuee()==1) {
            xoasp();
        }
    } else {
        j[device][type][color][ram]=0;
        ofstream ofs("/Users/macos/C++/Project/Project/data.json");
        ofs << j.dump(4);
        ofs.close();
        //clear file textdata
        ofstream cls("/Users/macos/C++/Project/Project/textdata.txt",ios_base::trunc);
        cls.close();
        string path="";
        // update textdata file
        textData(j,path);
        
        ifstream in("/Users/macos/C++/Project/Project/seri.txt");
        vector<string> serilist;
        string line;
        while(!in.eof()) {
            getline(in,line);
            serilist.push_back(line);
        }
        in.close();
        ofstream write("/Users/macos/C++/Project/Project/export.txt",ios::app);
        for (int i=0; i<serilist.size();i++) {
            
            decodeSeri(serilist[i], deviceData, typeData, colorData, ramData);
            if (deviceData==device && typeData==type && colorData==color && ramData==ram) {
                if (serilist[i]!="") {
                    write << serilist[i] << "-D" << endl;
                }
                serilist[i]="";
            }
        }
        
        ofstream out("/Users/macos/C++/Project/Project/seri.txt",ios::ate);
        out << endl;
        for (int i=0 ; i<serilist.size(); i++) {
            if (serilist[i]!="") {
                out << serilist[i] << endl;
            }
        }
        out.close();
        clear(1);
        cout << "~~~~~ Xoa thanh cong ~~~~~" << endl;
        if (continuee()==1) {
            xoasp();
        }
    }
    ifs.close();
}

void updateJson (string& deviceData, string& typeData, string& colorData, string& ramData) {
    // open - get object json
    ifstream ifs("/Users/macos/C++/Project/Project/data.json");
    json j = json::parse(ifs);
    ifs.close();
    // update quantity
    int quantity=j[deviceData][typeData][colorData][ramData];
    quantity-=1;
    j[deviceData][typeData][colorData][ramData]=quantity;
    // write to file after update
    ofstream ofs("/Users/macos/C++/Project/Project/data.json");
    ofs << j.dump(4);
    ofs.close();
    //clear file textdata
    ofstream cls("/Users/macos/C++/Project/Project/textdata.txt",ios_base::trunc);
    cls.close();
    string path="";
    // update textdata file
    textData(j,path);
}

void giohang(vector<string> list) {
    int choose;
    clear(2);
    cout << "--------GIO HANG--------" << endl;
    cout << "1. Xem gio hang" << endl;
    cout << "2. Them SP vao gio hang" << endl;
    cout << "3. Xoa SP khoi gio hang" << endl;
    cout << "4. Xuat don hang" << endl;
    cout << "[0] Tro ve menu" << endl;
    choose=getChoose(1, 4);
    if (choose==1) viewcart(list);
    if (choose==2) addcart(list);
    if (choose==3) deletecart(list);
    if (choose==4) orderOut(list);
}

void viewcart (vector<string>& list) {
    if (list.size()==0) {   // check cart list is clear?
        clear(1);
        cout << "-------XEM GIO HANG-------" << endl;
        cout << "!!! Chua co SP duoc chon !!!" << endl;
        clear(1);
        if (continuee()==1) {
            giohang(list);
        }
    } else {   // if cart list not clear
        clear(1);
        cout << "-------XEM GIO HANG-------" << endl;
        cout << "Danh sach SP da chon: " << endl;
        clear(1);
        for (int i=0,count=1; i<list.size();i++,count++) {
            cout << count << ". " << list[i] << endl;
        }
        if (continuee()==1) {
            giohang(list);
        }
    }
}

void addcart (vector<string>& list) {
    int quantity;
    int chooseDevice, chooseType, chooseColor, chooseRam;
    string device,type,color,ram;
    clear(1);
    cout << "-------THEM SP-------" << endl;
    cout << "Chon thiet bi: " << endl;
    cout << "1.IPhone\t" << "2.Macbook\t" << endl;
    cout << "[0] Tro ve menu" << endl;
    chooseDevice=getChoose(1,2);
    if (chooseDevice==1) {
        device="IP";
        clear(1);
        cout << "Chon dong san pham:" << endl;
        cout << "1.IPhone7\t" << "2.IphoneX\t" << "3.IPhone13\t" << endl;
        cout << "[0] Tro ve menu" << endl;
        chooseType=getChoose(1,3);
        if (chooseType==1) type="IP7";
        if (chooseType==2) type="IPX";
        if (chooseType==3) type="IP13";
        clear(1);
        cout << "Chon mau:" << endl;
        cout << "1.Black\t\t" << "2.White\t" << "3.Purple\t\t" << endl;
        cout << "[0] Tro ve menu" << endl;
        chooseColor=getChoose(1,3);
        if (chooseColor==1) color="black";
        if (chooseColor==2) color="white";
        if (chooseColor==3) color="purple";
        clear(1);
        cout << "Chon dung luong ram:" << endl;
        cout << "1. 2GB\t\t" << "2. 4GB\t\t" << endl;
        cout << "[0] Tro ve menu" << endl;
        chooseRam=getChoose(1,2);
        if (chooseRam==1) ram="02GB";
        if (chooseRam==2) ram="04GB";
    }
    if (chooseDevice==2) {
        device="Mac";
        clear(1);
        cout << "1.Macbook Air\t\t" << "2.Macbook Pro\t\t" << endl;
        cout << "[0] Tro ve menu" << endl;
        chooseType=getChoose(1,2);
        if (chooseType==1) type="MacAir";
        if (chooseType==2) type="MacPro";
        clear(1);
        cout << "1.Gold\t\t" << "2.Gray\t" << endl;
        cout << "[0] Tro ve menu" << endl;
        chooseColor=getChoose(1,2);
        if (chooseColor==1) color="gold";
        if (chooseColor==2) color="gray";
        clear(1);
        cout << "1. 8GB\t\t" << "2. 16GB\t\t" << endl;
        cout << "[0] Tro ve menu" << endl;
        chooseRam=getChoose(1,2);
        if (chooseRam==1) ram="08GB";
        if (chooseRam==2) ram="16GB";
    }
    // check quantity
    ifstream in("/Users/macos/C++/Project/Project/data.json");
    json j = json::parse(in);
    int defaultQuantity = j[device][type][color][ram]; // get default quantity
    if (defaultQuantity==0) {
        clear(1);
        cout << "!!! Khong ton tai SP !!!" << endl;
        clear(1);
        if (continuee()==1) {
            giohang(list);
        }
    } else {
        // check list cart
        string temp;
        string haveQuantity="";
        bool flags=false;
        for (int i=0; i<list.size(); i++) {
            // same ?
            if (list[i].find(device)!=string::npos && list[i].find(type)!=string::npos &&
                list[i].find(color)!=string::npos &&
                list[i].find(ram)!=string::npos) {
                flags=true;
                // get quantity avaiable
                temp=list[i].substr(list[i].length()-5,5);
                string p="0123456789";
                for (int i=0; i<temp.size();i++) {
                    if (p.find(temp[i])!=string::npos) {
                        haveQuantity+=temp[i];
                    }
                }
                // quantity avaiable with quantity default
                if (stoi(haveQuantity)<defaultQuantity) {
                    clear(1);
                    cout << "Nhap so luong (toi da " << defaultQuantity-stoi(haveQuantity) << "):" << endl;
                    quantity=getChoose(1, defaultQuantity-stoi(haveQuantity));
                    list[i]=device + "-" + type + "-" + color + "-" + ram + " (SL:" + to_string(quantity+stoi(haveQuantity)) + ")";
                    clear(1);
                    cout << "~~~~~ Them SP thanh cong ~~~~~" << endl;
                    if (continuee()==1) {
                        giohang(list);
                    }
                } else {
                    clear(1);
                    cout << "!!! SP het hang !!!" << endl;
                    if (continuee()==1) {
                        giohang(list);
                    }
                }
            }
        }
        if (flags==false) {
            // if not same
            clear(1);
            cout << "Nhap so luong (toi da " << defaultQuantity << "):" << endl;
            quantity=getChoose(1, defaultQuantity);
            // create string and push to cart
            string items = device + "-" + type + "-" + color + "-" + ram + " (SL:" + to_string(quantity) + ")";
            list.push_back(items);
            clear(1);
            cout << "~~~~~ Them SP thanh cong ~~~~~" << endl;
            if (continuee()==1) {
                giohang(list);
            }
        }
    }
    in.close();
}

void deletecart (vector<string>& list) {
    // show cart list
    clear(1);
    cout << "-------XOA SP-------" << endl;
    cout << "Danh sach SP da chon: " << endl;
    for (int i=0,count=1; i<list.size();i++,count++) {
        cout << count << ". " << list[i] << endl;
    }
    
    // choose device want to delete
    cout << endl << "Chon stt SP muon xoa: " << endl;
    cout << "[-1] Xoa tat ca" << endl;
    int dele;
    dele=getChoose(-1,(unsigned int)list.size());
    if (dele==-1) {  // delete all list
        list.clear();
        clear(1);
        cout << "~~~~~ Xoa thanh cong ~~~~~" << endl;
        if (continuee()==1) {
            giohang(list);
        }
    }
    // delete 1 device
    list.erase(list.begin()+dele-1);
    clear(1);
    cout << "~~~~~ Xoa thanh cong ~~~~~" << endl;
    if (continuee()==1) {
        giohang(list);
    }
}

void orderOut (vector<string>& list) {
    vector<string> order;
    if (list.size()==0) {
        clear(1);
        cout << "!!! Chua co SP nao duoc chon !!!" << endl;
        if (continuee()==1) {
            giohang(list);
        }
    } else {
        for (int j=0; j<list.size();j++) {
            //get quantity in cart list
            int count=1;
            string quantity;
            string temp=list[j].substr(list[j].length()-5,5);
            string p="0123456789";
            for (int i=0; i<temp.size(); i++) {
                if (p.find(temp[i])!=string::npos) {
                    quantity+=temp[i];
                }
            }
            // find seri in cart list
            ifstream ifs("/Users/macos/C++/Project/Project/seri.txt");
            while(!ifs.eof() && count<=stoi(quantity)) {
                bool flags=false;
                string str;
                getline(ifs,str);
                string seri= str.substr(0,7);
                for (int i=0; i<7;i++) {
                    if(list[j].find(seri[i])==string::npos) {
                        flags=true;
                    }
                }  // add seri to order list
                if (flags==false) {
                    order.push_back(str);
                    count++;
                }
            }
            ifs.close();
        }
        // get seri to temp array
        string* temp = new string;
        string line;
        ifstream infile("/Users/macos/C++/Project/Project/seri.txt");
        int p=0;
        while(!infile.eof()) {
            getline(infile,line);
            temp[p]=line;
            p++;
        }
        infile.close();
        ofstream write("/Users/macos/C++/Project/Project/export.txt",ios::app);
        // check temp array same with order list?
        for (int i=0; i<order.size();i++) {
            for (int j=0; j<p; j++) {
                if (order[i]==temp[j]) {
                    write << order[i] << "-O" << endl;
                    temp[j]=""; // delete
                }
            }
        }
        write.close();
        // update temp array to seri file after delete
        ofstream out("/Users/macos/C++/Project/Project/seri.txt");
        out << endl;
        for (int i=0; i<p;i++) {
            if (temp[i]!="") {
                out << temp[i] << endl;
            }
        }
        out.close();
        delete temp;
        // update to Json file after delete
        string deviceData, typeData, colorData, ramData;
        for (int i=0; i<order.size();i++) {
            decodeSeri(order[i], deviceData, typeData, colorData, ramData);
            updateJson(deviceData, typeData, colorData, ramData);
        }
        clear(1);
        cout << "~~~~~Xuat don hang thanh cong~~~~~" << endl;
        list.clear();
        order.clear();
        if (continuee()==1) {
            giohang(list);
        }
    }
}

string outQuantity(string s) {
    // function get quantity from string ( info device )
    string quantity="";
    string p="0123456789";
    if (s!="") {
        s=s.substr(s.length()-4,4);
        for (int i=0; i<s.size();i++) {
            if (p.find(s[i])!=string::npos) {
                quantity+=s[i];
            }
        }
    }
    return quantity;
}

void kho() {
    clear(2);
    cout << "--------KHO HANG--------" << endl;
    string line;
    string str;
    ifstream inp("/Users/macos/C++/Project/Project/textdata.txt");
    clear(1);
    cout << setw(17) << right << "Thong tin SP" << setw(25) << "So luong" << endl << endl;
    // edit info device before display
    for (int j=1; j<=26 ; j++) {
        string result;
        int count=0;
        string quantity;
        getline(inp,line);
        str=line.substr(1,line.length()-1);
        for (int i=0; i<str.length(); i++) {
            if (count==4) {
                result=result.erase(result.length()-1);
                break;
            }
            if (str[i]!=(char)'/') {
                result+=str[i];
            }
            if (str[i]==(char)'/') {
                result+=str[i];
                count++;
                result=result.replace(i, i, "-");
            }
        }
        quantity=outQuantity(line); // get quantity of divice
        cout << setw(2) << right << j << ". " << result << setw(10+24-(unsigned int)result.length()) << right << quantity << endl;
    }
    clear(1);
    cout << "[Nhan bat ki] Tro lai menu" << endl;
    string hold;
    cin >> hold;
    if (hold!="") {
        clear(2);
        menu();
        choose_menu();
    }
}

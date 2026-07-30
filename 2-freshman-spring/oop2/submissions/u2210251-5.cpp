#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Person {
private:
    string name, tel; 
public:
    Person(){}
    Person(string n, string t) {
        name = n;
        tel = t;
    }
    string getName() {
        return name;
    }
    string getTel() {
        return tel;
    }
    void setName(string name) {
        this->name = name;
    }
    void setTel(string tel) {
        this->tel = tel;
    }
};
int main(){
    string name, tel;
    Person objPer;
    int position;
    //specified position
    cout << "Enter the name of a person \n";
    cin >> name;
    cout << "Enter the telephone number of a person \n";
    cin >> tel;
    cout << "Enter the specified position \n";
    cin >> position;
    objPer.setName(name);
    objPer.setTel(tel);
    fstream file("contacts", ios::binary | ios::in | ios::out| ios::_Noreplace | ios::trunc);
    if (!file.is_open()) {
        file.open("contacts", ios::binary | ios::in | ios::out);
    }
    fstream tempFile("temp", ios::binary | ios::in | ios::out | ios::trunc);
    file.seekp((sizeof(objPer)*position), ios::beg);
    file.write((char*)&objPer, sizeof(objPer));
    file.close();
    //end
    //det tel num
    file.open("contacts", ios::binary | ios::in | ios::out | ios::_Noreplace | ios::trunc);
    if (!file.is_open()) {
        file.open("contacts", ios::binary | ios::in | ios::out);
    }
    cout << "Enter the telephone number: \n";
    cin >> tel;
    while (file.read((char*)&objPer, sizeof(objPer))) {
        if (objPer.getTel() == tel) {
            cout << "The name is: " << objPer.getName() << endl;
        }
    }
    file.close();
    //det name
    file.open("contacts", ios::binary | ios::in | ios::out | ios::_Noreplace | ios::trunc);
    if (!file.is_open()) {
        file.open("contacts", ios::binary | ios::in | ios::out);
    }
    cout << "Enter the name: \n";
    cin >> name;
    while (file.read((char*)&objPer, sizeof(objPer))) {
        if (objPer.getName() == name) {
            cout << "The phone number is: " << objPer.getTel() << endl;
        }
    }
    file.close();
    //delete a record
    file.open("contacts", ios::binary | ios::in | ios::out | ios::_Noreplace | ios::trunc);
    if (!file.is_open()) {
        file.open("contacts", ios::binary | ios::in | ios::out);
    }
    cout << "Which record you want to delete, send me a position number \n";
    cin >> position;
    while (file.read((char*)&objPer, sizeof(objPer))) {
        if (!(position-1 == file.tellg()/sizeof(objPer))) {
            tempFile.write((char*)&objPer, sizeof(objPer));
        }
    }
    file.close();
    remove("contacts");
    rename("temp", "contacts");
    system("pause");
    return 0;
}
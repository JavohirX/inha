#include<iostream>
#include<string>
#include "Triangle.h"
class Person{
private:
	std::string name;
	int age;
public:
	void display(){
		std::cout << "age: " << age << std::endl;
	}
	Person(){

	}
	Person(int a){
		age = a;
	}
};
class Records{
private:
	std::string name;
	float salary;
	std::string date_of_birth;
public:
	Records(){

	}
	Records(std::string name){
		this->name = name;
	}
	void setName(std::string name){
		this->name = name;
	}
	std::string getName(){
		return name;
	}
	void setSalary(float salary){
		this->salary = salary;
	}
	float getSalary(){
		return salary;
	}
	void setDOB(std::string DOB){//DOB = date of birth
		date_of_birth = DOB;
	}
	std::string getDOB(){
		return date_of_birth;
	}

};
int main(){
	//first task
	Person objPer(12);
	objPer.display();
	//second task
	double temp;
	Records objRec, *ptrRec;
	ptrRec = &objRec;
	objRec.setName("Javohir");
	objRec.setSalary(1000000);
	ptrRec->setDOB("12.12.1898");
	//3 task
	Triangle objTrig(0,0);
	std::cout << "Enter the hight of tringle: \n";
	std::cin >> temp;
	objTrig.setHeight(temp);
	std::cout << "Enter the base of tringle: \n";
	std::cin >> temp;
	objTrig.setBase(temp);
	std::cout <<"area: " << objTrig.getArea() << std::endl;
	std::cout <<"perimeter: " <<  objTrig.getBase() << std::endl;
	system("pause");
	return 0;
}
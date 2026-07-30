#include<iostream>
#include<string>
#include<fstream>
using namespace std;
class Staff {
protected:
	string name;
	int code;
public:
	Staff(int code, string name){
		this->code = code;
		this->name = name;
	}
	string getName() {
		return name;
	}
	int getCode() {
		return code;
	}
	void setName() {
		this->name = name;
	}
	void setCode() {
		this->code = code;
	}
};
class Education {
protected:
	string HPQ;//highest qualification qualification
public:
	string getHPQ() {
		return HPQ;
	}
	void setHPQ(string HPQ) {
		this->HPQ = HPQ;
	}
	Education(string HPQ) {
		this->HPQ = HPQ;
	}
};
class Teacher:public Staff,public Education {
private:
	string subject;
	int publication;
public:
	Teacher(int code, string name, string subject, int publication, string HPQ) :Staff(code, name), Education(HPQ) {
		this->subject = subject;
		this->publication = publication;
	}
	string getSubject() {
		return subject;
	}
	int getPublication() {
		return publication;
	}
	void setSubject(string subject) {
		this->subject = subject;
	}
	void setPublication(int publication) {
		this->publication = publication;
	}
};
class Officer:public Staff, public Education {
private:
	char grade;
public:
	char getGrade() {
		return grade;
	}
	void setGrade(char grade) {
		this->grade = grade;
	}
	Officer(int code, string name, char grade, string HPQ) :Staff(code, name), Education(HPQ) {
		this->grade = grade;
	}
};
class Typist:public Staff {
protected: 
	int speed;
public:
	void setSpeed(int speed) {
		this->speed = speed;
	}
	int getSpeed() {
		return speed;
	}
	Typist(int code, string name, int speed) : Staff(code, name) {
		this->speed = speed;
	}
};
class Regular:public Typist {
private:
	double monthlySalary;
public:
	double getMonthlySalary() {
		return monthlySalary;
	}
	void setMonthlySalary(double monthlySalary) {
		this->monthlySalary = monthlySalary;
	}
	Regular(int code, string name, int speed,double monthlySalary) :Typist(code, name, speed) {
		this->monthlySalary = monthlySalary;
	}
};
class Casual:public Typist {
private: 
	double dailyWages;
public:
	void setDailyWages(double dailyWages) {
		this->dailyWages = dailyWages;
	}
	double getDailyWages() {
		return dailyWages;
	}
	Casual(int code, string name, int speed, double dailyWages) : Typist(code, name, speed) {
		this->dailyWages = dailyWages;
	}
};
void firstProgram() {
	string subject, HPQ, name;
	int code, pulication, speed, userInput;
	double monthlySalary, dailyWages;
	char grade;
	cout << "1: Teacher\n2: Regular worker\n3: Casual worker\n4: officer\n5: exit \n";
	cin >> userInput;
	if (userInput == 1) {
		//teacher
		cout << "Enter the staff code: \n";
		cin >> code;
		cout << "Enter the staff name \n";
		cin >> name;
		cout << "Enter their subject \n";
		cin >> subject;
		cout << "Enter the number of their publication \n";
		cin >> pulication;
		cout << " Enter the highest qualification qualification \n";
		cin >> HPQ;
		Teacher teacher(code, name, subject, pulication, HPQ);
		cout << "Staff code: " << teacher.getCode() << endl;
		cout << "Staff name: " << teacher.getName() << endl;
		cout << "Subject: " << teacher.getSubject() << endl;
		cout << "Publication: " << teacher.getPublication() << endl;
		cout << "HPQ: " << teacher.getHPQ() << endl;
	}
	else if (userInput == 2) {
		//regular
		cout << "Enter the staff code: \n";
		cin >> code;
		cout << "Enter the staff name \n";
		cin >> name;
		cout << "Enter the typing speed \n";
		cin >> speed;
		cout << "Enter the monthly salary \n";
		cin >> monthlySalary;
		Regular regular(code, name, speed, monthlySalary);
		cout << "Staff code: " << regular.getCode() << endl;
		cout << "Staff name: " << regular.getName() << endl;
		cout << "Typing speed: " << regular.getSpeed() << endl;
		cout << "Monthly salary: " << regular.getMonthlySalary() << endl;
	}
	else if (userInput == 3) {
		//casual
		cout << "Enter the staff code: \n";
		cin >> code;
		cout << "Enter the staff name \n";
		cin >> name;
		cout << "Enter the typing speed \n";
		cin >> speed;
		cout << "Enter the daily wage \n";
		cin >> dailyWages;
		Casual casual(code, name, speed, dailyWages);
		cout << "Staff code: " << casual.getCode() << endl;
		cout << "Staff name: " << casual.getName() << endl;
		cout << "Typing speed: " << casual.getSpeed() << endl;
		cout << "Daily wage: " << casual.getDailyWages() << endl;
	}
	else if (userInput == 4) {
		//officer
		cout << "Enter the staff code: \n";
		cin >> code;
		cout << "Enter the staff name \n";
		cin >> name;
		cout << "Enter the grade \n";
		cin >> grade;
		cout << " Enter the highest qualification qualification \n";
		cin >> HPQ;
		Officer officer(code, name, grade, HPQ);
		cout << "Staff code: " << officer.getCode() << endl;
		cout << "Staff name: " << officer.getName() << endl;
		cout << "Grade: " << officer.getGrade() << endl; 
		cout << "HPQ: " << officer.getHPQ() << endl;
	}
	else {
		return;
	}
	firstProgram();
}
class Person {
protected:
	string name;
	int code;
public:
	Person(string name, int code) {
		this->name = name;
		this->code = code;
	}
};
class Account :public virtual Person {
protected:
	double pay;
public:
	Account(string name, int code, double pay) : Person(name, code) {
		this->pay = pay;
	}
	void setPay(double pay) {
		this->pay = pay;
	}
	double getPay() {
		return pay;
	}
};
class Admin :public virtual Person {
protected:
	int experience;	
public:
	Admin(string name, int code, int experience) : Person(name, code) {
		this->experience = experience;
	}
	void setExp(int exp) {
		experience = exp;
	}
	int getExp() {
		return experience;
	}
};
class Master : public Admin, public Account {
public:
	// Constructor for Master class
	Master(string name, int code, int experience, double pay) : Admin(name, code, experience), Account(name, code, pay) {}

	// Function to display the information of Master object
	void display() {
		cout << "Name: " << name << endl;
		cout << "Code: " << code << endl;
		cout << "Experience: " << experience << endl;
		cout << "Pay: " << pay << endl;
	}
};
void secondProgram() {
	string name;
	int code;
	int experience;
	double pay;
	cout << "Enter the name \n";
	cin >> name;
	cout << "Enter the code \n";
	cin >> code;
	cout << "Enter the experience \n";
	cin >> experience;
	cout << "Enter the pay \n";
	cin >> pay;
	Master master(name, code, experience, pay);
	master.display();
}
int main() {
	int userInput;
	cout << "1: first program\n2: second program \n";
	cin >> userInput;
	switch (userInput) {
	case 1:
		firstProgram();
		break;
	case 2:
		secondProgram();
		break;
	}
	system("pause");
	return 0;
}
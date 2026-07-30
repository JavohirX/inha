#include<iostream>
#include<string>
#include<fstream>
#include"stdlib.h"
#include <chrono>
#include <thread>
#include <ctime>
#include "Header.h"
using namespace std;
string testSelector();
void mainMenu();
//teachermenu
void profMainMenu();
class Question {
private:
	string question, * answer;
	int ansNum;
	char trueAns;
public:
	void setTrueAns(char trueAns) {
		this->trueAns = trueAns;
	}
	void answerInitializer(int ansNum) {// ALWAYS INITIALIZE THE ANSWER BEFORE GIVING VALUE TO IT
		answer = new string[ansNum];
	}
	void setQuestion(string question) {
		this->question = question;
	}
	void setAnswers(string answerOne, int i) {
		answer[i] = answerOne;
	}
	void setAnsNum(int ansNum) {
		this->ansNum = ansNum;
	}
	char getTrueAns() {
		return trueAns;
	}
	int getAnsNum() {
		return ansNum;
	}
	string* getAnswer() {
		return answer;
	}
	string getQuestion() {
		return question;
	}
};
void write(fstream& objFile, string test) {
	size_t testLen = test.size(); //size of the test is in testLen
	objFile.write((char*)&testLen, sizeof(testLen)); //giving to the file the testLen
	objFile.write(test.c_str(), testLen); //giving to the file the test itself, by using testLen as a sizeof the name
}
string read(fstream& objFile) {
	size_t testLen;
	objFile.read((char*)&testLen, sizeof(testLen));//we take the testLen from the file, testLen is for the size of the test
	std::string name(testLen, '\0'); //we create a string with a length testLen and all characters are '\0'
	objFile.read(&name[0], testLen);//we read the test from the file whose size is testLen
	return name;
}
void parser(string test, Question& obj) {
	int counter = 0, ansNum;
	string temp, tempAnsNum;
	char trueAns = test[1];
	obj.setTrueAns(trueAns);
	for (int i = 0; counter < 3; i++) {
		if (test[i] == '\"') {
			counter++;
		}
		if ((test[i] != '\"') && i > 2) {
			tempAnsNum += test[i];
		}
	}
	ansNum = stoi(tempAnsNum);
	obj.answerInitializer(ansNum);
	obj.setAnsNum(ansNum);
	counter = 0;

	for (int i = 0; counter < ansNum + 4; i++) {
		if ((test[i] == '\"') && (counter == 0)) {
			counter++;
			temp = "";
			continue;
		}
		if ((test[i] == '\"') && (counter == 1)) {
			counter++;
			temp = "";
			continue;
		}
		if ((test[i] == '\"') && (counter == 2)) {
			counter++;
			temp = "";
			continue;
		}
		if ((test[i] == '\"') && (counter == 3)) {
			obj.setQuestion(temp);
			counter++;
			temp = "";
			continue;
		}
		if ((test[i] == '\"') && (counter > 3)) {
			obj.setAnswers(temp, (counter - 4));
			counter++;
			temp = "";
			continue;
		}
		temp += test[i];
	}
}
void deleteLine(string testName, int line) {
	ifstream inputFile(testName);
	string tempName = "temp.txt";
	ofstream outputFile(tempName);
	int currentLine = 1;
	string currentContent;
	while (getline(inputFile, currentContent)) {
		if (currentLine != line) {
			outputFile << currentContent << endl;
		}
		currentLine++;
	}
	inputFile.close();
	outputFile.close();
	remove(testName.c_str());
	rename(tempName.c_str(), testName.c_str());
}
void appeals() {
	int choice;
	repeatAppeals:
	system("cls");
	string appeal, testName;
	fstream file;
	testName = testSelector();
	testName += "_APPEALS.txt";
	file.open(testName, ios::in | ios::out | ios::app);
	int k = 0;
	while (file) {
		getline(file, appeal);
		k++;
		if (appeal == "") { break; }
		appeal[8] = ' '; // here I replace the '*' with space in _APPEALS
		cout << appeal << endl;
		cout << "1: Delete and see the next \n2: Next \n3: Main menu";
		cin >> choice;
		cin.ignore();
		switch (choice) {
		case 1:
			deleteLine(testName, k);
			break;
		case 3:
			goto repeatAppeals;
			break;
		default:
			continue;
		}
		appeal = "";
	}
	//
}
string testSelector() {
	int choice;
	system("cls");
	cout << "Choose the test by entering it's number \n";
	fstream testSets("testSets.txt", ios::in | ios::out | ios::app);
	string testName, year = "";
	int k = 0;
	while (testSets) {
		getline(testSets, testName);
		k++;
		if (testName == "") {
			break;
		}
		for (int i = 0; i < 4; i++) {
			year += testName[i];
		}
		if (getYear() == year) {
			cout << k << ". ";
			cout << testName << endl;
		}
		year = "";
		testName = "";
	}
	cin >> choice;
	cin.ignore();
	testSets.close();
	testSets.open("testSets.txt", ios::in | ios::out | ios::app);
	for (int i = 0; i < choice; i++) {
		getline(testSets, testName);
	}
	testSets.close();
	return testName;
}
void tResult() {
	repeatTResult: // label for goto
	system("cls");
	string testName, resultsRow;
	int choice;
	testName = testSelector();
	testName += "_RESULTS.txt";
	fstream results;
	results.open(testName, ios::in | ios::out | ios::app);
	int k = 0;
	while (results) {
		getline(results, resultsRow);
		k++;
		if (resultsRow == "") { break; }
		resultsRow[8] = ' ';//here I replace the '*' with space in _RESULTS
		cout << resultsRow << endl;
		resultsRow = "";
	}
	cout << "1:See another test result \n2: Main menu\n";
	cin >> choice;
	cin.ignore();
	switch (choice) {
	case 1:
		goto repeatTResult;// calling gotot to do tResult from the beginning again
		break;
	default:
		return;
	}
}
void createTest() {
	system("cls");
	string *answer, question, test = "", temp, testSetName, rules, temp1; //test conists of one question and several options
	int ansNum, userInput, testsNum, testDuration, testsToShow;
	char trueAns, userAnswer;
	cout << "Enter the name of the test set you want to create (e.g. math 101) \n";
	getline(cin, testSetName);
	temp1 = getYear();
	temp1 += '_';
	temp1 += testSetName;
	testSetName = temp1;
	cout << "How many test will there be? \n";
	cin >> testsNum;
	cin.ignore();
	cout << "How many of the test we will give to the user? \n";
	cin >> testsToShow;
	cin.ignore();
	cout << "How long will test last(int minutes)? \n";
	cin >> testDuration; // in minutes
	cin.ignore();
	cout << "Enter rules or info about test to show it to the student before the test \n";
	getline(cin, rules);
	fstream file(testSetName, ios::binary | ios::in | ios::out | ios::trunc);
	file.write((char*)&testsNum, sizeof(int));
	for (int i = 0; i < testsNum; i++) {
		cout << "Enter the question \n";
		getline(cin, question);
		if (i == 0) {
			cout << "How many options will it have? \n";
			cin >> ansNum;
			cin.ignore();
		}
		answer = new string[ansNum];
		cout << "Enter the answers below: \n";
		for (int i = 0; i < ansNum; i++) {
			cout << char(97 + i) << ") ";
			getline(cin, answer[i]);
			cout << endl;
		}
		cout << "Enter the letter of the right answer(e.g. enter c) \n";
		getline(cin, temp1);
		trueAns = temp1[0];
		test = "\"" + string(1, trueAns) + "\"" + to_string(ansNum) + "\"" + question + "\"";
		for (int i = 0; i < ansNum; i++) {
			test += answer[i] + "\"";
		}
		write(file, test);
	}
	file.close();
	ofstream testList;
	testList.open("testSets.txt", ios::app);
	testList << testSetName << endl;
	testList.close();
	ofstream testInfo;
	testInfo.open("info.txt", ios::app);
	testInfo << testDuration << endl;
	testInfo << testsToShow << endl;
	testInfo << rules << endl;
	testInfo.close();
	cout << "1: Create another test\n2: Main menu\n";
	cin >> userInput;
	cin.ignore();
	switch (userInput) {
	case 1:
		createTest();
		break;
	default:
		return;
	}
}
void profMainMenu() {
	system("cls");
	int userInput;
	while (true) {
		cout << "Choose one of them by sending corresponding number: \n";
		cout << "1: Create test \n";
		cout << "2: Test results \n";//test reuslts of students
		cout << "3: Appeals \n";
		cout << "4: Back \n";
		cout << "5: Exit \n";
		cin >> userInput;
		cin.ignore();
		switch (userInput) {
		case 1:
			createTest();
			break;
		case 2:
			tResult();
			break;
		case 3:
			appeals();
			break;
		case 4:
			mainMenu();
			break;
		case 5:
			return;
			break;
		default:
			return;
		}
	}
}
//main menu
class User {
public:
	char id[9], password[16];
	bool isProf;
};
void mainMenu() {
	char id[9], password[16];
	int choice;
	bool isProf;
	User user;
	fstream file;
	bool exist = false;
	firstMenu:
	cout << "1: Sign up \n2: Log in \n";
	cin >> choice;
	cin.ignore();
	system("cls");
	switch (choice) {
	case 1:
		cout << "id: ";
		cin >> id;
		cin.ignore();
		cout << "password (max 16 symbols): ";
		cin >> password;
		cin.ignore();
		system("cls");
		cout << "1: I'm a student \n2: I'm a professor \n";
		cin >> choice;
		cin.ignore();
		if (choice == 1) {
			isProf = false;
		}
		else {
			isProf = true;
		}
		file.open("users", ios::binary | ios::in | ios::out);
		file.seekg(0, ios::beg);
		file.seekp(0, ios::beg);
		if (!file.is_open()) {
			file.open("users", ios::binary | ios::in | ios::out | ios::trunc);
			file.seekg(0, ios::beg);
			file.seekp(0, ios::beg);
		}
		while (file.read((char*)&user, sizeof(user))) {
			if ((!strcmp(user.id, id)) && !strcmp(user.password, password)) {
				system("cls");
				cout << "Your account already exist, logging you in... \n";
				this_thread::sleep_for(chrono::seconds(2));
				exist = true;
				break;
			}
		};
		file.close();
		file.open("users", ios::binary | ios::in | ios::out);
		if (!file.is_open()) {
			file.open("users", ios::binary | ios::in | ios::out | ios::trunc);
			file.seekg(0, ios::beg);
			file.seekp(0, ios::beg);
		}
		system("cls");
		if (exist == true) {
			if (user.isProf == true) {
				profMainMenu();
			}
			else {
				mainStudentMenu();
			}
		}
		else {
			file.seekg(0, ios::end);
			file.seekp(0, ios::end);
			strcpy_s(user.id, id);
			strcpy_s(user.password, password);
			user.isProf = isProf;
			file.write((char*)&user, sizeof(user));
			system("cls");
			cout << "You are signed in! \n";
			if (user.isProf == true) {
				profMainMenu();
			}
			else {
				mainStudentMenu();
			}
		}
		break;
	case 2:
		cout << "id: ";
		cin >> id;
		cin.ignore();
		cout << "password (max 16 symbols): ";
		cin >> password;
		cin.ignore();
		system("cls");
		file.open("users", ios::binary | ios::in | ios::out);
		if (!file.is_open()) {
			file.open("users", ios::binary | ios::in | ios::out | ios::trunc);
		}
		file.seekg(0, ios::beg);
		file.seekp(0, ios::beg);
		while (file.read((char*)&user, sizeof(user))) {
			if ((!strcmp(user.id, id)) && (!strcmp(user.password, password))) {
				system("cls");
				cout << "Logging you in... \n";
				this_thread::sleep_for(chrono::seconds(2));
				system("cls");
				exist = true;
				break;
			}
		};
		file.close();
		if (exist == true) {
			if (user.isProf == true) {
				profMainMenu();
			}
			else {
				mainStudentMenu();
			}
		}
		else {
			cout << "Couldn't find you, please try to sign up \n";
			goto firstMenu; // calling goto label
		}
		break;
	}
}

int main() {
	mainMenu();
	system("pause");
	return 0;
}
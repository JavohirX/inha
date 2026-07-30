#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <fstream>
#include<algorithm>
using namespace std;

int prog, start, studentID = 2210257;
string answer, appealText;

void mainStudentMenu();
void showAllTests();
void previosYearsTests();

class Test {
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
	string getAnswer(int i) {
		return answer[i];
	}
	string getQuestion() {
		return question;
	}
};


void parser(string test, Test& obj) {
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

int getAnsNum(string test, Test& obj) {
	int counter = 0, ansNum;
	string tempAnsNum;
	for (int i = 0; counter < 3; i++) {
		if (test[i] == '\"') {
			counter++;
		}
		if ((test[i] != '\"') && i > 2) {
			tempAnsNum += test[i];
		}
	}
	ansNum = stoi(tempAnsNum);
	return ansNum;
}

int getTime() {
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	int time = newtime.tm_min * 60 + newtime.tm_hour * 3600 + newtime.tm_sec;
	return time;
}
//get time (now)


string getYear() {
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	int time = newtime.tm_year;
	return to_string(time + 1900);
}


void myPreviousResult() {
result:
	fstream testFile("testSets.txt", ios::in | ios::out);
	string testName, testFileName;
	string str;
	string id;
	while (testFile) {
		getline(testFile, testName);
		if (testName == "") {
			break;
		}

		testFileName = testName + "_RESULT.txt";

		fstream test(testFileName, ios::in | ios::out);
		while (getline(test, str)) {
			if (str == "") {
				break;
			}
			for (int k = 0; k < 7; k++) {
				id += str[k];
			}

			if (id == to_string(studentID)) {
				cout << testName << ": " << str << endl;
			}

			str = "";
			id = "";
		}


		testName = "";
	}


	cout << "\n1.Back" << endl;
	cin >> prog;
	if (prog == 1) {
		mainStudentMenu();
	}
	else {
		goto result;
	}

}




void afterExam(int correct, int numberOfQuestion, string nameOfFile, int time, int numberOfShowQuestion) {
	int end = getTime();

	if ((end - start) > time * 60) {
		cout << "Fail" << endl;
	}
	else {
		cout << "time: " << (end - start) / 60 << " minutes" << endl;
		cout << "Result: " << correct << " / " << numberOfShowQuestion << endl;
		string send;
		string nameFile;
		string resultFile;

		resultFile = nameOfFile + "_RESULT.txt";
		fstream result;
		result.open(nameFile, ios::binary | ios::in | ios::out);
		if (!result.is_open()) {
			result.open(nameFile, ios::binary | ios::in | ios::out | ios::trunc);
		}
		result.seekg(0, ios::end);
		result.seekp(0, ios::end);
		send = to_string(studentID) + "*" + to_string(correct) + "/" + to_string(numberOfShowQuestion);
		result << send << endl;
		result.close();
		cout << "\n******************************\nWrite a appeal if you want" << endl;
		getline(cin, appealText);

		nameFile = nameOfFile + "_APPEALS.txt";

		fstream appeal;
		appeal.open(nameFile, ios::binary | ios::in | ios::out);
		if (!appeal.is_open()) {
			appeal.open(nameFile, ios::binary | ios::in | ios::out | ios::trunc);
		}

		send = to_string(studentID) + " " + appealText;
		appeal << send << endl;
		appeal.close();

		system("cls");

		mainStudentMenu();
	}
}
// appeal after Exam and result

void exam(string nameOfFile, int time, int numberOfShowQuestion) {
	int* arr = new int[numberOfShowQuestion];
	string studentAns;
	string trues = "";
	int correct = 0;
	start = getTime();
	int numberOfQuestion;
	Test t;

	fstream calc(nameOfFile, ios::binary | ios::in | ios::out);

	calc.read((char*)&numberOfQuestion, sizeof(int));

	int n = sizeof(arr) / sizeof(arr[0]);

	srand((unsigned)std::time(NULL));



	for (int l = 0; l < numberOfShowQuestion; l++) {
		int p = 0;
		while (p == 0) {
			arr[l] = rand() % numberOfQuestion;
			int o = 0;

			for (int u = 0; u < l; u++) {
				if (arr[u] == arr[l]) {
					o = 1;
				}
			}
			if (o == 0) {
				p = 1;
			}
		}

	}



	sort(arr, arr + n + 1);

	for (int l = 0; l < numberOfQuestion; l++) {

		size_t testLen;
		calc.read((char*)&testLen, sizeof(testLen));
		string test(testLen, '\0');
		calc.read(&test[0], testLen);
		parser(test, t);


		for (int y = 0; y < numberOfShowQuestion; y++) {
			if (l == arr[y]) {
			question:
				cout << t.getQuestion() << endl;

				for (int a = 0; a < getAnsNum(test, t); a++) {
					cout << char(97 + a) << ") ";
					cout << t.getAnswer(a) << endl;
				}

				cin >> studentAns;
				cin.ignore();

				if (studentAns.length() > 1) {
					cout << "enter inly 1 character" << endl;
					goto question;
				}

				if (studentAns[0] == t.getTrueAns()) {
					correct++;
				}
				cout << (((time * 60) - (getTime() - start)) / 60) << " minutes" << endl;
			}
		}




	}

	calc.close();

	afterExam(correct, numberOfQuestion, nameOfFile, time, numberOfShowQuestion);

}
//exam

void  preExam(string nameOfFile, int fileId, int where) {
	string rules, rule;
	int time;
	int numberOfShowQuestion;
	int i = 0;

	ifstream allRules("INFO.txt");

	while (getline(allRules, rule)) {
		if (i == fileId * 3) {
			time = stoi(rule);
		}
		if (i == fileId * 3 + 1) {
			numberOfShowQuestion = stoi(rule);
		}
		if (i == fileId * 3 + 2) {
			rules = rule;
			break;
		}
		i++;
	}

	allRules.close();
	system("cls");

	cout << "Rules of " << nameOfFile << " Test: \nTime: " << time << " minutes \n" << rules << endl;
	cout << "1. Start test \n2. Back\n" << endl;

	cin >> prog;
	switch (prog) {
	case 1: {
		system("cls");
		exam(nameOfFile, time, numberOfShowQuestion);
	}; break;
	case 2: {
		if (where == 0) {
			showAllTests();
		}
		else {
			previosYearsTests();
		}

	}; break;
	}

}
//rules of Exam


void previosYearsTests() {
	system("cls");
	string nameOfFile;
	string test, year;
	int select;
	int i = 1, back = 0;
	ifstream allTest("testSets.txt");

	while (allTest) {
		getline(allTest, test);
		if (test == "") {
			break;
		}
		for (int k = 0; k < 4; k++) {
			year += test[k];
		}

		if (year != getYear()) {
			cout << i << ". ";
			cout << test << endl;
		}

		year = "";
		i++;
		test = "";
	}

	back = i;
	allTest.close();
	cout << back << ". ";
	cout << "back" << endl;

	cin >> select;


	ifstream Test("testSets.txt");
	i = 0;

	while (getline(Test, test)) {
		if (i == select - 1) {
			nameOfFile = test;
			break;
		}
		if (test == "") {
			break;
		}
		test = "";
		i++;
	}

	Test.close();

	if (i >= back - 1) {
		mainStudentMenu();
	}


	preExam(nameOfFile, select - 1, 1);


}

void showAllTests() {
	system("cls");
	string nameOfFile;
	string test, year;
	int select;
	int i = 1, back = 0;
	ifstream allTest("testSets.txt");

	while (allTest) {
		getline(allTest, test);
		if (test == "") {
			break;
		}
		for (int k = 0; k < 4; k++) {
			year += test[k];
		}

		if (year == getYear()) {
			cout << i << ". ";
			cout << test << endl;
		}

		year = "";
		i++;
		test = "";
	}

	back = i;
	allTest.close();
	cout << back << ". ";
	cout << "back" << endl;

	cin >> select;


	ifstream Test("testSets.txt");
	i = 0;

	while (getline(Test, test)) {
		if (i == select - 1) {
			nameOfFile = test;
			break;
		}
		if (test == "") {
			break;
		}
		test = "";
		i++;
	}

	Test.close();

	if (i >= back - 1) {
		mainStudentMenu();
	}


	preExam(nameOfFile, select - 1, 0);
}

void mainStudentMenu() {
	int prog;
	string sub;

	cout << "Choose the operation: \n1. Tests \n2. Last years tests \n3. My previous results \n4. Exit \n";
	cin >> prog;


	switch (prog) {
	case 1: {
		showAllTests();
	}; break;
	case 2: {
		previosYearsTests();
	}; break;
	case 3: {
		myPreviousResult();
	}; break;
	case 4: {
		exit;
	}; break;
	default: mainStudentMenu(); break;
	}
}
//operation 

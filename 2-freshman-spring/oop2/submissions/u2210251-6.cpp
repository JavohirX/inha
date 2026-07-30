#include<iostream> 
#include<string> 
using namespace std;
//first 
class Publication {
protected:
    string title;
    float price;
public:
    void setTitle(string title) {
        this->title = title;
    }
    void setPrice(float price) {
        this->price = price;
    }
    string getTitle() {
        return title;
    }
    float getPrice() {
        return price;
    }
};
class Book : public Publication {
private:
    int pageCount;
public:
    void setPageCount(int pageCount) {
        this->pageCount = pageCount;
    }
    float getPageCount() {
        return pageCount;
    }
};
class Tape : public Publication {
private:
    float playTime;
public:
    void setPlayTime(float playTime) {
        this->playTime = playTime;
    }
    float getPlayTime() {
        return playTime;
    }
};
void firstProgram() {
    system("cls");
    string strTemp;
    float flTemp;
    Book objBook;
    Tape objTape;
    int intTemp;
    cout << "Enter the title \n";
    cin >> strTemp;
    objBook.setTitle(strTemp);
    cout << "Enter the price \n";
    cin >> flTemp;
    objBook.setPrice(flTemp);
    cout << "Enter the page count \n";
    cin >> intTemp;
    objBook.setPageCount(intTemp);
    cout << "Enter the play time \n";
    cin >> flTemp;
    objTape.setPlayTime(flTemp);
    cout << "----------------------- \n";
    cout << "Title: " << objBook.getTitle() << endl;
    cout << "Price: " << objBook.getPrice() << endl;
    cout << "Page count: " << objBook.getPageCount() << endl;
    cout << "Play time: " << objTape.getPlayTime() << endl;
}
//second 
class Account {
protected:
    string name;
    int accNumber;
    bool accType; //0 is for curr 1 is for saving
public:
    void setName(string name) {
        this->name = name;
    }
    void setAccNumber(int accNumber) {
        this->accNumber = accNumber;
    }
    void setAccType(bool accType) {
        this->accType = accType;
    }
    string getName() {
        return name;
    }
    int getAccNumber() {
        return accNumber;
    }
    bool getAccType() {
        return accType;
    }
};
class currAcc : public Account {
private:
    float amount = 0;
    float penalty;
public:
	void deposit(float amount){
		this->amount += amount;
		cout << "Done! " << endl;
	}
	void balance(){
		cout << "Balance: " <<  amount << endl;
	}
	void withdraw(float amount){
		if(amount > this->amount){
			cout << "Operation can't be done. \n";
			return;
		}
		this->amount -= amount;
		cout << "Done! " << endl;
		if(this-> amount < 100){
			this->amount -= 2;
			penalty = 2;
			cout << "As a penalty we took 2USD from your account \n";
		}
	}
    void setAmount(float amount) {
        this->amount = amount;
    }
    void setPenalty(float penalty) {
        this->penalty = penalty;
    }
};
class savAccount : public Account {
private:
    float amount = 0;
public:
	void computeInterest(){
		cout << "Interest is: " << amount*0.04 << endl;
	}
	void deposit(float amount){
		this->amount += amount;
		cout << "Done! " << endl;
	}
	void balance(){
		cout << "Balance: " <<  amount << endl;
	}
	void withdraw(float amount){
		if(amount > this->amount){
			cout << "Operation can't be done. \n";
			return;
		}
		this->amount -= amount;
		cout << "Done! " << endl;
	}
    void setAmount(float amount) {
        this->amount = amount;
    }
    float getAmount() {
        return amount;
    }
};
void secondProgram() {
	currAcc objCurr;
	savAccount objAcc;
	int userInput;
	float temp;
	cout  << "Select the account, 1 for current account, 2 for saving account \n";
	cin >> userInput;
	switch(userInput){
		case 1:
			cout << "1: Enter a deposit" << endl;
			cout << "2: Display the balance" << endl;
			cout << "3: Withdraw money" << endl;
			cout << "4: Exit" << endl;
			cin >> userInput;
			switch(userInput){
				case 1:
					cout << "Enter the amount of money \n";
					cin >> temp;
					objCurr.deposit(temp);
					break;
				case 2:
					objCurr.balance();
					break;
				case 3:
					cout << "Enter the amount of withdrawal \n";
					cin >> temp;
					objCurr.withdraw(temp);
					break;
				case 4: 
					return;
					break;
			}
			break;
		case 2:
			cout << "1: Enter a deposit" << endl;
			cout << "2: Display the balance" << endl;
			cout << "3: Compute and deposit interest" << endl;
			cout << "4: Withdraw money" << endl;
			cout << "5: Exit" << endl;
			cin >> userInput;
			switch(userInput){
				case 1:
					cout << "Enter the amount of money \n";
					cin >> temp;
					objAcc.deposit(temp);
					break;
				case 2:
					objAcc.balance();
					break;
				case 3:
					objAcc.computeInterest();
					break;
				case 4: 
					cout << "Enter the amount of withdrawal \n";
					cin >> temp;
					objAcc.withdraw(temp);
					break;
				case 5:
					return;
					break;
			}
			break;
	}
}

int main() {
    short userInput;
    cout << "Enter 1 to choose program 1, and 2 to choose program 2: \n";
    cin >> userInput;
    switch (userInput) {
    case 1:
		firstProgram();
        break;
    case 2:
		secondProgram();
        break;
    }
    //firstProgram(); 
    secondProgram();
    system("pause");
    return 0;
}

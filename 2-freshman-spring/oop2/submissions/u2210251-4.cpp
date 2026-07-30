#include <iostream>
#include <string>
using namespace std;

class Books {
private:
	string bookName;
	double bookPrice;

public:
	Books() {}
	Books(string bookName, double bookPrice) {
		this->bookName = bookName;
		this->bookPrice = bookPrice;
	}
};



class Magazine {
private:
	string publicationMonth;
	Books obj;
	static int numberOfCopies;
	int numberOfPages;

public:
	void setDetails(string bookName, double bookPrice, string publicationMonth, int numberOfCopies, int numberOfPages) {
		Books obj(bookName, bookPrice);
		this->publicationMonth = publicationMonth;
		this->numberOfCopies = numberOfCopies;
		this->numberOfPages = numberOfPages;
	}

	void listMagazine() {
		cout << publicationMonth << endl << numberOfCopies << endl << numberOfPages;
	}

	friend void bookIssued(int bookIssued) {


		if (bookIssued > numberOfCopies) {
			cout << "It is imposible";
		}
		else {
			cout << "Number of copies remain: " << (numberOfCopies - bookIssued);
		}
	}



};







int main() {

	string temp;
	double price;
	int copies;
	string month;
	int pages;

	cout << "Name: " << endl;
	cin >> temp;

	cout << "Price: " << endl;
	cin >> price;

	cout << "number of Copies: " << endl;
	cin >> copies;

	cout << "number of Pages: " << endl;
	cin >> pages;

	cout << "publicationMonth: " << endl;
	cin >> month;


	Magazine m;
	m.setDetails(temp, price, month, copies, pages);

	m.listMagazine();

	system("pause");
	return 0;

}
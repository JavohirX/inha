#include <iostream>
int main() {
	// beginning of first assignment
	double taxPercent, salary;
	double tax, taxedSalary; // tax is for amount of taxes, not for percentages, taxedSalary is salary after taxation
	std::cout << "Enter the amount of salary \n";
	std::cin >> salary; //user inputs salary and if else chain calculate the values
	if (salary <= 1500) {
		taxPercent = 0;
		tax = salary*taxPercent/100;
		taxedSalary = salary - tax; 
	}
	else if (salary >= 1501 && salary <= 3000) {
		taxPercent = 10;
		tax = salary * taxPercent / 100;
		taxedSalary = salary - tax;
	}
	else if (salary >= 3001 && salary <= 5000) {
		taxPercent = 20;
		tax = salary * taxPercent / 100;
		taxedSalary = salary - tax;
	}
	else if (salary >= 1501 && salary <= 3000) {
		taxPercent = 10;
		tax = salary * taxPercent / 100;
		taxedSalary = salary - tax;
	}
	else if (salary > 5000) {
		taxPercent = 30;
		tax = salary * taxPercent / 100;
		taxedSalary = salary - tax;
	}
	std::cout << "Tax payable: " <<  tax << std::endl;
	std::cout << "Tax percent: " << taxPercent << "%" << std::endl;
	std::cout << "Income after taxation: " << taxedSalary << std::endl;
	// end of the first assignment
	// beginning of the second assignment
	int number;
	std::cout << "Enter some number \n";
	std::cin >> number;
	if (number == 0) {
		std::cout << "Number is 0";
	}
	else if (number > 0) {
		std::cout << "Number is positive";
	}
	else if (number < 0) {
		std::cout << "Number is negative";
	}
	// end of the second assignment
	// beginning of the third assignment
	double hardness, carcon, tenstren;
	int grade;
	std::cout << "Enter hardness \n";
	std::cin >> hardness;
	std::cout << "Enter amount of carbon content \n";
	std::cin >> carcon;
	std::cout << "Enter the tensile strength \n";
	std::cin >> tenstren;
	if (hardness > 50 && carcon < 0.7) {
		grade = 9;
	}
	else if (carcon < 0.7 && tenstren > 5600) {
		grade = 8;
	}
	else if (hardness > 50 && tenstren > 5600) {
		grade = 7;
	}
	else if (hardness > 50 || tenstren > 5600 || carcon < 0.7) {
		grade = 6;
	}
	else if (hardness < 50 && tenstren < 5600 && carcon > 0.7) {
		grade = 5;
	}
	std::cout << "grade: " << grade << std::endl;

	// end of the third assignment
	// beginning of the fourth assignment
	char userInput;
	std::cin >> userInput;
	if (userInput == toupper(userInput)) { // program just compares user input with itself but upper cased, if they are equal, then it was upper initially
		std::cout << "Character is uppercase \n";
	}
	else if (userInput == tolower(userInput)) {// same as comment above but with lower case
		std::cout << "Character is lowercase \n";
	}
	// end of the fourth assignment
	// beginning of the fifth assignment
	int num1, num2, aOperator;
	std::cout << "Enter first number \n"; 
	std::cin >> num1; // first number entered
	std::cout << "Enter second number \n";
	std::cin >> num2; // second number entered
	std::cout << "Enter 1 for addition, 2 for subtraction, 3 for division and 4 for multiplication \n";
	std::cin >> aOperator; // user chooses the operator tied to the numbers
	switch (aOperator) {
		case 1:
			std::cout << "first number + second number: " << num1 + num2 << std::endl;
			break;
		case 2:
			std::cout << "first number - second number: " << num1 - num2 << std::endl;
			break;
		case 3:
			std::cout << "first number / second number: " << num1 / num2 << std::endl;
			break;
		case 4:
			std::cout << "first number * second number: " << num1 * num2 << std::endl;
			break;
	}
	// end of the fifth assignment
	// beginning of the sixths assignment
	int year = 0;
	std::cout << "Enter the year: \n";
	std::cin >> year;
	if (year % 4 == 0 ) {
		if (year % 100 == 0 && year % 400 != 0) {
			std::cout << year << " is not a leap year \n";
		}
		else {
		std::cout << year << " is a leap year \n";
		}
	}
	// end of the sixths assignmetnt
}
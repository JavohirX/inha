#include <iostream>
#include <string>
using namespace std;
int main() {
	int num1, num2, fnum, temp, sum = 0, num = 0, userInputInt;
	std::string stringNum, userInput, stringTemp, upperUserInput;
	while (true) { // loop for the whole program to execute repeteadly
		std::cout << "Enter a number to choose a program(ex: 1 for program1, 2 for program2 etc.): \n";
		std::cout << "Enter 'exit' or 'quit' to stop program \n";
		std::cin >> userInput;
		if (userInput.length() == 1) {//if the length of the user input is 1, then it is probably a number, so the user selected one of the three actions
			userInputInt = std::stoi(userInput);// converting user input to int to use in switch-case
			switch (userInputInt) {
			case 1:
				//first program
				std::cout << "Enter first number: \n";
				std::cin >> num1;
				std::cout << "Enter the second number: \n";
				std::cin >> num2;
				if (num2 > num1) { //changing values of num1 and num2 if num2 > num1
					temp = num1;
					num1 = num2;
					num2 = temp;
				}
				for (int i = num2; i <= num1; i++) { // i = num2 will gain a value untill it's eual to num1
					sum += i;
				}
				std::cout << "Sum of the numbers from " << num2 << " to " << num1 << " is " << sum << std::endl;
				std::cout << "Second program: \n";
				break;
			case 2:
				//second program
				num1 = 0;
				num2 = 1;
				for (int i = 2; i < 20; i++) {// as we already know first two numbers loop starts with two
					fnum = num1 + num2;// it adds two numbers and gives its value to whichever original value were less
					if (num2 > num1) {
						num1 = fnum;
					}
					else {
						num2 = fnum;
					}
					sum += fnum;
				}
				std::cout << "Sum of the first 20 fibonacci numbers" << sum << std::endl;
				break;
				//third program
			case 3:
				std::cout << "Input number \n";
				std::cin >> stringNum;
				for (int i = 0; i < stringNum.length(); i++) {//creating a loop to take each digit of the number and add them together to num
					num += stringNum[i] - '0';
				}
				std::cout << "Sum of the digits: " << num << std::endl;
				break;
			default:
				std::cout << "I think you typed something wrong try again \n";
				main(); //calls the main function to restart program
			}
		}
		else {//if the length of the user input isn't 1, then he is probably trying to exit
			for (int i = 0; i < userInput.length(); i++) {//making the user input uppercase via loop and assigning it to a new variable
				upperUserInput += char(toupper(userInput[i]));
			}
			if (upperUserInput == "EXIT" || upperUserInput == "QUIT" || upperUserInput == "STOP") { //comparing upper user input to string constants
				break;
			}
			else {
				std::cout << "I think you typed something wrong try again \n";
				main(); //calls the main function to restart program
			}
		}
		system("pause");
	}
}
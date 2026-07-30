//U2210251 Xatamov Javohirbek
#include<iostream>
#include<string>

double factorial(double a) { // function for calculating factorial
	if (a == 1) {//cases for stopping the loop
		return 1;
	}
	if (a == 0) {// cases for stopping the loop
		return 1;
	}
	return a * factorial(a - 1); // it uses recursion to multiply a number by a number-1 in factorial
}

int main() {
	int num, pow;
	double sum = 0;
	std::string word, temp;
	//first task
	
	std::cout << "Enter the base of the number you want to raise \n";
	std::cin >> num;
	std::cout << "Now enter the power itself \n";
	std::cin >> pow;
	for (int i = 0; i < pow - 1; i++){//this loop multiplies the number pow-time, simulating raising to power
		num *= num;
	}
	std::cout << num << std::endl;
	
	//second task
	
	std::cout << "Enter some word or a number for its inverse \n";
	std::cin >> word;
	for (int i = 0; i < word.length(); i++){//this loop gives the value of the last char of a word to the first char of another word
		temp += word[word.length() - i - 1];
	}
	std::cout << temp << std::endl;
	
	//third task
	
	for (int i = 0; i <= 5; i++){//this loop is for creating 5 lines
		for (int j = 0; j < i; j++){//this one for outputiing stars depending on the size of previous loop
			std::cout << "*";
		}
		std::cout << std::endl;
	}
	//fourth task
	
	for (int i = 0; i < 5; i++){//this loop is for creating 5 lines
		for (int j = 0; j < 4 - i; j++){//this loop is for printing spaces, as i increases number of spaces in each line decreases
			std::cout << " ";
		}
		for (int k = 0; k < i + 1; k++){
			std::cout << "*";//this loop is for printing stars, it increases with i
		}
		std::cout << std::endl;
	}
	//fifth task
	
	for (int i = 1, k = 0; i <= 3; i++, k = 0){ //this loop is for creating 3 lines
		for (int j = 1; j <= 3 - i; j++){ //this one for spaces
			std::cout << " ";
		}
		while (k != 2 * i - 1){// and this for stars
			std::cout << "*";
			k++;
		}
		std::cout << std::endl;
	}
	//sixth task
	
	for (int i = 0; i < 5; i++) {// this loop is for creating 5 lines
		for (int j = 0; j < i + 1; j++) {// this one is for printing stars based on i
			std::cout << "*";
		}
		std::cout << std::endl;
	}
	for (int i = 5; i > 0; i--) {// this one is just the reverse of the previous loop
		for (int j = 0; j < i; j++) {
			std::cout << "*";
		}
		std::cout << std::endl;
	}
	//seventh task
	
	for (int i = 1; i <= 7; i++) {
		sum += i/factorial(i);//i is given to the function factorial and diveded by it 7 times, and summed to the variable sum
	}
	std::cout << sum << std::endl;

	system("pause");// it's for the program not to quit after execution, but wait until user response
	return 0;
}
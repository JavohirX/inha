#include<iostream>

int powerCalc(int num, int power) {
	if (power == 1) {//if statement checks whether one of the values is 1
		return num;
	}
	return num * pow(num, power - 1);// if not it uses recursion for multiplying num to num^(power-1)
}

int numSum(int n) {
	static int sum = 0;
	if (n == 1) { 
		return sum + 1;
	}
	return n + sum + numSum(n - 1);//add sum with n and all numbers less than n
}

int fibonacci(int amount, int x, int y, int index){// giving index as an argument to track the number of fibonachi executed
	if (index > amount) {
		if (x > y) {//outputing the final fibonacci number after index reached amount
			return x;
		}
		else {
			return y;
		}
	}
	if (x < y) {
		std::cout << x << std::endl;
		return(fibonacci(amount, x + y, y, ++index));// assighning to x sum of x and y
	}
	if (y < x) {
		std::cout << y << std::endl;
		return(fibonacci(amount, x, x + y, ++index));// assighning to y sum of x and y
	}
}

int gcd(int x, int y) {
	if (x == 0) {
		return y;
	}
	return gcd(y % x, x);//assigning less number to the bigger, and assigning their module less one
}

int function(int x ,int y) {
	if (y <= x) {
		return function(x - y, y) + 1;
	}
	else if (x < y) {
		return 0;
	}
}

int main() {
	int x, y, num, power, i = 0;
	//FIRST PROGRAM
	std::cout << "First program: \n\n";
	std::cout << "Enter some number, and its power, by hitting Enter between them: \n";
	std::cin >> num >> power;
	std::cout << powerCalc(num, power) << std::endl;
	//SECOND PROGRAM
	std::cout << "First program: \n\n";
	std::cout << "Enter some number to find the sum until the sum of natural numbers umtil os it \n";
	std::cin >> x;
	std::cout << numSum(x) << std::endl;
	//THIRD PROGRAM
	std::cout << "First program: \n\n";
	x = 1;
	y = 2;
	std::cout << "Enter the number of the fibonacci numbers \n";
	std::cin >> num;
	std::cout << fibonacci(num, x, y, i) << std::endl;
	//FOURTH PROGRAM
	std::cout << "First program: \n\n";
	std::cout << "Enter two number to find GCD by pressing Enter between them \n";
	std::cin >> x >> y;
	std::cout << gcd(x, y) << std::endl;
	//FIFTH PROGRAM
	std::cout << "First program: \n\n";
	std::cout << "Enter some two numbers for task 5 by pressing between them: \n";
	std::cin >> x >> y;
	std::cout << function(x, y);
	system("pause");

	return 0;
}
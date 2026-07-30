#include<iostream>
#include<cmath>
#include<string>

void complexes() {
	int ComplexNumbers[2][2];
	std::string strNum1 = "", strNum2 = "", strTemp = "", expr = "", userInput = "";
	int num1 = 0, num2 = 0, labelExpr = 0, isNegative = 0;
	for (int k = 0; k < 2; k++) {
		num1 = 0;
		num2 = 0;
		labelExpr = 0;
		isNegative = 0;
		strNum1 = "";
		strNum2 = "";
		strTemp = "";
		expr = "";
		userInput = "";
		std::cout << "Enter the " << k + 1 << "th complex number in this format 3 + 4i \n";
		std::cin >> userInput;
		for (int i = 0; i < userInput.length(); i++) {
			if (userInput[0] == '-') {
				isNegative = 1;
				continue;
			}
			if (userInput[i] == '+' || userInput[i] == '-') {
				expr = userInput[i];
				labelExpr = i;
			}
			strNum1 += userInput[i];

		}
		for (int i = labelExpr + 1; i < userInput.length(); i++) {
			strNum2 += userInput[i];
		}
		num1 = stoi(strNum1);
		num2 = stoi(strNum2);
		if (isNegative == 0) {
			ComplexNumbers[k][0] = num1;
		}
		else {
			ComplexNumbers[k][0] = -num1;
		}
		if (userInput[labelExpr] == '+') {
			ComplexNumbers[k][1] = num2;
		}
		if (userInput[labelExpr] == '-') {
			ComplexNumbers[k][1] = -num2;
		}
	}
	int g = 4;
	std::cout << "Our complex numbers: \n";
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			if (ComplexNumbers[i][j] > 0 && g % 2 == 1) {
				std::cout << "+" << ComplexNumbers[i][j] << "i \n";
				g++;
			}
			else if (g % 2 == 1) {
				std::cout << ComplexNumbers[i][j] << "i \n";
				g++;
			}
			else if (g % 2 == 0) {
				std::cout << ComplexNumbers[i][j];
				g++;
			}
		}
	}
	std::cout << "Their addition: \n";
	std::cout << ComplexNumbers[0][0] + ComplexNumbers[1][0];
	if (ComplexNumbers[0][1] + ComplexNumbers[1][1] > 0) {
		std::cout << "+" << ComplexNumbers[0][1] + ComplexNumbers[1][1] << "i" << std::endl;
	}
	else {
		std::cout << "-" << ComplexNumbers[0][1] + ComplexNumbers[1][1] << "i" << std::endl;
	}
	std::cout << "Their subtraction: \n";
	std::cout << ComplexNumbers[0][0] - ComplexNumbers[1][0];
	if (ComplexNumbers[0][1] - ComplexNumbers[1][1] > 0) {
		std::cout << "+" << ComplexNumbers[0][1] - ComplexNumbers[1][1] << "i" << std::endl;
	}
	else {
		std::cout << ComplexNumbers[0][1] - ComplexNumbers[1][1] << "i" << std::endl;
	}
}
void TriangleArea(double a, double b, double c, double *area) {
	*area = 0.25 * (sqrt((a + b + c) * (a + b - c) * (a - b + c) * (b + c - a)));
}
void swaper(int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = *a;
}
int main() {
	std::string userInput;
	int arrNum;
	// first program
	
	std::cout << "Enter something \n";
	std::cin >> userInput;
	int a = 1, length;
	char temp;
	for (int i = 0, j = userInput.length() - 1; j > 0; j--, i++) {
		if (userInput[i] != userInput[j]) {
			std::cout << "your input is not a palindrome \n";
			a = 0;
			break;
		}
	}
	if (a == 1) {
		std::cout << "Your number is palindrome \n";
	}
	//second program
	std::cout << "Enter a word \n";
	std::cin >> userInput;
	std::string* ptr = &userInput;
	length = (*ptr).length() - 1;
	for (int i = 0, j = length; j > length / 2; j--, i++) {
		temp = (*ptr)[i];
		(*ptr)[i] = (*ptr)[j];
		(*ptr)[j] = temp;
	}
	std::cout << (*ptr) << std::endl;
	//third program
	int a2 = 10;
	int b = 0;
	srand((unsigned)time(NULL));
	int (*arr1)[10] = new int[a2][10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			int random = rand() % 100;
			arr1[i][j] = random;
		}
	}
	std::cout << "Enter some number from 1 to 100 \n";
	std::cout << "and my program will find it from the array with randumly arranged numbers \n";
	std::cin >> arrNum;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (*(*(arr1 + i) + j) == arrNum) {
				std::cout << "Your number is located at a[" << i << "][" << j << "]" << std::endl;
				b = 1;
				goto labelA;
			}
		}
	}
	labelA:
	if (b == 0) {
		std::cout << "Sorry your number doesn't exist in our array \n";
	}
	//fourth program
	complexes();
	//fifth program
	double a1, b1, c1, area;
	std::cout << "Enter the first side of triangle \n";
	std::cin >> a1;
	std::cout << "Enter the second side of triangle \n";
	std::cin >> b1;
	std::cout << "Enter the third side of triangle \n";
	std::cin >> c1;
	TriangleArea(a1, b1, c1, &area);
	std::cout << "Area of triangle: " << area << std::endl;

	//sixth program
	
	int num1, num2;
	std::cout << "Enter the first number \n";
	std::cin >> num1;
	std::cout << "Enter the second number \n";
	std::cin >> num2;
	swaper(&num1, &num2);
	std::cout << "now they are swaped! yay! \n";
	
	//seventh program
	int size, maxNum = 0, maxNumIndex;
	std::cout << "Enter the size of 1D array \n";
	std::cin >> size;
	int(*arr2) = new int[size];
	std::cout << "Now you'll write the values of the numbers \n";
	for (int i = 0; i < size; i++) {
		std::cout << "Enter the " << i+1 << "th element \n";
		std::cin >> arr2[i];
	}
	std::cout << "Elements of array: \n";
	for (int i = 0; i < size; i++) {
		std::cout << arr2[i] << std::endl;
	}
	for (int i = 0; i < size; i++) {
		if (arr2[i] > maxNum) {
			maxNum = arr2[i];
			maxNumIndex = i;
		}
	}
	std::cout << "The highest number is " << maxNum << " , and is located at " << maxNumIndex + 1 << std::endl;
	system("pause");
	return 0;
}
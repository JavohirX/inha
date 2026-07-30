#include<iostream>
void swaper(int *a, int *b) { //function for swaping two values, using pointers
	int temp;
	temp = *a; // using pointers to change the vlaue drastically
	*a = *b;
	*b = temp;
}
double timeConverter() { // funvtion for converting time
	double hrs, min, sec;
	std::cout << "Enter the value for hours \n";
	std::cin >> hrs;
	std::cout << "Enter the value for minutes \n";
	std::cin >> min;
	std::cout << "Enter the value for seconds \n";
	std::cin >> sec;
	min += hrs * 60;//multipliyng hours by 60 to convert to minutes
	min += sec / 60;//deviding seconds by 60 to convert to minutes
	std::cout << "Minutes: " << min << std::endl;
	return min;
}
double area(double r) {
	double area = 3.14 * pow(r, 2);//using formula 2pr
	std::cout << "Area of circle is: " << area << std::endl;
	return 0;
}
double area(double a, double b) {
	double area = a * b;
	std::cout << "Area of the rectangle is: " << area << std::endl;
	return 0;
}
double area(double a, double b, double c) {
	double area = sqrt((a + b + c) * (b + c - a) * (a + c - b) * (a + b - c)) / 4;//using gerons formula to calculate the area
	std::cout << "Area of the triangle is: " << area << std::endl;
	return 0;
}
float area(float a) {
	float area = pow(a, 2);//calcutlating the area of aaquare by a^2
	std::cout << "Area of the square is: " << area << std::endl;
	return 0;
}
double max(double a, double b, double c) {
	double nums[] = { a,b,c };//using array to assign the amount of numbers to array
	double max = 0;
	int i = 0;
	while (i < 3) {
		if (max < nums[i]) {
			max = nums[i];//assigning number to max if it is larger than max
		}
		i++;
	}
	std::cout << "Largest value among 2 values is: " << max << std::endl;
	return 0;
}

int max(int a, int b, int c) {
	int nums[] = { a,b,c };
	int max = 0;
	int i = 0;
	while (i < 3) {
		if (max < nums[i]) {
			max = nums[i];
		}
		i++;
	}
	std::cout << "Largest value among 2 values is: " << max << std::endl;
	return 0;
}

int main() {
	int userInput, num1, num2, d, e, f;//declaring d,e,f to use intead of a,b,c as their integer alternaitve
	double length, width, radius, a, b, c;
	float squareSide;
	int *pnum1, *pnum2;
	std::cout << "Enter which program you want to use(Enter numbers from 1 to 4):\n";
	std::cin >> userInput;
	switch (userInput) {
	case 1:

		// FIRST PROGRAM
		std::cout << "First program:" << std::endl << std::endl;
		std::cout << "Enter two numbers \n";
		std::cin >> num1 >> num2;
		pnum1 = &num1;
		pnum2 = &num2;
		swaper(pnum1, pnum2); // calling function swaper() and giving arguments
		std::cout << "first number after swap: " << num1 << std::endl;
		std::cout << "Second number after swap: " << num2 << std::endl;
		break;
	case 2:
		//SECOND PROGRAM
		std::cout << "Second program:" << std::endl << std::endl;
		timeConverter();
		break;
	case 3:
		//THIRD PROGRAM
		std::cout << "Third program:" << std::endl << std::endl;
		std::cout << "Enter the radius of a circle \n";
		std::cin >> radius;
		area(radius);
		std::cout << "Enter the length of rectangel \n";
		std::cin >> length;
		std::cout << "Enter the width of a rectangle \n";
		std::cin >> width;
		area(length, width);
		std::cout << "Enter the values of three sides of triangle \nby pressing enter after each value: \n";
		std::cin >> a >> b >> c;
		area(a, b, c);
		std::cout << "Enter the value of the square's side \n";
		std::cin >> squareSide;
		area(squareSide);\
	case 4:
		//FOURTH PROGRAM
		std::cout << "Fourth program:" << std::endl << std::endl;
		std::cout << "Enter the values of three integer numbers \nby pressing enter after each value: \n";
		std::cin >> d >> e >> f;
		max(d, e, f);
		std::cout << "Enter the values of three float numbers \nby pressing enter after each value: \n";
		std::cin >> a >> b >> c;
		max(a, b, c);
		break;
	default:
		std::cout << "I think you did something wrong, try again \n";
		main();
	}
	system("pause");
	return 0;
}
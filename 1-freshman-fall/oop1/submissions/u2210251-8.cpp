#include <iostream>
using namespace std;
int main() {
	int array1[50][50], array2[50][50], temp[50][50];
	int rows1, columns1, rows2, columns2, salesmanSold = 0, userInput, sum = 0, k=0;
	//input area for first array
	std::cout << "Enter the number of raws for the first array \n";
	std::cin >> rows1;
	std::cout << "Enter the number of columns for the first array \n";
	std::cin >> columns1;
	std::cout << "Now, you'll enter the numbers in the first array \n";
	//input for array1 values 
	for (int i = 0; i < rows1; i++) {
		for (int j = 0; j < columns1; j++) {
			std::cout << "Enter the " << "row " << i << " column " << j << " element \n";
			std::cin >> array1[i][j];
		}
	}
	//input area for array2
	std::cout << "Enter the number of raws for the second array \n";
	std::cin >> rows2;
	std::cout << "Enter the number of columns for the second array \n";
	std::cin >> columns2;
	std::cout << "Now, you'll enter the numbers in the second array \n";
	//vlaue input area for array2
	for (int i = 0; i < rows2; i++) {
		for (int j = 0; j < columns2; j++) {
			std::cout << "Enter the " << "row " << i << " column " << j << " element \n";
			std::cin >> array2[i][j];
		}
	}
	a:
	std::cout << "Now, select what you want to do \n";
	std::cout << "1: output both arrays \n";
	std::cout << "2: calculate product of the arrays\n";
	std::cout << "3: transpose the array \n";
	std::cout << "4: calculate total sales by each salesman \n";
	std::cout << "5: calculate total sales of each item \n";
	std::cout << "6: sum array calculator\n";
	std::cin >> userInput;
	switch (userInput) {
	case 1:
		//array1 output area
		std::cout << "first array \n";
		for (int i = 0; i < rows1; i++) {
			for (int j = 0; j < columns1; j++) {
				std::cout << array1[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "second array \n";
		//value output area for array2
		for (int i = 0; i < rows2; i++) {
			for (int j = 0; j < columns2; j++) {
				std::cout << array2[i][j] << " ";
			}
			std::cout << std::endl;
		}
		break;
	case 2:
		//product calculator
		if (rows1 != columns2 && columns1 != rows2) {
			std::cout << "We can't multiply if rows of the first array isn't equal to the columns of the second array \n";
				goto a;
		}
		for (int k = 0; k < rows1; k++) {
			for (int i = 0; i < rows1; i++) {
				for (int j = 0; j < columns1; j++) {
					sum += array1[k][j] * array2[j][i];
				}
				temp[k][i] = sum;
				sum = 0;
			}
		}
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				std::cout << temp[i][j] << " ";
			}
			std::cout << std::endl;
		}
		break;
	case 3:
		//transpose calculator
		for (int i = 0; i < rows1; i++) {
			for (int j = 0; j < columns1; j++) {
				temp[i][j] = array1[j][i];
			}
		}
		std::cout << "Transpose: \n";
		//transpose outputer
		for (int i = 0; i < rows1; i++) {
			for (int j = 0; j < columns1; j++) {
				std::cout << temp[i][j] << " ";
			}
			std::cout << std::endl;
		}
		break;
	case 4:
		//total sales by each salesman
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 5; j++) {
				std::cout << "How many items of the " << i + 1 << " type " << j + 1 << " salesman sold? \n";
				std::cin >> temp[i][j];
			}
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 3; j++) {
				salesmanSold += temp[j][i];
			}
			std::cout << i + 1 << " salesman sold: " << salesmanSold << std::endl;
			salesmanSold = 0;
		}
		break;
	case 5:
		//total sales of each item
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 5; j++) {
				std::cout << "How many items of the " << i + 1 << " type " << j + 1 << " salesman sold? \n";
				std::cin >> temp[i][j];
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 5; j++) {
				salesmanSold += temp[i][j];
			}
			std::cout << i + 1 << " type item were sold: " << salesmanSold << std::endl;
			salesmanSold = 0;
		}
		break;
	case 6:
		//sum calculator
		for (int i = 0; i < rows1; i++) {
			if ((rows1 != rows2) || (columns1 != columns2)) {
				std::cout << "This rrays can't be added \n";
				goto a;
			}
			for (int j = 0; j < columns1; j++) {
				temp[i][j] = array1[i][j] + array2[i][j];
			}
		}
		std::cout << "Sum of the arrays: \n";
		//sum array outputer
		for (int i = 0; i < rows2; i++) {
			for (int j = 0; j < columns2; j++) {
				std::cout << temp[i][j] << " ";
			}
			std::cout << std::endl;
		}
		break;
	}
	system("pause");
	return 0;
}
#include<iostream>
#include<string>
int main() {
	int arr1[5] = { 11, 13, 15, 17, 19 };
	int arr2[5] = { 12, 14, 16, 18, 20 };
	int sum = 0, average, indexArr1 = 0, indexArr2 = 0, element, valueForElement, userInput;
	std::cout << "Enter which program you want to launch by entering numbers from 1 to 5 \n";
	std::cin >> userInput;
	switch (userInput) {
	case 1:
		//first program
		for (int i = 0; i < 5; i++) {
			std::cout << arr1[i] << std::endl;//while i is lesss than 5(which is the length of an array it prints ith element
		}
		break;
		//second program
	case 2:
		for (int i = 0; i < 5; i++) {
			sum += arr1[i];//adds to sum ith element of an array
		}
		average = sum / 5;
		std::cout << "Average of the array is: " << average << std::endl;
		break;
	case 3:
		//third program
		int sortedArr[10]; 
		for (int i = 0; i < 10; i++) {
			if (i == 9) {//9 is the number where one array doesn't have any values left so we can't compare their values anymore
				if (indexArr1 > indexArr2) {//instead, program will compare which index is bigger as the array with bigger index means it still has values left, more about indexes se on the line 38
					sortedArr[i] = arr2[indexArr2];
				}
				else {
					sortedArr[i] = arr1[indexArr1];
				}
			}
			else if (arr1[indexArr1] > arr2[indexArr2]) {
				sortedArr[i] = arr2[indexArr2];
				indexArr2++;// indexes will increase as the element of an array being sorted is used, as there are two of them, there are two indexes
			}
			else {
				sortedArr[i] = arr1[indexArr1];
				indexArr1++;
			}
		}
		break;
	case 4:
		//fourth program
		std::cout << "Enter which element you want to insert (from 0 to 9) \n";
		std::cin >> element;
		std::cout << "Enter the value for the element \n";
		std::cin >> valueForElement;
		arr1[element] = valueForElement;
		std::cout << arr1[element] << std::endl;
		break;
	case 5:
		//fifth program
		std::cout << "Enter which element you want to delete \n (from 0 to 9) \n";
		std::cin >> element;
		for (int i = element; i < 5; i++) {
			arr1[i] = arr1[i + 1];//assigns elements bigger, starting from the choosen one
		}
		break;
	}
	system("pause");
	return 0;
}
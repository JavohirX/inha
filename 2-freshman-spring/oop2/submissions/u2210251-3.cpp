#include<iostream>
#include<string>
#include<cmath>
using namespace std;
class Rectangle {
private:
	double length, breadth;
public:
	double getArea(){
		return (length * breadth);
	}
	void setLength(double len) {
		length = len;
	}
	void setBreadth(double wid) {
		breadth = wid;
	}
	friend Rectangle operator+(Rectangle &obj1, Rectangle &obj2);
};
class Distance {
private:
	int kilometer, meter;
public:
	Distance(){}
	Distance(int km, int m){
		kilometer = km;
		meter = m;
		if (m >= 1000) {
			kilometer += meter / 1000;
			meter = m % 1000;
		}
	}
	void showDistance() {
		printf("kilometer: %d, meter: %d \n", kilometer, meter);
	}
	friend bool operator==(Distance obj1, Distance obj2);
	friend Distance operator-(Distance &obj1, Distance &obj2);
};
bool operator==(Distance obj1, Distance obj2) {
	if (obj1.kilometer == obj2.kilometer) {
		if (obj1.meter == obj2.meter) {
			return true;
		}
	}
	return false;
}
Rectangle operator+(Rectangle &obj1, Rectangle &obj2) {
	Rectangle obj3;
	obj3.breadth = obj1.breadth + obj2.breadth;
	obj3.length = obj1.length + obj2.length;
	return obj3;
}
Distance operator-(Distance &obj1, Distance &obj2) {
	Distance obj3;
	obj3.kilometer = abs(obj1.kilometer - obj2.kilometer);
	obj3.meter = abs(obj1.meter - obj2.meter);
	return obj3;
}
int main() {
	Distance objDis1(5,5), objDis2(1,1), objDis3;
	Rectangle objRec1, objRec2, objRec3;
	objRec1.setBreadth(12);
	objRec1.setLength(12);
	std::cout << "Area of the first rectangle " << objRec1.getArea() << std::endl;
	objRec2.setBreadth(6);
	objRec2.setLength(6);
	std::cout << "Area of the second rectangle " << objRec2.getArea() << std::endl;
	objRec3 = (objRec1 + objRec2);
	std::cout << "Area of the third rectangle " << objRec3.getArea() << std::endl;
	objDis3 = objDis1 - objDis2;
	if (objDis1 == objDis2) {
		std::cout << "distances are equal \n";
	}
	else {
		std::cout << "distances are not equal \n";
	}
	std::cout << "First one: ";
	objDis1.showDistance();
	std::cout << "Second one: ";
	objDis2.showDistance();
	objDis3 = objDis1 - objDis2;
	std::cout << "Their difference: ";
	objDis3.showDistance();
	system("pause");
	return 0;
}
#include<iostream>
#include<string>
class Triangle{
private:
	double height, base;
public:
	Triangle(double heigth, double base){
		this->height = height;
		this->base = base;
	}//constructor declration
	void setHeight(double height){
		this->height = height;
	}
	void setBase(double base){
		this->base = base;
	}
	double getHeight(){
		return height;
	}
	double getBase(){
		return base;
	}
	double getArea(){
		return (0.5*height*base);
	}
	double getPerimeter(){
		double side = pow((pow(base / 2, 2) + pow(height, 2)), 0.5);
		return (double)(side*2 + base);
	}
};
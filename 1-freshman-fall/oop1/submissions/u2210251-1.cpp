//U2210251
//Javohirbek Xatamov

#include <iostream>
#include <cmath>
using namespace std;

 void circle() { // function for calculating parameters of a circle
	const double PI = 3.1415926535;
	double radius, c, S;
	cout << "You choose circle \n";
	cout << "Enter its radius: \n";
	cin >> radius;
	c = 2 * PI * radius;
	S = PI * pow(radius, 2);
	cout << "Area is: " << S << endl;
	cout << "Circumference is: " << c << endl;
}

int main() {
	int TriangleInfo, TetragonInfo, shapeSelector, RightTrig, SquareType, PolygonType;
	double a, b, c, P, S, ha, hb, hc, ma, mb, mc, alpha, beta, gamma, d, d1, d2, fi, n;
	const double PI = 3.1415926535;

	cout << "Hey,this program can help you with geometry!" << endl;
	cout << "select the shape by entering corresponding number:" << endl;
	cout << "1: triangle" << endl;
	cout << "2: tetragon" << endl;
	cout << "3: polygons" << endl;
	cout << "4: circle" << endl;
	cin >> shapeSelector;
	switch (shapeSelector) {

	case 1: //case that determines the shape type

		cout << "you selcted triangle" << endl;
		cout << "now select the type of the triangle:" << endl;
		cout << "1: scalene" << endl;
		cout << "2: equilateral" << endl;
		cout << "3: right" << endl;
		cout << "4: back" << endl;
		cin >> TriangleInfo;
		switch (TriangleInfo) {
		case 1: // case that setermines triangle type. scalene
			cout << "Enter the value of a (one side)" << endl;
			cin >> a;
			cout << "Enter the value of b (one side)" << endl;
			cin >> b;
			cout << "Enter the value of c (one side)" << endl;
			cin >> c;
			//calculations
			P = a + b + c;
			S = 0.25 * sqrt((a + b + c) * (a + b - c) * (b + c - a) * (a + c - b));
			alpha = asin(2 * S / (b * c)) * 180 / PI;
			beta = asin(2 * S / (a * c)) * 180 / PI;
			gamma = asin(2 * S / (a * b)) * 180 / PI;
			ha = 2 * S / a;
			hb = 2 * S / b;
			hc = 2 * S / c;
			ma = 0.5 * sqrt(2 * pow(b, 2) + 2 * pow(c, 2) - pow(a, 2));
			mb = 0.5 * sqrt(2 * pow(a, 2) + 2 * pow(c, 2) - pow(b, 2));
			mc = 0.5 * sqrt(2 * pow(b, 2) + 2 * pow(a, 2) - pow(c, 2));
			//output of calculations
			cout << "Area is " << S << endl;
			cout << "Perimeter is " << P << endl;
			cout << "Angle alpha between b and c is " << alpha << endl;
			cout << "Angle beta between a and c is " << beta << endl;
			cout << "Angle gamma between a and b is " << gamma << endl;
			cout << "Height of triangle to base a is " << ha << endl;
			cout << "Height of triangle to base b is " << hb << endl;
			cout << "Height of triangle to base c is " << hc << endl;
			cout << "Median to base c is " << mc << endl;
			cout << "Median to base b is " << mb << endl;
			cout << "Median to base a is " << ma << endl;
			break;  // case that setermines triangle type. scalene
		case 2: // case that determines triangle type. equilateral
			cout << "enter the side of a equilateral triangle" << endl;
			cin >> a;
			P = 3 * a;
			S = 0.5 * pow(a, 2) * sqrt(3);
			ha = a * sqrt(3) * 0.5;
			cout << "Area is " << S << endl;
			cout << "Perimeter is " << P << endl;
			cout << "Height, bisector and median of the triangle is " << ha << endl;
			break; // case that determines triangle type. equilateral
		case 3: // case that determines triangle type. right
			cout << "select what's known by entering corresponding number:" << endl;
			cout << "1: both cathetuses" << endl;
			cout << "2: cathetus and hypotenuse" << endl;
			cin >> RightTrig;
			switch (RightTrig) {
			case 1: //case that determines right triangle type
				cout << "Enter the value of any cathetus" << endl;
				cin >> a;
				cout << "Enter the value of another cathetus" << endl;
				cin >> b;
				S = 0.5 * a * b;
				c = sqrt(pow(a, 2) + pow(b, 2));
				hc = a * b / c;
				P = a + b + c;
				mc = 0.5 * sqrt(2 * pow(b, 2) + 2 * pow(a, 2) - pow(c, 2));
				cout << "Area is " << S << endl;
				cout << "Perimeter is " << P << endl;
				cout << "Hypotenuse is " << c << endl;
				cout << "Height to hypotenuse is " << hc << endl;
				cout << "Median to hypotenuse is " << mc << endl;
				break;//case that determines right triangle type
			case 2: //case that determines right triangle type
				cout << "Enter the value of the cathetus" << endl;
				cin >> a;
				cout << "Enter the value of the hypotenuse" << endl;
				cin >> c;
				b = sqrt(pow(c, 2) - pow(a, 2));
				S = 0.5 * a * b;
				hc = a * b / c;
				P = a + b + c;
				mc = 0.5 * sqrt(2 * pow(b, 2) + 2 * pow(a, 2) - pow(c, 2));
				cout << "Area is " << S << endl;
				cout << "Perimeter is " << P << endl;
				cout << "value of another cathetus is " << b << endl;
				cout << "Height to hypotenuse is " << hc << endl;
				cout << "Median to hypotenuse is " << mc << endl;
				break; //case that determines right triangle type
			}
			break; // case that determines triangle type. right
		case 4:
			main();
			break;
		}
		break; //case that determines the shape type

	case 2: //case that determines the shape type
		cout << "You selcted tetragon, now select the type of the tetragon" << endl;
		cout << "By entering corresponding number" << endl;
		cout << "1: Square" << endl;
		cout << "2: Rectangle" << endl;
		cout << "3: Rhombus" << endl;
		cout << "4: Parallelogramm" << endl;
		cout << "5: back" << endl;
		cin >> TetragonInfo;
		switch (TetragonInfo) {
		case 1: // case that setermines tetragon type. square
			cout << "You selected square" << endl;
			cout << "Select what is known" << endl;
			cout << "1: side of square " << endl;
			cout << "2: diagonals" << endl;
			cin >> SquareType;
			switch (SquareType) {
			case 1: // case that determines square type
				cout << "Enter the length of the square's side" << endl;
				cin >> a;
				d = a * sqrt(2);
				P = 4 * a;
				S = pow(a, 2);
				cout << "Area is " << S << endl;
				cout << "Perimeter is " << P << endl;
				cout << "Diagonal is " << d << endl;
				break;
			case 2:// case that determines squre type
				cout << "Enter the length of the diagonal";
				cin >> d;
				a = d / sqrt(2);
				P = 4 * a;
				S = pow(a, 2);
				cout << "Area is " << S << endl;
				cout << "Perimeter is " << P << endl;
				cout << "square's side length is " << a << endl;
				break;
			}
			break;
		case 2: // case that setermines tetragon type. rectangle
			cout << "You selected rectangle" << endl;
			cout << "Select what is already known" << endl;
			cout << "1: both sides of rectangle " << endl;
			cout << "2: diagonal and one side of rectangle" << endl;
			int RectangleType;
			cin >> RectangleType;
			switch (SquareType) {
			case 1: // case that determines rectangle type
				cout << "Enter a (the length of rectangle's side)" << endl;
				cin >> a;
				cout << "Enter b (the length of rectangle's side)" << endl;
				cin >> b;
				d = sqrt(pow(a, 2) + pow(b, 2));
				P = 2 * (a + b);
				S = a * b;
				cout << "Area is " << S << endl;
				cout << "Perimeter is " << P << endl;
				cout << "Diagonal is " << d << endl;
				break;
			case 2: // case that determines rectangle type
				cout << "Enter the length of the diagonal" << endl;
				cin >> d;
				cout << "Enter a (the length of rectangle's side)" << endl;
				a = sqrt(pow(d, 2) - pow(b, 2));
				P = 2 * (a + b);
				S = a * b;
				cout << "Area is " << S << endl;
				cout << "Perimeter is " << P << endl;
				cout << "Length of the rectangle's another side is " << a << endl;
				break;
			}
			break;
		case 3:  // case that setermines tetragon type. rhombus
			cout << "You selected rhombus" << endl;
			cout << "Select what is known" << endl;
			cout << "1:  length of side and angle between them " << endl;
			cout << "2: diagonals" << endl;
			cin >> SquareType;
			switch (SquareType) {
			case 1: // case that determines rhombus type
				cout << "Enter 'a' which is the length of the side" << endl;
				cin >> a;
				cout << "Enter the angle between them (NOT in radians)" << endl;
				cin >> alpha;
				beta = 180 - alpha;
				d1 = a * sqrt(2 - 2 * cos(alpha * PI / 180));
				d2 = sqrt(4 * pow(a, 2) - pow(d1, 2));
				P = 4 * a;
				S = pow(a, 2) * sin(alpha * PI / 180);
				ha = S / a;
				cout << "Area is " << S << endl;
				cout << "Perimeter is " << P << endl;
				cout << "First diagonal is " << d1 << endl;
				cout << "Second diagonal is " << d2 << endl;
				cout << "Height of rhombus is " << ha << endl;
				cout << "Value of the second angle is " << beta << endl;
				break;
			case 2:// case that determines rhombus type
				cout << "Enter 'd1' which is the length of the first diagonal" << endl;
				cin >> d1;
				cout << "Enter 'd2' which is the length of the second diagonal" << endl;
				cin >> d2;
				a = 0.5 * sqrt(pow(d1, 2) + pow(d2, 2));
				S = d1 * d2 * 0.5;
				P = 4 * a;
				ha = S / a;
				alpha = asin(S / pow(a, 2)) * 180 / PI;
				beta = 180 - alpha;
				cout << "Area is " << S << endl;
				cout << "Perimeter is " << P << endl;
				cout << "Value of the side is " << a << endl;
				cout << "Value of the first angle is " << alpha << endl;
				cout << "Value of the second angle is " << beta << endl;
				cout << "Value of the second angle is " << beta << endl;
				cout << "Height of rhombus is " << ha << endl;
				break;
			}
			break;
		case 4:// case that setermines tetragon type. Parallelogram
			cout << "You selected parallelogramm" << endl;
			cout << "Select what is known" << endl;
			cout << "1: length of sides and angle between them" << endl;
			cout << "2: length of diagonals and angle between them" << endl;
			cin >> SquareType;
			switch (SquareType) {
			case 1: // case that determines parallelogramm type
				cout << "Enter 'a' which is the length of the side" << endl;
				cin >> a;
				cout << " Now enter 'b' which is the length of the other side" << endl;
				cin >> b;
				cout << "Enter the angle between them (NOT in radians)" << endl;
				cin >> alpha;
				S = a * b * sin(alpha * PI / 180);
				P = 2 * (a + b);
				beta = 180 - alpha;
				d1 = sqrt(pow(a, 2) + pow(b, 2) - 2 * a * b * cos(alpha * PI / 180));
				d2 = sqrt(pow(a, 2) + pow(b, 2) - 2 * a * b * cos(beta * PI / 180));
				ha = S / a;
				hb = S / b;
				fi = asin(2 * S / (d1 * d2)) * 180 / PI;
				gamma = 180 - fi;
				cout << "Area is " << S << endl;
				cout << "Perimeter is " << P << endl;
				cout << "Another angle is " << beta << endl;
				cout << "First diagonal is " << d1 << endl;
				cout << "Second diagonal is " << d2 << endl;
				cout << "Height to the base 'a' is " << ha << endl;
				cout << "Height to the base 'b' is " << hb << endl;
				cout << "Angles between diagonals are " << fi << ", " << gamma << endl;

				break;
			case 2:// case that determines parallelogramm type
				cout << "Enter the value of the first diagonal" << endl;
				cin >> d1;
				cout << "Enter the value of the second diagonal" << endl;
				cin >> d2;
				cout << "Enter the angle between them (NOT in radians)" << endl;
				cin >> fi;
				S = 0.5 * d1 * d2 * sin(alpha * PI / 180);
				a = sqrt(pow(d1 / 2, 2) + pow(d2 / 2, 2) - 0.5 * d1 * d2 * cos(fi * PI / 180));
				b = sqrt(pow(d1 / 2, 2) + pow(d2 / 2, 2) - 0.5 * d1 * d2 * cos(180 - fi * PI / 180));
				P = 2 * (a + b);
				alpha = asin(S / (a * b)) * 180 / PI;
				beta = 180 - alpha;
				ha = S / a;
				hb = S / b;
				cout << "Area is " << S << endl;
				cout << "Perimeter is " << P << endl;
				cout << "Angle of the parallelogramm is " << alpha << endl;
				cout << "Another angle of the parallelogramm is " << beta << endl;
				cout << "Side 'a' is equal to " << a << endl;
				cout << "Side 'b' is equal to " << b << endl;
				cout << "Height to the base 'b' is " << hb << endl;
				cout << "Height to the base 'a' is " << ha << endl;
				cout << "Height to the base 'b' is " << hb << endl;

				break;
			}
			break;
		case 5:
			main();
			break;
		}

		break;//case that determines the shape type
	case 3:
		cout << "You choose polygons" << endl;
		cout << "Enter what's known:" << endl;
		cout << "1:sum of inner angles" << endl;
		cout << "2:number of diagonals" << endl;
		cout << "3:value of each inner angle" << endl;
		cout << "4:number of sides" << endl;
		cout << "5:back" << endl;
		cin >> PolygonType;
		switch (PolygonType) {
		case 1:
			cout << "Enter the value of the sum of the inner angles" << endl;
			cin >> a;
			n = a / 180 + 2;
			b = (n - 3) * n * 0.5;
			c = (n - 2) * 180 / n;
			cout << "number of diagonals are " << b << endl;
			cout << "value of each inner angle " << c << endl;
			cout << "number of sides are " << n << endl;
			break;
		case 2:
			cout << "Enter the number of diagonals" << endl;
			cin >> b;
			n = 0.5 * (3 + sqrt(9 + 8 * b));
			a = (n - 2) * 180;
			c = (n - 2) * 180 / n;
			cout << "number of sides are " << n << endl;
			cout << "value of each inner angle " << c << endl;
			cout << "sum of inner angles are " << a << endl;
			break;
		case 3:
			cout << "Enter the value of each inner angle " << endl;
			cin >> c;
			n = 360 / (c - 180);
			a = (n - 2) * 180;
			b = (n - 3) * n * 0.5;
			cout << "number of sides are " << n << endl;
			cout << "sum of inner angles are " << a << endl;
			cout << "number of diagonals are " << b << endl;
			break;
		case 4:
			cout << "Enter the number of the sides " << endl;
			cin >> n;
			a = (n - 2) * 180;
			b = (n - 3) * n * 0.5;
			c = (n - 2) * 180 / n;
			cout << "sum of inner angles are " << a << endl;
			cout << "number of diagonals are " << b << endl;
			cout << "value of each inner angle " << c << endl;
			break;
		case 5:
			main();
			break;
		}
		break;
	case 4:
		circle();
		break;

	}
	cin >> a;
	return 0;
}
// originally, I wrote and posted this program on my github one month ago
//https://github.com/Khatamov?tab=repositories
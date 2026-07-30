#include <iostream>
#include <cmath>
using namespace std;

class shape {
protected:
    double x, y;
public:
    void get_data(double a, double b) {
        x = a;
        y = b;
    }
    virtual void display_area() {
        cout << "Area of shape: " << x * y << endl;
    }
};

class triangle : public shape {
public:
    void display_area() {
        cout << "Area of triangle: " << 0.5 * x * y << endl;
    }
};

class rectangle : public shape {
public:
    void display_area() {
        cout << "Area of rectangle: " << x * y << endl;
    }
};

class circle : public shape {
public:
    void get_data(double r) {
        x = r;
        y = 0;
    }
    void display_area() {
        cout << "Area of circle: " << 3.14 * x * x << endl;
    }
};

int main() {
    double temp1, temp2;
    shape* s;
    triangle t;
    rectangle r;
    circle c;
    s = &t;
    cout << "Enter the dimensions of the triangle \n";
    cin >> temp1 >> temp2;
    s->get_data(temp1, temp2);
    s->display_area();
    s = &r;
    cout << "Enter the dimentsions of rectangle \n";
    cin >> temp1 >> temp2;
    s->get_data(temp1, temp2);
    s->display_area();
    s = &c;
    cout << "Enter the radius of circle \n";
    cin >> temp1;
    c.get_data(temp1);
    s->display_area();
    system("pause");
    return 0;
}
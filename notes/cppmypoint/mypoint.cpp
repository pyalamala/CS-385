#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

class MyPoint {
   public:
    // constructor that uses an initializer list
    MyPoint(int x, int y, float z) : x_{x}, y_{y}, z_{z} {}

    //Destructor frees up memory allocated by the class.
    ~MyPoint() {
        cout << "Destructor called." << endl;
    }

    // Methods that do not modify member variables should be declared const
    void print_coords() const {
        cout << "(x, y, z) = (" << x_ << ", " << y_ << ", " << fixed
             << setprecision(2) << z_ << ")" << endl;
    }

    // Accessor (getter)
    int get_x() const {
        return x_;
    }

    // Mutator (setter)
    void set_x(int x) {
        x_ = x;
    }

   private:
    int x_, y_;
    float z_;
};

void display_points(const vector<MyPoint> &points) {
    for (auto it = points.cbegin(); it != points.cend(); ++it) {
        it->print_coords();
    }
}

int main() {
    int x, y;

    // creates on the Stack
    // do not need to "free-up" since when they leave the scope the destructor is called
    MyPoint point1(5, 7, 1.24);
    MyPoint point2(1, 2, 3);
    MyPoint point3(4, 5, 6);
    // point1.print_coords();

    vector<MyPoint> points;
    // push_back is similar to .add() in java
    points.push_back(point1);
    points.push_back(point2);
    points.push_back(point3);

    vector<MyPoint> points_above_two;
    // USE & to reference original object
    // auto creates a copy
    // for (const auto point : points)

    for (const auto &point : points) {
        if (point.get_x() > 2) {
            points_above_two.push_back(point);
        }
    }

    display_points(points_above_two);

    cout << "Input x: ";
    cin >> x;
    cout << "Input y: ";
    cin >> y;

    // calling new puts an object on the heap
    // since there is no direct access to the heap, we must create a pointer to the heap
    MyPoint *point4 = new MyPoint(x, y, 7.8);
    point4->print_coords();
    delete point4;
    return 0;
}
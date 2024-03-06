#include<iostream>

using namespace std;

class Wagon {
    int horsePower;
    int wheelCount;
    string licensePlate;
public:
    Wagon() {
        cout << "In default constructor ..." << endl;
    }

    Wagon(int horsePower, int wheelCount, string licensePlate) {
        cout << "In custom constructor ..." << endl;
        setHorsePower(horsePower);
        setWheelCount(wheelCount);
        setLicensePlate(licensePlate);
    }

    //Copy constructor
    Wagon(const Wagon& wagon) {
        cout << "In copy constructor ... " << endl;
        // wagon = new Wagon();
        this->horsePower = wagon.horsePower;
        setWheelCount(wagon.wheelCount);
        setLicensePlate(wagon.licensePlate);
    }

    //Operator=
    Wagon& operator=(const Wagon& wagon) {
        cout << "In operator= ... " << endl;
        if (this != &wagon) {
            this->horsePower = wagon.horsePower;
            setWheelCount(wagon.wheelCount);
            setLicensePlate(wagon.licensePlate);
        }
        return *this;
    }

    int getHorsePower() {
        return this->horsePower;
    }

    void setHorsePower(int horsePower) {
        this->horsePower = horsePower;
    }

    int getWheelCount() {
        return this->wheelCount;
    }

    void setWheelCount(int wheelCount) {
        this->wheelCount = wheelCount;
    }

    string getLicensePlate() {
        return this->licensePlate;
    }

    void setLicensePlate(string licensePlate) {
        this->licensePlate = licensePlate;
    }

    ~Wagon() {
        cout << "In destructor for: " << this->licensePlate << endl;
    }

 };

// Deep copy vs Shallow copy
int main() {
    //Reference
    int b = 10;
    int& a = b;
    b = 20;
    int c = 100;
    a = c;
    cout << a << endl;
    cout << b << endl;
    cout << &a << endl;
    cout << &b << endl;
    cout << &c << endl;

    Wagon w1(2,2,"sdsd");
    Wagon w4;
    Wagon* w = new Wagon(2, 2, "H0902TH");

    Wagon* w2 = new Wagon(*w);
    Wagon* w3 = new Wagon();

    *w3 = *w2;

    w4 = w1;

    cout << w->getLicensePlate() << endl;
    cout << w2->getLicensePlate() << endl;
    cout << w3->getLicensePlate() << endl;

    cout << w2 << endl;
    cout << w3 << endl;

    cout << &w1 << endl;
    cout << &w4 << endl;

    // // shallow copy again
    // Wagon* w5 = w2; // Calls the default operator= -> Wagon* operator=(const Wagon* wagon)
    // cout << w5 << endl;

    delete w;
    delete w2;
    delete w3;
    return 0;
}
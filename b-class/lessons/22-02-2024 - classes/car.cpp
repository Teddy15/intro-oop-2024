#include<iostream>

using namespace std;

class Car {
    string model;
    string make;
    double topSpeed;
public:
    Car() {
        cout << "In Default Constructor ... " << endl;
    }

    void printInformation() {
        cout << "=====:" << model << endl;
        cout << "=====:" << make << endl;
        cout << "=====:" << topSpeed << endl;
    }

    Car(string model, string make, double topSpeed) {
        cout << "In Custom Constructor ... " << endl;
        this->model = model; // setModel(model); or this->setModel(model);
        this->make = make;
        this->topSpeed = topSpeed;
        printInformation();
    }

    //Getters and setters
    string getModel() {
        return this->model;
    }

    void setModel(string model) {
        this->model = model; // From line 32 == c1->model = model;
                            // From line 33 == c.model = model;
    }

    string getMake() {
        return this->make;
    }

    void setMake(string make) {
        this->make = make;
    }

    double getTopSpeed() {
        return this->topSpeed;
    }

    void setTopSpeed(double topSpeed) {
        this->topSpeed = topSpeed;
    }

    ~Car() {
        cout << "In Destructor!" << endl;
    }

};

// NULL & nullptr, const
int main() {
    Car* c;
    Car c3("Passat", "VW", 200);
    Car* c1 = new Car();
    Car* c2 = new Car("Golf", "VW", 200);

    c1->setModel("Golf");
    c.setModel("Passat");
    cout << c1->getModel() << endl;

    c.printInformation();
    c1->printInformation();
    c2->printInformation();
    c3.printInformation();

    delete c1;
    delete c2;
    return 0;

}
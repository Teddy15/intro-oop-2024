#include<iostream>

using namespace std;

// Function
void foo() {

}

// S.O.L.I.D. - 5 Principles of OOP
// Encapsulation, Inheritance, Abstraction, Polymorphism - 4 Pillars of OOP

class Car {
// Access modifiers: private, public, protected - responsible for Encapsulation
// By default, everything within a class is private!
//private: 
    string model;
    string make;
    double topSpeed;

public:
    // Default constructor. The compilatros adds it by default, you don't need to write it.
    Car() {
        cout << "In default constructor..." << endl;
    }

    // Custom constructor. You create it.
    Car(string model) {

        cout << "In custom constructor 1..." << endl;
        this->model = model; //setModel(model); or this->setModel(model);
    }

    // Custom constructor. You create it.
    Car(string model, string make, double topSpeed) {
        cout << "In custom constructor 2..." << endl;
        this->model = model;
        this->make = make;
        this->topSpeed = topSpeed;
    }
    
    // Method - a function, which belongs to a class
    void printInformation() {
        cout << "========" << getModel() << endl;
        cout << "========" << this->getMake() << endl;
        cout << "========" << topSpeed << endl;

    }

    string getModel() {
        return this->model; // from line 98, then line 44 == return c->model;
    }

    void setModel(string model) {
        this->model = model; // From line 94 == c->model = model;
                            // From line 91 == c1->model = model;
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

    // Destructor. The compilator adds it by default as well. Like the default constructor.
    // You cannot define more than one Desctructor (unline the Constructors!)
    ~Car() {
        cout << getModel() << " " << "In default Destructor ..." << endl;
    }
};

int main() {
    Car c1; // object on the Stack
    Car* c = new Car(); //object on the Heap
    Car* c2 = new Car("Arteon"); //object on the Heap
    Car* c3 = new Car("Tiguan", "VW", 260); //object on the Heap

    string model, make;
    double topSpeed;

    c1.setModel("Passat");
    c1.setTopSpeed(60);
    
    c->setModel("Golf");
    c->setMake("VW");
    c->setTopSpeed(220);

    c->printInformation();
    c1.printInformation();
    c2->printInformation();
    c3->printInformation();

    delete c;
    delete c2;
    delete c3;

    return 0;
}
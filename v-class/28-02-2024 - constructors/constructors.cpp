#include<iostream>

using namespace std;

class Bachelor {
    int roses;
    bool bald;
    bool rich;
public:
    Bachelor() {
        cout << "In default constructor ..." << endl;
    }

    Bachelor(int roses, bool bald, bool rich) {
        cout << "In custom constructor ..." << endl;
        this->roses = roses;
        this->bald = bald;
        this->rich = rich;
    }

    // Copy constructor
    Bachelor(const Bachelor& bachelor) {
        this->roses = bachelor.roses;
        this->bald = bachelor.bald;
        this->rich = bachelor.rich;
    }

    // Operator=
    // int getRoses
    Bachelor& operator=(const Bachelor& bachelor) {
        if (this != &bachelor) {
            // bachelor.roses = 10; FORBIDDEN by const
            this->roses = bachelor.roses;
            this->bald = bachelor.bald;
            this->rich = bachelor.rich;
        }

        return *this;
    }


    int getRoses() {
        return this->roses;
    }

    void setRoses(int roses) {
        this->roses = roses;
    }

    bool isBald() {
        return this->bald;
    }

    void setBald(bool bald) {
        this->bald = bald;
    }

    bool isRich() {
        return this->rich;
    }

    void setRich(bool rich) {
        this->rich = rich;
    }

    ~Bachelor() {
        cout << "In destructor ..." << endl;
    }
};

int main() {
    Bachelor b(10,1,1);
    Bachelor b4(b);
    Bachelor* b1 = new Bachelor(26, 1, 0);
    Bachelor* b2 = new Bachelor(1, 0, 1);
    Bachelor* b3 = new Bachelor(*b1);

    cout << b1 << endl;
    cout << b3 << endl;

    cout << &b << endl;
    cout << &b4 << endl;

    // Shallow copy (created by the compilator by default)
    // b2 = b1;

    // Deep copy
    *b2 = *b1;

    // Dumb
    // b1 = b1;

    cout << b2->isBald() << endl;
    cout << b1->isBald() << endl;

    cout << b2 << endl;
    cout << b1 << endl;

    int d = 10;
    int& a = d; // Reference 
    d = 15;
    cout << a << endl; 
    return 0;
}
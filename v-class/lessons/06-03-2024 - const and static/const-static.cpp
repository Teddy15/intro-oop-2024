#include<iostream>

using namespace std;

class Test {
    int value;
    
public:
    static int t;
    Test() {
        cout << "In default ..." << endl;
        this->value = 10;
        cout << ++t << endl;
    }

    Test(int value) {
        this->value = value;
    }

    Test(const Test& test) {
        this->value = test.value;
    }

    Test& operator=(const Test& test) {
        if (this != &test) {
            this->value = test.getValue();
        }
        return *this;
    }

    int getValue() const {
        return this->value;
    }

    // Not good: void setValue(int value) const {};
    void setValue(int value) { 
        this->value = value;
    }

};

int Test::t = 5;

static string getMessage() {
    return "Error message!\n";
}

int foo () {
    static int a = 0;
    return a++;
}

int main() {
    int a = 10;
    int b = 20;
    int c = 30;

    // Non-constant pointer to constant value
    const int* x = &a;
    a = 30;
    x = &b;
    // *x = 15; -> CTE
    cout << a << ", " << b << ", " << c << endl;
    cout << *x << endl;
    cout << x << endl;

    // Constant pointer to non-constant value
    int* const y = &b;
    b = 40;
    // y = &c; // -> CTE
    *y = 25; 

    cout << a << ", " << b << ", " << c << endl;
    cout << *y << endl;
    cout << y << endl;

    // Constant pointer to constant value
    const int* const z = &c;
    c = 50;
    // z = &a; // CTE
    // *z = 35; // CTE

    cout << a << ", " << b << ", " << c << endl;
    cout << *z << endl;
    cout << z << endl;


    for (int i = 0; i < 5; i++) {
        cout << foo() << endl;
    }


    Test t1;
    cout << t1.t << endl;
    Test t2;
    cout << t2.t << endl;
    Test t3;
    cout << t3.t << endl;
    cout << t2.t << endl;

    return 0;
}
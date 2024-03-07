#include<iostream>

using namespace std;

class Test {
    int value;
public:
    static int test;
    Test() {
        this->value = 5;
        test++;
    }

    Test(const Test& test) {
        this->value = test.getValue();
    }

    Test& operator=(const Test& test) {
        if (this != &test) {
            this->value = test.getValue();
            // this->value = value -> allowed
        }

        return *this;
    }

    int getValue() const {
        // int a = 10; -> this is allowed
        // value = 10; -> this is not allowed
        return this->value;
    }

    void setValue(int value) {
        this->value = value;
    } 
};

int Test::test = 1;

void foo() {
    static int a = 1;
    cout << ++a << endl;
}

void test() {
    static int a = 0;
    cout << ++a << endl;
}

int main() {
    // Non-constant pointer to constant value
    int a = 10;
    int b = 20;
    int c = 30; // add const to see what happens

    const int* x = &a;
    a = 15;
    x = &b;
    // *x = 25; CTE

    cout << a << endl;
    cout << x << endl;
    cout << *x << endl;

    // Constant pointer to non-constant value
    int* const y = &b;
    b = 25;
    // y = &c; CTE - compile time error
    *y = 35;

    cout << b << endl;
    cout << y << endl;
    cout << *y << endl;

    // Constant pointer to constant value
    const int* const z = &c;
    c = 35;
    // z = &a;  CTE
    // *z = 45;  CTE

    cout << c << endl;
    cout << z << endl;
    cout << *z << endl;

    for (int i = 0; i < 5; i++) {
        test();
    }

    for (int i = 0; i < 5; i++) {
        foo();
    }

    Test t1;
    cout << t1.test << endl;
    Test t2;
    cout << t2.test << endl;
    cout << t1.test << endl;


    return 0;
}
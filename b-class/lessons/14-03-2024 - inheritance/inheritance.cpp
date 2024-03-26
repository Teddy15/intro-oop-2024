#include<iostream>

using namespace std;

class Test {
public:
    Test() {
        cout << "In defaul Test" << endl;
    }
};

class Exception {
    int checkSum;
protected:
    string message;
public:
    Exception() {
        cout << "In default Exception" << endl;
    }

    void throwException() {
        throw string("Invalid argument");
    }
};

// Forbidden - Child class, Exception - Parent class
class ForbiddenAccessException : protected Exception {
public:
    ForbiddenAccessException() {
        cout << "In default ForbiddenAccessException" << endl;
        // cout << checkSum << endl;
    }

    void test() {
        cout << message << endl;
        throwException();
    }

    // void throwException() {
    //     throw string("Invalid argument 2");
    // }
};

int main() {
    ForbiddenAccessException* e = new ForbiddenAccessException();
    // cout << e.message << endl;
    // ForbiddenAccessException e1;
    // e1.test();
    try {
        e->throwException();
    } catch(string message) {
        cout << message << endl;
    }
    return 0;
}
#include<iostream>

using namespace std;

class Test {

};

// inheritance
class Exception {
protected:
    string message;
public:
    Exception() {
        cout << "In Exception constructor ..." << endl;
        this->message = "empty";
    }

    void throwException() {
        throw string("Invalid argument");
    }
};

class UnsupportedOperationException : protected Exception {
protected:
    int checkSum;
public:
    UnsupportedOperationException() {
        cout << "In UnsupportedOperationException constructor ..." << endl;
        cout << message << endl;
    }

    // void throwException() {
    //     throw string("Invalid argument 2");
    // }

    void test () {
        throwException();
    }
};

class ForbiddenException : public UnsupportedOperationException {
public:
    ForbiddenException() {
        cout << "In Forbidden exception" << endl;
        cout << checkSum << endl;
    }
};

int main() {
    // Exception* e = new UnsupportedOperationException();
    // Exception* e1 = new ForbiddenException();
    ForbiddenException* u = new ForbiddenException();
    try {
        u->throwException();
    } catch (string message) {
        cout << message << endl;
    }
    return 0;
}
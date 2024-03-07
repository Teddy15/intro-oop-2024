#include<iostream>

using namespace std;

// Use only char*, no direct usage of the C++ string is allowed!

class String {
    char* value;
public:
    // Default constructor

    // Custom constructor

    // Copy constructor

    // Overload operator=

    // Getter and setter

    //Destructor

    // Length method
    // String* str = new String("ABC");
    // cout << str->length() << endl; -> Output should be 3

    // Concat method 
    // String* str = new String("ABC"); 
    // str->concat("abc");
    // cout << str->getValue() << endl; -> Output should be ABCabc
    // If an empty char array is given as argument, then show an error message (or throw an exception)

    // Replace method
    // String* str = new String("ABC"); 
    // Case 1: 
    // str->replace(1, "DEFGH");
    // cout << str->getValue() << endl; -> Output should be ADEFGHC
    // Case 2:
    // str->replace(0, "DEFGH");
    // cout << str->getValue() << endl; -> Output should be DEFGHBC
    // Case 3:
    // str->replace(2, "DEFGH");
    // cout << str->getValue() << endl; -> Output should be ABDEFGH
    // !!! If the index is out of bounds (< 0 or > length), then show an error message (or throw an exception)
};

// Write driver code to show every functionality of the class:
// all the constructors, destructor, all methods (except getters and setters)
int main() {
    return 0;
}
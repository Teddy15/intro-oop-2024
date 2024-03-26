#include<iostream>

using namespace std;

class Marks {
    double* marks;
    int size;
    int capacity;
public:
    Marks() 
    : size(0), capacity(2) {
        marks = new double[capacity];
        for (int i = 0; i < capacity; i++) {
            this->marks[i] = 2.00;
        }
    }

    Marks(double* marks, int size, int capacity) 
    : size(size), capacity(capacity) {
        cout << "In custom constructor Marks" << endl;
        this->marks = new double[capacity];
        for (int i = 0; i < size; i++) {
            this->marks[i] = marks[i];
        }
    }

    Marks(const Marks& object) 
    : Marks(object.marks, object.size, object.capacity) {
        cout << "In copy constructor Marks" << endl;
    }

    Marks& operator=(const Marks& object) {
        if (this != &object) {
            size = object.size;
            capacity = object.capacity;
            delete [] marks;
            marks = new double[capacity];
            for (int i = 0; i < size; i++) {
                marks[i] = object.marks[i];
            }
        }
        return *this;
    }

    int getCapacity() {
        return capacity;
    }

    int getSize() {
        return size;
    }

    double* getMarks() {
        return marks;
    }

    void setMarks(double* marks) {
        this->marks = marks;
    }

    void printMarks() {
        for(int i = 0; i < size; i++) {
            cout << marks[i] << " ";
        }
        cout << endl;
    }

    ~Marks() {
        delete [] marks;
    }
};

class Person {
    string firstName;
    string lastName;
    int age;
    
public:
    int static personCount;

    Person() {
        cout << "In default constructor" << endl;
        this->firstName = "Test";
        lastName = "Test";
        age = 1;
        personCount++;
    }

    Person(string firstName, string lastName, int age) 
        : firstName(firstName), lastName(lastName), age(age) {
        cout << "In custom 1 Person constructor" << endl;
        personCount++;
    }

    Person(string firstName) : firstName(firstName) {
        cout << "In custom 2 Person constructor" << endl;
        personCount++;
    }

    string getFirstName() {
        return firstName;
    }
    
    string getLastName() {
        return lastName;
    }

    int getAge() {
        return age;
    }

    void printInfo() {
        cout << "FirstName: " << firstName << endl;
        cout << "LastName: " << lastName << endl;
        cout << "Age: " << age << endl;
    }

    ~Person() {
        cout << "In Person destructor" << endl;
        personCount--;
    }
};

int Person::personCount = 0;

// Explaination about private, public, protected inheritance mode:
// https://www.programiz.com/cpp-programming/public-protected-private-inheritance
class Student : public Person {
    Marks marks;
public:
    Student() {
       cout << "In Student default constructor" << endl;
    }

    Student(string firstName, string lastName, int age, Marks marks) 
    : Person(firstName, lastName, age) {
        cout << "In Student custom constructor" << endl;
        this->marks = marks;
    }

    void printInfo() {
        Person::printInfo();
        cout << "Marks: ";
        for (int i = 0; i < marks.getSize(); i++) {
            cout << marks.getMarks()[i] << " ";
        }
        cout << endl;
    }

    ~Student() {
        cout << "In Student destructor" << endl;
    }
};

int main() {
    Person* person = new Person("Pesho", "Petrov", 16);
    
    double* marks = new double[2];
    marks[0] = 6;
    marks[1] = 5;
    
    Marks m(marks, 2, 2);
    Marks* m1 = new Marks(marks, 2, 2);
    Marks* m2 = new Marks(*m1);
    Marks* m3 = new Marks();
    *m3 = *m1;

    m.printMarks();
    cout << &m << endl;
    m1->printMarks();
    cout << m1 << endl;
    m2->printMarks();
    cout << m2 << endl;
    m3->printMarks();
    cout << m3 << endl;

    Student* student = new Student("Ivan", "Ivanov", 17, m);
    student->printInfo();

    cout << student->personCount << endl;
    delete person;
    cout << student->personCount << endl;
    delete student;
    cout << student->personCount << endl;

    return 0;
}
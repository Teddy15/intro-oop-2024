#include <iostream>
#include <cstring>
#include <exception>
#include <string>
#include <sstream>

using namespace std;

class Registry {
protected:
    char* registryName;
    string* records;
    size_t numberOfRecords;
public:
    static int numberOfActiveRegistries;

    Registry() {
        registryName = new char[2];
        registryName[0] = ' ';
        registryName[1] = '\0';
        records = new string[2];
        numberOfRecords = 2;
        numberOfActiveRegistries++;
    }

    Registry(const char *registryName, const string *records, size_t numberOfRecords) {
        if (numberOfRecords <= 0 || registryName == nullptr || records == nullptr) {
            throw "error";
        }

        this->registryName = new char[strlen(registryName) + 1];
        strcpy(this->registryName, registryName);

        this->records = new string[numberOfRecords];
        for (int i = 0; i < numberOfRecords; i++) {
            this->records[i] = records[i];
        }

        this->numberOfRecords = numberOfRecords;

        numberOfActiveRegistries;
    }

    Registry(const Registry &other) : Registry(other.registryName, other.records, other.numberOfRecords) {}

    ~Registry() {
        cout << "destructor super" << endl;
        delete [] registryName;
        delete [] records;
        numberOfActiveRegistries--;
    }

    Registry &operator=(const Registry &other) {
        if (this != &other) {
            delete [] this->registryName;
            delete [] this->records;

            this->registryName = new char[strlen(other.registryName) + 1];
            strcpy(this->registryName, other.registryName);

            this->records = new string[other.numberOfRecords];
            for (int i = 0; i < other.numberOfRecords; i++) {
                this->records[i] = other.records[i];
            }

            this->numberOfRecords = other.numberOfRecords;
        }

        return *this;
    }

    static int getActiveRegistries() {
        return numberOfActiveRegistries;
    }

    void printRegistryInformation() const {
        cout << this->registryName << endl;
        for (int i = 0; i < this->numberOfRecords; i++) {
            cout << this->records[i] << endl;
        }
    }
};

int Registry::numberOfActiveRegistries = 0;

class PhoneRegistry : public Registry {
    string* phoneNumbers;
    size_t numberOfPhoneNumbers;
public:
    PhoneRegistry(const char *registryName, const string *records, size_t numberOfRecords, const string *phoneNumbers, size_t numberOfPhoneNumbers) 
    : Registry (registryName, records, numberOfRecords) {
        if (phoneNumbers == nullptr || numberOfPhoneNumbers <= 0) {
            throw "error";
        }

        this->numberOfPhoneNumbers = numberOfPhoneNumbers;
        this->phoneNumbers = new string[numberOfPhoneNumbers];
        for (int i = 0; i < numberOfPhoneNumbers; i++) {
            this->phoneNumbers[i] = phoneNumbers[i];
        }
    }

    PhoneRegistry(const PhoneRegistry &other) 
    : PhoneRegistry(other.registryName, other.records, other.numberOfRecords, other.phoneNumbers, other.numberOfPhoneNumbers) {}

    ~PhoneRegistry() {
        cout << "destructor" << endl;
        delete [] phoneNumbers;
    }

    PhoneRegistry &operator=(const PhoneRegistry &other) {
        if (this != &other) {
            Registry::operator=(other);
            
            delete [] phoneNumbers;
            
            this->numberOfPhoneNumbers = other.numberOfPhoneNumbers;
            this->phoneNumbers = new string[this->numberOfPhoneNumbers];
            for (int i = 0; i < this->numberOfPhoneNumbers; i++) {
                this->phoneNumbers[i] = other.phoneNumbers[i];
            }
        }

        return *this;
    }

    void printRegistryInformation() const {
        cout << this->registryName << endl;
        for (int i = 0; i < this->numberOfRecords; i++) {
            cout << this->records[i];
            if (i >= numberOfPhoneNumbers) {
                cout << " - ";
            } else {
                cout << " " << this->phoneNumbers[i];
            }
            cout << endl;
        }
    }
};

int main() {
    string* records = new string[2];
    records[0] =  "record1";
    records[1] = "record2";
    string* phoneNumbers = new string[1];
    phoneNumbers[0] = "00000";
    PhoneRegistry p("name", records, 2, phoneNumbers, 1);
    p.printRegistryInformation();

    int a = 10;
    stringstream s;
    s << a; // this will get the integer 10 and keep it as string in the stream

    string b;
    s >> b;

    cout << a << " " << b << endl;

    string line = "What a good day not to check homeworks!";
    stringstream ss(line);
    string word;
    
    while (ss >> word) {
        cout << word << endl;
    }

    getline(cin, word);
    cout << word << endl;


    while(1) {
        getline(cin, word);
        if (word == "q") {
            break;
        }
        cout << word << endl;
    }
    return 0;
}
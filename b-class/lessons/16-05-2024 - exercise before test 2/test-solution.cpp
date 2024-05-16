#include <iostream>
#include <cstring>
#include <exception>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class Registry {
protected:
    char* registryName;
    string* records;
    size_t numberOfRecords;
public:
    static int numberOfActiveRegistries;

    Registry() {
        registryName = new char[1];
        registryName[0] = '\0';
        records = new string[1];
        numberOfRecords++;

        numberOfActiveRegistries++;
    }

    Registry(const char *registryName, const string *records, size_t numberOfRecords) {
        if (registryName == nullptr || records == nullptr || numberOfRecords <=0) {
            throw "Invalid arguments";
        }

        this->registryName = new char[strlen(registryName) + 1];
        strcpy(this->registryName, registryName);

        this->records = new string[numberOfRecords];
        for(size_t i = 0; i < numberOfRecords; i++) {
            this->records[i] = records[i];
        }

        this->numberOfRecords = numberOfRecords;
        numberOfActiveRegistries++;
    }

    Registry(const Registry &other) : Registry(other.registryName, other.records, other.numberOfRecords) {}

    ~Registry() {
        cout << "In destructor ~Registry()" << endl;
        delete [] registryName;
        delete [] records;
        numberOfActiveRegistries--;
    }

    Registry &operator=(const Registry &other) {
        if (this != &other) {
            delete [] registryName;
            delete [] records;

            this->registryName = new char[strlen(other.registryName) + 1];
            strcpy(this->registryName, other.registryName);

            this->records = new string[other.numberOfRecords];
            for(size_t i = 0; i < other.numberOfRecords; i++) {
                this->records[i] = other.records[i];
            }

            this->numberOfRecords = other.numberOfRecords;
        }

        return *this;
    }

    static int getActiveRegistries() {
        return numberOfActiveRegistries;
    }

    virtual void printRegistryInformation() const = 0;
};

int Registry::numberOfActiveRegistries = 0;

class PhoneRegistry : public Registry {
    string* phoneNumbers;
    size_t numberOfPhoneNumbers;
public:
    PhoneRegistry(const char *registryName, const string *records, size_t numberOfRecords, const string *phoneNumbers, size_t numberOfPhoneNumbers) 
    : Registry(registryName, records, numberOfRecords) {
        if (phoneNumbers == nullptr || numberOfPhoneNumbers <= 0) {
            throw "Invalid arguments";
        }

        this->phoneNumbers = new string[numberOfPhoneNumbers];
        for (size_t i = 0; i < numberOfPhoneNumbers; i++) {
            this->phoneNumbers[i] = phoneNumbers[i];
        }

        this->numberOfPhoneNumbers = numberOfPhoneNumbers;
    }
    

    PhoneRegistry(const PhoneRegistry &other) 
    : PhoneRegistry(other.registryName, other.records, other.numberOfRecords, other.phoneNumbers, other.numberOfPhoneNumbers) {}
    
    ~PhoneRegistry() {
        cout << "In destructor ~PhoneRegistry()" << endl;
        delete [] phoneNumbers;
    }

    PhoneRegistry& operator=(const PhoneRegistry &other) {
        if (this != &other) {
            Registry::operator=(other);
            
            delete [] phoneNumbers;

            this->phoneNumbers = new string[other.numberOfPhoneNumbers];
            for (size_t i = 0; i < other.numberOfPhoneNumbers; i++) {
                this->phoneNumbers[i] = other.phoneNumbers[i];
            }

            this->numberOfPhoneNumbers = other.numberOfPhoneNumbers;

        }

        return *this;
    }

    virtual void printRegistryInformation() const {
        cout << this->registryName << endl;
        for (size_t i = 0; i < numberOfRecords; i++) {
            cout << this->records[i] << " ";
            if (i < numberOfPhoneNumbers)  {
                cout << this->phoneNumbers[i];
            }
            cout << endl;
        }
    }

    friend istream& operator>>(istream& in, PhoneRegistry& phoneRegistry);
    friend ostream& operator<<(ostream& out, PhoneRegistry& phoneRegistry);

};

istream& operator>>(istream& in, PhoneRegistry& phoneRegistry) {
    // Delete memory for the properties of the object
    delete [] phoneRegistry.registryName;
    delete [] phoneRegistry.records;
    delete [] phoneRegistry.phoneNumbers;

    // Read the file content line
    string line;
    getline(in, line);
    stringstream s(line);

    // Read the registryName in a temp variable
    char* name = new char[50];
    s >> name;

    // Allocate the registryName using strlen(name) + 1 as size
    phoneRegistry.registryName = new char[strlen(name)+1];
    strcpy(phoneRegistry.registryName, name);

    // Read the number of records and allocate memory for the array
    s >> phoneRegistry.numberOfRecords;
    phoneRegistry.records = new string[phoneRegistry.numberOfRecords];
    for (size_t i = 0; i < phoneRegistry.numberOfRecords; i++) {
        s >> phoneRegistry.records[i];
    }    
    
    // Read the number of phone numbers and allocate memory for the array
    s >> phoneRegistry.numberOfPhoneNumbers;
    phoneRegistry.phoneNumbers = new string[phoneRegistry.numberOfPhoneNumbers];
    for (size_t i = 0; i < phoneRegistry.numberOfPhoneNumbers; i++) {
        s >> phoneRegistry.phoneNumbers[i];
    } 

    return in;
}

ostream& operator<<(ostream& out, PhoneRegistry& phoneRegistry) {
    out << phoneRegistry.registryName << " ";
    for (size_t i = 0; i < phoneRegistry.numberOfRecords; i++) {
        out << phoneRegistry.records[i] << " ";
    }
    out << phoneRegistry.numberOfRecords << " ";

    for (size_t i = 0; i < phoneRegistry.numberOfPhoneNumbers; i++) {
        out << phoneRegistry.phoneNumbers[i] << " ";
    }
    out << phoneRegistry.numberOfPhoneNumbers << endl;

    return out;
}

int main() {
    PhoneRegistry* r = new PhoneRegistry("Name", new string[1]{"record"}, 1, new string[1]{"number"}, 1);
    r->printRegistryInformation();
    
    // When using ifstream, you do not need to specify ios::in, it is the default mode.
    // If you use fstream, then you need to add ios::in -> fstream f("input.txt", ios::in);
    ifstream inputFile("input.txt");
    inputFile >> *r;
    inputFile.close();
    
    r->printRegistryInformation();
    
    // When using ofstream, you do not need to specify ios::out, it is the default mode.
    // If you use fstream, then you need to add ios::out -> fstream f("output.txt", ios::out);

    // Use trunc mode to always display latest results from the programme.
    ofstream outputFile("output.txt", ios::trunc);
    outputFile << *r;
    outputFile.close();

    delete r;
    return 0;
}
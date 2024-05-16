#include <iostream>
#include <string>
#include <cstring>
#include <exception>
#include <sstream>
#include <fstream>

using namespace std;

class Race {
protected:
    char* raceName;
    double* results;
    size_t numberOfResults;
public: 
    static int numberOfTotalRaces;

    Race() {
        raceName = new char[1];
        raceName[0] = '\0';
        results = new double[1];
        results[0] = 0.0;
        numberOfResults = 1;

        numberOfTotalRaces++;
    }

    Race(const char *raceName, const double *results, size_t numberOfResults) {
        if (numberOfResults <= 0 || results == nullptr || raceName == nullptr) {
            throw "error";
        }

        this->raceName = new char[strlen(raceName) + 1];
        strcpy(this->raceName, raceName);

        this->numberOfResults = numberOfResults;
        this->results = new double[this->numberOfResults];
        for (int i = 0; i < numberOfResults; i++) {
            this->results[i] = results[i];
        }

        numberOfTotalRaces++;
    }

    Race(const Race &other) : Race(other.raceName, other.results, other.numberOfResults) {}

    ~Race() {
        cout << "in race destructor" << endl;
        delete [] raceName;
        delete [] results;
        numberOfTotalRaces--;
    }

    Race &operator=(const Race &other) {
        if (this != &other) {
            delete [] raceName;
            delete [] results;

            this->raceName = new char[strlen(other.raceName) + 1];
            strcpy(this->raceName, other.raceName);

            this->numberOfResults = other.numberOfResults;
            this->results = new double[this->numberOfResults];
            for (int i = 0; i < other.numberOfResults; i++) {
                this->results[i] = other.results[i];
            }
        }
        return *this;
    }

    int getTotalRaces () const {
        return numberOfTotalRaces;
    }

    virtual void printRaceInformation() const = 0;
};

int Race::numberOfTotalRaces = 0;

class Formula1Race : public Race {
    string* teams;
    size_t numberOfTeams;
public:
    Formula1Race(const char *raceName, const double *results, size_t numberOfResults, const string *teams, size_t numberOfTeams) 
    : Race(raceName, results, numberOfResults) {
        if (numberOfTeams <= 0 || teams == nullptr) {
            throw "error";
        }

        this->numberOfTeams = numberOfTeams;
        this->teams = new string[numberOfTeams];
        for (int i = 0; i < numberOfTeams; i++) {
            this->teams[i] = teams[i];
        }
    }

    Formula1Race(const Formula1Race &other) 
    : Formula1Race(other.raceName, other.results, other.numberOfResults, other.teams, other.numberOfTeams) {}

    ~Formula1Race() {
        cout << "in f1 destructor" << endl;
        delete [] teams;
    }

    Formula1Race &operator=(const Formula1Race &other) {
        if (this != &other) {
            Race::operator=(other);
            delete [] teams;

            this->numberOfTeams = other.numberOfTeams;
            this->teams = new string[other.numberOfTeams];
            for (int i = 0; i < other.numberOfTeams; i++) {
                this->teams[i] = other.teams[i];
            }
        }

        return *this;
    }

    void printRaceInformation() const {
        double averageScore = 0.0;
        for (int i = 0; i < numberOfResults; i++) {
            averageScore += results[i];
        }

        averageScore = averageScore / numberOfResults;
        cout << getTotalRaces() << " " << raceName << " " << averageScore << endl;

        for (int i = 0; i < numberOfTeams; i++) {
            cout << teams[i] << endl;
        }
    }

    friend istream& operator>>(istream& in, Formula1Race& race);
    friend ostream& operator<<(ostream& out, Formula1Race& race);
};

istream& operator>>(istream& in, Formula1Race& race) {
        // Delete memory for the properties of the object
    delete [] race.raceName;
    delete [] race.results;
    delete [] race.teams;

    // Read the file content line
    string line;
    getline(in, line);
    stringstream s(line);

    // Read the registryName in a temp variable
    char* name = new char[50];
    s >> name;

    // Allocate the racName using strlen(name) + 1 as size
    race.raceName = new char[strlen(name)+1];
    strcpy(race.raceName, name);

    // Read the number of results and allocate memory for the array
    s >> race.numberOfResults;
    race.results = new double[race.numberOfResults];
    for (size_t i = 0; i < race.numberOfResults; i++) {
        s >> race.results[i];
    }    
    
    // Read the number of teams and allocate memory for the array
    s >> race.numberOfTeams;
    race.teams = new string[race.numberOfTeams];
    for (size_t i = 0; i < race.numberOfTeams; i++) {
        s >> race.teams[i];
    } 

    return in;
}

ostream& operator<<(ostream& out, Formula1Race& race) {
    out << race.raceName << " ";
    for (size_t i = 0; i < race.numberOfResults; i++) {
        out << race.results[i] << " ";
    }

    out << race.numberOfResults << " ";
    
    for (size_t i = 0; i < race.numberOfTeams; i++) {
        out << race.teams[i] << " ";
    }

    out << race.numberOfTeams << endl;
    
    return out;
}

int main() {
    double* results = new double[2]{2.5, 3.4};
    string* teams = new string[2]{"team1", "team2"};

    Formula1Race f("race name", results, 2, teams, 2);
    f.printRaceInformation();
    f.getTotalRaces();

    // When using ifstream, you do not need to specify ios::in, it is the default mode.
    // If you use fstream, then you need to add ios::in -> fstream f("input.txt", ios::in);
    ifstream inputFile("input.txt");
    inputFile >> f;
    inputFile.close();
    
    f.printRaceInformation();
    
    // When using ofstream, you do not need to specify ios::out, it is the default mode.
    // If you use fstream, then you need to add ios::out -> fstream f("output.txt", ios::out);

    // Use trunc mode to always display latest results from the programme.
    ofstream outputFile("output.txt", ios::trunc);
    outputFile << f;
    outputFile.close();
    return 0;
}
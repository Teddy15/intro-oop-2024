#include <iostream>
#include <string>
#include <cstring>
#include <exception>

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

    void printRaceInformation() const {
        double averageScore = 0.0;
        for (int i = 0; i < numberOfResults; i++) {
            averageScore += results[i];
        }

        averageScore = averageScore / numberOfResults;
        cout << getTotalRaces() << " " << raceName << " " << averageScore << endl;
    }
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
        Race::printRaceInformation();
        for (int i = 0; i < numberOfTeams; i++) {
            cout << teams[i] << endl;
        }
    }
};

int main() {
    double* results = new double[2]{2.5, 3.4};
    string* teams = new string[2]{"team1", "team2"};

    Formula1Race f("race name", results, 2, teams, 2);
    f.printRaceInformation();
    f.getTotalRaces();
    return 0;
}
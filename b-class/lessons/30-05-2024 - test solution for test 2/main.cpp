#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Place {
	string tenantName;
	double area;
	int floor;
public:
    Place() {
		tenantName = "";
		area = 0.0;
		floor = 0;
	}

    friend istream &operator>>(istream &in, Place &p) {
		string tenantName;
		double area;
		int floor;

		in >> tenantName >> floor >> area;

		if (tenantName.empty() || floor < 0 || area < 0) {
			throw "Invalid place data";
		}

		p.tenantName = tenantName;
		p.floor = floor;
		p.area = area;

		return in;
    }

	string getTenantName() const {
		return tenantName;
	}

	double getArea() const {
		return area;
	}

	int getFloor() const {
		return floor;
	}
};

class Building {
	string address;
	vector<Place> places; 
public:
    double calculateTotalArea() const {
		double totalArea = 0;

		for (int i = 0; i < places.size(); i++) {
			totalArea += places[i].getArea();
		}

		return totalArea;
	}

    double estimateReturn(unsigned months) const {
		return calculateTotalArea() * months * getPricePerMonth();
    }

    double estimateNetReturn(unsigned months) const {
		return estimateReturn(months) - (calculateTotalArea() * estimateExpenses(months));
	}

    friend istream &operator>>(istream &in, Building &b) {
		string address;
		int count;
		
		getline(in, address);
		in >> count;

		if (address.empty() || count <= 0) {
			throw "Invalid Building data";
		}

		for (int i = 0; i < count; i++) {
			Place p;
			in >> p;
			b.places.push_back(p);
		}

		return in;
	}

    virtual double getPricePerMonth() const = 0;
    virtual double estimateExpenses(unsigned months) const = 0;
};

class House : public Building {
public:
	double getPricePerMonth() const {
		return 1000;
	}
    
	double estimateExpenses(unsigned months) const {
		return months * 100;
	}
};

class Office : public Building {
public:
	double getPricePerMonth() const {
		return 2000;
	}
	
	double estimateExpenses(unsigned months) const {
		return months * 200;
	}
};

int main() {
    vector<Building*> buildings;
	fstream file("buildings.txt", ios::in);

	if (!file.is_open()) {
		cerr << "Error opening file" << endl;
		return 1;
	}

	int months;
	file >> months;

	string buildingType;
	
	while(!file.eof()) {

		getline(file, buildingType);

		try {
			if (buildingType == "House") {
				Building* b = new House();
				file >> *b;
				buildings.push_back(b);
			} 
			
			if (buildingType == "Office") {
				Building* b = new Office();
				file >> *b;
				buildings.push_back(b);
			} 
		} catch (const char* message) {
			cout << message << endl;
		}
	}

	file.close();

	double totalIncome = 0;
	double totalNetIncome = 0;

	for (int i = 0; i < buildings.size(); i++) {
		totalIncome += buildings[i]->estimateReturn(months);
		totalNetIncome += buildings[i]->estimateNetReturn(months);
	}

	cout << "Total income: " << totalIncome << " USD" << endl;
	cout << "Total net income: " << totalNetIncome << " USD" << endl;

    return 0;
}
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Currency {
	string name;
	double price;
	double amount;
public:
	Currency() {
		name = "";
		price = 0;
		amount = 0;
	}

    friend istream &operator>>(istream &in, Currency &bet) {
		string name;
		double price, amount;
		in >> name >> price >> amount;
		if (name.empty() || price < 0 || amount < 0) {
			throw "Invalid currency data";
		}
		bet.name = name;
		bet.price = price;
		bet.amount = amount;

		return in;
	}

	string getName() const {
		return name;
	}

	double getPrice() const {
		return price;
	}

	double getAmount() const {
		return amount;
	}
};

class Portfolio {
	string name;
	vector<Currency> currencies; 
public:
    double calculateTotalPortfolioBalance() const {
		double totalAmount = 0;
		for (int i = 0; i < currencies.size(); i++) {
			totalAmount += currencies.at(i).getPrice() * currencies.at(i).getAmount();
		}
		return totalAmount;
	}

    double estimateReturn() const {
		return calculateTotalPortfolioBalance() * getRisk() / 100;
	}

    double estimateReturnAfterTax() const {
		return estimateReturn() - (estimateReturn() * getTax() / 100);
	}

    virtual double getTax() const = 0;
    virtual double getRisk() const = 0;

    friend istream &operator>>(istream &in, Portfolio &portfolio) {
		string name;
		int count;
		
		in >> name;
		in >> count;

		if (name.empty() || count <= 0) {
			throw "Invalid portfolio data";
		}

		portfolio.name = name;

		for (int i = 0; i < count; i++) {
			Currency c;
			in >> c;
			portfolio.currencies.push_back(c);
		}

		return in;
    }

	string getName() const {
		return name;
	}

	vector<Currency>& getCurrencies() {
		return currencies;
	}
};

class CryptoPortfolio : public Portfolio {
public:
	double getRisk() const {
		return 1000;
	}

	double getTax() const {
		return 10;
	}
};

class StocksPortfolio: public Portfolio {
public:
	double getRisk() const {
		return 10;
	}

	double getTax() const {
		return 0;
	}
};

int main()
{
    vector<Portfolio *> arr;
	ifstream file("portfolios.txt"); // file.open("portfolios.txt")
	if (!file.is_open()) {
		cerr << "Error opening file" << endl;
		return 1;
	}

	string type;
	Portfolio* portfolio;
	try {
		while (!file.eof()) {
			file >> type;
			if (type == "C") {
				portfolio = new CryptoPortfolio();
			} else if (type == "S") {
				portfolio = new StocksPortfolio();
			} else {
				cerr << "Invalid portfolio type" << endl;
				return 2;
			}
			file >> *portfolio;
			arr.push_back(portfolio);
		}
	} catch (const char* message) {
		cout << message << endl;
	}

	file.close();

	double totalIncome = 0;
	double totalNetIncome = 0;
	for (int i = 0; i < arr.size(); i++) {
		totalIncome += arr.at(i)->estimateReturn();
		totalNetIncome += arr.at(i)->estimateReturnAfterTax();
	}

	cout << "Total income: " << totalIncome << " USD" << endl;
	cout << "Total net income: " << totalNetIncome << " USD" << endl;

    return 0;
}
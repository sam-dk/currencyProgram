#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <sstream>
using namespace std;

struct Currency
{
    string cAbb;
    double exchangeRate;
    string cType;
    string country;
};

unordered_map<string, Currency> createMap(string filename)
{
    unordered_map<string, Currency> m;
    ifstream fin(filename);
    string line;
    string abb;
    Currency curr;
    while(getline(fin, line))
    {
        stringstream ss(line);
        string word;
        getline(ss, abb, ',');
        m.insert(make_pair(abb, curr));
        m.at(abb).cAbb = abb;

        getline(ss, word, ',');
        m.at(abb).exchangeRate = stod(word);

        getline(ss, word, ',');
        m.at(abb).cType = word;

        getline(ss, word, ',');
        m.at(abb).country = word;
    }
    return m;
}

void getRates(unordered_map<string, Currency> m, string currCountry, string xferCountry, double amount, double exchangeRateNew)
{
    double newAmount;
    newAmount = (amount/m.at(currCountry).exchangeRate) * exchangeRateNew;
    cout << to_string((int)amount) << " " << m.at(currCountry).country << "(" << m.at(currCountry).cType<< ") is equal to " << fixed << setprecision(2) << setfill('0') <<
        newAmount << " " << m.at(xferCountry).country << "(" << m.at(xferCountry).cType << ")" << endl;
}

int main()
{
    unordered_map<string, Currency> map = createMap("CurrentCCAV.csv");
    string currCountry;
    string xferCountry;
    double amount;
    double exchangeRateNew;

    ifstream fin("exchange.csv");
    string line;
    string word;
    while(getline(fin, line))
    {
        stringstream ss(line);
        getline(ss, word, ',');
        currCountry = word;
        getline(ss, word, ',');
        amount = stod(word);
        getline(ss, word, ',');
        xferCountry = word;
        exchangeRateNew = map.at(xferCountry).exchangeRate;
        
        getRates(map, currCountry, xferCountry, amount, exchangeRateNew);
    }
}
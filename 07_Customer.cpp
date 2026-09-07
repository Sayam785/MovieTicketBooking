#pragma once
#include <string>
using namespace std;


class Customer {
private:
    string name;
    string phone;

public:
    
    explicit Customer(const string& name) {
        this->name = name;
        this->phone = "N/A";
    }

    Customer(const string& name, const string& phone) {
        this->name = name;
        this->phone = phone;
    }

    string getName() const { return name; }
    string getPhone() const { return phone; }
};

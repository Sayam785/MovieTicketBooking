#pragma once
#include <iostream>
#include <string>
#include "09_Payment.cpp"
using namespace std;


class UpiPayment : public Payment {
private:
    string upiId;

public:
    explicit UpiPayment(const string& upiId) {
        this->upiId = upiId;
    }

    bool pay(double amount) override {
        cout << "  [UPI] Rs." << amount << " paid successfully" << endl;
        return true;
    }
};


class CardPayment : public Payment {
private:
    string cardNumber;

public:
    explicit CardPayment(const string& cardNumber) {
        this->cardNumber = cardNumber;
    }

    bool pay(double amount) override {
        bool isTestFailureCard = (cardNumber == "0000");
        if (isTestFailureCard) {
            cout << "  [CARD] Payment declined" << endl;
            return false;
        }
        cout << "  [CARD] Rs." << amount << " paid successfully" << endl;
        return true;
    }
};


class CashPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "  [CASH] Rs." << amount << " received successfully" << endl;
        return true;
    }
};

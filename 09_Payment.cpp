#pragma once


class Payment {
protected:
    double amount;

public:
  
    virtual bool pay(double amount) = 0;
    virtual ~Payment() {}
};

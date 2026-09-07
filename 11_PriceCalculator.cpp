#pragma once
#include <vector>
#include "06_ShowSeat.cpp"
using namespace std;


class PriceCalculator {
private:
   
    static constexpr double SILVER_PRICE = 150.0;
    static constexpr double GOLD_PRICE = 250.0;
    static constexpr double PLATINUM_PRICE = 400.0;

    static double priceOf(SeatType type) {
        if (type == SeatType::SILVER) return SILVER_PRICE;
        if (type == SeatType::GOLD) return GOLD_PRICE;
        return PLATINUM_PRICE;
    }

public:
    static double calculateTotal(const vector<ShowSeat*>& seats) {
        double total = 0.0;
        for (ShowSeat* seat : seats) {
            total += priceOf(seat->getSeat().getType());
        }
        return total;
    }
};

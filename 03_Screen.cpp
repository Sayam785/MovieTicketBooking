#pragma once
#include <vector>
#include "02_Seat.cpp"
using namespace std;


class Screen {
private:
    int screenNumber;
    vector<Seat> seats;

public:
    explicit Screen(int screenNumber) {
        this->screenNumber = screenNumber;
    }

    void addSeat(const Seat& seat) {
        seats.push_back(seat);
    }

    vector<Seat>& getSeats() { return seats; }
    int getScreenNumber() const { return screenNumber; }
};

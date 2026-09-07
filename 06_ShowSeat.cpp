#pragma once
#include "02_Seat.cpp"


enum class SeatStatus { AVAILABLE, BOOKED };

class ShowSeat {
private:
    Seat seat;
    SeatStatus status;

public:
    explicit ShowSeat(const Seat& seat) : seat(seat) {
        status = SeatStatus::AVAILABLE;
    }

    bool isAvailable() const { return status == SeatStatus::AVAILABLE; }

    void book() { status = SeatStatus::BOOKED; }
    void release() { status = SeatStatus::AVAILABLE; }

    Seat getSeat() const { return seat; }
};

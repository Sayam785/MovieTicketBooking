#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "08_Booking.cpp"
using namespace std;


class TicketPrinter {
public:
    
    void printTicket(Booking* booking) const {
        cout << "\n  ================ TICKET ================" << endl;
        cout << "   Booking ID : " << booking->getBookingId() << endl;
        cout << "   Movie      : " << booking->getShow()->getMovie()->getTitle() << endl;
        cout << "   Screen     : Screen-" << booking->getShow()->getScreen()->getScreenNumber()
             << "   " << booking->getShow()->getStartTime() << endl;
        cout << "   Seats      : " << seatListText(booking) << endl;
        cout << "   Amount     : Rs." << booking->getTotalAmount()
             << "\tStatus: " << statusName(booking->getStatus()) << endl;
        cout << "  =========================================" << endl;
    }

private:
    string seatListText(Booking* booking) const {
        vector<ShowSeat*> seats = booking->getBookedSeats();
        string result;
        for (size_t i = 0; i < seats.size(); ++i) {
            bool isFirstSeat = (i == 0);
            if (!isFirstSeat) {
                result += ", ";
            }
            result += seats[i]->getSeat().getSeatNumber();
        }
        return result;
    }

    string statusName(BookingStatus status) const {
        if (status == BookingStatus::CONFIRMED) return "CONFIRMED";
        if (status == BookingStatus::CANCELLED) return "CANCELLED";
        if (status == BookingStatus::FAILED) return "FAILED";
        return "PENDING";
    }
};

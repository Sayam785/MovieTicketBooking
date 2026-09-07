#pragma once
#include <vector>
#include <string>
#include <sstream>
#include "05_Show.cpp"
#include "07_Customer.cpp"
using namespace std;

enum class BookingStatus { PENDING, CONFIRMED, FAILED, CANCELLED };


class Booking {
private:
    
    static int nextBookingId;

    string bookingId;
    Show* show;
    Customer customer;
    vector<ShowSeat*> bookedSeats;
    double totalAmount;
    BookingStatus status;

public:
    Booking(Show* show, const Customer& customer, const vector<ShowSeat*>& bookedSeats, double totalAmount)
        : customer(customer) {
        this->show = show;
        this->bookedSeats = bookedSeats;
        this->totalAmount = totalAmount;
        this->status = BookingStatus::PENDING;

        ++nextBookingId;
        stringstream idStream;
        idStream << "BK" << (1000 + nextBookingId);
        this->bookingId = idStream.str();
    }

    void confirm() { status = BookingStatus::CONFIRMED; }

   
    void cancel() {
        for (ShowSeat* seat : bookedSeats) {
            seat->release();
        }
        status = BookingStatus::CANCELLED;
    }

    string getBookingId() const { return bookingId; }
    BookingStatus getStatus() const { return status; }
    double getTotalAmount() const { return totalAmount; }
    Show* getShow() const { return show; }
    Customer getCustomer() const { return customer; }
    vector<ShowSeat*> getBookedSeats() const { return bookedSeats; }
};

int Booking::nextBookingId = 0;

#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "05_Show.cpp"
#include "07_Customer.cpp"
#include "08_Booking.cpp"
#include "10_PaymentTypes.cpp"
#include "11_PriceCalculator.cpp"
#include "12_TicketPrinter.cpp"
using namespace std;


class BookingService {
private:
    vector<Booking*> bookings;
    TicketPrinter ticketPrinter;

public:
    
    vector<ShowSeat*> holdSeatsIfAvailable(Show* show, const vector<string>& seatNumbers) {
        vector<ShowSeat*> seatsToBook = findAvailableSeats(show, seatNumbers);
        if (!seatsToBook.empty()) {
            holdSeats(seatsToBook);
        }
        return seatsToBook;
    }

    
    Booking* chargeAndConfirm(Show* show, const Customer& customer,
                               vector<ShowSeat*> heldSeats, Payment* payment) {
        double total = PriceCalculator::calculateTotal(heldSeats);

        bool paymentSucceeded = payment->pay(total); 
        delete payment;

        if (!paymentSucceeded) {
            releaseSeats(heldSeats);
            return nullptr; 
        }

        Booking* booking = new Booking(show, customer, heldSeats, total);
        booking->confirm();
        bookings.push_back(booking);

        ticketPrinter.printTicket(booking);
        return booking;
    }

  
    bool cancelBooking(const string& bookingId) {
        for (Booking* booking : bookings) {
            bool idMatches = (booking->getBookingId() == bookingId);
            bool isCancellable = (booking->getStatus() == BookingStatus::CONFIRMED);
            if (idMatches && isCancellable) {
                booking->cancel();
                return true;
            }
        }
        return false;
    }

    vector<Booking*> getAllBookings() const { return bookings; }

private:
    
    vector<ShowSeat*> findAvailableSeats(Show* show, const vector<string>& seatNumbers) {
        vector<ShowSeat*> result;
        for (const string& seatNumber : seatNumbers) {
            ShowSeat* seat = show->findShowSeat(seatNumber);
            bool seatExists = (seat != nullptr);
            if (!seatExists) {
                cout << "  Seat " << seatNumber << " does not exist. Booking rejected." << endl;
                return {};
            }
            bool seatIsFree = seat->isAvailable();
            if (!seatIsFree) {
                cout << "  Seat " << seatNumber << " is already booked. Booking rejected." << endl;
                return {};
            }
            result.push_back(seat);
        }
        return result;
    }

    void holdSeats(vector<ShowSeat*>& seats) {
        for (ShowSeat* seat : seats) {
            seat->book();
        }
    }

    void releaseSeats(vector<ShowSeat*>& seats) {
        for (ShowSeat* seat : seats) {
            seat->release();
        }
    }
};

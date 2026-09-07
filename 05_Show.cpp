#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "01_Movie.cpp"
#include "03_Screen.cpp"
#include "06_ShowSeat.cpp"
using namespace std;


class Show {
private:
    int showId;
    Movie* movie;
    Screen* screen;
    string startTime;
    vector<ShowSeat> showSeats;

public:
    Show(int showId, Movie* movie, Screen* screen, const string& startTime) {
        this->showId = showId;
        this->movie = movie;
        this->screen = screen;
        this->startTime = startTime;
        for (Seat& physicalSeat : screen->getSeats()) {
            showSeats.push_back(ShowSeat(physicalSeat));
        }
    }

    int getShowId() const { return showId; }
    string getStartTime() const { return startTime; }
    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    vector<ShowSeat>& getShowSeats() { return showSeats; }

   
    ShowSeat* findShowSeat(const string& seatNumber) {
        for (ShowSeat& showSeat : showSeats) {
            if (showSeat.getSeat().getSeatNumber() == seatNumber) {
                return &showSeat;
            }
        }
        return nullptr;
    }

   
    void printSeatLayout() const {
        cout << "  SCREEN-" << screen->getScreenNumber() << "  " << startTime
             << "  |  " << movie->getTitle() << endl;
        printSeatRow("SILVER", SeatType::SILVER);
        printSeatRow("GOLD", SeatType::GOLD);
        printSeatRow("PLATINUM", SeatType::PLATINUM);
        cout << "  ( [ ] = available   [X] = booked )" << endl;
    }

private:
    void printSeatRow(const string& label, SeatType type) const {
        cout << "  " << label;
        for (const ShowSeat& showSeat : showSeats) {
            bool sameType = (showSeat.getSeat().getType() == type);
            if (sameType) {
                cout << " " << showSeat.getSeat().getSeatNumber()
                     << (showSeat.isAvailable() ? "[ ]" : "[X]");
            }
        }
        cout << endl;
    }
};

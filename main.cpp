#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include "04_Cinema.cpp"
#include "13_BookingService.cpp"
using namespace std;


class CinemaApp {
private:
    Cinema cinema;
    vector<Show> shows;
    BookingService bookingService;

public:
    CinemaApp() : cinema("PVR Cinemas") {
        setupDemoData();
    }

    void run() {
        cout << "===== MOVIE TICKET BOOKING =====" << endl;
        int choice = -1;
        while (choice != 0) {
            printMenu();
            choice = readInt("Choose: ");
            handleChoice(choice);
        }
        cout << "Thank you for visiting " << cinema.getName() << "!" << endl;
    }

private:
   

    void setupDemoData() {
        static Movie movie1("3 Idiots", "Hindi", 170);
        static Movie movie2("Interstellar", "English", 169);

        Screen screen1(1);
        addNineSeats(screen1);
        Screen screen2(2);
        addNineSeats(screen2);

        cinema.addScreen(screen1);
        cinema.addScreen(screen2);

        shows.push_back(Show(1, &movie1, &cinema.getScreens()[0], "06:00 PM"));
        shows.push_back(Show(2, &movie1, &cinema.getScreens()[1], "09:00 PM"));
        shows.push_back(Show(3, &movie2, &cinema.getScreens()[0], "10:00 PM"));
    }

    void addNineSeats(Screen& screen) {
        screen.addSeat(Seat("A1", SeatType::SILVER));
        screen.addSeat(Seat("A2", SeatType::SILVER));
        screen.addSeat(Seat("A3", SeatType::SILVER));
        screen.addSeat(Seat("A4", SeatType::SILVER));
        screen.addSeat(Seat("B1", SeatType::GOLD));
        screen.addSeat(Seat("B2", SeatType::GOLD));
        screen.addSeat(Seat("B3", SeatType::GOLD));
        screen.addSeat(Seat("C1", SeatType::PLATINUM));
        screen.addSeat(Seat("C2", SeatType::PLATINUM));
    }

   

    void printMenu() const {
        cout << "\n1. Movies  2. Book  3. Cancel  4. My tickets  0. Exit" << endl;
    }

    void handleChoice(int choice) {
        if (choice == 1) { showMoviesMenu(); }
        else if (choice == 2) { handleBooking(); }
        else if (choice == 3) { handleCancellation(); }
        else if (choice == 4) { handleMyTickets(); }
        else if (choice == 0) { /* exiting */ }
        else { cout << "  Invalid menu choice. Please try again." << endl; }
    }


    void showMoviesMenu() {
        vector<Movie*> distinctMovies = getDistinctMovies();
        cout << endl;
        for (size_t i = 0; i < distinctMovies.size(); ++i) {
            Movie* movie = distinctMovies[i];
            cout << "  [" << (i + 1) << "] " << movie->getTitle()
                 << "\t" << movie->getLanguage()
                 << "\t" << movie->getDurationMinutes() << " min" << endl;
        }
    }

    

    void handleBooking() {
        Movie* movie = chooseMovie();
        if (movie == nullptr) return;

        Show* show = chooseShow(movie);
        if (show == nullptr) return;

        cout << endl;
        show->printSeatLayout(); // F3

        vector<string> seatNumbers = readSeatNumbers();
        if (seatNumbers.empty()) {
            cout << "  No seats entered." << endl;
            return;
        }

        
        vector<ShowSeat*> heldSeats = bookingService.holdSeatsIfAvailable(show, seatNumbers);
        if (heldSeats.empty()) {
            cout << "  Booking could not be completed." << endl;
            return;
        }

        Customer customer = readCustomer();
        Payment* payment = choosePayment(); // F6 method selection

        Booking* booking = bookingService.chargeAndConfirm(show, customer, heldSeats, payment);
        if (booking == nullptr) {
            cout << "  Booking could not be completed." << endl;
        }
    }

    
    Movie* chooseMovie() {
        vector<Movie*> distinctMovies = getDistinctMovies();
        cout << endl;
        for (size_t i = 0; i < distinctMovies.size(); ++i) {
            cout << "  [" << (i + 1) << "] " << distinctMovies[i]->getTitle() << endl;
        }
        int choice = readInt("Choose movie: ");
        bool isValidChoice = (choice >= 1 && choice <= (int)distinctMovies.size());
        if (!isValidChoice) {
            cout << "  Invalid movie choice." << endl;
            return nullptr;
        }
        return distinctMovies[choice - 1];
    }

    Show* chooseShow(Movie* movie) {
        vector<Show*> matchingShows = getShowsForMovie(movie);
        for (size_t i = 0; i < matchingShows.size(); ++i) {
            cout << "  [" << (i + 1) << "] Screen-" << matchingShows[i]->getScreen()->getScreenNumber()
                 << "\t" << matchingShows[i]->getStartTime() << endl;
        }
        int choice = readInt("Choose show: ");
        bool isValidChoice = (choice >= 1 && choice <= (int)matchingShows.size());
        if (!isValidChoice) {
            cout << "  Invalid show choice." << endl;
            return nullptr;
        }
        return matchingShows[choice - 1];
    }

    Customer readCustomer() {
        string name = readLine("Your name: ");
        return Customer(name);
    }

   
    Payment* choosePayment() {
        cout << "Pay by: 1.UPI  2.Card  3.Cash > ";
        int choice = readInt("");
        if (choice == 1) {
            string upiId = readLine("Enter UPI id: ");
            return new UpiPayment(upiId);
        }
        if (choice == 2) {
            string cardNumber = readLine("Enter card number (try 0000 to simulate failure): ");
            return new CardPayment(cardNumber);
        }
        return new CashPayment();
    }

   

    void handleCancellation() {
        string bookingId = readLine("Enter booking id to cancel: ");
        bool cancelled = bookingService.cancelBooking(bookingId);
        if (cancelled) {
            cout << "  Booking " << bookingId << " cancelled. Seats are AVAILABLE again." << endl;
        } else {
            cout << "  Booking id not found or already cancelled." << endl;
        }
    }

    void handleMyTickets() {
        vector<Booking*> allBookings = bookingService.getAllBookings();
        if (allBookings.empty()) {
            cout << "  No bookings yet." << endl;
            return;
        }
        for (Booking* booking : allBookings) {
            cout << "  " << booking->getBookingId()
                 << "  " << booking->getShow()->getMovie()->getTitle()
                 << "  Rs." << booking->getTotalAmount() << endl;
        }
    }


    vector<Movie*> getDistinctMovies() {
        vector<Movie*> distinctMovies;
        for (Show& show : shows) {
            bool alreadyAdded = false;
            for (Movie* seen : distinctMovies) {
                if (seen == show.getMovie()) alreadyAdded = true;
            }
            if (!alreadyAdded) distinctMovies.push_back(show.getMovie());
        }
        return distinctMovies;
    }

    vector<Show*> getShowsForMovie(Movie* movie) {
        vector<Show*> matchingShows;
        for (Show& show : shows) {
            if (show.getMovie() == movie) matchingShows.push_back(&show);
        }
        return matchingShows;
    }

   
    vector<string> readSeatNumbers() {
        string line = readLine("Seats (e.g. A1,B2): ");
        vector<string> seatNumbers;
        stringstream stream(line);
        string token;
        while (getline(stream, token, ',')) {
            string trimmed = trim(token);
            if (!trimmed.empty()) seatNumbers.push_back(trimmed);
        }
        return seatNumbers;
    }

    string trim(const string& text) {
        size_t start = text.find_first_not_of(" \t");
        size_t end = text.find_last_not_of(" \t");
        bool isAllWhitespace = (start == string::npos);
        if (isAllWhitespace) return "";
        return text.substr(start, end - start + 1);
    }

   
    int readInt(const string& prompt) {
        if (!prompt.empty()) cout << prompt;
        int value;
        while (!(cin >> value)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Please enter a number: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }

    string readLine(const string& prompt) {
        cout << prompt;
        string line;
        getline(cin, line);
        return line;
    }
};

int main() {
    CinemaApp app;
    app.run();
    return 0;
}

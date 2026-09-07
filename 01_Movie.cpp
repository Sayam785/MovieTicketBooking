#pragma once
#include <string>
using namespace std;


class Movie {
private:
    string title;
    string language;
    int durationMinutes;

public:
    Movie(const string& title, const string& language, int durationMinutes) {
      
        this->title = title;
        this->language = language;
        this->durationMinutes = durationMinutes;
    }

    string getTitle() const { return title; }
    string getLanguage() const { return language; }
    int getDurationMinutes() const { return durationMinutes; }
};

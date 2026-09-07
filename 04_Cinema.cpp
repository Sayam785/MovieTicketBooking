#pragma once
#include <vector>
#include <string>
#include "03_Screen.cpp"
using namespace std;


class Cinema {
private:
    string name;
    vector<Screen> screens;

public:
    explicit Cinema(const string& name) {
        this->name = name;
    }

    void addScreen(const Screen& screen) {
        screens.push_back(screen);
    }

    vector<Screen>& getScreens() { return screens; }
    string getName() const { return name; }
};

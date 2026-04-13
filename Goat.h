// Goat.h

#ifndef GOAT_H
#define GOAT_H
#include <iostream>
using namespace std;

class Goat {
private:
    string name;
    int age;
    string color;
public: 
    Goat()                          { name = ""; age = 0; color = ""; }
    // write three more constructors
    
    // constructor where they enter just the name
    Goat(string n) {
        name = n;
    }

    // constructor where they enter the name and age
    // with error checking for whole number age
    Goat(string n, int a) {
        name = n;
        if (a >= 0) 
            age = a;
        else {
            // if they entered a negative number, output a basic error message
            cout << "Age cannot be negative. Age is set to 0.";
            age = 0;
        }
    }

    // constructor that sets all three member variables
    // with error checking for whole number age
    Goat(string n, int a, string c) {
        name = n;
        if (a >= 0) 
            age = a;
        else {
            cout << "Age cannot be negative.  Age is set to 0.";
            age = 0;
        }
        color = c;
    }

    // setters and getters
    void set_name(string n)         { name = n; };
    string get_name() const         { return name; };
    void set_age(int a)             { age = a; };
    int get_age() const             { return age; }
    void set_color(string c)        { color = c; }
    string get_color() const        { return color; }

    // write overloaded < operator for the std::list
    bool operator< (const Goat &other) const {
        return this->name < other.name;
    }

    // I couldn't use remove() without also overloading ==
    // and I couldn't find another way to remove a selected list item
    bool operator== (const Goat &other) const {
        return this->name == other.name;
    }
};

#endif
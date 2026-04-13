// COMSC 210 | Lab 28 | Gillian Rhett
#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <limits> // for try-catch
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(const set<Goat>&);
void delete_goat(set<Goat>&);
void add_goat(set<Goat>&, string, int, string);
void display_trip(const set<Goat>&);
int main_menu();

int main() {
    srand(time(0));

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create a set for goats
    set <Goat> goats;

    int choice = 0;
    while (choice != 12) {
    // keep showing the menu after doing the action until user chooses 4 to quit
        choice = main_menu();
        if (choice == 1) { // add a goat
            // random inputs
            string rnd_name = names[rand() % (SZ_NAMES)];
            int rnd_age = rand() % (MAX_AGE + 1);
            string rnd_color = colors[rand() % (SZ_COLORS)];
            
            add_goat(goats, rnd_name, rnd_age, rnd_color);
        }
        if (choice == 2) { // delete a goat
            delete_goat(goats);
        }
        if (choice == 3) { // list goats
            display_trip(goats);
        }
        if (choice == 4) { // search for a goat
            
        }
        if (choice == 5) { // 
            
        }
        if (choice == 6) { // 
            
        }
        if (choice == 7) { // 
            
        }
        if (choice == 8) { // 
            
        }
        if (choice == 9) { // 
            
        }
        if (choice == 10) { // 
        }
        if (choice == 11) { // 
        }
        if (choice == 12) { // quit
            cout << "\tGoodbye." << endl;
        }
    }
    return 0;
}

int select_goat(const set<Goat>& gs) {
// return the index of a goat given the name input by user
    string nameIn; // user enters name of goat to delete
    cout << "Enter name of goat to delete: ";
    cin >> nameIn;
    int count = 0; // for checking whether we've reached the end of the set
    // search for a goat with this name
    for(const Goat g : gs){
        if (g.get_name() == nameIn) 
            break;
        count++;
    }
    if (count == gs.size()) {
        cout << "\tName not found." << endl;
        count = -1;
    }
    return count;
}

void delete_goat(set<Goat>& gs) {
// prompt the user for a name and delete the first instance of the goat with that name
    if(gs.size() == 0) {
        cout << "The set is empty." << endl;
        return;
    }
    int i = select_goat(gs); // i = index of the goat to delete
    int cur = 0; // current index in the for loop
    if (i != -1) { // if the goat was found
        for (Goat g : gs) {
            if (i == cur) {
                gs.erase(g);
                return;
            }
            cur++;
        }
    }
}

void add_goat(set<Goat>& gs, string name, int age, string color ) {
// create a new goat and add it to the set
    Goat g(name, age, color);
    gs.insert(g);
}

void display_trip(const set<Goat>& gs) {
// display a list of all the goats and their info
    if(gs.size() == 0) {
        cout << "The set is empty." << endl;
        return;
    }
    int count = 0; // for numbering the list of goats displayed
    for(const Goat g : gs){
        count++;
        cout << "\t[" << count << "] " << g.get_name() << " (" << g.get_age() << ", " << g.get_color() << ")" << endl;
    }
}

int main_menu() {
// display the menu and then obtain, validate, and return the user's choice
    int choice = 0; // will store user input
    cout << "*** GOAT MANAGER 3001 ***" << endl;
    cout << "[1] Add a goat" << endl;
    cout << "[2] Delete a goat" << endl;
    cout << "[3] List goats" << endl;
    cout << "[4] Search for a goat" << endl;
    cout << "[5] " << endl;
    cout << "[6] " << endl;
    cout << "[7] " << endl;
    cout << "[8] " << endl;
    cout << "[9] " << endl;
    cout << "[10] " << endl;
    cout << "[11] " << endl;
    cout << "[12] Quit" << endl;
    while (!(choice >= 1 && choice <=12)) {
        cout << "Choice --> ";
        try {
            cin >> choice;
            if (cin.fail() || !(choice >= 1 && choice <=12))
                throw invalid_argument("Invalid input. Enter a number 1 to 12.");
        }
        catch(invalid_argument& e)
        {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return choice;
}
// COMSC 210 | Lab 28 | Gillian Rhett
#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <limits> // for try-catch
#include <vector> // for displaying in age order
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(const set<Goat>&);
void delete_goat(set<Goat>&);
void add_goat(set<Goat>&, string, int, string);
void display_trip(const set<Goat>&);
int main_menu();
void edit_goat_name(set<Goat>&, int);
void edit_goat_age(set<Goat>&, int);
void edit_goat_color(set<Goat>&, int);
void display_by_age(const set<Goat>&);
void RadixSort(vector<Goat>&, int);

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
        if (choice == 4) { // search for a goat MILESTONE 1
            int i = select_goat(goats);
            if (i >= 0)
                cout << "Goat found." << endl;
        }
        if (choice == 5) { // change a goat's name MILESTONE 2
            int i = select_goat(goats);
            if (i >= 0)
                edit_goat_name(goats, i);
        }
        if (choice == 6) { // change a goat's age MILESTONE 3
            int i = select_goat(goats);
            if (i >= 0)
                edit_goat_age(goats, i);
        }
        if (choice == 7) { // change a goat's color MILESTONE 4
            int i = select_goat(goats);
            if (i >= 0)
                edit_goat_color(goats, i);
        }
        if (choice == 8) { // list all goats in order by age MILESTONE 5
            display_by_age(goats);
        }
        if (choice == 9) { // MILESTONE 7
            
        }
        if (choice == 10) { // MILESTONE 8
            
        }
        if (choice == 11) { // delete all goats MILESTONE 6 but I think it should be the last choice
            goats.clear();
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
    cout << "Enter name of goat: ";
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
    cout << "[5] Change a goat's name" << endl;
    cout << "[6] Change a goat's age" << endl;
    cout << "[7] Change a goat's color" << endl;
    cout << "[8] List in order by age" << endl;
    cout << "[9] " << endl;
    cout << "[10] " << endl;
    cout << "[11] Delete all goate" << endl;
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

void edit_goat_name(set<Goat>& gs, int i) {
// user enters the goat's name and then can edit its name
    if (i != -1) { // if the goat was found
        // get the user input
        string name;
        cout << "Enter new name: ";
        cin >> name;
        // edit the goat's data
        int cur = 0; // current index in the for loop
        for (Goat g : gs) {
            if (i == cur) {
                Goat temp(name, g.get_age(), g.get_color());
                gs.erase(g);
                gs.insert(temp);
                return;
            }
            cur++;
        }
    }
}

void edit_goat_age(set<Goat>& gs, int i) {
// user enters the goat's name and then can edit its age
    if (i != -1) { // if the goat was found
        // get the user input
        int cur = 0; // current index in the for loop
        int age = -1;
        while ( age < 0 ) {
            cout << "Enter new age: ";
            try {
                cin >> age;
                if (cin.fail() || age < 0)
                    throw invalid_argument("Invalid input. Enter a number 0 or greater.");
            }
            catch(invalid_argument& e)
            {
                cout << "Error: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        // put the new data in the set
        for (Goat g : gs) {
            if (i == cur) {
                Goat temp(g.get_name(), age, g.get_color());
                gs.erase(g);
                gs.insert(temp);
            }
            cur++;
        }
    }
}

void edit_goat_color(set<Goat>& gs, int i) {
// user enters the goat's name and then can edit its color
    if (i != -1) { // if the goat was found
        // get the user input
        string color;
        cout << "Enter new color: ";
        cin >> color;
        // edit the goat's data
        int cur = 0; // current index in the for loop
        for (Goat g : gs) {
            if (i == cur) {
                Goat temp(g.get_name(), g.get_age(), color);
                gs.erase(g);
                gs.insert(temp);
                return;
            }
            cur++;
        }
    }
}

void display_by_age(const set<Goat>& gs) {
// get the goats from the set and show them in order by age instead of name
    // put the goats into a vector so they can be sorted by something other than name
    vector<Goat> temp;
    for (Goat g : gs)
        temp.push_back(g);
    
    // sort the goats by age
    RadixSort(temp, temp.size());
    
    // display the goats from youngest to oldest
    for (Goat g : temp)
        cout << "\t" << g.get_name() << " (" << g.get_age() << ", " << g.get_color() << ")" << endl;
}

void RadixSort(vector<Goat>& v, int size) {
    vector<vector<Goat>> buckets(10);
    int copyBackIndex;      
    int maxDigits = 2;    
    int pow10 = 1;
    for (int digitIndex = 0; digitIndex < maxDigits; digitIndex++) {
        // sort the goats into buckets by age
        for (int i = 0; i < v.size(); i++) {
            Goat g = v[i];
            int bucketIndex = (abs(g.get_age()) / pow10) % 10;
            buckets[bucketIndex].push_back(g);
        }
        // put the goats back into the vector
        copyBackIndex = 0;
        for (int i = 0; i < 10; i++) {
            vector<Goat>& bucket = buckets[i];
            for (int j = 0; j < bucket.size(); j++) {
                v[copyBackIndex] = bucket[j];
                copyBackIndex++;
            }
            bucket.clear();
        }      
        pow10 *= 10;
    }
}
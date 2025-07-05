#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

class Room 
{
public:
    int roomNo;
    string type;
    double pricePerDay;
    bool isBooked;

    Room(int r, string t, double price, bool b = false) {
        roomNo = r;
        type = t;
        pricePerDay = price;
        isBooked = b;
    }

    void display() 
    {
        cout << left << setw(10) << roomNo << setw(15) << type << setw(15) << pricePerDay << (isBooked ? "Booked" : "Available") << endl;
    }
};

class Guest 
{
public:
    string name;
    string idCard;
    int roomNo;
    int days;
    string checkInDate;
    string feedback;

    Guest(string n, string id, int r, int d, string date, string fb = "") 
    {
        name = n;
        idCard = id;
        roomNo = r;
        days = d;
        checkInDate = date;
        feedback = fb;
    }

    void display() {
        cout << left << setw(15) << name << setw(15) << idCard << setw(10) << roomNo << setw(10) << days << setw(15) << checkInDate << endl;
    }
};

class Hotel {
private:
    vector<Room> rooms;
    vector<Guest> guests;

public:
    Hotel() {
        loadRooms();
        loadGuests();
    }

    void loadRooms() {
        for (int i = 1; i <= 10; ++i) {
            string type;
            double price;
            if (i <= 3) type = "Single", price = 1000.0;
            else if (i <= 7) type = "Double", price = 2000.0;
            else type = "Deluxe", price = 3500.0;
            rooms.push_back(Room(i, type, price));
        }
    }

    void loadGuests() {
        ifstream in("guests.txt");
        string name, id, date, feedback;
        int room, days;
        while (in >> name >> id >> room >> days >> date) {
            getline(in, feedback);
            guests.push_back(Guest(name, id, room, days, date, feedback));
            for (auto &r : rooms) {
                if (r.roomNo == room) r.isBooked = true;
            }
        }
        in.close();
    }

    void saveGuests() {
        ofstream out("guests.txt");
        for (auto &g : guests) {
            out << g.name << " " << g.idCard << " " << g.roomNo << " " << g.days << " " << g.checkInDate << " " << g.feedback << endl;
        }
        out.close();
    }

    void printWelcome() {
        cout << "\n========================================\n";
        cout << "        Welcome to The Luxe Hotel        \n";
        cout << "========================================\n";
    }

    void printGoodbye() {
        cout << "\n========================================\n";
        cout << "   Thank you for using our system! Bye! \n";
        cout << "========================================\n" << endl;
    }

    void bookRoom() {
        string name, id, date, feedback;
        int roomNo, days;
        showAvailableRooms();
        cout << "Enter your name: ";
        cin >> name;
        cout << "Enter your ID card number: ";
        cin >> id;
        cout << "Choose room number: ";
        cin >> roomNo;
        cout << "Enter number of stay days: ";
        cin >> days;
        cout << "Enter check-in date (dd-mm-yyyy): ";
        cin >> date;

        for (auto &r : rooms) {
            if (r.roomNo == roomNo && !r.isBooked) {
                guests.push_back(Guest(name, id, roomNo, days, date));
                r.isBooked = true;
                saveGuests();
                cout << "\n>> Room booked successfully for " << name << "!\n";
                return;
            }
        }
        cout << ">> Room not available!\n";
    }

    void checkoutGuest() {
        string id, feedback;
        cout << "Enter guest ID card to checkout: ";
        cin >> id;

        for (int i = 0; i < guests.size(); ++i) {
            if (guests[i].idCard == id) {
                int room = guests[i].roomNo;
                int days = guests[i].days;
                double rate = 0;
                for (auto &r : rooms) {
                    if (r.roomNo == room) {
                        rate = r.pricePerDay;
                        r.isBooked = false;
                    }
                }
                double bill = days * rate;
                cout << "\n>> Total Bill: Rs. " << bill << endl;

                cout << "\nWould you like to upgrade room for next visit? (yes/no): ";
                string upgrade;
                cin >> upgrade;
                if (upgrade == "yes") cout << "\n>> Room upgrade request noted.\n";

                cout << "\nPlease provide feedback: ";
                cin.ignore();
                getline(cin, feedback);
                guests[i].feedback = feedback;

                saveGuests();
                guests.erase(guests.begin() + i);
                return;
            }
        }
        cout << ">> Guest not found!\n";
    }

    void showAvailableRooms() {
        cout << "\n-- Available Rooms --\n";
        cout << left << setw(10) << "Room#" << setw(15) << "Type" << setw(15) << "Rate" << "Status" << endl;
        for (auto &r : rooms) {
            if (!r.isBooked) r.display();
        }
    }

    void showBookings() {
        cout << "\n-- Guest List --\n";
        cout << left << setw(15) << "Name" << setw(15) << "ID Card" << setw(10) << "Room" << setw(10) << "Days" << setw(15) << "Check-In" << endl;
        for (auto &g : guests) g.display();
    }

    void searchGuest() {
        string id;
        cout << "Enter guest ID to search: ";
        cin >> id;
        for (auto &g : guests) {
            if (g.idCard == id) {
                cout << "\n>> Guest found:\n";
                g.display();
                cout << "Feedback: " << g.feedback << endl;
                return;
            }
        }
        cout << ">> Guest not found.\n";
    }
};

bool signup() {
    string user, pass, role;
    cout << "\nSIGN UP\n--------\n";
    cout << "Create username: ";
    cin >> user;
    cout << "Create password: ";
    cin >> pass;
    cout << "Assign role (admin/guest): ";
    cin >> role;

    ofstream out("users.txt", ios::app);
    out << user << " " << pass << " " << role << endl;
    out.close();
    cout << ">> Account created successfully!\n";
    return true;
}

string login() {
    string user, pass, fileUser, filePass, fileRole;
    cout << "\nLOGIN\n-----\n";
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    ifstream in("users.txt");
    while (in >> fileUser >> filePass >> fileRole) {
        if (fileUser == user && filePass == pass) {
            return fileRole;
        }
    }
    return "";
}

int main() {
    int option;
    cout << "1. Login\n2. Sign Up\nChoose option: ";
    cin >> option;

    string role;
    if (option == 1) role = login();
    else if (option == 2) {
        signup();
        role = login();
    } else {
        cout << ">> Invalid option.\n";
        return 0;
    }

    if (role == "") {
        cout << ">> Login Failed. Exiting...\n";
        return 0;
    }

    Hotel h;
    int choice;
    h.printWelcome();
    do {
        cout << "\n===== HOTEL MANAGEMENT SYSTEM =====\n==                               ==\n";
        if (role == "admin") {
            cout << "1. Book Room\n2. View Bookings\n3. Available Rooms\n4. Checkout Guest\n5. Search Guest\n6. Exit\n";
        } else {
            cout << "1. Book Room\n2. Available Rooms\n3. Exit\n";
        }
        cout << "Enter choice: ";
        cin >> choice;

        if (role == "admin") {
            switch (choice) {
                case 1: h.bookRoom(); break;
                case 2: h.showBookings(); break;
                case 3: h.showAvailableRooms(); break;
                case 4: h.checkoutGuest(); break;
                case 5: h.searchGuest(); break;
                case 6: h.printGoodbye(); break;
                default: cout << ">> Invalid option.\n"; break;
            }
        } else {
            switch (choice) {
                case 1: h.bookRoom(); break;
                case 2: h.showAvailableRooms(); break;
                case 3: h.printGoodbye(); break;
                default: cout << ">> Invalid option.\n"; break;
            }
        }
    } while ((role == "admin" && choice != 6) || (role != "admin" && choice != 3));

    return 0;
}


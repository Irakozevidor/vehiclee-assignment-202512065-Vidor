#include "vehicle.h"

User::User() : name(""), email(""), phone("") {}

User::User(string name, string email, string phone)
    : name(name), email(email), phone(phone) {}

string User::getName()  const { return name;  }
string User::getEmail() const { return email; }
string User::getPhone() const { return phone; }

void User::setName(string n)  { name  = n; }
void User::setEmail(string e) { email = e; }
void User::setPhone(string p) { phone = p; }

VehicleOwner::VehicleOwner() : User() {}

VehicleOwner::VehicleOwner(string name, string email, string phone)
    : User(name, email, phone) {}

Vehicle::Vehicle() : plateNumber(""), vehicleType(""), year(0), owner() {}

Vehicle::Vehicle(string plate, string type, int year, VehicleOwner owner)
    : plateNumber(plate), vehicleType(type), year(year), owner(owner) {}

string       Vehicle::getPlateNumber() const { return plateNumber; }
string       Vehicle::getVehicleType() const { return vehicleType; }
int          Vehicle::getYear()        const { return year;        }
VehicleOwner Vehicle::getOwner()       const { return owner;       }

void Vehicle::setPlateNumber(string p)  { plateNumber = p; }
void Vehicle::setVehicleType(string t)  { vehicleType = t; }
void Vehicle::setYear(int y)            { year = y;        }
void Vehicle::setOwner(VehicleOwner o)  { owner = o;       }

string Vehicle::toCSV() const {
    return plateNumber + "," +
           vehicleType + "," +
           to_string(year) + "," +
           owner.getName()  + "," +
           owner.getEmail() + "," +
           owner.getPhone();
}
bool validateEmail(const string& email) {
    size_t at  = email.find('@');
    size_t dot = email.find('.', at);
    if (at == string::npos || dot == string::npos) return false;
    if (at == 0 || dot == email.size() - 1)        return false;
    return true;
}

bool validatePhone(const string& phone) {
    if (phone.size() != 13)          return false;
    if (phone.substr(0, 4) != "+250") return false;
    for (size_t i = 4; i < phone.size(); i++) {
        if (!isdigit(phone[i])) return false;
    }
    return true;
}
bool validatePlate(const string& plate) {
    if (plate.size() != 7) return false;
    if (!isalpha(plate[0]) || !isalpha(plate[1]) || !isalpha(plate[2])) return false;
    if (!isdigit(plate[3]) || !isdigit(plate[4]) || !isdigit(plate[5])) return false;
    if (!isalpha(plate[6])) return false;
    return true;
}
void saveRecord(const Vehicle& v) {
    ofstream file("records.txt", ios::app);
    if (file.is_open()) {
        file << v.toCSV() << "\n";
        file.close();
    } else {
        cout << "Error: Could not open records.txt for writing.\n";
    }
}
static Vehicle parseCSV(const string& line) {
    stringstream ss(line);
    string plate, type, yearStr, name, email, phone;

    getline(ss, plate,   ',');
    getline(ss, type,    ',');
    getline(ss, yearStr, ',');
    getline(ss, name,    ',');
    getline(ss, email,   ',');
    getline(ss, phone,   ',');

    int year = stoi(yearStr);
    VehicleOwner owner(name, email, phone);
    return Vehicle(plate, type, year, owner);
}

void displayAll() {
    ifstream file("records.txt");
    if (!file.is_open()) {
        cout << "No records found.\n";
        return;
    }

    string line;
    bool   hasData = false;

    cout << "\n"
         << left
         << setw(10) << "Plate"
         << setw(12) << "Type"
         << setw(8)  << "Year"
         << setw(18) << "Owner"
         << setw(28) << "Email"
         << setw(15) << "Phone"
         << "\n"
         << string(91, '-') << "\n";

    while (getline(file, line)) {
        if (line.empty()) continue;
        hasData = true;
        Vehicle v = parseCSV(line);
        cout << left
             << setw(10) << v.getPlateNumber()
             << setw(12) << v.getVehicleType()
             << setw(8)  << v.getYear()
             << setw(18) << v.getOwner().getName()
             << setw(28) << v.getOwner().getEmail()
             << setw(15) << v.getOwner().getPhone()
             << "\n";
    }

    if (!hasData) cout << "No records found.\n";
    file.close();
}

void searchByPlate(const string& plate) {
    ifstream file("records.txt");
    if (!file.is_open()) {
        cout << "No records found.\n";
        return;
    }

    string line;
    bool   found = false;

    while (getline(file, line)) {
        if (line.empty()) continue;
        Vehicle v = parseCSV(line);
        if (v.getPlateNumber() == plate) {
            found = true;
            cout << "\n--- Vehicle Found ---\n"
                 << "Plate   : " << v.getPlateNumber()      << "\n"
                 << "Type    : " << v.getVehicleType()       << "\n"
                 << "Year    : " << v.getYear()              << "\n"
                 << "Owner   : " << v.getOwner().getName()   << "\n"
                 << "Email   : " << v.getOwner().getEmail()  << "\n"
                 << "Phone   : " << v.getOwner().getPhone()  << "\n";
            break;
        }
    }

    if (!found) cout << "No vehicle found with plate: " << plate << "\n";
    file.close();
}
void addRecord() {
    string plate, type, yearStr, name, email, phone;
    int    year;

    do {
        cout << "Plate number (e.g. RAA123A): ";
        cin  >> plate;
        if (!validatePlate(plate))
            cout << "Invalid plate. Format must be 3 letters + 3 digits + 1 letter (e.g. RAA123A).\n";
    } while (!validatePlate(plate));

    cin.ignore();
    cout << "Vehicle type (e.g. Sedan, SUV): ";
    getline(cin, type);

    while (true) {
        cout << "Year of manufacture: ";
        cin  >> yearStr;
        bool ok = true;
        for (char c : yearStr) if (!isdigit(c)) { ok = false; break; }
        if (ok && yearStr.size() == 4) { year = stoi(yearStr); break; }
        cout << "Invalid year. Enter a 4-digit number.\n";
    }

    cin.ignore();
    cout << "Owner full name: ";
    getline(cin, name);

    do {
        cout << "Email: ";
        getline(cin, email);
        if (!validateEmail(email))
            cout << "Invalid email. Must contain '@' and '.'.\n";
    } while (!validateEmail(email));

    do {
        cout << "Phone (+250XXXXXXXXX): ";
        cin  >> phone;
        if (!validatePhone(phone))
            cout << "Invalid phone. Must start with +250 and be exactly 13 characters.\n";
    } while (!validatePhone(phone));

    VehicleOwner owner(name, email, phone);
    Vehicle      v(plate, type, year, owner);
    saveRecord(v);

    cout << "Record saved successfully.\n";
}

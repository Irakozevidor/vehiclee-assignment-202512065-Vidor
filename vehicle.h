#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;
class User {
private:
    string name;
    string email;
    string phone;

public:
    User();
    User(string name, string email, string phone);

    string getName()  const;
    string getEmail() const;
    string getPhone() const;

    void setName(string n);
    void setEmail(string e);
    void setPhone(string p);
};
class VehicleOwner : public User {
public:
    VehicleOwner();
    VehicleOwner(string name, string email, string phone);
};
class Vehicle {
private:
    string plateNumber;
    string vehicleType;
    int    year;
    VehicleOwner owner;

public:
    Vehicle();
    Vehicle(string plate, string type, int year, VehicleOwner owner);

    string       getPlateNumber() const;
    string       getVehicleType() const;
    int          getYear()        const;
    VehicleOwner getOwner()       const;

    void setPlateNumber(string p);
    void setVehicleType(string t);
    void setYear(int y);
    void setOwner(VehicleOwner o);

    string toCSV() const;
};
bool   validateEmail(const string& email);
bool   validatePhone(const string& phone);
bool   validatePlate(const string& plate);

void   saveRecord(const Vehicle& v);
void   displayAll();
void   searchByPlate(const string& plate);
void   addRecord();

#endif

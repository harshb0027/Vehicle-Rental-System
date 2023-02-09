

#pragma once
#include <iostream>
#include "RentalLocation.h"
using namespace std;

class Vehicle {
protected:
	string vehicleName;
	string vehicleString;
	string locationString;
	RentalLocation* location;
public:
	Vehicle(string &vName, RentalLocation* loc) {
		this->vehicleName = vName;
		this->location = loc;
		vehicleString = "vehicle name:- " + vehicleName + " at location:- " + location->toString();
	}

	Vehicle(string& vName, string loc) {
		this->vehicleName = vName;
		this->locationString = loc;
		vehicleString = "vehicle name:- " + vehicleName + " at " + location->toString();
	}

	/*/~Vehicle() {
		cout << "In vehicle destructor\n" << endl;
	}*/

	string toString() {
		return vehicleString;
	}

};
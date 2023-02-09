

#pragma once
#include <ostream>
#include <iostream>
//using namespace std;
class RentalLocation {
protected:
	string rentalLocationName;
	string rentalLocationString;
public:
	RentalLocation(string &rName) {
		this->rentalLocationName = rName;
		rentalLocationString = "rental location = " + rentalLocationName;
	}

	string toString() {
		return rentalLocationString;
	}

	string getLocationName() {
		return rentalLocationName;
	}

};

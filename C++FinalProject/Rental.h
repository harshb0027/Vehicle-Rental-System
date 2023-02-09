

#pragma once
#include "Customers.h"
#include "Vehicle.h"
#include <ostream>
#include <string>
#include <nana/datetime.hpp>
using namespace std;
class Rental {
	
protected:
	Customer* rentalCustomer;
	Vehicle* rentalVehicle;
	string startingDate;
	string endingDate;
	string rentalString;
	int amountEntered;
	

public:
	
	Rental(Customer*c, Vehicle* v, string sd, string ed, int amount) {
		this->rentalCustomer = c;
		this->rentalVehicle = v;
		this->startingDate = sd;
		this->endingDate = ed;
		this->amountEntered = amount;
		rentalString = "Rental " + v->toString() + " assigned to " + c->toString() + " from " + startingDate + " to " + endingDate + " and owes:- " + to_string(amount);


	}

	string toString() {
		return rentalString;
	}

	Vehicle* getVehicle() {
		return rentalVehicle;
	}
	Customer* getCustomer() {
		return rentalCustomer;
	}

	int getAmount() {
		return amountEntered;
	}
};

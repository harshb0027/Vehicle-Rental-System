
#pragma once
#include <ostream>
#include <iostream>
#include <string>
using namespace std;
class Customer {
	
protected:
	string firstName;
	string lastName;
	string streetAddress;
	string age;
	string customerString;
	string preferredCustomer;
public:
	Customer(string &a, string &b, string &c, string &d, string &e) {
		this->firstName = a;
		this->lastName = b;
		this->streetAddress = c;
		age = d;
		this->preferredCustomer = e;

		customerString = "name:" + this->firstName + " " + this->lastName +  + " address:- " + this->streetAddress + " age:" + age + "preferred customer:- " + preferredCustomer;

	}

	string toString() {
		return customerString;
	}
	string getAge() {
		return age;
	}
	string getPreferredCustomer() {
		return preferredCustomer;
	}
};
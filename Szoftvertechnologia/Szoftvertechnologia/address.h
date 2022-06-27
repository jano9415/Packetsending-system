#ifndef ADDRESS_H
#define ADDRESS_H

#include<iostream>
#include<string>

using namespace std;


class Address
{
private:
	int postCode;
	string city;
	string street;
	int number;

public:
	Address(int _postCode, const string& _city, const string& _street, int _number);

	int getPostCode() const;
	const string& getCity() const;
	const string& getStreet() const;
	int getNumber() const;

};

#endif 
#include "address.h"

Address::Address(int _postCode, const string& _city, const string& _street, int _number):
	postCode(_postCode),city(_city),street(_street),number(_number)
{

}

int Address::getPostCode() const
{
	return postCode;
}

const string & Address::getCity() const
{
	return city;
}

const string & Address::getStreet() const
{
	return street;
}

int Address::getNumber() const
{
	return number;
}


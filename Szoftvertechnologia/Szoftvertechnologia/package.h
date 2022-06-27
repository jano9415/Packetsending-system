#ifndef PACKAGE_H
#define PACKAGE_H

#include<iostream>
#include<string>

using namespace std;


class Package
{
private:
	int width, height, lenght, price;
	string id;

public:
	Package(const string& _id, int _width, int _height, int _lenght, int _price);
	int getWidth() const;
	int getHeight() const;
	int getLenght() const;
	int getPrice() const;
	const string &getId() const;

};

#endif // PACKAGE_H

#ifndef CONTAINER_H
#define CONTAINER_H

#include "box.h"
#include<list>
#include<string>
#include "package.h"
#include<vector>
#include"address.h"

using namespace std;

class Container
{
private:
	vector<Box*> boxes;
	Address address;
public:
	Container(int _postCode, const string& _city, const string& _street, int _number);
	~Container();

	vector<Box*> getBoxes() const;
	Address getAddress() const;
};

#endif // CONTAINER_H

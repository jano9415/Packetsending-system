#include "container.h"

Container::Container(int _postCode, const string& _city, const string& _street, int _number):
	address(_postCode,_city,_street,_number)
{
	for (int i = 0; i <= 9; i++) {
		boxes.push_back(new Box(1, 20, 20, 20, nullptr));
	}
	for (int i = 10; i <= 19; i++) {
		boxes.push_back(new Box(1, 60, 60, 60, nullptr));
	}
	for (int i = 20; i <= 29; i++) {
		boxes.push_back(new Box(1, 100, 100, 100, nullptr));
	}


}

Container::~Container()
{
	for (auto b : boxes) {
		delete b;
	}
}

vector<Box*> Container::getBoxes() const
{
	return boxes;
}

Address Container::getAddress() const
{
	return address;
}

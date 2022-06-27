#include "package.h"

int Package::getWidth() const
{
	return width;
}

int Package::getHeight() const
{
	return height;
}

int Package::getLenght() const
{
	return lenght;
}

int Package::getPrice() const
{
	return price;
}

const string &Package::getId() const
{
	return id;
}

Package::Package(const string& _id, int _width, int _height, int _lenght, int _price) :
	id(_id) , width(_width), height(_height), lenght(_lenght), price(_price)
{

}

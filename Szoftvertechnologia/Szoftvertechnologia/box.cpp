#include "box.h"

bool Box::getEmpty() const
{
	return empty;
}

int Box::getWidth() const
{
	return width;
}


int Box::getHeight() const
{
	return height;
}

int Box::getLenght() const
{
	return lenght;
}

Package *Box::getPackage() const
{
	return package;
}

void Box::setPackage(Package * _package)
{
	package = _package;
}

void Box::setEmpty(bool _empty)
{
	empty = _empty;
}

Box::Box(bool _empty, int _width, int _height, int _lenght, Package* _package):
	empty(_empty), width(_width), height(_height), lenght(_lenght), package(_package)
{

}

Box::~Box()
{
	delete package;
}

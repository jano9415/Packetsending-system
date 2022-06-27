#ifndef BOX_H
#define BOX_H

#include "package.h"


class Box
{
private:
	bool empty;
	int width, height, lenght;
	Package* package;

public:
	Box(bool _empty, int _width, int _height, int _lenght, Package* _package);
	~Box();
	bool getEmpty() const;
	int getWidth() const;
	int getHeight() const;
	int getLenght() const;
	Package *getPackage() const;
	void setPackage(Package* _package); 	//A rekesz feltöltése egy csomaggal.
	void setEmpty(bool _empty);

};

#endif // BOX_H

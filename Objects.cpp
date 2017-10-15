#include "Objects.h"



Objects::Objects() {
	this->emptySpace = 0;
	this->player = 1;
	this->box = 2;
	this->wall = 3;
	this->winnigPoint = 4;
}


Objects::~Objects()
{
}

short int Objects::EmptySpace()
{
	return emptySpace;
}

short int Objects::Player()
{
	return player;
}

short int Objects::Box()
{
	return box;
}

short int Objects::Wall()
{
	return wall;
}

short int Objects::WinnigPoint()
{
	return winnigPoint;
}

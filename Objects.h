#pragma once
class Objects
{
	public:
		Objects();
		~Objects();

		short int EmptySpace();
		short int Player();
		short int Box();
		short int Wall();
		short int WinnigPoint();

	private:

		/*-------------------------------------------------
		0 is an empty space
		1 is the player
		2 is the box
		3 is the wall
		4 is the winnig point
		-------------------------------------------------*/
		short int emptySpace;
		short int player;
		short int box;
		short int wall;
		short int winnigPoint;
};


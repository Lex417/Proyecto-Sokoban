#include <SFML/Graphics.hpp>
#include <iostream>
#include "Objects.h"

using namespace sf;
using namespace std;

struct Node{
	int objectID;
	Node *next;
	Node *prev;
};

class List : public Objects {

public:
	List();
	void insert(int i);
	int getObject(int);
	bool movements(int);
	bool movementsR(int);
	bool movementsL(int);
	void CambiarEstado(int, int);
	void deleteList();

	bool ganar(List, int);
	bool ganar2(List, int);
	bool ganar3(List, int);


private:
	Node *head;
	Node *temp;

};
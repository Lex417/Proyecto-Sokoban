#include <SFML/Graphics.hpp>
#include <iostream>
#include "Objects.h"

using namespace sf;
using namespace std;

struct Nodo {
	int objectID;
	Nodo *next;
	Nodo *prev;	
};

class Lista : public Objects {

public:
	Lista();
	void insert(int i);
	int getObject(int);
	bool movements(int);
	bool movementsR(int);
	bool movementsL(int);
	void CambiarEstado(int, int);
	void deleteList();
	
	bool ganar(Lista, int);
	bool ganar2(Lista, int);
	bool ganar3(Lista, int);


private:
	Nodo *head;
	Nodo *temp;

};
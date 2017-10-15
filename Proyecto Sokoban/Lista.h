#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using std::cout;
using std::endl;


struct Nodo {

	int objectID;
	Nodo *next;
	Nodo *prev;
	//LOS NODOS SOLO TENDRAN UN NUMERO Y DEPENDE DE ESTE SE PINTAR� EN LA VENTANA
};

class Lista {

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
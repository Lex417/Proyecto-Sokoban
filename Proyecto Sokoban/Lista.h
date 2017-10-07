#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using std::cout;
using std::endl;


struct Nodo {

	int tipoPosicion;
	Nodo *next;
	Nodo *prev;
					//LOS NODOS SOLO TENDRAN UN NUMERO Y DEPENDE DE ESTE SE PINTARÁ EN LA VENTANA

};

class Lista {

public:
	Lista();
	void insertar(int i);
	int getTipo(int);
	bool Movimiento(int);
	bool MovimientoDerecha(int);
	bool MovimientoIzquierda(int);
	void CambiarEstado(int, int);
	void Borrar();
	bool ganar(Lista, int);
	bool ganar2(Lista, int);


private:
	Nodo *inicio;
	Nodo *temp;

};
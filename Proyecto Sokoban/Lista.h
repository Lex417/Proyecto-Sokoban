#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;



struct Nodo {

	Nodo *siguiente;
	Nodo *anterior;
	int tipoPosicion;				//LOS NODOS SOLO TENDRAN UN NUMERO Y DEPENDE DE ESTE SE PINTARÁ EN LA VENTANA

};

class Lista {


private:
	Nodo *inicio;

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
};
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Lista.h"
#include "Menu.h"
#include <sstream>
#include <fstream>

using namespace sf;
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::ios;

class Ventana {
private:

	RenderWindow VentanaPrincipal;
	Texture Pared;
	Texture Caja;
	Texture Jugador;
	Texture JugadorArriba;
	Texture JugadorDer;
	Texture JugadorIzq;
	Texture PuntoGanar;
	Texture EspacioLibre;

	Sprite LaPared;
	Sprite LaCaja;
	Sprite ElJugador;
	Sprite Ganar;
	Sprite Disponible;
	Font font;
	Text opciones[4];
	Text Level;

	Event eventos;

	Lista L1;
	Lista L2;
	Lista L3;
	Lista L4;
	Lista L5;
	Lista L6;
	Lista L7;
	Lista L8;
	Lista ListaGanadora;


	int lista, nodo, temporal, ganar1;
	bool completo1, completo2, completo3, completo4, completo5;

public:
	Ventana();
	int inicializar();
	void LosEventos();
	void update();
	void render();
	void cleared();
	void run();
	void setCompleto1();
	void setCompleto2();
	void setCompleto3();
	void setCompleto4();
	void setCompleto5();
	void LlenarListas();
	int validarEntrada();
	void iniciarMenu();

};

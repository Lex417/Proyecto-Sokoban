#include <SFML/Graphics.hpp>
//--------------------------
#include "Lista.h"
#include "Menu.h"
#include "TexturesSprites.h"
//--------------------------
#include <sstream>
#include <fstream>
#include <Windows.h>
#include <cstdlib>
#include <iostream>
//--------------------------
using namespace sf;
using namespace std;
//--------------------------
class Ventana {

	public:
		Ventana();

		void paintLevel(int,Lista,int);
		int initializeWindow();
		void nextLevel(bool);
		void movements();
		void update();
		void render();
		void run();
		void setCompleto1();
		void setCompleto2();
		void setCompleto3();
		void setCompleto4();
		void setCompleto5();
		void fillLists();
		int validation();
		void initiateMenu();
		void deleteLists();

	private:
		RenderWindow VentanaPrincipal;
//--------------------Textures------------------------
		Texture wall;
		Texture emptySpace;
		Texture box;
		Texture playerDown;
		Texture playerUp;
		Texture playerRight;
		Texture playerLeft;
		Texture winnigPoints;
		Texture red;
//--------------------Sprites------------------------
		Sprite wallsSprite;
		Sprite boxesSprite;
		Sprite playerSprite;
		Sprite winnigSprite;
		Sprite emptySprite;
		Sprite pokemonRed;
//--------------------Texts------------------------
		Text opciones[4];
		Text Level;
//--------------------Font------------------------
		Font font;
//--------------------Event------------------------
		Event eventos;
//--------------------Lists------------------------
		Lista L1;
		Lista L2;
		Lista L3;
		Lista L4;
		Lista L5;
		Lista L6;
		Lista L7;
		Lista L8;
		Lista WL;
//--------------------Extras------------------------
		int lista, nodo, temporal, ganar1;
		string repetition;
//--------------------bools------------------------
		bool completo1, completo2, completo3, completo4, completo5;
};

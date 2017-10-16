#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//--------------------------
#include "List.h"
#include "Menu.h"
//--------------------------
#include <sstream>
#include <fstream>
#include <Windows.h>
#include <cstdlib>
#include <iostream>
#include <vector>
//--------------------------
using namespace sf;
using namespace std;
//--------------------------
class Interface {

public:
	Interface();

	void paintLevel(int, List, int);
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
	void replay();
	void deleteReplay();

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
	Texture finish;
	//--------------------Sprites------------------------
	Sprite wallsSprite;
	Sprite boxesSprite;
	Sprite playerSprite;
	Sprite winnigSprite;
	Sprite emptySprite;
	Sprite pokemonRed;
	Sprite winner;
	//--------------------Texts------------------------
	Text opciones[4];
	Text Level;
	//--------------------Font------------------------
	Font font;
	//--------------------Event------------------------
	Event eventos;
	//--------------------Lists------------------------
	List L1;
	List L2;
	List L3;
	List L4;
	List L5;
	List L6;
	List L7;
	List L8;
	List WL;
	//--------------------Extras------------------------
	int lista, nodo, temporal, ganar1;
	vector<string> repetition;
	
	//--------------------bools------------------------
	bool completo1, completo2, completo3, completo4, completo5, flag;
};




#include "SFML/Graphics.hpp"

using namespace sf;


#define misOpciones 3

class Menu
{
public:
	Menu(float, float);
	~Menu();

	void draw(RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return opcionSeleccionada; }
private:
	int opcionSeleccionada;
	Font font;
	Text menu[misOpciones];
	Text titulo;
	Texture imagen;
	Sprite opcion;

};
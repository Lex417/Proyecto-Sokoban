#include "SFML/Graphics.hpp"
#define misOpciones 3
using namespace sf;


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
	Texture fondo;
	Sprite opcion;
	Sprite miFondo;

};
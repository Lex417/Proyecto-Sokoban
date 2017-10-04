#include "SFML/Graphics.hpp"
using namespace sf;
using namespace std;
#define POSICIONES 3
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
	Text menu[POSICIONES];
	Text titulo;
	Texture imagen;
	Sprite opcion;

};
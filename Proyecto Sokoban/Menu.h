#include "SFML/Graphics.hpp"
#define myOptions 3

using namespace sf;

class Menu
{
	public:

		Menu(float, float);
		~Menu();

		void draw(RenderWindow &window);
		void MoveUp();
		void MoveDown();
		int GetPressedItem();

	private:
	
		Font font;
		Text menu[myOptions];
		Text title;
		Texture picture;
		Texture background;
		Sprite option;
		Sprite myBackground;
		int pressedItem;
};
#include "Menu.h"


Menu::Menu(float ancho, float largo) 
{
	if (!font.loadFromFile("SuperRetro54.ttf"))
	{
		system("No se ha encontrado el font&pause");

	}

	
	if (!background.loadFromFile("City.png"))
	{
		system("No se ha encontrado el font&pause");
	}

	myBackground.setTexture(background);
	

	menu[0].setFont(font);
	menu[0].setColor(Color::Cyan);
	menu[0].setString("Start!");
	menu[0].setCharacterSize(35);
	menu[0].setPosition(Vector2f((ancho / 2) -66 , largo / (myOptions)+50 * 1));


	menu[1].setFont(font);
	menu[1].setColor(Color::White);
	menu[1].setString("Load");
	menu[1].setCharacterSize(35);
	menu[1].setPosition(Vector2f((ancho / 2) - 54, largo / (myOptions + 1) * 2));


	menu[2].setFont(font);
	menu[2].setColor(Color::White);
	menu[2].setString("Quit");
	menu[2].setPosition(Vector2f((ancho / 2)-40, largo / (myOptions + 1) * 3));


	title.setFont(font);
	title.setColor(Color::Cyan);
	title.setCharacterSize(90);
	title.setString("SOKOBAN");
	title.setPosition(Vector2f(150.f, 0.f));


	pressedItem = 0;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window)
{
	window.draw(myBackground);

	for (int i = 0; i < myOptions; i++)	
		window.draw(menu[i]);
	
	
	window.draw(option);
	window.draw(title);
		
}

void Menu::MoveUp()
{
	if (pressedItem - 1 >= 0)
	{

		menu[pressedItem].setColor(Color::White);
		pressedItem--;
		menu[pressedItem].setColor(Color::Cyan);
		
	}
}

void Menu::MoveDown()
{
	if (pressedItem + 1 < myOptions)
	{

		menu[pressedItem].setColor(Color::White);
		pressedItem++;
		menu[pressedItem].setColor(Color::Cyan);
	}
}

int Menu::GetPressedItem()
{
	return pressedItem;
}
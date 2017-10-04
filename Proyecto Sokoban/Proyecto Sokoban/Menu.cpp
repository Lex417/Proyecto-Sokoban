#include "Menu.h"


Menu::Menu(float ancho, float largo)
{
	if (!font.loadFromFile("SuperRetro54.ttf"))
	{
		system("No se ha encontrado el font&pause");

	}

	if (!imagen.loadFromFile("Character4.png")) {
		system("No se ha encontrado el font&pause");
	}
	opcion.setTexture(imagen);

	menu[0].setFont(font);
	menu[0].setColor(Color::Cyan);
	menu[0].setString("Start!");
	menu[0].setPosition(Vector2f((ancho / 2) -55 , largo / (POSICIONES) * 1));
	opcion.setPosition(menu[0].getPosition().x -52, menu[0].getPosition().y);
	menu[1].setFont(font);
	menu[1].setColor(Color::White);
	menu[1].setString("Load");
	menu[1].setPosition(Vector2f((ancho / 2) - 46, largo / (POSICIONES + 1) * 2));


	menu[2].setFont(font);
	menu[2].setColor(Color::White);
	menu[2].setString("Quit");
	menu[2].setPosition(Vector2f((ancho / 2)-40, largo / (POSICIONES + 1) * 3));


	titulo.setFont(font);
	titulo.setColor(Color::Cyan);
	titulo.setCharacterSize(90);
	titulo.setString("SOKOBAN");
	titulo.setPosition(Vector2f(150.f, 0.f));


	opcionSeleccionada = 0;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < POSICIONES; i++)
	{
		window.draw(menu[i]);

	}
	window.draw(opcion);
	window.draw(titulo);

}

void Menu::MoveUp()
{
	if (opcionSeleccionada - 1 >= 0)
	{

		menu[opcionSeleccionada].setColor(Color::White);
		opcionSeleccionada--;
		menu[opcionSeleccionada].setColor(Color::Cyan);
		opcion.setPosition(menu[opcionSeleccionada].getPosition().x - 50, menu[opcionSeleccionada].getPosition().y);

	}
}

void Menu::MoveDown()
{
	if (opcionSeleccionada + 1 < POSICIONES)
	{

		menu[opcionSeleccionada].setColor(Color::White);
		opcionSeleccionada++;
		menu[opcionSeleccionada].setColor(Color::Cyan);
		opcion.setPosition(menu[opcionSeleccionada].getPosition().x - 50, menu[opcionSeleccionada].getPosition().y);
	}
}
#include "Ventana.h" 

Ventana::Ventana() :VentanaPrincipal{ VideoMode{ 900,700 },"Sokoban.exe",Style::Titlebar | Style::Close }
{
	completo1 = false;
	completo2 = false;
	completo3 = false;
	completo4 = false;
	completo5 = false;
	repetition = " ";

}

void Ventana::paintLevel(int x, Lista list, int num){

	/*	0 is an empty space
		1 is the player
		2 is the box
		3 is the wall
		4 is the winnig point	*/

	for (int i = 0; i < 9; i++) {
		
		int pos = -1;

		pos = list.getObject(i);// will have the list numbers

		switch (pos) {

		case 0:	break;
		case 1:													
			playerSprite.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(playerSprite);
			lista = num;
			nodo = i;
			break;
		case 2:														
			boxesSprite.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(boxesSprite);
			break;
		case 3:														
			wallsSprite.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(wallsSprite);
			break;
		case 4:
			winnigSprite.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(winnigSprite);
			break;
		default:{}
		}
	}
}//end of paint level

int Ventana::initializeWindow() {
	VentanaPrincipal.setFramerateLimit(10);				//Game speed
	VentanaPrincipal.setVerticalSyncEnabled(true);		//Pantalla no parpadee cuando se actualice
	VentanaPrincipal.setKeyRepeatEnabled(false);		//Evitar que se realicen muchas acciones al presionar un boton

	if (!wall.loadFromFile("wall.jpg")){
		cout << "No se ha encontrado la imagen&pause";
		return -1;
	}
	wallsSprite.setTexture(wall);
	if (!emptySpace.loadFromFile("GroundGravel_Concrete.png")){
		system("No se ha encontrado la imagen&pause");
		return EXIT_FAILURE;
	}
	emptySprite.setTexture(emptySpace);
	if (!box.loadFromFile("CrateDark_Red.png")){
		system("No se ha encontrado la imagen&pause");
		return EXIT_FAILURE;
	}
	boxesSprite.setTexture(box);
	if (!playerDown.loadFromFile("Character4.png")){
		system("No se ha encontrado la imagen&pause");
		return EXIT_FAILURE;
	}
	playerSprite.setTexture(playerDown);
	if (!playerUp.loadFromFile("CharacterArriba.png")){
		system("No se ha encontrado la imagen&pause");
		return EXIT_FAILURE;
	}
	if (!playerRight.loadFromFile("CharacterDer.png")){
		system("No se ha encontrado la imagen&pause");
		return EXIT_FAILURE;
	}
	if (!playerLeft.loadFromFile("CharacterIzq.png")) {
		system("No se ha encontrado la imagen&pause");
		return EXIT_FAILURE;
	}
	if (!winnigPoints.loadFromFile("endpoint.png")){
		system("No se ha encontrado la imagen&pause");
		return EXIT_FAILURE;
	}
	winnigSprite.setTexture(winnigPoints);
	if (!font.loadFromFile("SuperRetro54.ttf")){
		system("No se ha encontrado la imagen&pause");
		return EXIT_FAILURE;
	}
	if (!red.loadFromFile("Red_skin.png")){
		system("No se ha encontrado la imagen&pause");
		return EXIT_FAILURE;
	}
	pokemonRed.setTexture(red);

	opciones[0].setFont(font);
	opciones[0].setCharacterSize(20);
	opciones[0].setColor(Color::Black);
	opciones[0].setString("[Shift to Restart");
	opciones[0].setPosition(Vector2f(20.f, 610.f));

	opciones[1].setFont(font);
	opciones[1].setCharacterSize(20);
	opciones[1].setColor(Color::Black);
	opciones[1].setString("[BackSpace] to Menu");
	opciones[1].setPosition(Vector2f(20.f, 580.f));

	opciones[2].setFont(font);
	opciones[2].setCharacterSize(20);
	opciones[2].setColor(Color::Black);
	opciones[2].setString("[Escape] to Quit");
	opciones[2].setPosition(Vector2f(600.f, 600.f));

	opciones[3].setFont(font);
	opciones[3].setCharacterSize(20);
	opciones[3].setColor(Color::Black);
	opciones[3].setString("Move with arrows or WASD");
	opciones[3].setPosition(Vector2f(20.f, 550.f));

	Level.setFont(font);
	Level.setCharacterSize(55);
	Level.setColor(Color(178,34 ,34));
	Level.setPosition(Vector2f(580.f, 40.f));

	fillLists();
}// End of initializeWindow

void Ventana::nextLevel(bool done)
{
	if (done) {// check if level 1 is completed										
		deleteLists();
		int opc;
		cout << "Digite la opci" << char(162) << "n que desee realizar?" << endl;
		cout << "[1]. Avanzar al siguiente nivel" << endl;
		cout << "[2]. Ver repetici" << char(162) << "n" << endl;
		cin >> opc;
		while (cin.fail()) {
			cout << "\rPor favor digite una opcion valida";
			Sleep(1500);
			cin.clear();
			cin.ignore(500, '\n');
		}
		switch (opc) {
		case 1:
			fillLists();
			return;
		case 2:
			cout << repetition;
			fillLists();
			return;
		default:{}

		}	
	}
}// End of nextLevel

/*-------------------------------------------------
		 0 is an empty space
		 1 is the player
		 2 is the box
		 3 is the wall
		 4 is the winnig point
		 lista-- up
		 lista++ down
		 nodo-- left
		 nodo++ right
		 list 1 and 8 are all walls
-------------------------------------------------*/

void Ventana::movements() {

	while (VentanaPrincipal.pollEvent(eventos)) {
		if (eventos.type == Event::Closed) {
			VentanaPrincipal.close();// closes the game	
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) { // Sprite's movements
		system("cls");
		string rep = " Up";
		cout << rep << endl;
		repetition += rep;
	//----------------------- principle switch----------------------------------
		switch (lista) {
			case 2:// list 2
				system("cls");
				cout << "Arriba hay un muro, no se puede mover" << endl;
				playerSprite.setTexture(playerUp);
				break;// list 2

			case 3:// list 3
	//----------------------- sub switch list 3----------------------------------
				switch (L2.getObject(nodo)) {
					case 0:								
						temporal = L2.getObject(nodo);				//Se guarda el numero que tenga la lista 2
						L2.CambiarEstado(nodo, L3.getObject(nodo));	//La lista 2 pasa a tener el numero que tenga la lista 3
						L3.CambiarEstado(nodo, temporal);			//La Lista 3 pasa a tener el numero que se habia guardado de la lista 2
						lista--;									
						playerSprite.setTexture(playerUp);
						break;
					case 2:													
						if (L1.movements(nodo)) {
							L1.CambiarEstado(nodo, L2.getObject(nodo));		//La Lista 1 pasa a tener el numero que tiene la Lista 2
							L2.CambiarEstado(nodo, L3.getObject(nodo));		//La Lista 2 pasa a tener el numero que tiene la Lista 3
							L3.CambiarEstado(nodo, 0);						//La Lista 1 pasa a tener un espacio libre 
							lista--;										
							playerSprite.setTexture(playerUp);
						}
						break;
					case 3:													
						system("cls");
						cout << "No se puede subir xq hay un muro" << endl;
						playerSprite.setTexture(playerUp);
						break;
					case 4:												
						L2.CambiarEstado(nodo, L3.getObject(nodo));		//La lista de arriba se actualiza al numero que tengo la lista
						L3.CambiarEstado(nodo, 0);						//La lista se actualiza a un espacio vacio
						lista--;										
						playerSprite.setTexture(playerUp);
						break;
				}
	//-----------------------end of sub switch list 3--------------------------------
				break;// list 3

			case 4: // list 4
	//-----------------------sub switch list 4--------------------------------------
				switch (L3.getObject(nodo)) {
					case 0:
						temporal = L3.getObject(nodo);
						L3.CambiarEstado(nodo, L4.getObject(nodo));
						L4.CambiarEstado(nodo, temporal);
						lista--;
						playerSprite.setTexture(playerUp);
						break;
					case 2:
						if (L2.movements(nodo)) {
							L2.CambiarEstado(nodo, L3.getObject(nodo));
							L3.CambiarEstado(nodo, L4.getObject(nodo));
							L4.CambiarEstado(nodo, 0);
							lista--;
							playerSprite.setTexture(playerUp);
						}
						break;
					case 3:
						system("cls");
						cout << "No se puede subir xq hay un muro" << endl;
						playerSprite.setTexture(playerUp);
						break;
					case 4:
						L3.CambiarEstado(nodo, L4.getObject(nodo));
						L4.CambiarEstado(nodo, 0);
						lista--;
						playerSprite.setTexture(playerUp);
						break;
				}
	//-----------------------end of sub switch list 4-------------------------------
				break;// list 4

			case 5:// list 5
	//-----------------------sub switch list 5--------------------------------------
				switch (L4.getObject(nodo)) {
					case 0:
						temporal = L4.getObject(nodo);
						L4.CambiarEstado(nodo, L5.getObject(nodo));
						L5.CambiarEstado(nodo, temporal);
						lista--;
						playerSprite.setTexture(playerUp);
						break;
					case 2:
						if (L3.movements(nodo)) {
							L3.CambiarEstado(nodo, L4.getObject(nodo));
							L4.CambiarEstado(nodo, L5.getObject(nodo));
							L5.CambiarEstado(nodo, 0);
							lista--;
							playerSprite.setTexture(playerUp);
						}
						break;
					case 3:
						system("cls");
						cout << "No se puede subir porque hay un muro" << endl;
						playerSprite.setTexture(playerUp);
						break;
					case 4:
						L4.CambiarEstado(nodo, L5.getObject(nodo));
						L5.CambiarEstado(nodo, 0);
						lista--;
						playerSprite.setTexture(playerUp);
						break;
				}
	//-----------------------end of sub switch list 5-------------------------------
				break;// list 5

			case 6: // list 6
	//-----------------------sub switch list 6--------------------------------------
				switch (L5.getObject(nodo)) {
					case 0:
						temporal = L5.getObject(nodo);
						L5.CambiarEstado(nodo, L6.getObject(nodo));
						L6.CambiarEstado(nodo, temporal);
						lista--;
						playerSprite.setTexture(playerUp);
						break;
					case 2:
						if (L4.movements(nodo)) {
							L4.CambiarEstado(nodo, L5.getObject(nodo));
							L5.CambiarEstado(nodo, L6.getObject(nodo));
							L6.CambiarEstado(nodo, 0);
							lista--;
							playerSprite.setTexture(playerUp);
						}
						break;
					case 3:
						system("cls");
						cout << "No se puede subir porque hay un muro" << endl;
						playerSprite.setTexture(playerUp);
						break;
					case 4:
						L5.CambiarEstado(nodo, L6.getObject(nodo));
						L6.CambiarEstado(nodo, 0);
						lista--;
						playerSprite.setTexture(playerUp);
						break;
				}
	//-----------------------end of sub switch list 6-------------------------------
				break;// list 6

			case 7: // list 7
	//-----------------------sub switch list 7--------------------------------------
				switch (L6.getObject(nodo)) {
					case 0:
						temporal = L6.getObject(nodo);
						L6.CambiarEstado(nodo, L7.getObject(nodo));
						L7.CambiarEstado(nodo, temporal);
						lista--;
						playerSprite.setTexture(playerUp);
						break;
					case 2:
						if (L5.movements(nodo)) {
							L5.CambiarEstado(nodo, L6.getObject(nodo));
							L6.CambiarEstado(nodo, L7.getObject(nodo));
							L7.CambiarEstado(nodo, 0);
							lista--;
							playerSprite.setTexture(playerUp);
						}
						break;
					case 3:
						system("cls");
						cout << "No se puede subir porque hay un muro" << endl;
						playerSprite.setTexture(playerUp);
						break;
					case 4:
						L6.CambiarEstado(nodo, L7.getObject(nodo));
						L7.CambiarEstado(nodo, 0);
						lista--;
						playerSprite.setTexture(playerUp);
						break;
				}
	//----------------------- end of sub switch list 7-------------------------------
				break;// list 7
		}
	//----------------------- end of principle switch--------------------------------
	}// End of up keyboard up

	if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
		system("cls");
		string rep = " Left";
		cout << rep << endl;
		repetition += rep;

		switch (lista) {
			case 2:
				playerSprite.setTexture(playerLeft);
				if (L2.movementsL(nodo)) {
					nodo--;									
				}
				break;
			case 3:
				playerSprite.setTexture(playerLeft);
				if (L3.movementsL(nodo)) {
					nodo--;
				}
				break;
			case 4:
				playerSprite.setTexture(playerLeft);
				if (L4.movementsL(nodo)) {
					nodo--;
				}
				break;
			case 5:
				playerSprite.setTexture(playerLeft);
				if (L5.movementsL(nodo)) {
					nodo--;
				}
				break;
			case 6:
				playerSprite.setTexture(playerLeft);
				if (L6.movementsL(nodo)) {
					nodo--;
				}
				break;
			case 7:
				playerSprite.setTexture(playerLeft);
				if (L7.movementsL(nodo)) {
					nodo--;
					playerSprite.setTexture(playerLeft);
				}
				break;
			default: {}
		}
	}//End of keyboard left


	if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
		system("cls");
		string rep = " Down";
		cout << rep << endl;
		repetition += rep;
	//----------------------- principle switch----------------------------------
		switch (lista) {
			case 2:	// list 2
	//----------------------- sub switch list 2---------------------------------
				switch (L3.getObject(nodo)) {
					case 0:
						temporal = L3.getObject(nodo);
						L3.CambiarEstado(nodo, L2.getObject(nodo));
						L2.CambiarEstado(nodo, temporal);
						lista++;
						playerSprite.setTexture(playerDown);
						break;
					case 2:
						if (L4.movements(nodo)) {
							L4.CambiarEstado(nodo, L3.getObject(nodo));
							L3.CambiarEstado(nodo, L2.getObject(nodo));
							L2.CambiarEstado(nodo, 0);
							lista++;
							playerSprite.setTexture(playerDown);
						}
						break;
					case 3:
						system("cls");
						cout << "No se puede bajar xq hay un muro" << endl;
						playerSprite.setTexture(playerDown);
						break;
					case 4:
						L3.CambiarEstado(nodo, L2.getObject(nodo));
						L2.CambiarEstado(nodo, 0);
						lista++;
						playerSprite.setTexture(playerDown);
						break;
				}
	//----------------------- end of sub switch list 2----------------------------
				break;// list 2

			case 3:	// list 3
	//-----------------------sub switch list 3------------------------------------
				switch (L4.getObject(nodo)) {
					case 0:
						temporal = L4.getObject(nodo);
						L4.CambiarEstado(nodo, L3.getObject(nodo));
						L3.CambiarEstado(nodo, temporal);
						lista++;
						playerSprite.setTexture(playerDown);
						break;
					case 2:
						if (L5.movements(nodo)) {
							L5.CambiarEstado(nodo, L4.getObject(nodo));
							L4.CambiarEstado(nodo, L3.getObject(nodo));
							L3.CambiarEstado(nodo, 0);
							lista++;
							playerSprite.setTexture(playerDown);
						}
						break;
					case 3:
						system("cls");
						cout << "No se puede bajar xq hay un muro" << endl;
						playerSprite.setTexture(playerDown);
						break;
					case 4:
						L4.CambiarEstado(nodo, L3.getObject(nodo));
						L3.CambiarEstado(nodo, 0);
						lista++;
						playerSprite.setTexture(playerDown);
						break;
				}
	//----------------------- end of sub switch list 3-----------------------------
				break; // list 3

			case 4: //list 4
	//-----------------------sub switch list 4-------------------------------------
				switch (L5.getObject(nodo)){
					case 0:
						temporal = L5.getObject(nodo);
						L5.CambiarEstado(nodo, L4.getObject(nodo));
						L4.CambiarEstado(nodo, temporal);
						lista++;
						playerSprite.setTexture(playerDown);
						break;
					case 2:
						if (L6.movements(nodo)) {
							L6.CambiarEstado(nodo, L5.getObject(nodo));
							L5.CambiarEstado(nodo, L4.getObject(nodo));
							L4.CambiarEstado(nodo, 0);
							lista++;
							playerSprite.setTexture(playerDown);
						}
						break;
					case 3:
						system("cls");
						cout << "No se puede bajar xq hay un muro" << endl;
						playerSprite.setTexture(playerDown);
						break;
					case 4:
						L5.CambiarEstado(nodo, L4.getObject(nodo));
						L4.CambiarEstado(nodo, 0);
						lista++;
						playerSprite.setTexture(playerDown);
						break;
				}
	//----------------------- end of sub switch list 4-----------------------------
				break;// list 4

			case 5:// list 5
	//-----------------------sub switch list 5-------------------------------------
				switch (L6.getObject(nodo)){
					case 0:
						temporal = L6.getObject(nodo);
						L6.CambiarEstado(nodo, L5.getObject(nodo));
						L5.CambiarEstado(nodo, temporal);
						lista++;
						playerSprite.setTexture(playerDown);
						break;
					case 2:
						if (L7.movements(nodo)) {
							L7.CambiarEstado(nodo, L6.getObject(nodo));
							L6.CambiarEstado(nodo, L5.getObject(nodo));
							L5.CambiarEstado(nodo, 0);
							lista++;
							playerSprite.setTexture(playerDown);
						}
						break;
					case 3:
						system("cls");
						cout << "No se puede bajar xq hay un muro" << endl;
						break;
						playerSprite.setTexture(playerDown);
					case 4:
						L6.CambiarEstado(nodo, L5.getObject(nodo));
						L5.CambiarEstado(nodo, 0);
						lista++;
						playerSprite.setTexture(playerDown);
						break;
				}
	//----------------------- end of sub switch list 5-----------------------------
				break;// list 5

			case 6: // list 6
	//-----------------------sub switch list 6-------------------------------------
				switch (L7.getObject(nodo)) {
				case 0:
					temporal = L7.getObject(nodo);
					L7.CambiarEstado(nodo, L6.getObject(nodo));
					L6.CambiarEstado(nodo, temporal);
					lista++;
					playerSprite.setTexture(playerDown);
					break;
				case 2:
					if (L8.movements(nodo)) {
						L8.CambiarEstado(nodo, L7.getObject(nodo));
						L7.CambiarEstado(nodo, L6.getObject(nodo));
						L6.CambiarEstado(nodo, 0);
						lista++;
						playerSprite.setTexture(playerDown);
					}
					break;
				case 3:
					system("cls");
					cout << "No se puede bajar xq hay un muro" << endl;
					break;
					playerSprite.setTexture(playerDown);
				case 4:
					L7.CambiarEstado(nodo, L6.getObject(nodo));
					L6.CambiarEstado(nodo, 0);
					lista++;
					playerSprite.setTexture(playerDown);
					break;
				}
	//----------------------- end of sub switch list 6-----------------------------
				break;// list 6

			case 7: // list 7
				system("cls");
				cout << "Abajo hay un muro, no puede bajar" << endl;
				playerSprite.setTexture(playerDown);
				break; //Lista 7
		}
	//-----------------------end of principle switch------------------------------
	}// End of keyboard down

	if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)){
		system("cls");
		string rep = " Right";
		cout << rep << endl;
		repetition += rep;

		switch (lista) {	
			case 2:
				if (L2.movementsR(nodo)) {
					nodo++;									
					playerSprite.setTexture(playerRight);
				}
				break;
			case 3:
				if (L3.movementsR(nodo)) {
					nodo++;
					playerSprite.setTexture(playerRight);
				}
				break;
			case 4:
				if (L4.movementsR(nodo)) {
					nodo++;
					playerSprite.setTexture(playerRight);
				}
				break;
			case 5:
				if (L5.movementsR(nodo)) {
					nodo++;
					playerSprite.setTexture(playerRight);
				}
				break;
			case 6:
				if (L6.movementsR(nodo)) {
					nodo++;
					playerSprite.setTexture(playerRight);
				}
				break;
			case 7:
				if (L7.movementsR(nodo)) {
					nodo++;
					playerSprite.setTexture(playerRight);
				}
				break;
			default: {}
		}
	}// end of keyboard right

	if (Keyboard::isKeyPressed(Keyboard::LShift)){// restard the game
		deleteLists();
		system("cls");
		cout << "Se ha reiniciado el nivel" << endl;
		fillLists();
	}// end of keyboard left shift

	if (Keyboard::isKeyPressed(Keyboard::BackSpace)){ // go to menu
		deleteLists();
		completo1 = false;
		completo2 = false;
		completo3 = false;
		completo4 = false;
		completo5 = false;
		initiateMenu();
	}// end of keyboard backspace

	if (Keyboard::isKeyPressed(Keyboard::Escape)){ // close the game
		VentanaPrincipal.close();					
	}// end of keyboard escape
}// end of movements

void Ventana::update(){
	if (!completo1){
		completo1 = WL.ganar3(WL, ganar1);
		nextLevel(completo1);
	}// level 1 complete
	else if (!completo2){	
		completo2 = WL.ganar2(WL, ganar1);
		nextLevel(completo2);
	}// level 2 complete
	else if (!completo3){
		completo3 = WL.ganar2(WL, ganar1);
		nextLevel(completo3);
	}// level 3 complete
	else if (!completo4) {
		completo4 = WL.ganar(WL, ganar1);
		nextLevel(completo4);
	}// level 4 complete
	else if (!completo5) {
		completo5 = WL.ganar(WL, ganar1);
	}// level 5 complete
	else if (completo5) {
		system("cls");
		cout << "HAS COMPLETADO TODOS LO NIVELES!!!!" << endl << endl;
		system("pause");
		deleteLists();
		completo1 = false;
		completo2 = false;
		completo3 = false;
		completo4 = false;
		completo5 = false;
		initiateMenu();
	}
}// end of update

void Ventana::render() {

	VentanaPrincipal.clear(Color(205, 201, 201));
	pokemonRed.setPosition(600.f, 125.f);
	VentanaPrincipal.draw(pokemonRed);

	int x = 0;// use as a coordinate to paint each frame

	paintLevel(x, L1, 1); // paints the first row
	x = x++;

	paintLevel(x, L2, 2); // paints the sencond row
	x = x++;

	paintLevel(x, L3, 3); // paints the third row
	x = x++;

	paintLevel(x, L4, 4); // paints the fourth row
	x = x++;

	paintLevel(x, L5, 5); // paints the fifth row
	x = x++;

	paintLevel(x, L6, 6); // paints the sixth row
	x = x++;

	paintLevel(x, L7, 7); // paints the seventh row
	x = x++;

	paintLevel(x, L8, 8); // paints the eighth row

	for (int i = 0; i < 4; i++) {
		VentanaPrincipal.draw(opciones[i]);	// prints game's options
	}
	VentanaPrincipal.draw(Level);// prints the level's number
	VentanaPrincipal.display();
}// end of render

void Ventana::run() {

	initializeWindow();
	while (VentanaPrincipal.isOpen()){
		movements();
		update();
		render();
	}
	VentanaPrincipal.close();
}

void Ventana::fillLists() {

	if (!completo1) {			
		Level.setString("Level 1");
		ifstream Nivel1;
		Nivel1.open("Nivel 1.txt", ios::in);
		if (Nivel1.is_open()) {
			int c;
			while (!Nivel1.eof()) {
				for (int i = 0; i < 9; i++) {	
					Nivel1 >> c;
					if (c == 4) {								
						WL = L1;
						ganar1 = i + 1;							
					}
					L1.insert(c);				
				}
				for (int i = 0; i < 9; i++) {		
					Nivel1 >> c;				
					if (c == 4) {
						WL = L2;
						ganar1 = i + 1;
					}
					L2.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel1 >> c;
					if (c == 4) {
						WL = L3;
						ganar1 = i + 1;
					}
					L3.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel1 >> c;
					if (c == 4) {
						WL = L4;
						ganar1 = i + 1;
					}
					L4.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel1 >> c;
					if (c == 4) {
						WL = L5;
						ganar1 = i + 1;
					}
					L5.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel1 >> c;
					if (c == 4) {
						WL = L6;
						ganar1 = i + 1;
					}
					L6.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel1 >> c;
					if (c == 4) {
						WL = L7;
						ganar1 = i + 1;
					}
					L7.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel1 >> c;
					if (c == 4) {
						WL = L8;
						ganar1 = i + 1;
					}
					L8.insert(c);
				}
			}
			return;
		}
		else {
		}
	}//NIVEL 1 COMPLETADO
	else if (!completo2) {								//SI EL NIVEL 1 ESTÁ COMPLETO  Y EL NIVEL 2 N0..., SE REALIZA EL MISMO RECORRIDO 
		Level.setString("Level 2");						//LEYENDO EL ARCHIVO DEL NIVEL 2
		ifstream Nivel2;
		Nivel2.open("Nivel 2.txt", ios::in);
		if (Nivel2.is_open()) {
			int c;
			while (!Nivel2.eof()) {
				for (int i = 0; i < 9; i++) {
					Nivel2 >> c;
					if (c == 4) {
						WL = L1;
						ganar1 = i + 1;
					}
					L1.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel2 >> c;
					if (c == 4) {
						WL = L2;
						ganar1 = i + 1;
					}
					L2.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel2 >> c;
					if (c == 4) {
						WL = L3;
						ganar1 = i + 1;
					}
					L3.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel2 >> c;
					if (c == 4) {
						WL = L4;
						ganar1 = i + 1;
					}
					L4.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel2 >> c;
					if (c == 4) {
						WL = L5;
						ganar1 = i + 1;
					}
					L5.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel2 >> c;
					if (c == 4) {
						WL = L6;
						ganar1 = i + 1;
					}
					L6.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel2 >> c;
					if (c == 4) {
						WL = L7;
						ganar1 = i + 1;
					}
					L7.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel2 >> c;
					if (c == 4) {
						WL = L8;
						ganar1 = i + 1;
					}
					L8.insert(c);
				}
			}
			return;
		}
		else {
			cout << "No se encontro el archivo" << endl;
		}
	}//NIVEL 2 COMPLETADO

	else if (!completo3) {						//SI EL NIVEL 1 Y 2 ESTÁN COMPLETOS  Y EL NIVEL 3 N0..., SE REALIZA EL MISMO RECORRIDO 
		Level.setString("Level 3");				//LEYENDO EL ARCHIVO DEL NIVEL 3
		ifstream Nivel3;
		Nivel3.open("Nivel 3.txt", ios::in);
		if (Nivel3.is_open()) {
			int c;
			while (!Nivel3.eof()) {

				for (int i = 0; i < 9; i++) {
					Nivel3 >> c;
					if (c == 4) {
						WL = L1;
						ganar1 = i + 1;
					}
					L1.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel3 >> c;
					if (c == 4) {
						WL = L2;
						ganar1 = i + 1;
					}
					L2.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel3 >> c;
					if (c == 4) {
						WL = L3;
						ganar1 = i + 1;
					}
					L3.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel3 >> c;
					if (c == 4) {
						WL = L4;
						ganar1 = i + 1;
					}
					L4.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel3 >> c;
					if (c == 4) {
						WL = L5;
						ganar1 = i + 1;
					}
					L5.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel3 >> c;
					if (c == 4) {
						WL = L6;
						ganar1 = i + 1;
					}
					L6.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel3 >> c;
					if (c == 4) {
						WL = L7;
						ganar1 = i + 1;
					}
					L7.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel3 >> c;
					if (c == 4) {
						WL = L8;
						ganar1 = i + 1;
					}
					L8.insert(c);
				}
			}
			return;
		}
		else {
			cout << "No se encontro el archivo" << endl;
		}
	}//NIVEL 3 COMPLETADO
	else if (!completo4) {						//SI EL NIVEL 1 Y 2 Y 3 ESTÁN COMPLETOS  Y EL NIVEL 4 N0..., SE REALIZA EL MISMO RECORRIDO 
		ifstream Nivel4;						//LEYENDO EL ARCHIVO DEL NIVEL 4
		Level.setString("Level 4");
		Nivel4.open("Nivel 4.txt", ios::in);
		if (Nivel4.is_open()) {
			int c;
			while (!Nivel4.eof()) {
				for (int i = 0; i < 9; i++) {
					Nivel4 >> c;
					if (c == 4) {
						WL = L1;
						ganar1 = i + 1;
					}
					L1.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel4 >> c;
					if (c == 4) {
						WL = L2;
						ganar1 = i + 1;
					}
					L2.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel4 >> c;
					if (c == 4) {
						WL = L3;
						ganar1 = i + 1;
					}
					L3.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel4 >> c;
					if (c == 4) {
						WL = L4;
						ganar1 = i + 1;
					}
					L4.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel4 >> c;
					if (c == 4) {
						WL = L5;
						ganar1 = i + 1;
					}
					L5.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel4 >> c;
					if (c == 4) {
						WL = L6;
						ganar1 = i + 1;
					}
					L6.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel4 >> c;
					if (c == 4) {
						WL = L7;
						ganar1 = i + 1;
					}
					L7.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel4 >> c;
					if (c == 4) {
						WL = L8;
						ganar1 = i + 1;
					}
					L8.insert(c);
				}
			}
			return;
		}
		else {
			cout << "No se encontro el archivo" << endl;
		}
	}//NIVEL 4 COMPLETADO
	else if (!completo5) {					//SI EL NIVEL 1 Y 2 Y 3 Y 4 ESTÁN COMPLETOS  Y EL NIVEL 5 N0..., SE REALIZA EL MISMO RECORRIDO 
		Level.setString("Level 5");			//LEYENDO EL ARCHIVO DEL NIVEL 5
		ifstream Nivel5;
		Nivel5.open("Nivel 5.txt", ios::in);
		if (Nivel5.is_open()) {
			int c;
			while (!Nivel5.eof()) {
				for (int i = 0; i < 9; i++) {
					Nivel5 >> c;
					if (c == 4) {
						WL = L1;
						ganar1 = i + 1;
					}
					L1.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel5 >> c;
					if (c == 4) {
						WL = L2;
						ganar1 = i + 1;
					}
					L2.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel5 >> c;
					if (c == 4) {
						WL = L3;
						ganar1 = i + 1;
					}
					L3.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel5 >> c;
					if (c == 4) {
						WL = L4;
						ganar1 = i + 1;
					}
					L4.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel5 >> c;
					if (c == 4) {
						WL = L5;
						ganar1 = i + 1;
					}
					L5.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel5 >> c;
					if (c == 4) {
						WL = L6;
						ganar1 = i + 1;
					}
					L6.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel5 >> c;
					if (c == 4) {
						WL = L7;
						ganar1 = i + 1;
					}
					L7.insert(c);
				}
				for (int i = 0; i < 9; i++) {
					Nivel5 >> c;
					if (c == 4) {
						WL = L8;
						ganar1 = i + 1;
					}
					L8.insert(c);
				}
			}
			return;
		}
		else {
			cout << "No se encontro el archivo" << endl;
		}
	}//NIVEL 5 COMPLETADO
}

void Ventana::setCompleto1() {
	completo1 = true;
}

void Ventana::setCompleto2() {
	completo2 = true;
}

void Ventana::setCompleto3() {
	completo3 = true;
}

void Ventana::setCompleto4() {
	completo4 = true;
}

void Ventana::setCompleto5() {
	completo5 = true;
}

void Ventana::initiateMenu() {

	Menu menu(VentanaPrincipal.getSize().x, VentanaPrincipal.getSize().y);

	while (VentanaPrincipal.isOpen()){
		sf::Event event;
		while (VentanaPrincipal.pollEvent(event)){
	//-----------------------switch Event----------------------------------------
			switch (event.type){
			case sf::Event::KeyReleased:
	//-----------------------switch key released----------------------------------
				switch (event.key.code){
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;
				case sf::Keyboard::Down:
					menu.MoveDown();
					break;
				case sf::Keyboard::W:
					menu.MoveUp();
					break;
				case sf::Keyboard::S:
					menu.MoveDown();
					break;
				case sf::Keyboard::Return:
		//-----------------------switch return----------------------------------
					switch (menu.GetPressedItem()){
						case 0:
							run();
							break;
						case 1:
							int opc;
							system("cls");
							cout << " ______________________________" << endl; 
							cout << "| ***Menu para cargar mapas*** |" << endl;
							cout << "| Digite la opcion:            |" << endl;
							cout << "|______________________________|" << endl;
							cout << "| [1] Nivel 1                  |" << endl;
							cout << "| [2] Nivel 2                  |" << endl;
							cout << "| [3] Nivel 3                  |" << endl;
							cout << "| [4] Nivel 4                  |" << endl;
							cout << "| [5] Nivel 5                  |" << endl;
							cout << "|______________________________|" << endl;

							opc = validation();
							if (opc < 1 || opc>5) {

								system("cls");
								cout << "Por favor ingrese una de las opciones validas" << endl;
							}
							else {
								switch (opc) {
									case 1:
										run();
										break;
									case 2:
										setCompleto1();
										run();
										break;
									case 3:
										setCompleto1();
										setCompleto2();
										run();
										break;
									case 4:
										setCompleto1();
										setCompleto2();
										setCompleto3();
										run();
										break;
									case 5:
										setCompleto1();
										setCompleto2();
										setCompleto3();
										setCompleto4();
										run();
										break;
									}
								}
								break;
							case 2:
								VentanaPrincipal.close();
								break;
					}
	//-----------------------end of switch return-----------------------------------
					break;
				}
	//-----------------------end of switch key released-----------------------------
				break;
			case sf::Event::Closed:
				VentanaPrincipal.close();
				break;
			}
	//-----------------------end of switch Event---------------------------------------
		}// end of second while
		VentanaPrincipal.clear(Color(72, 61,139));
		menu.draw(VentanaPrincipal);
		VentanaPrincipal.display();
	}// end of first while
}

void Ventana::deleteLists(){
	for (int i = 0; i < 9; i++) {
		L1.deleteList();
		L2.deleteList();
		L3.deleteList();
		L4.deleteList();
		L5.deleteList();
		L6.deleteList();
		L7.deleteList();
		L8.deleteList();
	}
}// End of deleteLists

int Ventana::validation() {
	int val;
	try {
		int x = 0;
		while (x == 0) {
			if (!(cin >> val)) {
				cout << "Nivel seleccionado no existe, Por favor selecciona un nivel posible" << endl; cin.get();
				cin.clear();
				cin.ignore(255, '\n');
			}// end if
			else {
				x = 1;
				throw val;
			}// end else
		}// end while
	}// end try
	catch (int i){
		return i;
	}// end catch
	return val;
}// End of validarEntrada
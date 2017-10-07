#include "Ventana.h" 

Ventana::Ventana() :VentanaPrincipal{ VideoMode{ 900,700 },"Sokoban.exe",Style::Titlebar | Style::Close }

{
	completo1 = false;
	completo2 = false;
	completo3 = false;
	completo4 = false;
	completo5 = false;

}


int Ventana::inicializar() {


	VentanaPrincipal.setFramerateLimit(10);				//El juego corra a cierta velocidad
	VentanaPrincipal.setVerticalSyncEnabled(false);		//Pantalla no parpadee cuando se actualice
	VentanaPrincipal.setKeyRepeatEnabled(false);		//Evitar que se realicen muchas acciones al presionar un boton

	if (!Pared.loadFromFile("Wall_Brown.png")) {			//Si no logran cargarse las texturas
		cout << "No se ha encontrado la imagen&pause";
		return -1;
	}
	LaPared.setTexture(Pared);

	if (!EspacioLibre.loadFromFile("GroundGravel_Concrete.png")) {
		system("No se ha encontrado la imagen&pause");
		return EXIT_FAILURE;
	}
	Disponible.setTexture(EspacioLibre);

	if (!Caja.loadFromFile("Crate_Red.png")) {
		system("No se ha encontrado la imagen&pause");
		return EXIT_FAILURE;
	}
	LaCaja.setTexture(Caja);

	if (!Jugador.loadFromFile("Character4.png")) {
		system("No se ha encontrado la imagen&pause");
		return EXIT_FAILURE;
	}
	ElJugador.setTexture(Jugador);

	if (!JugadorArriba.loadFromFile("CharacterArriba.png")) {
		system("No se ha encontrado la imagen&pause");
		return EXIT_FAILURE;
	}

	if (!JugadorDer.loadFromFile("CharacterDer.png")) {
		system("No se ha encontrado la imagen&pause");
		return EXIT_FAILURE;
	}

	if (!JugadorIzq.loadFromFile("CharacterIzq.png")) {
		system("No se ha encontrado la imagen&pause");
		return EXIT_FAILURE;
	}


	if (!PuntoGanar.loadFromFile("EndPoint_Red.png")) {
		system("No se ha encontrado la imagen&pause");
		return EXIT_FAILURE;
	}
	Ganar.setTexture(PuntoGanar);

	if (!font.loadFromFile("SuperRetro54.ttf")) {
		system("No se ha encontrado la imagen&pause");
		return EXIT_FAILURE;
	}
	if (!Red.loadFromFile("Red_skin.png")) {
		system("No se ha encontrado la imagen&pause");
		return EXIT_FAILURE;
	}
	PokemonRed.setTexture(Red);

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

	LlenarListas();
}


void Ventana::LosEventos() {

	while (VentanaPrincipal.pollEvent(eventos)) {

		if (eventos.type == Event::Closed) { //Si el evento que recibo es cerrar
			VentanaPrincipal.close();			//Cierro la ventana
		}
	}

	//Movimiento del Sprite
	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
		system("cls");
		cout << "Arriba" << endl;

		switch (lista) {			//Switch para saber en cual lista estoy de la 2 a la 7


		case 2:	//estoy en lista 2
			system("cls");
			cout << "Arriba hay un muro, no se puede mover" << endl;
			ElJugador.setTexture(JugadorArriba);
			break;



		case 3:		//Case estoy en lista 3

			switch (L2.getTipo(nodo)) {			//Saber que numero hay en la lista 2

			case 0:								// si es un 0 (Espacio Libre)

				temporal = L2.getTipo(nodo);				//Se guarda el numero que tenga la lista 2
				L2.CambiarEstado(nodo, L3.getTipo(nodo));	//La lista 2 pasa a tener el numero que tenga la lista 3
				L3.CambiarEstado(nodo, temporal);			//La Lista 3 pasa a tener el numero que se habia guardado de la lista 2
				lista--;									//El jugador pasa a estar en la lista de arriba
				ElJugador.setTexture(JugadorArriba);
				break;


			case 2:													//Si es un 2 (Una caja)
				if (L1.Movimiento(nodo)) {							//Pregunto si me puedo mover  retorna true si sí se puede o false si no
					L1.CambiarEstado(nodo, L2.getTipo(nodo));		//La Lista 1 pasa a tener el numero que tiene la Lista 2
					L2.CambiarEstado(nodo, L3.getTipo(nodo));		//La Lista 2 pasa a tener el numero que tiene la Lista 3
					L3.CambiarEstado(nodo, 0);						//La Lista 1 pasa a tener un espacio libre 
					lista--;										//El Jugador pasa a estar a la lista de arriba
					ElJugador.setTexture(JugadorArriba);
				}
				break;

			case 3:													//Si es un 3 (Un Muro)
				system("cls");
				cout << "No se puede subir xq hay un muro" << endl;		//No se puede mover
				ElJugador.setTexture(JugadorArriba);
				break;

			case 4:												//Si es un 4, punto de llegada


				L2.CambiarEstado(nodo, L3.getTipo(nodo));		//La lista de arriba se actualiza al numero que tengo la lista
				L3.CambiarEstado(nodo, 0);						//La lista se actualiza a un espacio vacio
				lista--;										//El Jugador pasa a estar en la lista de arriba
				ElJugador.setTexture(JugadorArriba);
				break;


			}//FIN SWITCH DE LO QUE ME RETORNÓ EL NUMERO DE LA LISTA DE ARRIBA

			break; //break del case 3 de la lista en la que estoy
				   //OCURRE LO MISMO PARA CUALQUIER LISTA EN LA QUE ESTE

		case 4: //Estoy en lista 4

			switch (L3.getTipo(nodo)) {

			case 0:

				temporal = L3.getTipo(nodo);
				L3.CambiarEstado(nodo, L4.getTipo(nodo));
				L4.CambiarEstado(nodo, temporal);
				lista--;
				ElJugador.setTexture(JugadorArriba);
				break;


			case 2:
				if (L2.Movimiento(nodo)) {
					L2.CambiarEstado(nodo, L3.getTipo(nodo));
					L3.CambiarEstado(nodo, L4.getTipo(nodo));
					L4.CambiarEstado(nodo, 0);
					lista--;
					ElJugador.setTexture(JugadorArriba);
				}
				break;

			case 3:
				system("cls");
				cout << "No se puede subir xq hay un muro" << endl;
				ElJugador.setTexture(JugadorArriba);
				break;

			case 4:


				L3.CambiarEstado(nodo, L4.getTipo(nodo));
				L4.CambiarEstado(nodo, 0);
				lista--;
				ElJugador.setTexture(JugadorArriba);
				break;


			}//FIN SWITCH DE LO QUE ME RETORNÓ EL NUMERO DE LA LISTA DE ARRIBA

			break;//Break Lista 4


		case 5://estoy en lista 5


			switch (L4.getTipo(nodo)) {

			case 0:

				temporal = L4.getTipo(nodo);
				L4.CambiarEstado(nodo, L5.getTipo(nodo));
				L5.CambiarEstado(nodo, temporal);
				lista--;
				ElJugador.setTexture(JugadorArriba);
				break;


			case 2:
				if (L3.Movimiento(nodo)) {
					L3.CambiarEstado(nodo, L4.getTipo(nodo));
					L4.CambiarEstado(nodo, L5.getTipo(nodo));
					L5.CambiarEstado(nodo, 0);
					lista--;
					ElJugador.setTexture(JugadorArriba);
				}
				break;

			case 3:
				system("cls");
				cout << "No se puede subir xq hay un muro" << endl;
				ElJugador.setTexture(JugadorArriba);
				break;

			case 4:


				L4.CambiarEstado(nodo, L5.getTipo(nodo));
				L5.CambiarEstado(nodo, 0);
				lista--;
				ElJugador.setTexture(JugadorArriba);
				break;

			}//FIN SWITCH DE LO QUE ME RETORNÓ EL NUMERO DE LA LISTA DE ARRIBA
			break;//Break Lista 5



		case 6: //Estoy en lista 6

			switch (L5.getTipo(nodo)) {

			case 0:

				temporal = L5.getTipo(nodo);
				L5.CambiarEstado(nodo, L6.getTipo(nodo));
				L6.CambiarEstado(nodo, temporal);
				lista--;
				ElJugador.setTexture(JugadorArriba);
				break;



			case 2:
				if (L4.Movimiento(nodo)) {
					L4.CambiarEstado(nodo, L5.getTipo(nodo));
					L5.CambiarEstado(nodo, L6.getTipo(nodo));
					L6.CambiarEstado(nodo, 0);
					lista--;
					ElJugador.setTexture(JugadorArriba);
				}
				break;

			case 3:
				system("cls");
				cout << "No se puede subir xq hay un muro" << endl;
				ElJugador.setTexture(JugadorArriba);
				break;

			case 4:


				L5.CambiarEstado(nodo, L6.getTipo(nodo));
				L6.CambiarEstado(nodo, 0);
				lista--;
				ElJugador.setTexture(JugadorArriba);
				break;




			}//FIN SWITCH DE LO QUE ME RETORNÓ EL NUMERO DE LA LISTA DE ARRIBA

			break;//Break lista 6

		case 7: //estoy en lista 7

			switch (L6.getTipo(nodo)) {

			case 0:

				temporal = L6.getTipo(nodo);
				L6.CambiarEstado(nodo, L7.getTipo(nodo));
				L7.CambiarEstado(nodo, temporal);
				lista--;
				ElJugador.setTexture(JugadorArriba);
				break;


			case 2:
				if (L5.Movimiento(nodo)) {
					L5.CambiarEstado(nodo, L6.getTipo(nodo));
					L6.CambiarEstado(nodo, L7.getTipo(nodo));
					L7.CambiarEstado(nodo, 0);
					lista--;
					ElJugador.setTexture(JugadorArriba);
				}
				break;

			case 3:
				system("cls");
				cout << "No se puede subir xq hay un muro" << endl;
				ElJugador.setTexture(JugadorArriba);
				break;

			case 4:


				L6.CambiarEstado(nodo, L7.getTipo(nodo));
				L7.CambiarEstado(nodo, 0);
				lista--;
				ElJugador.setTexture(JugadorArriba);
				break;


			}//FIN SWITCH DE LO QUE ME RETORNÓ EL NUMERO DE LA LISTA DE ARRIBA
			break; //Lista 7

		}//fin Switch LISTA EN LA QUE ESTOY

	}// Fin de presionar arriba


	if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
		system("cls");
		cout << "Izquierda" << endl;

		switch (lista) {

		case 2:
			ElJugador.setTexture(JugadorIzq);
			if (L2.MovimientoIzquierda(nodo)) {			//PREGUNTO A LA LISTA SI ME PUEDO MOVER, RETORNA TRUE SI SÍ o FALSE SI NO
				nodo--;									//ME MUEVO UNA POSICION A LA IZQUIERDA

			}
			break;

		case 3:
			ElJugador.setTexture(JugadorIzq);
			if (L3.MovimientoIzquierda(nodo)) {
				nodo--;

			}
			break;

		case 4:
			ElJugador.setTexture(JugadorIzq);
			if (L4.MovimientoIzquierda(nodo)) {
				nodo--;
			}
			break;

		case 5:
			ElJugador.setTexture(JugadorIzq);
			if (L5.MovimientoIzquierda(nodo)) {
				nodo--;

			}
			break;

		case 6:
			ElJugador.setTexture(JugadorIzq);
			if (L6.MovimientoIzquierda(nodo)) {
				nodo--;

			}

			break;

		case 7:
			ElJugador.setTexture(JugadorIzq);
			if (L7.MovimientoIzquierda(nodo)) {
				nodo--;
				ElJugador.setTexture(JugadorIzq);
			}
			break;

		default: {}
		}//fin switch


	}//Presionar Izquierda


	if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
		system("cls");
		cout << "Abajo" << endl;						//SUCEDE LO MISMO QUE PARA SUBIR, SOLO QUE AL CONTRARIA
														//PREGUNTO SI LA LISTA DE ABAJO ME PERMITE BAJAR

		switch (lista) {			//Switch para saber en cual lista estoy de la 2 a la 7


		case 2:	//estoy en lista 2

			switch (L3.getTipo(nodo)) {

			case 0:

				temporal = L3.getTipo(nodo);
				L3.CambiarEstado(nodo, L2.getTipo(nodo));
				L2.CambiarEstado(nodo, temporal);
				lista++;
				ElJugador.setTexture(Jugador);
				break;


			case 2:
				if (L4.Movimiento(nodo)) {
					L4.CambiarEstado(nodo, L3.getTipo(nodo));
					L3.CambiarEstado(nodo, L2.getTipo(nodo));
					L2.CambiarEstado(nodo, 0);
					lista++;
					ElJugador.setTexture(Jugador);
				}
				break;

			case 3:
				system("cls");
				cout << "No se puede bajar xq hay un muro" << endl;
				ElJugador.setTexture(Jugador);
				break;

			case 4:


				L3.CambiarEstado(nodo, L2.getTipo(nodo));
				L2.CambiarEstado(nodo, 0);
				lista++;
				ElJugador.setTexture(Jugador);
				break;

			}	//FIN SWITCH DE LO QUE ME DEVUELVE EL NUMERO DE ABAJO

			break;//break de estoy en lista 2


		case 3:		//Case estoy en lista 3

			switch (L4.getTipo(nodo)) {

			case 0:

				temporal = L4.getTipo(nodo);
				L4.CambiarEstado(nodo, L3.getTipo(nodo));
				L3.CambiarEstado(nodo, temporal);
				lista++;
				ElJugador.setTexture(Jugador);
				break;


			case 2:
				if (L5.Movimiento(nodo)) {
					L5.CambiarEstado(nodo, L4.getTipo(nodo));
					L4.CambiarEstado(nodo, L3.getTipo(nodo));
					L3.CambiarEstado(nodo, 0);
					lista++;
					ElJugador.setTexture(Jugador);
				}
				break;

			case 3:
				system("cls");
				cout << "No se puede bajar xq hay un muro" << endl;
				ElJugador.setTexture(Jugador);
				break;

			case 4:


				L4.CambiarEstado(nodo, L3.getTipo(nodo));
				L3.CambiarEstado(nodo, 0);
				lista++;
				ElJugador.setTexture(Jugador);
				break;


			}//FIN DE LO QUE ME DEVUELVE EL NUMERO DE ABAJO

			break; //break estoy en lista 3


		case 4: //Estoy en lista 4

			switch (L5.getTipo(nodo)) {

			case 0:

				temporal = L5.getTipo(nodo);
				L5.CambiarEstado(nodo, L4.getTipo(nodo));
				L4.CambiarEstado(nodo, temporal);
				lista++;
				ElJugador.setTexture(Jugador);
				break;


			case 2:
				if (L6.Movimiento(nodo)) {
					L6.CambiarEstado(nodo, L5.getTipo(nodo));
					L5.CambiarEstado(nodo, L4.getTipo(nodo));
					L4.CambiarEstado(nodo, 0);
					lista++;
					ElJugador.setTexture(Jugador);
				}
				break;

			case 3:
				system("cls");
				cout << "No se puede bajar xq hay un muro" << endl;
				ElJugador.setTexture(Jugador);
				break;

			case 4:


				L5.CambiarEstado(nodo, L4.getTipo(nodo));
				L4.CambiarEstado(nodo, 0);
				lista++;
				ElJugador.setTexture(Jugador);
				break;


			}//FIN SWITCH DE LO QUE ME RETORNÓ EL NUMERO DE LA LISTA DE Abajo
			break;//Break Estoy en Lista 4


		case 5://estoy en lista 5


			switch (L6.getTipo(nodo)) {

			case 0:

				temporal = L6.getTipo(nodo);
				L6.CambiarEstado(nodo, L5.getTipo(nodo));
				L5.CambiarEstado(nodo, temporal);
				lista++;
				ElJugador.setTexture(Jugador);
				break;


			case 2:
				if (L7.Movimiento(nodo)) {
					L7.CambiarEstado(nodo, L6.getTipo(nodo));
					L6.CambiarEstado(nodo, L5.getTipo(nodo));
					L5.CambiarEstado(nodo, 0);
					lista++;
					ElJugador.setTexture(Jugador);
				}
				break;

			case 3:
				system("cls");
				cout << "No se puede bajar xq hay un muro" << endl;
				break;
				ElJugador.setTexture(Jugador);

			case 4:


				L6.CambiarEstado(nodo, L5.getTipo(nodo));
				L5.CambiarEstado(nodo, 0);
				lista++;
				ElJugador.setTexture(Jugador);
				break;


			}//FIN SWITCH DE LO QUE ME RETORNÓ EL NUMERO DE LA LISTA DE ABAJO


			break;//Break estoy en Lista 5


		case 6: //Estoy en lista 6

			switch (L7.getTipo(nodo)) {

			case 0:

				temporal = L7.getTipo(nodo);
				L7.CambiarEstado(nodo, L6.getTipo(nodo));
				L6.CambiarEstado(nodo, temporal);
				lista++;
				ElJugador.setTexture(Jugador);
				break;


			case 2:
				if (L8.Movimiento(nodo)) {
					L8.CambiarEstado(nodo, L7.getTipo(nodo));
					L7.CambiarEstado(nodo, L6.getTipo(nodo));
					L6.CambiarEstado(nodo, 0);
					lista++;
					ElJugador.setTexture(Jugador);
				}
				break;

			case 3:
				system("cls");
				cout << "No se puede bajar xq hay un muro" << endl;
				break;
				ElJugador.setTexture(Jugador);

			case 4:


				L7.CambiarEstado(nodo, L6.getTipo(nodo));
				L6.CambiarEstado(nodo, 0);
				lista++;
				ElJugador.setTexture(Jugador);
				break;

			}//FIN SWITCH DE LO QUE ME RETORNÓ EL NUMERO DE LA LISTA DE ARRIBA

			break;//Break lista 6

		case 7: //estoy en lista 7

			system("cls");
			cout << "Abajo hay un muro, no puede bajar" << endl;
			ElJugador.setTexture(Jugador);
			break; //Lista 7

		}//FIN SWITCH LISTA EN LA QUE ESTOY

	}//Boton abajo


	if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
		system("cls");
		cout << "Derecha" << endl;


		switch (lista) {			//SABER EN QUE LISTA ESTOY

		case 2:
			if (L2.MovimientoDerecha(nodo)) {			//PREGUNTO A LA LISTA SI ME PUEDO MOVER, RETORNA TRUE SI SÍ o FALSE SI NO
				nodo++;									//ME MUEVO UNA POSICION A LA DERECHA
				ElJugador.setTexture(JugadorDer);
			}

			break;

		case 3:
			if (L3.MovimientoDerecha(nodo)) {
				nodo++;
				ElJugador.setTexture(JugadorDer);
			}
			break;

		case 4:
			if (L4.MovimientoDerecha(nodo)) {
				nodo++;
				ElJugador.setTexture(JugadorDer);
			}

			break;

		case 5:
			if (L5.MovimientoDerecha(nodo)) {
				nodo++;
				ElJugador.setTexture(JugadorDer);
			}

			break;

		case 6:
			if (L6.MovimientoDerecha(nodo)) {
				nodo++;
				ElJugador.setTexture(JugadorDer);
			}

			break;

		case 7:
			if (L7.MovimientoDerecha(nodo)) {
				nodo++;
				ElJugador.setTexture(JugadorDer);
			}

			break;

		default: {}
		}//fin switch

	}//fin boton presionado derecha

	 //PRESIONAR PARA REINICIAR
	if (Keyboard::isKeyPressed(Keyboard::LShift)){
		for (int i = 0; i < 9; i++) {			//SE BORRAN TODAS LAS LISTAS, SI NO SE HICIERA SE AÑADERIAN MÁS NODOS

			L1.Borrar();
			L2.Borrar();
			L3.Borrar();
			L4.Borrar();
			L5.Borrar();
			L6.Borrar();
			L7.Borrar();
			L8.Borrar();
		}
		system("cls");
		cout << "Se ha reiniciado el nivel" << endl;
		LlenarListas();							//SE VUELVEN A LLENAR LAS LISTAS
	}

	if (Keyboard::isKeyPressed(Keyboard::BackSpace)){ //SE RETORNA AL MENU PRINCIPAL BORRANDO TODAS LAS LISTAS
		for (int i = 0; i < 9; i++) {

			L1.Borrar();
			L2.Borrar();
			L3.Borrar();
			L4.Borrar();
			L5.Borrar();
			L6.Borrar();
			L7.Borrar();
			L8.Borrar();
		}

		completo1 = false;
		completo2 = false;
		completo3 = false;
		completo4 = false;
		completo5 = false;
		iniciarMenu();
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		VentanaPrincipal.close();					//SE CIERRA LA VENTANA Y SE SALE DEL JUEGO
	}

}


void Ventana::update() {

	if (!completo1) {
		completo1 = ListaGanadora.ganar(ListaGanadora, ganar1);		//SE PREGUNTA SI EL NIVEL 1 SE COMPLETÓ
		if (completo1) {											//SI ES ASÍ
			for (int i = 0; i < 9; i++) {							//SE BORRAN TODAS LAS LISTAS, SI NO SE HICIERA SE AÑADERIAN MÁS NODOS

				L1.Borrar();
				L2.Borrar();
				L3.Borrar();
				L4.Borrar();
				L5.Borrar();
				L6.Borrar();
				L7.Borrar();
				L8.Borrar();
			}
			cout << "Pasando a al nivel 2" << endl;
			LlenarListas();									//SE VUELVE A LLENAR LAS LISTAS CON EL NIVEL 1 COMPLETO
			return;
		}
	}//NIVEL 1 COMPLETO

	else if (!completo2) {									//SI EL NIVEL 2 NO HA SIDO COMPLETADO

		completo2 = ListaGanadora.ganar2(ListaGanadora, ganar1);		//SE PREGUNTA SI EL NIVEL 2 SE COMPLETÓ
		if (completo2) {											//SI ES ASÍ
			for (int i = 0; i < 9; i++) {							//SE BORRAN TODAS LAS LISTAS, SI NO SE HICIERA SE AÑADERIAN MÁS NODOS

				L1.Borrar();
				L2.Borrar();
				L3.Borrar();
				L4.Borrar();
				L5.Borrar();
				L6.Borrar();
				L7.Borrar();
				L8.Borrar();
			}
			cout << "Pasando a nivel3" << endl;
			LlenarListas();									//SE LLENAN LAS LISTAS CON EL NIVEL 1 Y 2 COMPLETOS
			return;
		}
	}//NIVEL 2 COMPLETO

	else if (!completo3) {

		completo3 = ListaGanadora.ganar2(ListaGanadora, ganar1);
		if (completo3) {
			for (int i = 0; i < 9; i++) {

				L1.Borrar();
				L2.Borrar();
				L3.Borrar();
				L4.Borrar();
				L5.Borrar();
				L6.Borrar();
				L7.Borrar();
				L8.Borrar();
			}
			cout << "Pasando a nivel 4" << endl;
			LlenarListas();
			return;
		}
	}
	else if (!completo4) {

		completo4 = ListaGanadora.ganar(ListaGanadora, ganar1);
		if (completo4) {
			for (int i = 0; i < 9; i++) {

				L1.Borrar();
				L2.Borrar();
				L3.Borrar();
				L4.Borrar();
				L5.Borrar();
				L6.Borrar();
				L7.Borrar();
				L8.Borrar();
			}
			cout << "Pasando a Nivel 5" << endl;
			LlenarListas();
			return;
		}
	}
	else if (!completo5) {

		completo5 = ListaGanadora.ganar(ListaGanadora, ganar1);

	}
	else if (completo5) {
		system("cls");
		cout << "HAS COMPLETADO TODOS LO NIVELES!!!!" << endl << endl;
		system("pause");
		for (int i = 0; i < 9; i++) {

			L1.Borrar();
			L2.Borrar();
			L3.Borrar();
			L4.Borrar();
			L5.Borrar();
			L6.Borrar();
			L7.Borrar();
			L8.Borrar();
		}

		completo1 = false;
		completo2 = false;
		completo3 = false;
		completo4 = false;
		completo5 = false;
		iniciarMenu();
	}


}

void Ventana::render() {

	VentanaPrincipal.clear(Color(250, 235, 215));
	//ventana un for para recorrer la lista y 
	//for donde voy recorriendo la lista

	PokemonRed.setPosition(600.f, 125.f);
	VentanaPrincipal.draw(PokemonRed);


	int x = 0;						//VARIABLE GLOBAL PARA EL METODO QUE SETTEARÁ LA POSICION "Y" DEL OBJETO

	for (int i = 0; i < 9; i++) {

		//Obtener los numeros de la primera lista
		int pos = L1.getTipo(i);

		switch (pos) {						//SE DISTRIBUIRÁ SEGUN EL NUMERO QUE TENGA

		case 0:								//SI ES UN 0 NO SE HARÁ NADA PUES ES UN ESPACIO LIBRE

			break;

		case 1:														// SI ES UN 1 SE PINTARÁ AL JUGADOR
			ElJugador.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(ElJugador);
			lista = 1;
			nodo = i;
			break;

		case 2:														// SI ES UN 2 SE PINTARÁ LA CAJA					
			LaCaja.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(LaCaja);
			break;

		case 3:														// SI ES UN 3 SE PINTARÁ EL MURO
			LaPared.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(LaPared);
			break;

		case 4:
			Ganar.setPosition(Vector2f(i*63.f, x*63.f));			// SI ES UN 4 SE PINTARÁ EL PUNTO DE GANAR
			VentanaPrincipal.draw(Ganar);
			break;

		default: {}
		}
	}

	x = x + 1;		//LA VARIABLE X AUMENTARÁ UNO PARA LAS IMAGENES NO CAIGAN ENCIMA DE LAS ANTERIORES

	for (int i = 0; i < 9; i++) {									//SE REALIZA LO MISMO PARA TODAS LAS LISTAS

																	//Obtener los numeros de la segunda lista
		int pos = L2.getTipo(i);

		switch (pos) {

		case 0:

			break;

		case 1:
			ElJugador.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(ElJugador);
			lista = 2;
			nodo = i;
			break;

		case 2:
			LaCaja.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(LaCaja);
			break;

		case 3:
			LaPared.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(LaPared);
			break;

		case 4:
			Ganar.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(Ganar);
			break;

		default: {}
		}
	}


	x = x++;

	for (int i = 0; i < 9; i++) {

		//Obtener los numeros de la tercera lista
		int pos = L3.getTipo(i);

		switch (pos) {

		case 0:

			break;

		case 1:
			ElJugador.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(ElJugador);
			lista = 3;
			nodo = i;
			break;

		case 2:
			LaCaja.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(LaCaja);
			break;

		case 3:
			LaPared.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(LaPared);
			break;

		case 4:
			Ganar.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(Ganar);
			break;

		default: {}
		}
	}

	x = x++;

	for (int i = 0; i < 9; i++) {

		//Obtener los numeros de la cuarta lista
		int pos = L4.getTipo(i);

		switch (pos) {

		case 0:

			break;

		case 1:
			ElJugador.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(ElJugador);
			lista = 4;
			nodo = i;
			break;


		case 2:
			LaCaja.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(LaCaja);
			break;

		case 3:
			LaPared.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(LaPared);
			break;

		case 4:
			Ganar.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(Ganar);
			break;

		default: {}
		}
	}

	x = x++;

	for (int i = 0; i < 9; i++) {

		//Obtener los numeros de la quinta lista
		int pos = L5.getTipo(i);

		switch (pos) {

		case 0:

			break;

		case 1:
			ElJugador.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(ElJugador);
			lista = 5;
			nodo = i;
			break;

		case 2:
			LaCaja.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(LaCaja);
			break;

		case 3:
			LaPared.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(LaPared);
			break;

		case 4:

			Ganar.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(Ganar);
			break;

		default: {}
		}
	}

	x = x++;

	for (int i = 0; i < 9; i++) {

		//Obtener los numeros de la sexta lista
		int pos = L6.getTipo(i);

		switch (pos) {

		case 0:

			break;

		case 1:
			ElJugador.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(ElJugador);
			lista = 6;
			nodo = i;
			break;

		case 2:
			LaCaja.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(LaCaja);
			break;

		case 3:
			LaPared.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(LaPared);
			break;

		case 4:

			Ganar.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(Ganar);
			break;

		default: {}
		}
	}

	x = x++;

	for (int i = 0; i < 9; i++) {

		//Obtener los numeros de la setima lista
		int pos = L7.getTipo(i);

		switch (pos) {

		case 0:

			break;

		case 1:
			ElJugador.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(ElJugador);
			lista = 7;
			nodo = i;
			break;

		case 2:
			LaCaja.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(LaCaja);
			break;

		case 3:
			LaPared.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(LaPared);
			break;

		case 4:
			Ganar.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(Ganar);
			break;

		default: {}
		}
	}


	x = x++;

	for (int i = 0; i < 9; i++) {

		//Obtener los numeros de la octava lista
		int pos = L8.getTipo(i);

		switch (pos) {

		case 0:

			break;

		case 1:
			ElJugador.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(ElJugador);
			lista = 8;
			nodo = i;
			break;

		case 2:
			LaCaja.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(LaCaja);
			break;

		case 3:
			LaPared.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(LaPared);
			break;

		case 4:

			Ganar.setPosition(Vector2f(i*63.f, x*63.f));
			VentanaPrincipal.draw(Ganar);
			break;

		default: {}
		}
	}

	for (int i = 0; i < 4; i++) {
		VentanaPrincipal.draw(opciones[i]);			//SE DIBUJAN LAS OPCIONES DE REINICAR, VOLVER AL MENU Y SALIR
	}
	VentanaPrincipal.draw(Level);					//SE DIBUJA EL NUMERO DEL NIVEL

	VentanaPrincipal.display();



}

void Ventana::run() {

	inicializar();

	while (VentanaPrincipal.isOpen())
	{

		LosEventos();
		update();
		render();

	}
	cleared();
}

void Ventana::cleared() {
	VentanaPrincipal.close();
}


void Ventana::LlenarListas() {

	if (!completo1) {					//SI EL NIVEL 1 NO HA SIDO COMPLETADO
		Level.setString("Level 1");
		ifstream Nivel1;

		Nivel1.open("Nivel 1.txt", ios::in);
		if (Nivel1.is_open()) {
			int c;
			while (!Nivel1.eof()) {

				for (int i = 0; i < 9; i++) {				//FOR DE 9 PARA LLENAR 9 NODOS DE LA PRIMERA LISTA
					Nivel1 >> c;
					if (c == 4) {								//SI SE LEE UN "4" ESTA LISTA TIENE LOS ESPACIOS DE GANE
						ListaGanadora = L1;
						ganar1 = i + 1;							// El número "i" del corrido será el último espacio de gane

					}
					L1.insertar(c);				//SE INSERTA EL NUMERO QUE SE LEE DESDE EL ARCHIVO A LA PRIMERA LISTA
				}

				for (int i = 0; i < 9; i++) {				//FOR DE 9 PARA LLENAR 9 NODOS DE LA SEGUNDA LISTA
					Nivel1 >> c;							//Se realizan las mismas acciones con las otras 7 Listas
					if (c == 4) {
						ListaGanadora = L2;
						ganar1 = i + 1;

					}
					L2.insertar(c);
				}


				for (int i = 0; i < 9; i++) {
					Nivel1 >> c;
					if (c == 4) {
						ListaGanadora = L3;
						ganar1 = i + 1;

					}
					L3.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel1 >> c;
					if (c == 4) {
						ListaGanadora = L4;
						ganar1 = i + 1;

					}
					L4.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel1 >> c;
					if (c == 4) {
						ListaGanadora = L5;
						ganar1 = i + 1;

					}
					L5.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel1 >> c;
					if (c == 4) {
						ListaGanadora = L6;
						ganar1 = i + 1;

					}
					L6.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel1 >> c;
					if (c == 4) {
						ListaGanadora = L7;
						ganar1 = i + 1;

					}
					L7.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel1 >> c;
					if (c == 4) {
						ListaGanadora = L8;
						ganar1 = i + 1;

					}
					L8.insertar(c);
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
						ListaGanadora = L1;
						ganar1 = i + 1;

					}
					L1.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel2 >> c;
					if (c == 4) {
						ListaGanadora = L2;
						ganar1 = i + 1;

					}
					L2.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel2 >> c;
					if (c == 4) {
						ListaGanadora = L3;
						ganar1 = i + 1;

					}
					L3.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel2 >> c;
					if (c == 4) {
						ListaGanadora = L4;
						ganar1 = i + 1;

					}
					L4.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel2 >> c;
					if (c == 4) {
						ListaGanadora = L5;
						ganar1 = i + 1;

					}
					L5.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel2 >> c;
					if (c == 4) {
						ListaGanadora = L6;
						ganar1 = i + 1;

					}
					L6.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel2 >> c;
					if (c == 4) {
						ListaGanadora = L7;
						ganar1 = i + 1;

					}
					L7.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel2 >> c;
					if (c == 4) {
						ListaGanadora = L8;
						ganar1 = i + 1;

					}
					L8.insertar(c);
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
						ListaGanadora = L1;
						ganar1 = i + 1;

					}
					L1.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel3 >> c;
					if (c == 4) {
						ListaGanadora = L2;
						ganar1 = i + 1;

					}
					L2.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel3 >> c;
					if (c == 4) {
						ListaGanadora = L3;
						ganar1 = i + 1;

					}
					L3.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel3 >> c;
					if (c == 4) {
						ListaGanadora = L4;
						ganar1 = i + 1;

					}
					L4.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel3 >> c;
					if (c == 4) {
						ListaGanadora = L5;
						ganar1 = i + 1;

					}
					L5.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel3 >> c;
					if (c == 4) {
						ListaGanadora = L6;
						ganar1 = i + 1;

					}
					L6.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel3 >> c;
					if (c == 4) {
						ListaGanadora = L7;
						ganar1 = i + 1;

					}
					L7.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel3 >> c;
					if (c == 4) {
						ListaGanadora = L8;
						ganar1 = i + 1;

					}
					L8.insertar(c);
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
						ListaGanadora = L1;
						ganar1 = i + 1;

					}
					L1.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel4 >> c;
					if (c == 4) {
						ListaGanadora = L2;
						ganar1 = i + 1;

					}
					L2.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel4 >> c;
					if (c == 4) {
						ListaGanadora = L3;
						ganar1 = i + 1;

					}
					L3.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel4 >> c;
					if (c == 4) {
						ListaGanadora = L4;
						ganar1 = i + 1;

					}
					L4.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel4 >> c;
					if (c == 4) {
						ListaGanadora = L5;
						ganar1 = i + 1;

					}
					L5.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel4 >> c;
					if (c == 4) {
						ListaGanadora = L6;
						ganar1 = i + 1;

					}
					L6.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel4 >> c;
					if (c == 4) {
						ListaGanadora = L7;
						ganar1 = i + 1;

					}
					L7.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel4 >> c;
					if (c == 4) {
						ListaGanadora = L8;
						ganar1 = i + 1;

					}
					L8.insertar(c);
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
						ListaGanadora = L1;
						ganar1 = i + 1;

					}
					L1.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel5 >> c;
					if (c == 4) {
						ListaGanadora = L2;
						ganar1 = i + 1;

					}
					L2.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel5 >> c;
					if (c == 4) {
						ListaGanadora = L3;
						ganar1 = i + 1;

					}
					L3.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel5 >> c;
					if (c == 4) {
						ListaGanadora = L4;
						ganar1 = i + 1;

					}
					L4.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel5 >> c;
					if (c == 4) {
						ListaGanadora = L5;
						ganar1 = i + 1;

					}
					L5.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel5 >> c;
					if (c == 4) {
						ListaGanadora = L6;
						ganar1 = i + 1;

					}
					L6.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel5 >> c;
					if (c == 4) {
						ListaGanadora = L7;
						ganar1 = i + 1;

					}
					L7.insertar(c);
				}

				for (int i = 0; i < 9; i++) {
					Nivel5 >> c;
					if (c == 4) {
						ListaGanadora = L8;
						ganar1 = i + 1;

					}
					L8.insertar(c);
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


void Ventana::iniciarMenu() {

	Menu menu(VentanaPrincipal.getSize().x, VentanaPrincipal.getSize().y);

	while (VentanaPrincipal.isOpen())
	{
		sf::Event event;

		while (VentanaPrincipal.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
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

					switch (menu.GetPressedItem())
					{
					case 0:
						run();
						break;

					case 1:
						int opc;
						system("cls");
						cout << "Digite la opcion para cargar el nivel?" << endl << endl;
						cout << "[1] Nivel 1" << endl;
						cout << "[2] Nivel 2" << endl;
						cout << "[3] Nivel 3" << endl;
						cout << "[4] Nivel 4" << endl;
						cout << "[5] Nivel 5" << endl;

						opc = validarEntrada();
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

					break;
				}

				break;
			case sf::Event::Closed:
				VentanaPrincipal.close();

				break;

			}
		}

		VentanaPrincipal.clear(Color(72, 61,139));
		

		menu.draw(VentanaPrincipal);
		VentanaPrincipal.display();
	}

}

int Ventana::validarEntrada() {
	int val;
	try {
		int x = 0;
		while (x == 0) {

			if (!(cin >> val)) {
				cout << "Nivel seleccionado no existe, Por favor selecciona un nivel posible" << endl; cin.get();
				cin.clear();
				cin.ignore(255, '\n');
			}
			else {
				x = 1;
				throw val;
			}

		}
	}
	catch (int i) { return i; }
	return val;
}
#include "Lista.h"

Lista::Lista() {
	inicio = nullptr;
}

void Lista::insertar(int v) {


	Nodo *temp = inicio;
	Nodo *nuevo = new Nodo();

	nuevo->tipoPosicion = v;
	nuevo->siguiente = nullptr;
	nuevo->anterior = nullptr;

	if (inicio == nullptr) {
		inicio = nuevo;

		return;
	}

	while (temp->siguiente != nullptr) {
		temp = temp->siguiente;
	}
	temp->siguiente = nuevo;
	nuevo->anterior = temp;


}

int Lista::getTipo(int num) {

	Nodo* temp = inicio;


	for (int i = 0; i<9; i++) {		//ME MUEVO POR LOS 9 NODOS DE LA LISTA
		if (i == num) {				//SI ALGUNA POSICION COINCIDE CON EL NUMERO ENVIADO (QUE SERIA EL NODO DE LA POSICION EN LA QUE ESTOY
			return temp->tipoPosicion;		//RETORNO EL NUMERO QUE TIENE EL NODO
		}
		temp = temp->siguiente;
	}


}

bool Lista::Movimiento(int numeroNodo) {
	Nodo *temp = inicio;

	for (int i = 0; i < numeroNodo; i++) {
		temp = temp->siguiente;					//ME POSICIONO EN LA POSICION DEL NODO EN EL QUE ESTOY
	}


	if (temp->tipoPosicion == 3) {					//SI EL NUMERO EN LA POSICION DEL NODO ES UN 3 (MURO)
		cout << "Arriba hay un muro luego de la caja, no se puede mover" << endl;
		return false;								//NO SE PUEDE MOVER
	}

	else if (temp->tipoPosicion == 2) {					//SI EL NUMERO EN LA POSICION DEL NODO ES UN 2 (CAJA)
		cout << "No se puede subir xq hay una caja contiguo a la caja" << endl;
		return false;									//NO SE PUEDE MOVER

	}
	else if (temp->tipoPosicion == 0 || temp->tipoPosicion == 4) {	//SI EL NUMERO EN LA POSICION DEL NODO ES UN 0 (LIBRE) o 4(LUGAR DE GANAR)
		return true;
	}

}


bool Lista::MovimientoDerecha(int numeroNodo) {

	Nodo*temp = inicio;

	for (int i = 0; i < numeroNodo; i++) {
		temp = temp->siguiente;						//ME POSICIONO EN EL NODO EN EL QUE ESTOY
	}


	if (temp->siguiente->tipoPosicion == 3) {			//SI EL NUMERO DEL NODO EN EL QUE ESTOY ES UN 3 (MURO)
		cout << "es un muro, no se puede mover" << endl;
		return false;									//NO ME PUEDO MOVER
	}
	else if (temp->siguiente->tipoPosicion == 2) {				//SI EL NUMERO DEL NODO EN EL QUE ESTOY ES UN 2 (CAJA)
		if (temp->siguiente->siguiente->tipoPosicion == 3) {	//Y SI LA SIGUIENTE A LA DERECHA ES UN MURO
			cout << "Lo siguiente a la caja es un muro, no se puede  mover" << endl;
			return false;										//NO SE PUEDE MOVER
		}
		else if (temp->siguiente->siguiente->tipoPosicion == 2) {	//Y SI LA SIGUIENTE A LA DERECHA TAMBIEN ES UNA CAJA
			cout << "Lo siguiente a la caja es una caja, no se puede  mover" << endl;
			return false;											//NO SE PUEDE MOVER
		}
		else {
			temp->tipoPosicion = 0;								//SI ES UN ESPACIO LIBRE O UN PUNTO GANAR
			temp->siguiente->tipoPosicion = 1;					//LO SIGUIENTE A LA DERECHA ES UN JUGADOR
			temp->siguiente->siguiente->tipoPosicion = 2;		//LO SIGUIENTE AL JUGADOR ES LA CAJA
			return true;										// SI ME PUEDO MOVER
		}
	}
	else if (temp->siguiente->tipoPosicion == 0) {				//SI LA POSICION ES LIBRE
		temp->siguiente->tipoPosicion = 1;						// LO SIGUIENTE ES EL JUGADOR
		temp->tipoPosicion = 0;									//EN DONDE ESTOY PASA A SER UN ESPACIO LIBRE
		return true;											//SI ME PUEDO MOVER
	}



	if (temp->anterior->tipoPosicion == 4 && temp->siguiente->tipoPosicion == 4) {		// SI ES UN PUNTO DE GANE
		temp->siguiente->tipoPosicion = 1;
		temp->tipoPosicion = 4;
		return true;

	}
	else if (temp->siguiente->siguiente->siguiente->tipoPosicion == 4) {
		temp->siguiente->tipoPosicion = 1;
		temp->tipoPosicion = 0;
		return true;
	}
	else {
		temp->siguiente->tipoPosicion = 1;
		temp->tipoPosicion = 4;
		return true;
	}

}

bool Lista::MovimientoIzquierda(int numeroNodo) {
	//LO MISMO DE LA DERECHA SOLO QUE SE PREGUNTA POR EL ANTERIOR
	Nodo*temp = inicio;

	for (int i = 0; i < numeroNodo; i++) {
		temp = temp->siguiente;
	}

	if (temp->anterior->tipoPosicion == 3) {
		cout << "es un muro, no se puede mover" << endl;
		return false;
	}
	else if (temp->anterior->tipoPosicion == 2) {
		if (temp->anterior->anterior->tipoPosicion == 3) {
			cout << "Lo siguiente a la caja es un muro, no se puede  mover" << endl;
			return false;
		}
		else if (temp->anterior->anterior->tipoPosicion == 2) {
			cout << "Lo siguiente a la caja es una caja, no se puede  mover" << endl;
			return false;
		}

		else {
			temp->tipoPosicion = 0;
			temp->anterior->tipoPosicion = 1;
			temp->anterior->anterior->tipoPosicion = 2;
			return true;
		}
	}
	else if (temp->anterior->tipoPosicion == 0) {
		temp->anterior->tipoPosicion = 1;
		temp->tipoPosicion = 0;
		return true;
	}




	if (temp->anterior->anterior->tipoPosicion == 4) {
		temp->anterior->tipoPosicion = 1;
		temp->tipoPosicion = 4;
		return true;
	}
	else {
		temp->anterior->tipoPosicion = 1;
		temp->tipoPosicion = 4;
		return true;
	}


}

void Lista::CambiarEstado(int numeroNodo, int actualizar) {

	Nodo *temp = inicio;

	for (int i = 0; i < numeroNodo; i++) {
		temp = temp->siguiente;					//ME POSICIONO EN EL NODO EN EL QUE ESTOY
	}

	temp->tipoPosicion = actualizar;				//SE ACTUALIZA EL NUMERO DEL NODO EN EL QUE ESTOY


}

bool Lista::ganar(Lista L, int numero) {


	Nodo* temp = inicio;

	for (int i = 1; i < 9; i++) {			//VOY RECCORIENDO LOS NODOS
		if (i == numero) {
			if (temp->tipoPosicion == 2 && temp->anterior->tipoPosicion == 2 && temp->anterior->anterior->tipoPosicion == 2) { //SI EL PUNTO DE GANAR TIENE UN 2(CAJA) Y EL ANTERIOR TAMBIEN, Y EL ANTERIOR DEL ANTERIOR TAMBIEN ES UN 2
				cout << "NIVEL COMPLETADO" << endl;
				return true;							//EL NIVEL PASA A ESTAR COMPLETO
			}
			else {
				return false;		//SI NO SIGUE ESTANDO INCOMPLETO
			}
		}
		temp = temp->siguiente;
	}
	return false;

}

void Lista::Borrar()
{

	if (inicio == nullptr) {
		cout << "La lista esta vacia" << endl;
		return;
	}

	Nodo * nodo = inicio;



	//Si es el primero de la lista
	inicio = inicio->siguiente;
	if (inicio == nullptr) {
		delete nodo;
		return;
	}
	inicio->anterior = nullptr;
	delete nodo;

}
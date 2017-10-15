#include "Lista.h"

Lista::Lista() {
	head = nullptr;
	temp = nullptr;
}

void Lista::insert(int v) {
	temp = head;
	Nodo *nuevo = new Nodo();
	nuevo->objectID = v;
	nuevo->next = nullptr;
	nuevo->prev = nullptr;

	if (head == nullptr) {
		head = nuevo;
		return;
	}
	while (temp->next != nullptr)
		temp = temp->next;
	temp->next = nuevo;
	nuevo->prev = temp;
}

int Lista::getObject(int num) {
	temp = head;

	for (int i = 0; i<9; i++) {
		if (i == num)
			return temp->objectID;
		temp = temp->next;
	}
}

bool Lista::movements(int numeroNodo) {
	temp = head;

	for (int i = 0; i < numeroNodo; i++)
		temp = temp->next;
	if (temp->objectID == 3)
		return false;
	else if (temp->objectID == 2)
		return false;
	else if (temp->objectID == 0 || temp->objectID == 4)
		return true;
}

/*-------------------------------------------------
0 is an empty space
1 is the player
2 is the box
3 is the wall
4 is the winnig point
-------------------------------------------------*/
bool Lista::movementsR(int numeroNodo) {
	temp = head;

	for (int i = 0; i < numeroNodo; i++)
		temp = temp->next;
	if (temp->next->objectID == 3)
		return false;
	else if (temp->next->objectID == 2) {
		if (temp->next->next->objectID == 3)
			return false;
		else if (temp->next->next->objectID == 2)
			return false;
		else {
			temp->objectID = 0;
			temp->next->objectID = 1;
			temp->next->next->objectID = 2;
			return true;
		}
	}
	else if (temp->next->objectID == 0) {
		temp->next->objectID = 1;
		temp->objectID = 0;
		return true;
	}
	if (temp->prev->objectID == 4 && temp->next->objectID == 4) {
		temp->next->objectID = 1;
		temp->objectID = 4;
		return true;
	}
	else if (temp->next->next->next->objectID == 4) {
		temp->next->objectID = 1;
		temp->objectID = 0;
		return true;
	}
	else {
		temp->next->objectID = 1;
		temp->objectID = 4;
		return true;
	}
}

bool Lista::movementsL(int numeroNodo) {
	temp = head;

	for (int i = 0; i < numeroNodo; i++)
		temp = temp->next;
	if (temp->prev->objectID == 3)
		return false;
	else if (temp->prev->objectID == 2) {
		if (temp->prev->prev->objectID == 3)
			return false;
		else if (temp->prev->prev->objectID == 2)
			return false;
		else {
			temp->objectID = 0;
			temp->prev->objectID = 1;
			temp->prev->prev->objectID = 2;
			return true;
		}
	}
	else if (temp->prev->objectID == 0) {
		temp->prev->objectID = 1;
		temp->objectID = 0;
		return true;
	}
	if (temp->prev->prev->objectID == 4) {
		temp->prev->objectID = 1;
		temp->objectID = 4;
		return true;
	}
	else {
		temp->prev->objectID = 1;
		temp->objectID = 4;
		return true;
	}
}

void Lista::CambiarEstado(int numeroNodo, int actualizar) {
	temp = head;

	for (int i = 0; i < numeroNodo; i++)
		temp = temp->next;
	temp->objectID = actualizar;
}

bool Lista::ganar(Lista L, int numero) {
	temp = head;

	for (int i = 1; i < 9; i++) {
		if (i == numero) {
			if (temp->objectID == 2 && temp->prev->objectID == 2 && temp->prev->prev->objectID == 2) {
				system("cls");
				cout << " Felicidades !! Has completado el nivel!" << endl;
				return true;
			}
			else
				return false;
		}
		temp = temp->next;
	}
	return false;
}

bool Lista::ganar2(Lista L, int numero) {
	temp = head;

	for (int i = 1; i < 9; i++) {
		if (i == numero) {
			if (temp->objectID == 2 && temp->prev->objectID == 2 && temp->prev->prev->prev->prev->prev->prev->objectID == 2) {
				system("cls");
				cout << " Felicidades !! Has completado el nivel!" << endl;
				return true;
			}
			else
				return false;
		}
		temp = temp->next;
	}
	return false;
}

bool Lista::ganar3(Lista L, int numero) {
	temp = head;

	for (int i = 1; i < 9; i++) {
		if (i == numero) {
			if (temp->objectID == 2 && temp->prev->prev->objectID == 2) {
				system("cls");
				cout << " Felicidades !! Has completado el nivel!" << endl;
				return true;
			}
			else
				return false;
		}
		temp = temp->next;
	}
	return false;
}
void Lista::deleteList() {
	if (head == nullptr) {
		cout << "List is empty" << endl;
		return;
	}
	Nodo * nodo = head;
	head = head->next;
	if (head == nullptr) {
		delete nodo;
		return;
	}
	head->prev = nullptr;
	delete nodo;
}
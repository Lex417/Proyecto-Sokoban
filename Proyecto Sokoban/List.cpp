#include "List.h"

List::List() {
	head = nullptr;
	temp = nullptr;
}

void List::insert(int v) {
	temp = head;
	Node *nuevo = new Node();
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

int List::getObject(int num) {
	temp = head;

	for (int i = 0; i<9; i++) {
		if (i == num)
			return temp->objectID;
		temp = temp->next;
	}
}

bool List::movements(int object) {
	temp = head;

	for (int i = 0; i < object; i++)
		temp = temp->next;
	if (temp->objectID == Wall())//3 					
		return false;
	else if (temp->objectID == Box())
		return false;
	else if (temp->objectID == EmptySpace() || temp->objectID == WinnigPoint()) //0 y 4
		return true;
}

bool List::movementsR(int object) {
	temp = head;

	for (int i = 0; i < object; i++)
		temp = temp->next;
	if (temp->next->objectID == Wall())//3	
		return false;
	else if (temp->next->objectID == Box()) {//2									
		if (temp->next->next->objectID == Box())//2
			return false;
		else if (temp->next->next->objectID == Wall())//3
			return false;
		else {
			temp->objectID = EmptySpace();//0							
			temp->next->objectID = Player();//1					
			temp->next->next->objectID = Box();//2		
			return true;
		}
	}
	else if (temp->next->objectID == EmptySpace()) {//0													
		temp->next->objectID = Player();//1						
		temp->objectID = EmptySpace();//0									
		return true;
	}
	if (temp->prev->objectID == WinnigPoint() && temp->next->objectID == WinnigPoint()) {//4 y 4															
		temp->next->objectID = Player();//1
		temp->objectID = WinnigPoint();//4
		return true;
	}
	else if (temp->next->next->next->objectID == WinnigPoint()) {//4
		temp->next->objectID = Player();//1
		temp->objectID = EmptySpace();//0
		return true;
	}
	else {
		temp->next->objectID = Player();//1
		temp->objectID = EmptySpace();//4
		return true;
	}
}

bool List::movementsL(int object) {
	temp = head;

	for (int i = 0; i < object; i++)
		temp = temp->next;
	if (temp->prev->objectID == Wall())//3
		return false;
	else if (temp->prev->objectID == Box()) {//2
		if (temp->prev->prev->objectID == Wall())//3
			return false;
		else if (temp->prev->prev->objectID == Box())//2
			return false;
		else {
			temp->objectID = EmptySpace();//0
			temp->prev->objectID = Player();//1
			temp->prev->prev->objectID = Box();//2
			return true;
		}
	}
	else if (temp->prev->objectID == EmptySpace()) {//0
		temp->prev->objectID = Player();//1
		temp->objectID = EmptySpace();//0
		return true;
	}
	if (temp->prev->prev->objectID == WinnigPoint()) {//4
		temp->prev->objectID = Player();//1
		temp->objectID = WinnigPoint();//4
		return true;
	}
	else {
		temp->prev->objectID = Player();//1
		temp->objectID = WinnigPoint();//4
		return true;
	}
}

void List::CambiarEstado(int object, int newObject) {
	temp = head;

	for (int i = 0; i < object; i++)
		temp = temp->next;
	temp->objectID = newObject;
}

bool List::ganar(List L, int object) {
	temp = head;

	for (int i = 1; i < 9; i++) {
		if (i == object) {
			if (temp->objectID == Box() && temp->prev->objectID == Box() && temp->prev->prev->objectID == Box()) {
				cout << " Congratulations! you have completed this level!" << endl;
				return true;
			}
			else
				return false;
		}
		temp = temp->next;
	}
	return false;
}

bool List::ganar2(List L, int numero) {
	temp = head;

	for (int i = 1; i < 9; i++) {
		if (i == numero) {
			if (temp->objectID == Box() && temp->prev->objectID == Box() && temp->prev->prev->prev->prev->prev->prev->objectID == Box()) {
				cout << " Congratulations! you have completed this level!" << endl;
				return true;
			}
			else
				return false;
		}
		temp = temp->next;
	}
	return false;
}

bool List::ganar3(List L, int numero) {
	temp = head;

	for (int i = 1; i < 9; i++) {
		if (i == numero) {
			if (temp->objectID == Box() && temp->prev->prev->objectID == Box()) {
				system("cls");
				cout << " Congratulations! you have completed this level!" << endl;
				return true;
			}
			else
				return false;
		}
		temp = temp->next;
	}
	return false;
}
void List::deleteList() {
	if (head == nullptr) {
		cout << "The list is empty" << endl;
		return;
	}
	Node * nodo = head;
	head = head->next;
	if (head == nullptr) {
		delete nodo;
		return;
	}
	head->prev = nullptr;
	delete nodo;
}
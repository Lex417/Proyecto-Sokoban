#include "Lista.h"

Lista::Lista() {
	first = nullptr;
	temp = nullptr;
}

void Lista::insert(int v) 
{

	temp = first;
	Nodo *nuevo = new Nodo();

	nuevo->objectID = v;
	nuevo->next = nullptr;
	nuevo->prev = nullptr;

	if (first == nullptr)
	{
		first = nuevo;

		return;
	}

	while (temp->next != nullptr) 	
		temp = temp->next;
	
	temp->next = nuevo;
	nuevo->prev = temp;


}

int Lista::getTipo(int num)
{

	temp = first;


	for (int i = 0; i<9; i++)
	{		//ME MUEVO POR LOS 9 NODOS DE LA LISTA
		if (i == num) 			//SI ALGUNA POSICION COINCIDE CON EL NUMERO ENVIADO (QUE SERIA EL NODO DE LA POSICION EN LA QUE ESTOY
			return temp->objectID;		//RETORNO EL NUMERO QUE TIENE EL NODO
		
		temp = temp->next;
	}


}

bool Lista::Movimiento(int numeroNodo)
{
	temp = first;

	for (int i = 0; i < numeroNodo; i++) 
		temp = temp->next;					//ME POSICIONO EN LA POSICION DEL NODO EN EL QUE ESTOY
	


	if (temp->objectID == 3) 					//SI EL NUMERO EN LA POSICION DEL NODO ES UN 3 (MURO)
		return false;								//NO SE PUEDE MOVER
	

	else if (temp->objectID == 2) 				//SI EL NUMERO EN LA POSICION DEL NODO ES UN 2 (CAJA)
		return false;									//NO SE PUEDE MOVER

	
	else if (temp->objectID == 0 || temp->objectID == 4) 	//SI EL NUMERO EN LA POSICION DEL NODO ES UN 0 (LIBRE) o 4(LUGAR DE GANAR)
		return true;
	

}


bool Lista::MovimientoDerecha(int numeroNodo)
{

	temp = first;

	for (int i = 0; i < numeroNodo; i++) 
		temp = temp->next;						//ME POSICIONO EN EL NODO EN EL QUE ESTOY
	

	if (temp->next->objectID == 3) 			//SI EL NUMERO DEL NODO EN EL QUE ESTOY ES UN 3 (MURO)
		return false;									//NO ME PUEDO MOVER
	

	else if (temp->next->objectID == 2)
	{													//SI EL NUMERO DEL NODO EN EL QUE ESTOY ES UN 2 (CAJA)
		if (temp->next->next->objectID == 3) 	//Y SI LA SIGUIENTE A LA DERECHA ES UN MURO
			return false;										//NO SE PUEDE MOVER
		
		else if (temp->next->next->objectID == 2) 	//Y SI LA SIGUIENTE A LA DERECHA TAMBIEN ES UNA CAJA
			return false;											//NO SE PUEDE MOVER
		
		else 
		{
			temp->objectID = 0;								//SI ES UN ESPACIO LIBRE O UN PUNTO GANAR
			temp->next->objectID = 1;					//LO SIGUIENTE A LA DERECHA ES UN JUGADOR
			temp->next->next->objectID = 2;		//LO SIGUIENTE AL JUGADOR ES LA CAJA
			return true;										// SI ME PUEDO MOVER
		}
	}
	else if (temp->next->objectID == 0)
	{														//SI LA POSICION ES LIBRE
		temp->next->objectID = 1;						// LO SIGUIENTE ES EL JUGADOR
		temp->objectID = 0;									//EN DONDE ESTOY PASA A SER UN ESPACIO LIBRE
		return true;											//SI ME PUEDO MOVER
	}



	if (temp->prev->objectID == 4 && temp->next->objectID == 4)
	{																	// SI ES UN PUNTO DE GANE
		temp->next->objectID = 1;
		temp->objectID = 4;
		return true;

	}
	else if (temp->next->next->next->objectID == 4)
	{
		temp->next->objectID = 1;
		temp->objectID = 0;
		return true;
	}
	else
	{
		temp->next->objectID = 1;
		temp->objectID = 4;
		return true;
	}

}

bool Lista::MovimientoIzquierda(int numeroNodo) 
{
	//LO MISMO DE LA DERECHA SOLO QUE SE PREGUNTA POR EL ANTERIOR
	temp = first;

	for (int i = 0; i < numeroNodo; i++) 
		temp = temp->next;
	

	if (temp->prev->objectID == 3)
		return false;
	
	else if (temp->prev->objectID == 2)
	{
		if (temp->prev->prev->objectID == 3)
			return false;
		
		else if (temp->prev->prev->objectID == 2)
			return false;
		

		else
		{
			temp->objectID = 0;
			temp->prev->objectID = 1;
			temp->prev->prev->objectID = 2;
			return true;
		}
	}
	else if (temp->prev->objectID == 0)
	{
		temp->prev->objectID = 1;
		temp->objectID = 0;
		return true;
	}




	if (temp->prev->prev->objectID == 4)
	{
		temp->prev->objectID = 1;
		temp->objectID = 4;
		return true;
	}
	else 
	{
		temp->prev->objectID = 1;
		temp->objectID = 4;
		return true;
	}


}

void Lista::CambiarEstado(int numeroNodo, int actualizar) 
{

	temp = first;

	for (int i = 0; i < numeroNodo; i++) 
		temp = temp->next;					//ME POSICIONO EN EL NODO EN EL QUE ESTOY
	

	temp->objectID = actualizar;				//SE ACTUALIZA EL NUMERO DEL NODO EN EL QUE ESTOY

}

bool Lista::ganar(Lista L, int numero) 
{

	temp = first;

	for (int i = 1; i < 9; i++) {			//VOY RECCORIENDO LOS NODOS
		if (i == numero) 
		{
			if (temp->objectID == 2 && temp->prev->objectID == 2 && temp->prev->prev->objectID == 2  )
			{														//SI EL PUNTO DE GANAR TIENE UN 2(CAJA) Y EL ANTERIOR TAMBIEN, Y EL ANTERIOR DEL ANTERIOR TAMBIEN ES UN 2
				cout << " Felicidades !! Has completado el nivel!" << endl;	
				return true;							//EL NIVEL PASA A ESTAR COMPLETO
			}
			else if (temp->objectID == 2 && temp->prev->prev->objectID == 2)
			{
				cout << " Felicidades !! Has completado el nivel!" << endl;
				return true;
			}

			else 
				return false;		//SI NO SIGUE ESTANDO INCOMPLETO
			
		}
		temp = temp->next;
	}
	return false;

}

bool Lista::ganar2(Lista L, int numero) 
{


	temp = first;

	for (int i = 1; i < 9; i++) 
	{			//VOY RECCORIENDO LOS NODOS
		if (i == numero) 
		{
			if (temp->objectID == 2 && temp->prev->objectID == 2 && temp->prev->prev->prev->prev->prev->prev->objectID == 2)
			{
				cout << " Felicidades !! Has completado el nivel!" << endl;
				return true;
			}											//EL NIVEL PASA A ESTAR COMPLETO
		
			else 
				return false;		//SI NO SIGUE ESTANDO INCOMPLETO
			
		}
		temp = temp->next;
	}
	return false;

}		
void Lista::Borrar()
{

	if (first == nullptr)
	{
		cout << "La lista esta vacia" << endl;
		return;
	}

	Nodo * nodo = first;



	//Si es el primero de la lista
	first = first->next;
	if (first == nullptr)
	{

		delete nodo;
		return;
	}
	first->prev = nullptr;
	delete nodo;

}
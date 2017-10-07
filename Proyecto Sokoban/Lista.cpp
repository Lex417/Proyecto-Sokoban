#include "Lista.h"

Lista::Lista() {
	inicio = nullptr;
	temp = nullptr;
}

void Lista::insertar(int v) 
{

	temp = inicio;
	Nodo *nuevo = new Nodo();

	nuevo->tipoPosicion = v;
	nuevo->next = nullptr;
	nuevo->prev = nullptr;

	if (inicio == nullptr)
	{
		inicio = nuevo;

		return;
	}

	while (temp->next != nullptr) 	
		temp = temp->next;
	
	temp->next = nuevo;
	nuevo->prev = temp;


}

int Lista::getTipo(int num)
{

	temp = inicio;


	for (int i = 0; i<9; i++)
	{		//ME MUEVO POR LOS 9 NODOS DE LA LISTA
		if (i == num) 			//SI ALGUNA POSICION COINCIDE CON EL NUMERO ENVIADO (QUE SERIA EL NODO DE LA POSICION EN LA QUE ESTOY
			return temp->tipoPosicion;		//RETORNO EL NUMERO QUE TIENE EL NODO
		
		temp = temp->next;
	}


}

bool Lista::Movimiento(int numeroNodo)
{
	temp = inicio;

	for (int i = 0; i < numeroNodo; i++) 
		temp = temp->next;					//ME POSICIONO EN LA POSICION DEL NODO EN EL QUE ESTOY
	


	if (temp->tipoPosicion == 3) 					//SI EL NUMERO EN LA POSICION DEL NODO ES UN 3 (MURO)
		return false;								//NO SE PUEDE MOVER
	

	else if (temp->tipoPosicion == 2) 				//SI EL NUMERO EN LA POSICION DEL NODO ES UN 2 (CAJA)
		return false;									//NO SE PUEDE MOVER

	
	else if (temp->tipoPosicion == 0 || temp->tipoPosicion == 4) 	//SI EL NUMERO EN LA POSICION DEL NODO ES UN 0 (LIBRE) o 4(LUGAR DE GANAR)
		return true;
	

}


bool Lista::MovimientoDerecha(int numeroNodo)
{

	temp = inicio;

	for (int i = 0; i < numeroNodo; i++) 
		temp = temp->next;						//ME POSICIONO EN EL NODO EN EL QUE ESTOY
	

	if (temp->next->tipoPosicion == 3) 			//SI EL NUMERO DEL NODO EN EL QUE ESTOY ES UN 3 (MURO)
		return false;									//NO ME PUEDO MOVER
	

	else if (temp->next->tipoPosicion == 2)
	{													//SI EL NUMERO DEL NODO EN EL QUE ESTOY ES UN 2 (CAJA)
		if (temp->next->next->tipoPosicion == 3) 	//Y SI LA SIGUIENTE A LA DERECHA ES UN MURO
			return false;										//NO SE PUEDE MOVER
		
		else if (temp->next->next->tipoPosicion == 2) 	//Y SI LA SIGUIENTE A LA DERECHA TAMBIEN ES UNA CAJA
			return false;											//NO SE PUEDE MOVER
		
		else 
		{
			temp->tipoPosicion = 0;								//SI ES UN ESPACIO LIBRE O UN PUNTO GANAR
			temp->next->tipoPosicion = 1;					//LO SIGUIENTE A LA DERECHA ES UN JUGADOR
			temp->next->next->tipoPosicion = 2;		//LO SIGUIENTE AL JUGADOR ES LA CAJA
			return true;										// SI ME PUEDO MOVER
		}
	}
	else if (temp->next->tipoPosicion == 0) 
	{														//SI LA POSICION ES LIBRE
		temp->next->tipoPosicion = 1;						// LO SIGUIENTE ES EL JUGADOR
		temp->tipoPosicion = 0;									//EN DONDE ESTOY PASA A SER UN ESPACIO LIBRE
		return true;											//SI ME PUEDO MOVER
	}



	if (temp->prev->tipoPosicion == 4 && temp->next->tipoPosicion == 4) 
	{																	// SI ES UN PUNTO DE GANE
		temp->next->tipoPosicion = 1;
		temp->tipoPosicion = 4;
		return true;

	}
	else if (temp->next->next->next->tipoPosicion == 4)
	{
		temp->next->tipoPosicion = 1;
		temp->tipoPosicion = 0;
		return true;
	}
	else
	{
		temp->next->tipoPosicion = 1;
		temp->tipoPosicion = 4;
		return true;
	}

}

bool Lista::MovimientoIzquierda(int numeroNodo) 
{
	//LO MISMO DE LA DERECHA SOLO QUE SE PREGUNTA POR EL ANTERIOR
	temp = inicio;

	for (int i = 0; i < numeroNodo; i++) 
		temp = temp->next;
	

	if (temp->prev->tipoPosicion == 3) 
		return false;
	
	else if (temp->prev->tipoPosicion == 2) 
	{
		if (temp->prev->prev->tipoPosicion == 3) 
			return false;
		
		else if (temp->prev->prev->tipoPosicion == 2) 
			return false;
		

		else
		{
			temp->tipoPosicion = 0;
			temp->prev->tipoPosicion = 1;
			temp->prev->prev->tipoPosicion = 2;
			return true;
		}
	}
	else if (temp->prev->tipoPosicion == 0) 
	{
		temp->prev->tipoPosicion = 1;
		temp->tipoPosicion = 0;
		return true;
	}




	if (temp->prev->prev->tipoPosicion == 4) 
	{
		temp->prev->tipoPosicion = 1;
		temp->tipoPosicion = 4;
		return true;
	}
	else 
	{
		temp->prev->tipoPosicion = 1;
		temp->tipoPosicion = 4;
		return true;
	}


}

void Lista::CambiarEstado(int numeroNodo, int actualizar) 
{

	temp = inicio;

	for (int i = 0; i < numeroNodo; i++) 
		temp = temp->next;					//ME POSICIONO EN EL NODO EN EL QUE ESTOY
	

	temp->tipoPosicion = actualizar;				//SE ACTUALIZA EL NUMERO DEL NODO EN EL QUE ESTOY

}

bool Lista::ganar(Lista L, int numero) 
{

	temp = inicio;

	for (int i = 1; i < 9; i++) {			//VOY RECCORIENDO LOS NODOS
		if (i == numero) 
		{
			if (temp->tipoPosicion == 2 && temp->prev->tipoPosicion == 2 && temp->prev->prev->tipoPosicion == 2  ) 
			{														//SI EL PUNTO DE GANAR TIENE UN 2(CAJA) Y EL ANTERIOR TAMBIEN, Y EL ANTERIOR DEL ANTERIOR TAMBIEN ES UN 2
				cout << "'Has completado el nivel!" << endl;	
				return true;							//EL NIVEL PASA A ESTAR COMPLETO
			}
			else if (temp->tipoPosicion == 2 && temp->prev->prev->tipoPosicion == 2)
			{
				cout << "Has completado el nivel!" << endl;
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


	temp = inicio;

	for (int i = 1; i < 9; i++) 
	{			//VOY RECCORIENDO LOS NODOS
		if (i == numero) 
		{
			if (temp->tipoPosicion == 2 && temp->prev->tipoPosicion == 2 && temp->prev->prev->prev->prev->prev->prev->tipoPosicion == 2)
			{
				cout << "Has completado el nivel!" << endl;
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

	if (inicio == nullptr) 
	{
		cout << "La lista esta vacia" << endl;
		return;
	}

	Nodo * nodo = inicio;



	//Si es el primero de la lista
	inicio = inicio->next;
	if (inicio == nullptr) 
	{

		delete nodo;
		return;
	}
	inicio->prev = nullptr;
	delete nodo;

}
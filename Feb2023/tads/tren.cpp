/*
 * TAD TREN
 * Tads implicados:
 * PILA:
 * Tipo abstracto de datos usado para representar una secuencia de elementos ordenados mediante una estructura LIFO.
 * Al desconocerse el número máximo de trenes a almacenar, vamos a utilizar la representación enlazada.
 * Especificación de la estructura de datos utilizada:
 *
 * template <class t>
 * class PilaEnla<T> 
 * {
 * 	...
 * 	private:
 * 		struct nodo		
 *		{
 *			nodo* sig;
 *			t elto;
 *			nodo(nodo* s, T e = 0): sig(s), elto(e){}
 *		}
 *		nodo* tope_;
 * }
 *
 * Especificación de las operaciones utilizadas => insertar operaciones de la clase implicada
 *
 * Especificación del TAD tren:
 *
 * Resumen:
 * Se nos pide representar una serie de vagones de un tren, los cuales se podrán desplazar de múltiples maneras mediante un robot que se encargará de esta tarea.
 *
 * Especificaciones de las operaciones => insertar operaciones del nuevo tad. 
 */

#include <iostream>
#include <string>
#include "../clasicos/PilaEnla.h"
typedef string Wagon;

class Tren
{
	private:
		int elementsInsideStack(PilaEnla<Wagon> st); //number of elements in the stack.
		{
			int i = 0;
			while (!st.vacia())
			{
				st.pop();
				++i;
			}
			return i;
		}
		PilaEnla<Wagon> stRight, stLeft;

	public:
		Tren() = default;	//not necessary
		~Tren() = default;
		void moveRight();
		void moveLeft();
		void deleteActiveWagon();
		void addActiveWagon(const Wagon& w);
		const Wagon &activeWagon();
		const bool &isEmpty();
};

int main() { return 0; }

void moveRight()
{
	if(!stLeft.vacia())
	{
		const Wagon wTemp = stLeft.tope();
		stLeft.pop();

		if (stLeft.vacia())
			stLeft.push(wTemp);
		else
			stRight.push(wTemp);
	}
}
void moveLeft()
{
	if(!stRight.vacia())
	{
		const Wagon wTemp = stRight.tope();
		stRight.pop();

		if (stRight.vacia())
			stRight.push(wTemp);
		else
			stLeft.push(wTemp);
	}

void Tren::deleteActiveWagon()
{
	if (isEmpty() && stLeft.vacia()) //no vagon activo
		std::throw runtime_error("El tren está vacío y no puede eliminar el vagón activo");

	if (stLeft.vacia() || elementsInsideStack(stRight) >= 2)
		stRight.pop();
	else
	{
		stRight.pop();
		const Wagon wTemp = stLeft.tope();
		stLeft.pop();
		stRight.push(wTemp);
	}
}

void Tren::addActiveWagon(const Wagon& w) { stRight.push(w); }
const Wagon& Tren::activeWagon() { return stRight.tope(); }
const bool& Tren::isEmpty() { return !(stRight.vacia()); }

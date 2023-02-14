/*
 * Una empresa ha robotizado su almacén.
 * Para ello, lo ha dividido en 60 estantes de tres tamaños diferentes.
 * (pequeño, mediano y grande) a partes iguales.
 * A cada estante se le asigna un elemento según su tamaño (en cada estante solo hay elementos de un tipo,
 * pero puede haber hasta 50 elementos del mismo tipo).
 *
 * Se pide diseñar un TAD para el funcionamiento del robot que incluya las siguientes operaciones:
 *
 * 1. Crear un almacén vacío.
 * 2. Insertar un elemento en un estante. Si ya hay un estante asignado, y el elemento cabe, se coloca en ese. Si no es así,
 * se busca otro estante del mismo tamaño. (si no hay devuelve false, else true).
 * 3. Comprobar si hay elementos de un tipo determinado.
 * 4. Sacar un elemento de un tipo dado.
 * 5. Vaciar el almacén (destructor del TAD).
 */

#include <iostream>
#include <string>
#include "../clasicos/ListaEnla.h"

typedef struct Objeto
{
	char cSizeEstante;
	int iId;
	Objeto(char estante = '#', int id = 0) : cSizeEstante(estante), iId(id) {}
	bool operator ==(const Objeto& o) { return iId == o.iId; }
};

typedef struct Estante
{
	const int iCapacidad = 50;
	int iOcupados;
	char cType;
	bool lleno() { return iOcupados == 50; }
	void addObj(const Objeto& o)
	{
		if (!lleno() && o.cSizeEstante == cType)
		{
			objetos.insertar(o, objetos.fin());
			iOcupados++;
		}
	}

	int iId;
	ListaEnla<Objeto> objetos;
	Estante(int id = 0, char type = '#') : iId(id), iOcupados(0) {}
};

class Almacen
{
	public:
		Almacen();
		bool addObject(const Objeto& o);
		void popObject(const Objeto& o, const char& type);
		bool existeTipo(const char& type);

	private:
		ListaEnla<Estante> lEstantes;
}

int main() { return 0; }

Almacen::Almacen()
{
	auto pos = lEstantes.fin();
	for (int i = 0; i < 60; ++i)
	{
		if (i < 20)
			lEstantes.insertar(Estante(i + 1, 's'), pos);
		else if (i >= 20 && i < 40)
			lEstantes.insertar(Estante(i + 1, 'm'), pos);
		else if (i >= 40)
			lEstantes.insertar(Estante(i + 1, 'l'), pos);
	}
}

bool Almacen::addObject(const Objeto& o)
{
	if (o.cSizeEstante == '#')
		throw std::invalid_argument("El tamaño del objeto no ha sido añadido.");

	bool bNocabe = false;

	//Busqueda de la posicion del nuevo objeto
	auto pEstante = lEstantes.primera();
	for (; pEstante != lEstantes.fin() && bNocabe; pEstante = lEstantes.siguiente(pEstante))
	{
		if (!lEstantes.elemento(pEstante).lleno() && lEstantes.elemento(pEstante).cType == o.cSizeEstante)
			bNocabe == true;
	}

	//Hay hueco para insertar
	if (bNocabe == false)
		lEstantes.elemento(pEstante).addObj(o);

	return bNocabe;
}

void Almacen::popObj(const Objeto& o, const char &type)
{
	bool erased = false;
	for (auto pEstantes = lEstantes.primera(); lEstantes.fin() && !bErased; pEstantes.siguiente(pEstantes))
	{
		if (lEstantes.elemento(pEstantes).cType == type)
		{
			auto pObjects = lEstantes.elemento(pEstantes).objetos.buscar(o);
			if (pObjects != lEstantes.elemento(pEstantes).objetos.fin());
			{
				lEstantes.elemento(pEstantes).objetos.eliminar(o);
				lEstantes.elemento(pEstantes).iOcupados--;
			}
		}
	}
}

bool Almacen::existeTipo(const char& type)
{
	if (type != 's' && type != 'm' && type != 'l')
		throw std::invalid_argument("No existe ese tipo de Objeto. Los tipos existentes son: s(small), m(medium) y l(large).");

	bool bExists = false;

	auto p = lEstantes.primera();
	while(!bExists && p != lEstantes.fin())
	{
		if (lEstantes.elemento(p).iOcupados > 0)
			bExists = true;

		p = lEstantes.siguiente(p);
	}
	return bExists;
}

#include <iostream>
#include "../clasicos/ListaEnla.h"
#include <string>

typedef struct Traduccion
{
	string strWord;
	ListaEnla<string> lPalabras;
	Traduccion(const string s = "") : strWord(s) {}
	ListaEnla<string>::Posicion BuscarPalabras(const string& s)
	{
		auto pos = lPalabras.primera();
		while (pos != lPalabras.fin() && lPalabras.elemento(pos) != s)
			pos = lPalabras.siguiente(pos);

		return pos;
	}
};

class Diccionario
{
	public:
		void insertarTraduccion (const string& strWord, const string &strPalabra);
		void eliminarTraduccionEsp (const string& strEng, const string& strEsp);
		void mostrarTraduccionAlEsp (const string& strEng);

	private:
		ListaEnla<Traduccion> lTraducciones;
		ListaEnla<Traduccion>::posicion BuscarTraduccion(const string& strSearchedWord)
		{
			auto pos = lTraducciones.primera();
			while (pos != lTraducciones.fin() && lTraducciones.elemento(pos) != strSearchedWord)
				pos = lTraducciones.siguiente(pos);

			return pos;
		}
};

int main() { return 0; }

void Diccionario::insertarTraduccion (const string& strWord, const string &strPalabra)
{
	auto pos = BuscarTraduccion(strWord);
	if (pos != lTraducciones.fin())
		lTraducciones.elemento(pos).lPalabras.insertar(strPalabra, lTraducciones.elemento(pos).lPalabra.fin());
	else
	{
		Traduccion t(strWord);
		t.lPalabras.insertar(strPalabra, t.lPalabras,fin());
		lTraducciones.insertar(t, lTraducciones.fin());
	}
}

void Diccionario::eliminarTraduccionEsp (const string& strEng, const string& strEsp)
{
	auto posTraduccionEng = BuscarTraduccion(strEng);
	if (posTraduccionEng == lTraducciones.fin())
		throw std::invalid_argument("Esa palabra no está recogida en el diccionario Inglés.")
	
	for (auto i = lTraducciones.elemento(posTraduccionEng).lPalabras.primera());
		i != lTraducciones.elemento(posTraduccionEng).lPalabras.fin();
		i = lTraducciones.elemento(posTraduccionEng).lPalabras.siguiente(i);
	{
		std::cout << lTraducciones.elemento(posTraduccionEng).lPalabras.elemento(i) << ", ";
	}
	std::cout << std::endl;
}


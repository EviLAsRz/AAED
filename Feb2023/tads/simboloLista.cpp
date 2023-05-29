#include <iostream>
#include "../clasicos.ListaEnla.h"

class Symbol
{
	public:
		Symbol() : iNumberOfTraces(0);
		void addTrace(const char cTrace);
		void eraseTrace(const int iNtraces);
		void rotateSymbolX();
		void rotateSymbolY();
		void rotateSymbolXY();

	private:
		ListaEnla<char> lTraces;
		int iNumbersOfTraces;
};

int main() { return 0; }

void Symbol::addTrace(const char cTrace)
{
	if (cTrace != 'I' || cTrace != 'D' || cTrace != 'B' || cTrace != 'S')
		throw std::invalid_argument("Invalid trace");

	iNumberOfTraces++;
	lTraces.insertar(cTrace, lTraces.fin());
}

void Symbol::eraseTrace(const int iNtraces)
{
	if (iNtraces > iNumberOfTraces || iNtraces < 0)
		throw std::invalid_argument("Can´t delete. Invalid number of traces.");

	auto p = lTraces.anterior(lTraces.fin());
	while(iNtraces > 0)
	{
		iNtraces--;
		lTraces.eliminar(lTraces.anterior(lTraces.fin()));
	}
	iNumberOfTraces -= iNtraces;
}

void Symbol::rotateSymbolX()
{
	if (iNumberOfTraces == 0)
		throw std::runtime_error("There is no trace to rotate");

	for (auto p = lTraces.primera(); p != lTraces.fin(); lTraces.siguiente(p))
	{
		if (lTraces.elemento(p) == 'A')
			lTraces.elemento(p) = 'B';
		else if (lTraces.elemento(p) == 'B')
			lTraces.elemento(p) = 'A';
	}
}
void Symbol::rotateSymbolY()
{
	if (iNumberOfTraces == 0)
		throw std::runtime_error("There is no trace to rotate");

	for (auto p = lTraces.primera(); p != lTraces.fin(); lTraces.siguiente(p))
	{
		if (lTraces.elemento(p) == 'I')
			lTraces.elemento(p) = 'D';
		else if (lTraces.elemento(p) == 'D')
			lTraces.elemento(p) = 'I';
	}
}

void Symbol::rotateSymbolXY()
{
	rotateSymbolX();
	rotateSymbolY();
}

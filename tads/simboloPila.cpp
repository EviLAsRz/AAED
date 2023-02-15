#include <iostream>
#include "../clasicos/PilaEnla.h"

class Symbol
{
	public:
		Symbol() : iNumberOfTraces(0) {}
		void addTrace(const char cTrace);
		void eraseTrace(const int iNtraces);
		void rotateSymbolX();
		void rotateSymbolY();
		void rotateSymbolXY();

	private:
		PilaEnla<char> stTraces;
		int iNumberOfTraces;
};

int main() { return 0; }

void Symbol::addTrace(const char cTrace)
{
	if (cTrace != 'A' || cTrace != 'D' || cTrace != 'B' ||cTrace != 'S')
		throw std::invalid_argument("Invalid trace, must be A, D, B or S.")

	iNumberOfTraces++;
	stTraces.push(cTrace);
}

void Symbol::eraseTrace(const int iNtraces)
{
	if (iNtraces > iNumberOfTraces || iNtraces < 0)
		throw std::invalid_argument("Invalid number of traces.");
	
	while (iNtraces > 0)
	{
		stTraces.pop(); //erase the same value as Ntraces. (10 = 10 pops)
		iNtraces--;
	}
	iNumberOfTraces -= iNtraces;
}

void Symbol::rotateSymbolX()
{
	if (iNumberOfTraces == 0)
		throw std::runtime_error("This trace can not be rotated. Size = 0");

	PilaEnla<char> stTracesAux;
	while (stTraces != vacia())
	{
		if (stTraces.tope() == 'A')
			stTracesAux.push('B');
		else if (stTraces.tope() == 'B')
			stTracesAux.push('A');
	}
	stTraces = stTracesAux;
}
void Symbol::rotateSymbolY()
{
	if (iNumberOfTraces == 0)
		throw std::runtime_error("This trace can not be rotated. Size = 0");

	PilaEnla<char> stTracesAux;
	while (stTraces != vacia())
	{
		if (stTraces.tope() == 'I')
			stTracesAux.push('D');
		else if (stTraces.tope() == 'D')
			stTracesAux.push('I');
	}
	stTraces = stTracesAux;
}

void Symbol::rotateSymbolXY()
{
	rotateSymbolX();
	rotateSymbolY();
}

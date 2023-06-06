#include <iostream>
#include "../tads/Lista_Enla.h"
/*
    Trazo es un tipo caracter
    Simbolo pueden ser 4: A, B ,I , D.
    Simetría -> inverso del caracter actual.
*/
typedef char Trazo;

class Simbolo
{
    private:
        ListaEnla<Trazo> lTrazos;

    public:
        Simbolo();
        void addSimbolo(const char& cTrazo);
        void simetriaX();
        void simetriaY();
        void simetriaXY();
};

void Simbolo::addSimbolo(const char& cTrazo)
{
    if (cTrazo != 'I' && cTrazo != 'D' && cTrazo != 'A' && cTrazo != 'B')
        throw std::invalid_argument("ERROR: El caracter del trazo no es correcto.");
    
    lTrazos.insertar(cTrazo, lTrazos.fin());
}

void Simbolo::simetriaX()
{
    ListaEnla<Trazo>::posicion pos = lTrazos.primera();
    for(; pos != lTrazos.fin(); pos = lTrazos.siguiente(pos))
    {
        switch(lTrazos.elemento(pos))
        {
            case 'B':
                lTrazos.elemento(pos) = 'A';
                break;
            case 'A':
                lTrazos.elemento(pos) = 'B';
                break;
        }
    }
}

void Simbolo::simetriaY()
{
    ListaEnla<Trazo>::posicion pos = lTrazos.primera();
    for(; pos != lTrazos.fin(); pos = lTrazos.siguiente(pos))
    {
        switch(lTrazos.elemento(pos))
        {
            case 'I':
                lTrazos.elemento(pos) = 'D';
                break;
            case 'D':
                lTrazos.elemento(pos) = 'I';
                break;
        }
    }
}

void Simbolo::simetriaXY()
{
    simetriaX();
    simetriaY();
}

int main()
{
    return 0;
}
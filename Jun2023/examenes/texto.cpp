#include <iostream>
#include <string>
#include "../tads/Lista_Enla.h"

struct Palabra
{
    int iCortada;
    bool bCortadaInicio;    //Se muestra la parte inicial de la palabra.
    bool bCortadaFinal;     //Se muestra la parte final de la palabra. 
    std::string sPalabra;   //Palabra tipo string.
    bool operator ==(const Palabra& p);
    friend std::ostream& operator <<(std::ostream& os, const Palabra& p);
    Palabra(const std::string& str = "",const int& cortada = -1,
        const bool& cortadaInicio = false, const bool& cortadaFinal = false);
};

struct Linea
{
    ListaEnla<Palabra> lPalabras;
};

bool Palabra::operator ==(const Palabra& p)
{
    return sPalabra == p.sPalabra;
}

std::ostream& operator <<(std::ostream& os, const Palabra& p)
{
    if(p.iCortada != -1 && p.bCortadaInicio)
    {
        for(int i = 0; i < p.iCortada; i++)
            os << p.sPalabra[i];
        
        os << '-';
    }
    else if (p.iCortada != -1 && p.bCortadaFinal)
    {
        for(int i = p.iCortada; i < p.sPalabra.size(); i++)
            os << p.sPalabra[i];
    }
    else    //no hay corte
    {
        os << p.sPalabra;
    }
    return os;
}

void occurrenciasPalabra(const ListaEnla<Linea>& lTexto, Palabra ocurrencia, Palabra sustitucion)
{
    
}
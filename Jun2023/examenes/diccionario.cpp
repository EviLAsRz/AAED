#include <iostream>
#include <string>
#include "../tads/Lista_Enla.h"

//   Crear un diccionario de traduccion de palabras de ingles a espannol
//   cada palabra inglesa tendrá 1 o más traduciones al espannol
//   forma mas eficiente posible (ordenar alfabéticamente)
//   funciones :
//   - crear diccionario vacio
//   - insertar una traduccion de espannol de una palabra en inglés
//   - consultar si es correcta la traducion en espannol de una palabra en ingles
//   - consultar todas las traduccines del espannol de una palabra en ingles
//   - eliminar una traduccion en espannol de una palabra en ingles
//   - eliminar diccionario

struct PalabraInglesa
{
    ListaEnla<std::string> lsPalabrasEsp;
    std::string sPalabraIng;
    PalabraInglesa(const std::string& str);
    bool operator !=(const std::string& str);
};

class Diccionario
{
    private:
        ListaEnla<PalabraInglesa> lTraducciones;
        ListaEnla<PalabraInglesa>::posicion BuscarPalabra(const std::string& str);

    public:
        Diccionario();
        void insertarTraduccion(const std::string& sInglesa, const std::string& sEsp);
        bool traduccionCorrecta(const std::string& sPing, const std::string& sEsp);
        void eliminarTraduccionEsp(const std::string& sPing, const std::string& sEsp);
        void eliminarTodas(const std::string& sPing, const std::string& sEsp);
};

PalabraInglesa::PalabraInglesa(const std::string& str) : 
    sPalabraIng(str), lsPalabrasEsp(ListaEnla<std::string>()) 
{
    if (str == "")
        throw std::invalid_argument("ERROR: La palabra inglesa está vacía.");
}

bool PalabraInglesa::operator!= (const std::string& str) { return str != sPalabraIng; }

ListaEnla<PalabraInglesa>::posicion Diccionario::BuscarPalabra(const std::string& str)
{
    /*
    SE PUEDE HACER CON UN FOR TAMBIEN.
    Desde primera, mientras que pos no sea fin y que la palabra no coincida, loopeamos (pos apunta a siguiente).
    Se devuelve pos.
    */
    auto pos = lTraducciones.primera();
    while (pos != lTraducciones.fin() && lTraducciones.elemento(pos).sPalabraIng != str)
        pos = lTraducciones.siguiente(pos);
    
    return pos;
}

void Diccionario::insertarTraduccion(const std::string &sInglesa, const std::string &sEsp)
{
    if (sInglesa == "" || sEsp == "")
        throw std::invalid_argument("ERROR: Las cadenas no pueden estar vacías.");
    
    auto pos = BuscarPalabra(sInglesa);
    if (pos == lTraducciones.fin()) //no existe la palabra, la creamos
    {
        PalabraInglesa trad(sInglesa);
        trad.lsPalabrasEsp.insertar(sEsp, trad.lsPalabrasEsp.fin());
        lTraducciones.insertar(trad, lTraducciones.fin());
    }
    else    //existe la palabra
    {
        auto posTr = lTraducciones.elemento(pos).lsPalabrasEsp.primera();
        while(posTr != lTraducciones.elemento(pos).lsPalabrasEsp.primera()
        && sEsp != lTraducciones.elemento(pos).lsPalabrasEsp.elemento(posTr))
            posTr = lTraducciones.elemento(pos).lsPalabrasEsp.siguiente(posTr);
        
        if (posTr == lTraducciones.elemento(pos).lsPalabrasEsp.fin())
            lTraducciones.elemento(pos).lsPalabrasEsp.insertar(sEsp, posTr);
    }
}

bool Diccionario::traduccionCorrecta(const std::string& sPing, const std::string& sEsp)
{
    auto posIng = BuscarPalabra(sPing);
    if(posIng == lTraducciones.fin())
    {
        throw std::invalid_argument("ERROR: La palabra inglesa no existe.");
    }

    auto posTr = lTraducciones.elemento(posIng).lsPalabrasEsp.primera();
    while(posTr != lTraducciones.elemento(posIng).lsPalabrasEsp.fin())
        posTr = lTraducciones.elemento(posIng).lsPalabrasEsp.siguiente(posTr);
    
    if (posTr == lTraducciones.elemento(posIng).lsPalabrasEsp.fin())
        return false;
    else
        return true;
}


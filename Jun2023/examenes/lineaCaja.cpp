#include <iostream>
#include <string>
#include "../tads/lista_vec.h"

/*
    50 cajas numeradas del 1 al 50.
    Siempre debe haber entre 10 y 50 en movimiento.
    Dos turnos de trabajo.
*/

typedef std::string Cajero;
struct Caja
{
    int iIdentificador; //id caja
    Cajero cajeroActual;    //cajero actual
    double dFacturacion;    //facturacion de la caja
    bool bActiva;   //esActivo
    char cTurno;    //turno
    Caja(const int &id = 0) : //ctor de caja, con id = 0 y param default
        iIdentificador(id), cajeroActual(""), dFacturacion(0), bActiva(false) {}
    
    bool operator ==(const int& idCaja) { return idCaja == iIdentificador; } //operator ==
};

class LineaCajas
{
    private:
        ListaVec<Caja> lCajas;  //lista de cajas
    
    public:
        LineaCajas(const int iMaxCajas);    //ctor
        void abrirCaja(const int& idCaja); //abrir una caja
        const double cerrarCaja(const int& idCaja); //cerrar una caja
        void cobrarClienteCaja(const int& idCaja, const double& dCobro);    //cobrar cliente en caja
        void sustituirCajero(const int& idCaja, const std::string& sCajero); //sustituir cajero
        double cambiarTurno(char turno); //cambiar turno
        double cerrarCajas();   //cerrar todas las cajas
};

LineaCajas::LineaCajas(const int iMaxCajas) : lCajas(ListaVec<Caja>(50))
{
    /*
    Consideraciones:
    1-. Pasamos el numero maximo de cajas y se la pasamos a la lista de cajas
        (creamos una listaVec<Caja>(50)).
    2-. Con un bucle, rellenamos las cajas, desde i + 1 hasta fin.
    */
    for(int i = 0; i < iMaxCajas; ++i)
        lCajas.insertar(Caja(i + 1), lCajas.fin());
}

void LineaCajas::abrirCaja(const int& idCaja)
{
/*
Consideraciones:
*/
    if (idCaja < 1 || idCaja > 50)
        throw std::invalid_argument("El id de Caja debe estar entre el 1 y el 50");
    
    ListaVec<Caja>::posicion pos = idCaja - 1; //id va de 1-50 aunque realmente es 0-49.
    lCajas.elemento(pos).bActiva = true;    //true
}


#include <iostream>
#include "../tads/pila_Enla.h"
/*
Se tiene un TAD Tren con una secuencia de elementos tipo vagón. Si el tren no está vacío entonces
hay un vagón activo que puede ser manipulado por un robot. Hacer la especificación de las
siguientes operaciones:
a. Construir un tren vacío.
b. Desplazar tren a la izquierda (el vagón activo pasa a ser el de la derecha, si no hay vagón a la
    derecha no se hace nada).
c. Desplazar tren a la derecha (el vagón activo pasa a ser el de la izquierda, si no hay vagón a la
    izquierda no se hace nada).
d. Eliminar vagón activo: El vagón activo pasa a ser el de la derecha, si no hay vagón a la
    derecha, pasa a ser el de la izquierda, si tampoco hay, el tren está vacío.
e. Observar vagón activo: Devuelve cuál es el vagón activo.
f. Comprobar si el tren está vacío
*/

typedef int Vagon; //para código mas explicativo, no es necesario

class Tren
{
    private:
        PilaEnla<Vagon> PilaIzq, PilaDer;   //vagones representados por dos pilas

    public:
        Tren(); //ctor
        void insertarVagon(const int& iVagon);  //insertar vagon
        void desplazarTrenIzq();    //desplazar a la izquierda
        void desplazarTrenDer();    //desplazar a la derecha
        void eliminarVagonActivo(); //eliminar vagon activo
        Vagon vagonActivo() const;  //observador de vagon activo
        bool trenVacio();   //si tren es vacio
};

void Tren::insertarVagon(const int& iVagon) { PilaDer.push(Vagon(iVagon)); }

void Tren::desplazarTrenIzq()
{
    /*
    Para desplazar tren a la izq tres consideraciones:
    1-. PilaDerecha vacia -> no se hace nada.
    2-. PilaDerecha no vacia pero solo un vagon -> no se hace nada.
    3-. PilaDerecha no vacia con nº vagones > 1 -> se desplaza.
    */
    if (!PilaDer.vacia())
    {
        Vagon v = PilaDer.tope();
        PilaDer.pop();

        if (PilaDer.vacia())
            PilaDer.push(v);
        else
            PilaIzq.push(v);
    }
}

void Tren::desplazarTrenDer()
{
    /*
    Para desplazar tren a la derecha tres consideraciones:
    1-. PilaIzq vacía -> no se hace nada.
    2-. PilaIzq no vacía pero con un solo vagon -> no se hace nada.
    3-. PilaIzq no vacía con nº vagones > 1 -> se desplaza.
    */
    if (!PilaIzq.vacia())
    {
        Vagon v = PilaIzq.tope();
        PilaIzq.pop();

        if (PilaIzq.vacia())
            PilaIzq.push(v);
        else
            PilaDer.push(v);
    }
}

void Tren::eliminarVagonActivo()
{
    /*
    Consideraciones:
    1-. Si no hay vagon tanto en izq como en derecha, no se hace nada (lanzar una excepción).
    2-. Si al eliminar el vagon activo la pila derecha queda vacía, vagon activo pasa a ser izq.
    3-. Si al eliminar el vagon activo la pila derecha no está vacia, vagon activo pasa a ser der.
    */
    if (PilaDer.vacia() && PilaIzq.vacia())
        throw std::runtime_error("No es posible eliminar el vagon activo: Tren vacio.");
    
    PilaDer.pop();  //eliminamos vagon activo.
    if (PilaDer.vacia())
    {
        if (!PilaIzq.vacia())
        {
            PilaDer.push(PilaIzq.tope());   //push hacia la pilaDer del tope de pilaIzq
            PilaIzq.pop();                  //pop pilaIzq
        }
    }
}

Vagon Tren::vagonActivo() const
{
/*
    Consideraciones:
    1-. Si la pilaDer está vacía, entonces no hay vagon activo.
    2-. Si la PilaDer no está vacía, entonces el vagon activo es el tope de la PilaDer.
*/
    if (PilaDer.vacia())
        throw std::runtime_error("Tren vacio: No hay vagón activo.");
    
    return PilaDer.tope();
}

bool Tren::trenVacio() { return !PilaDer.vacia(); }

int main()
{
    return 0;   //para que deje ejecutar el archivo.
}
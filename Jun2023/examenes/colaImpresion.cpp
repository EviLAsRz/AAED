#include <iostream>
#include <string>
#include "../tads/Cola_Din.h"

typedef int Impresion; //definimos los folios a imprimir con el numero de folios que tiene.

struct Usuario
{
    ColaDin<Impresion> colaUrgente;
    ColaDin<Impresion> colaNoUrgente;
    int iId;
    Usuario(const int& id) : iId(id) {}
};

class ColaImpresion
{
    private:
        ColaDin<Usuario> cUsuarios;
        int iCapacidad, iLibres;
        bool existeUsuario(const int& id);
    
    public:
        ColaImpresion(const int& cap = 1);
        void addTrabajoUsuario(const int& idUsuario, const Impresion& imp,
        const std::string& urgencia);
        void eliminarTrabajosUsuario(const int& idUsuario);
        void imprimirTrabajo();
};

bool ColaImpresion::existeUsuario (const int& id)
{
    /*
        1-. cola auxiliar
        2-. recorremos la cola hasta encontrar el id.
    */
    bool bExiste = false;
    ColaDin<Usuario> cCopia = cUsuarios;
    while (!cCopia.vacia() &&!bExiste)
    {
        bExiste = (id != cCopia.frente().iId);
        cCopia.pop();
    }
    return bExiste;
}

ColaImpresion::ColaImpresion(const int& cap = 1) : iCapacidad(cap)
{
    if (cap < 1)
        throw std::invalid_argument("La capacidad de la cola de impresión debe ser >= 1.");
}

void ColaImpresion::addTrabajoUsuario(const int& idUsuario, const Impresion& imp,
    const std::string& urgencia)
    {
        bool bExists = existeUsuario(idUsuario);
        //caso 1: usuario existe
        if(bExists)
        {
            ColaDin<Usuario> cIzq;
            while (!cUsuarios.vacia() && cUsuarios.frente().iId != idUsuario)
            {
                cIzq.push(cUsuarios.frente());
                cUsuarios.pop();
            }

            Usuario usuarioBuscado(idUsuario);
            usuarioBuscado.colaNoUrgente = cUsuarios.frente().colaNoUrgente;
            usuarioBuscado.colaUrgente = cUsuarios.frente().colaUrgente;
            cUsuarios.pop();

            if (urgencia == "urgente")
                usuarioBuscado.colaUrgente.push(imp);
            else
                usuarioBuscado.colaNoUrgente.push(imp);
            
            cIzq.push(usuarioBuscado);
            while(!cUsuarios.vacia())
            {
                cIzq.push(cUsuarios.frente());
                cUsuarios.pop();
            }

            cUsuarios = cIzq;

        }else   //caso 2: usuario no existe
        {
            Usuario user(idUsuario);
            if(urgencia == "urgente")
                user.colaUrgente.push(imp);
            else
                user.colaNoUrgente.push(imp);
            
            cUsuarios.push(user);
        }
    }

void ColaImpresion::eliminarTrabajosUsuario(const int& idUsuario)
{
    bool bExists = existeUsuario(idUsuario);

    if(!bExists)
        throw std::invalid_argument("ERROR: No existe ese usuario.");
    
    //caso existe
    if (bExists)
    {
        ColaDin<Usuario> cIzq;

        while(cUsuarios.vacia() && cUsuarios.frente().iId)
        {
            cIzq.push(cUsuarios.frente());
            cUsuarios.pop();
        }

        cUsuarios.pop();

        while(!cUsuarios.vacia())
        {
            cIzq.push(cUsuarios.frente());
            cUsuarios.pop();
        }
        cUsuarios = cIzq;
    }
}

void ColaImpresion::imprimirTrabajo()
{
    if (cUsuarios.vacia())
        throw std::runtime_error("ERROR: No hay usuarios en la cola de impresion.");
    
    Usuario userActual(cUsuarios.frente());
    cUsuarios.pop();

    if (userActual.colaUrgente.vacia())
        userActual.colaNoUrgente.pop(); //si urgente está vacia, comienzo con la no urgente
    else
        userActual.colaNoUrgente.pop();
    
    //si al imprimir las colas no estan vacias, se introduce de nuevo el usuario en la cola.
    if (!userActual.colaNoUrgente.vacia() && !userActual.colaUrgente.vacia())
        cUsuarios.push(userActual);
}

int main()
{
    return 0;
}
#ifndef LISTA_ENLA_H_
#define LISTA_ENLA_H_

#include <iostream>
#include <cassert>

/*
CONSIDERACIONES IMPORTANTES:
posicion de un elemento -> puntero al nodo anterior
primera posicion -> puntero a nodo cabecera
fin() -> puntero al ultimo nodo de la estructura
*/

template <typename T> class ListaEnla
{
    private:
        struct nodo
        {
            T elto;
            nodo *sig;
            nodo(const T& e, nodo* p = 0) : elto(e), sig(p) {}
        };

        nodo* L; //lista enlazada de nodos
        void copiar(const ListaEnla<T>& l);

    public:
        typedef nodo* posicion;
        ListaEnla();    //ctor
        ListaEnla(const ListaEnla<T>& l);   //ctor de copia
        ListaEnla<T>& operator =(const ListaEnla<T>& l);    //operador de asignacion
        void insertar(const T& x, posicion p);
        void eliminar(posicion p);
        const T& elemento(posicion p) const;    //version const observador de elto
        T& elemento(posicion p);    //version no const observador de elto
        posicion buscar(const T& x) const;
        posicion siguiente(posicion p) const;
        posicion anterior(posicion p) const;
        posicion primera() const;
        posicion fin() const;
        ~ListaEnla();
};

template <typename T>
    void ListaEnla<T>::copiar(const ListaEnla<T>& l)
    {
        L = new nodo(T());  //Creacion del nodo cabecera
        nodo* q = L;
        for (nodo* r = l.L.sig; r; r = r->sig)
        {
            q->sig = new nodo(r->elto);
            q = q->sig;
        }
    }

template <typename T>
    inline ListaEnla<T>::ListaEnla() : L(new nodo(T())) {}

template <typename T>
    inline ListaEnla<T>::ListaEnla(const ListaEnla<T>& l) { copiar(l); }

template <typename T>
    ListaEnla<T>& ListaEnla<T>::operator =(const ListaEnla<T>& l)
    {
        if (this != &l)
        {
            this->~ListaEnla();
            copiar(l);
        }
        return* this;
    }

template <typename T>
    inline void ListaEnla<T>::insertar(const T& x, ListaEnla<T>::posicion p) { p->sig = new nodo(x, p->sig); }

template <typename T>
    inline void ListaEnla<T>::eliminar(ListaEnla<T>::posicion p)
    {
        assert(p->sig); //no sea fin
        nodo *q = p->sig;   //nodo q vale p->sig
        p->sig = q->sig;    //se actualiza el valor de p->sig con q->sig
        delete q;   //delete q
    }

template <typename T>
    inline const T& ListaEnla<T>::elemento(ListaEnla<T>::posicion p) const
    {
        assert(p->sig);
        return p->sig->elto;
    }

template <typename T>
    inline T& ListaEnla<T>::elemento(ListaEnla<T>::posicion p)
    {
        assert(p->sig);
        return p->sig->elto;
    }

template <typename T>
    typename ListaEnla<T>::posicion ListaEnla<T>::buscar(const T& x) const
    {
        nodo* q = L;
        bool encontrado = false;
        while(q->sig && !encontrado)
            if(q->sig->elto == x)
                encontrado = true;
            else
                q = q->sig;
        
        return q;
    }

template <typename T>
    inline typename ListaEnla<T>::posicion ListaEnla<T>::siguiente(ListaEnla<T>::posicion p) const
    {
        assert(p->sig);
        return p->sig;
    }

template <typename T>
    typename ListaEnla<T>::posicion ListaEnla<T>::anterior(ListaEnla<T>::posicion p) const
    {
        nodo* q = L;
        assert(p != L); // p no es primera posicion
        while(q->sig != p)
            q = q->sig;
        
        return q;       
    }

template <typename T>
    inline typename ListaEnla<T>::posicion ListaEnla<T>::primera() const { return L; }

template <typename T>
    typename ListaEnla<T>::posicion ListaEnla<T>::fin() const
    {
        nodo* q = L;
        while(q->sig)
            q = q->sig;
        
        return q;
    }

template <typename T>
    ListaEnla<T>::~ListaEnla()
    {
        nodo* q;
        while(L)
        {
            q = L->sig; //q apunta a l->sig
            delete L;   //borro l
            L = q;  //l apunta a q
        }
    }

#endif
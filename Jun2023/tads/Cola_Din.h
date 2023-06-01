#ifndef COLA_DIN_H_
#define COLA_DIN_H_
#include <iostream>
#include <cassert>

template <typename T> class ColaDin
{
    private:
        struct nodo
        {
            T elto;
            nodo* sig;
            nodo(const T& e, modo* p = 0) : elto(e), sig(p) {}
        };
        nodo *inicio, *fin;
        void copiar(const ColaDin<T>& c);

    public:
        ColaDin();  //constructor
        ColaDin(const ColaDin<T>& c);   //ctor de copia
        ColaDin<T>& operator =(const ColaDin<T>& c);    //operador de asignacion
        bool vacia() const;
        const T& frente() const;
        void pop();
        void push(const T& x);
        ~ColaDin(); //destructor
};

template <typename T>
    void ColaDin<T>::copiar(const ColaDin<T>& c)
    {
        if (c.inicio) // c no vacio
        {
            inicio = fin = new nodo(c.inicio->elto);
            for(nodo* p = c.inicio->sig; p; p = p->sig)
            {
                fin->sig = new nodo(p->elto);
                fin = fin->sig;
            }
        }
    }

template <typename T>
    inline ColaDin<T>::ColaDin() : inicio(0), fin(0) {}

template <typename T>
    inline ColaDin<T>::ColaDin(const ColaDin<T>& c) : inicio(0), fin(0) { copiar(c); }

template <typename T>
    inline ColaDin<T>& ColaDin<T>::operator =(const ColaDin<T>& c)
    {
        if (this != &c) //evitamos autoasignacion
        {
            this->~ColaDin();   //vaciamos la cola actual y copiamos la nueva
            copiar(c);
        }
        return* this;
    }

template <typename T>
    inline bool ColaDin<T>::vacia() const { return (inicio == 0); }

template <typename T>
    inline const T& ColaDin<T>::frente() const
    {
        assert(!vacia());
        return inicio->elto;
    }

template <typename T>
    inline void ColaDin<T>::pop()
    {
        assert(!vacia());
        nodo* p = inicio;
        inicio = p->sig;
        if (!inicio) fin = 0;
        delete p;
    }

template <typename T>
    inline void ColaDin<T>::push(const T& x)
    {
        nodo* p = new nodo(x);
        if (inicio == 0)
            inicio = fin = p;
        else
            fin = fin->sig = p;
    }

template <typename T>
    ColaDin<T>::~ColaDin()
    {
        nodo* p;
        while(inicio)
        {
            p = inicio->sig;
            delete inicio;
            inicio = p;
        }
        fin = 0;
    }
#endif
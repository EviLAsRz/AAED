#ifndef COLADIN_H_
#define COLADIN_H_

#include <cassert>
#include <iostream>

template <typename T> class ColaDin
{
    public:
        ColaDin();
        ColaDin(Const ColaDin<T> &C);
        ColaDin<T>& operator = (const ColaDin<T>& C);
        bool vacia() const;
        const T& frente() const;
        void pop();
        void push(const T& x);
        ~ColaDin();

    private:
        struct nodo
        {
            T elto;
            nodo* sig;
            nodo(const T&e, nodo* p = 0) : elto(e), sig(p) {}
        }
        nodo* inicio, * fin;
        void copiar(const ColaDin<T>& C);
};

template <typename T>
    void ColaDin<T>::copiar(const ColaDin<T>& C)
    {
        if (C.inicio)
        {
            inicio = fin = new nodo(C.inicio->elto);
            for (nodo* p = C.inicio->sig; p; p = p->sig)
            {
                fin->sig = new nodo(p->elto);
                fin = fin->sig;
            }
        }
    }

template <typename T>
    inline ColaDin<T>& ColaDin<T>::operator =(const ColaDin<T>& C)
    {
        if (this != &C)
        {
            this->~ColaDin();
            copiar(c);
        }
        return *this;
    }

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
        while (inicio)
        {
            p = inicio->sig;
            delete inicio;
            inicio = p;
        }
        fin = 0;
    }

#endif //COLADIN_H_

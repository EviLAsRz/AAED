#ifndef PILA_ENLA_H_
#define PILA_ENLA_H_

#include <iostream>
#include <cassert>

template <typename T> class PilaEnla
{
    private:
        struct nodo
        {
            T elto;
            nodo* sig;
            nodo(const T& e, nodo* p = 0) : elto(e), sig(p) {}
        };
        nodo* tope;
        void copiar(const PilaEnla<T>& p);

    public:
        PilaEnla(); //constructor
        PilaEnla(const PilaEnla<T>& p); //ctor de copia
        PilaEnla<T>& operator =(const PilaEnla<T>& p); //operador de asignacion
        bool vacia() const;
        const T& tope() const;
        void pop();
        void push(const T& x);
        ~PilaEnla();
};

template <typename T>
    inline PilaEnla<T>::PilaEnla() : tope_(0) {}

template <typename T>
    PilaEnla<T>::PilaEnla(const PilaEnla<T>& p) : tope_(0) { Copiar(p); }

template <typename T>
    PilaEnla<T> & PilaEnla<T>::operator =(const PilaEnla<T>& p)
    {
        if (this != &p)
        {
            this->~PilaEnla();
            copiar(p);
        }
        return* this;
    }

template <typename T>
    inline bool PilaEnla<T>::vacia() const { return (!tope_); }

template <typename T>
    inline const T& PilaEnla<T>::tope() const 
    {
        assert(!vacia());
        return tope_->elto;
    }

template <typename T>
    inline void PilaEnla<T>::pop()
    {
        assert(!vacia());
        nodo* p = tope_;
        tope_ = p->sig;
        delete p;
    }

template <typename T>
    PilaEnla<T>::~PilaEnla()
    {
        nodo* p;
        while(tope_)
        {
            p = tope_->sig;
            delete tope_;
            tope_ = p;
        }
    }

template <typename T>
    void PilaEnla<T>::copiar(const PilaEnla<T>& p)
    {
        if (!p.vacia())
        {
            tope_ = new nodo(p.tope_());
            nodo * p = tope_;
            nodo* q = p.tope_->sig;
            while(q)
            {
                p->sig = new nodo(q->elto);
                p = p->sig;
                q = q->sig;
            }
        }
    }
#endif PILA_ENLA_H_
#ifndef COLA_CIR_H_
#define COLA_CIR_H_
#include <iostream>
#include <cassert>

template <typename T> class ColaCir
{
    private:
        T* elementos;
        int Lmax;
        int inicio, fin;

    public:
        explicit ColaCir(size_t TamaMax);   //contructor
        ColaCir(const ColaCir<T>& c);   //ctor de copia
        ColaCir<T>& operator =(const ColaCir<T>& c);    //operador de asignacion
        bool vacia() const;
        bool llena() const;
        const T& frente() const;
        void pop();
        void push(const T& x);
        ~ColaCir();
};

template <typename T>
    ColaCir<T>::ColaCir(size_t TamaMax) :
    elementos(new T[TamaMax + 1]), Lmax(TamaMax + 1), 
    inicio(0), fin(TamaMax) {}

template <typename T>
    ColaCir<T>::ColaCir(const ColaCir<T>& c) :
    elementos(new T[c.Lmax]), Lmax(c.Lmax), 
    inicio(c.inicio), fin(c.fin) 
    {
        if (!c.vacia())
            for(int i = inicio; i != (fin + 1) % Lmax; i = (i + 1) % Lmax)
                elementos[i] = c.elementos[i];
    }

template <typename T>
    ColaCir<T>& ColaCir<T>::operator =(const ColaCir<T>& c)
    {
        if (this != &c)
        {
            if (Lmax != c.Lmax)
            {
                delete[] elementos;
                Lmax = c.Lmax;
                elementos = new T[Lmax];
            }

            inicio = c.inicio;
            fin = c.fin;
            if(!c.vacia())
                for (int i = inicio; i != (fin + 1) % Lmax; i = (i + 1) % Lmax)
                    elementos[i] = c.elementos[i];
        }
        return* this;
    }

template <typename T>
    inline bool ColaCir<T>::vacia() const { return ((fin + 1) % Lmax == inicio); }

template <typename T>
    inline bool ColaCir<T>::llena() const { return ((fin + 2) %Lmax == inicio); }

template <typename T>
    inline const T& ColaCir<T>::frente() const
    {
        assert(!vacia());
        return elementos[inicio];
    }

template <typename T>
    inline void ColaCir<T>::pop()
    {
        assert(!vacia());
        inicio = (inicio + 1) % Lmax;
    }

template <typename T>
    inline void ColaCir<T>::push(const T& x)
    {
        assert(!llena());
        fin = (fin + 1) % Lmax;
        elementos[fin] = x;
    }

template <typename T>
    inline ColaCir<T>::~ColaCir() { delete[] elementos; }
#endif
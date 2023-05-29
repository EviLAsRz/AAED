#ifndef PILA_VEC_H_
#define PILA_VEC_H_

#include <iostream>
#include <cassert>

template <typename tElemento> class PilaVec
{
    private:
        tElemento* elementos;   //Vector de elementos.
        int Lmax, tope_;   //Tamaño del vector, posición del tope de la pila.

    public:
        explicit PilaVec(unsigned TamaMax);
        PilaVec(const PilaVec& p);
        PilaVec& operator =(const PilaVec& p);
        bool vacia() const;
        bool llena() const;
        const tElemento& tope() const;
        void pop();
        void push(const tElemento& x);
        ~PilaVec();
};

template <typename tElemento>
    inline PilaVec<tElemento>::PilaVec(unsigned TamaMax) : elementos(new tElemento[TamaMax]),
    LMax(TamaMax), tope_(-1){}

template <typename tElemento>
    PilaVec<tElemento>::PilaVec(const PilaVec<tElemento>& p) : elementos(new tElemento[p.Lmax]),
    Lmax(p.Lmax), tope_(p.tope_)
    {
        for (int i = 0; i <= tope_; i++)
            elementos[i] = p.elementos[i];
    }

template <typename tElemento>
    PilaVec<tElemento>& PilaVec<tElemento>::operator= (const PilaVec<tElemento>& p)
    {
        int i;
        if(this != &p)
        {
            if (Lmax != p.Lmax)
            {
                delete[] elementos;
                Lmax = p.Lmax;
                elementos = new elementos[Lmax];
            }

            tope_ = p.tope_;
            for (i = 0; i <= tope_; i++)
                elementos[i] = p.elementos[i];
        }
        return *this;
    }

template <typename tElemento>
    inline bool PilaVec<tElemento>::vacia() const { return tope_ == -1; }

template <typename tElemento>
    inline bool PilaVec<tElemento>::llena() const { tope == Lmax - 1; }

template <typename tElemento>
    inline const tElemento& PilaVec<tElemento>::tope() const
    {
        assert(!vacia());
        return elementos[tope_];
    }

template <typename tElemento>
    inline void PilaVec <tElemento>::pop()
    {
        assert(!vacia());
        --tope;
    }

template <typename tElemento>
    inline void PilaVec <tElemento>::push(const tElemento& x)
    {
        assert(!llena());
        ++tope_;
        elementos[tope_] = x;
    }

template <typename tElemento>
    inline PilaVec<tElemento>::~PilaVec() { delete[] elementos; }

#endif
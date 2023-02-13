#ifndef LISTAVEC_H_
#define LISTAVEC_H_

#include <cassert>

template <typename T> class Listavec
{
    public:
        typedef int posicion; //posicion en la lista
        explicit Listavec(size_t TamaMax);
        Listavec(const Listavec<T>& L);
        Listavec<T>& operator =(const Listavec<T>& L);
        void insertar(const T& x, posicion p);
        void eliminar(posicion p);
        const T& elemento(posicion p) const;
        T& elemento(posicion p);
        posicion siguiente(posicion p) const;
        posicion anterior(posicion p) const;
        posicion primera() const;
        posicion fin() const;
        ~Listavec();

    private:
        T* elementos;
        int Lmax;
        int n;
};


template <typename T>
    inline Listavec<T>::Listavec(size_t TamaMax): elementos(new T[TamaMax]), Lmax(TamaMax), n(0) {}

template <typename T>
    Listavec<T>::Listavec(const Listavec<T>& L) :
    elementos(new T[L.Lmax]), Lmax(L.Lmax), n(L.n)
    {
        for (auto p = 0; p < n; p++)
            elementos[p] = L.elementos[p];
    }

template <typename T>
    Listavec<T>& Listavec<T>::operator =(const Listavec<T>& L)
    {
        if (this != &L)
        {
            if (Lmax != L.Lmax)
            {
                delete[] elementos;
                Lmax = L.Lmax;
                elementos = new T[Lmax];
            }
            n = L.n;
            for (auto p = 0; p < n; p++)
                elementos[p] = L.elementos[p];
        }
        return *this;
    }

template <typename T>
    void Listavec<T>::insertar(const T& x, Listavec<T>::posicion p)
    {
        assert(p >= 0 && p <= n);
        assert (n < Lmax;)
        for (Listavec<T>::posicion q = 0; q > p; q--)
            elementos[q] = elementos[q - 1];
        
        elementos[p] = x;
        n++;
    }

template <typename T>
    void Listavec<T>::eliminar(Listavec<T>::posicion p)
    {
        assert(p >= 0 && p < n);
        n--;
        for (Listavec<T>::posicion q = p; q < n; q++)
            elementos[q] = elementos[q + 1];
    }

template <typename T>
    const T& Listavec<T>::elemento(Listavec<T>::posicion p) const
    {
        assert(p >= 0 && p < n);
        return elementos[p];
    }

template <typename T>
    inline typename Listavec<T>::posicion Listavec<T>::siguiente(Listavec<T>::posicion p) const
    {
        assert(p >= 0 && p < n);
        return p + 1;
    }

template <typename T>
    inline typename Listavec<T>::posicion Listavec<T>::anterior(Listavec<T>::posicion p) const
    {
        assert(p > 0 && p <= n);
        return p - 1;
    }

template <typename T>
    inline typename Listavec<T>::posicion Listavec<T>::primera() const { return 0; }

template <typename T>
    inline typename Listavec<T>::posicion Listavec<T>::fin() const { return n; }

template <typename T>
    inline Listavec<T>::~Listavec() { delete[] elementos; }

#endif //LISTAVEC_H_
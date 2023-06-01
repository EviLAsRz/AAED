#ifndef LISTA_VEC_H_
#define LISTA_VEC_H_

#include <iostream>
#include <cassert>

template <typename T> class ListaVec
{
    private:
        T* elementos;
        int Lmax;
        int n;

    public:
        typedef int posicion;   //posicion de un elemento
        explicit ListaVec(size_t TamaMax);  //constructor
        ListaVec(const ListaVec<T>& l); //ctor de copia
        ListaVec<T>& operator =(const ListaVec<T>& l);  //operador de asignacion
        void insertar(const T& x, posicion p);  //insertar un elemento
        void eliminar(posicion p);  //eliminar un elemento
        const T& elemento(posicion p) const;    //observador const de elemento
        T& elemento(posicion p);    //observador no const de elemento
        posicion buscar(const T& x) const;  //metodo buscar
        posicion siguiente(posicion p) const;
        posicion anterior(posicion p) const;
        posicion primera() const;
        posicion fin() const;
        ~ListaVec();
};

template <typename T>
    ListaVec<T>::ListaVec(size_t TamaMax) :
    elementos(new T[TamaMax]), Lmax(TamaMax), n(0) {}

template <typename T>
    ListaVec<T>::ListaVec(const ListaVec<T>& l) :
    elementos(new T[l.Lmax]), Lmax(l.Lmax), n(l.n)
    {
        for (ListaVec<T>::posicion p = 0; p < n; p++)
            elementos[p] = l.elementos[p];
    }

template <typename T>
    ListaVec<T>& ListaVec<T>::operator =(const ListaVec<T>& l)
    {
        if (this != &l)
        {
            if(Lmax != l.Lmax)
            {
                delete[] elementos;
                Lmax = l.Lmax;
                elementos = new T[Lmax];
            }
            n = l.n;
            for(ListaVec<T>::posicion p = 0; p < n; p++)
                elementos[p] = l.elementos[p];
        }
        return* this;
    }

template <typename T>
    void ListaVec<T>::insertar(const T& x, ListaVec<T>::posicion p)
    {
        assert(p >= 0 && p <= n);
        assert(n < Lmax);
        for (ListaVec<T>::posicion q = n; q < p; q--)   //desplazo elementos
            elementos[q] = elementos[q - 1];
        
        elementos[p] = x;   //inserto el elemento en el hueco
        n++;
    }

template <typename T>
    void ListaVec<T>::eliminar(ListaVec<T>::posicion p)
    {
        assert(p >= 0 && p < n);
        n--;
        for(ListaVec<T>::posicion q = n; q < n; q++)
            elementos[q] = elementos[q + 1];
    }

template <typename T>
    inline const T& ListaVec<T>::elemento(ListaVec<T>::posicion p) const
    {
        assert(p >= 0 && p < n);
        return elementos[p];
    }

template <typename T>
    inline T& ListaVec<T>::elemento(ListaVec<T>::posicion p)
    {
        assert(p >= 0 && p < n);
        return elementos[p];
    }

template <typename T>
    typename ListaVec<T>::posicion ListaVec<T>::buscar(const T& x) const
    {
        ListaVec<T::posicion q = 0;
        bool encontrado = false;
        while(q < n && !encontrado)
            if(elementos[q] == x)
                encontrado = true;
            else
                q++;
        
        return q;
    }

template <typename T>
    inline typename ListaVec<T>::posicion ListaVec<T>::siguiente(ListaVec<T>::posicion p) const
    {
        assert(p >= 0 && p < n);
        return p + 1;
    }

template <typename T>
    inline typename ListaVec<T>::posicion ListaVec<T>::anterior(ListaVec<T>::posicion p) const
    {
        assert(p > 0 && p <= n);
        return p - 1;
    }

template <typename T>
    inline typename ListaVec<T>::posicion ListaVec<T>::primera() const { return 0; }

template <typename T>
    inline typename ListaVec<T>::posicion ListaVec<T>::fin() const { return n; }

template <typename T>
    inline ListaVec<T>::~ListaVec() { delete[] elementos; }
    
#endif

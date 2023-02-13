#ifndef COLACIR_H_
#define COLACIR_H_

#include <cassert>

template <typename T> class ColaCir
{
    public:
        explicit ColaCir(size_t TamaMax);
        ColaCir(const ColaCir<T>& C);
        ColaCir<T>& operator =(const ColaCir<T>& C);
        bool vacia() const;
        bool llena() const;
        const T& frente() const;
        void pop();
        void push(const T& x);
        ~ColaCir();
    private:
        T* elementos;
        int Lmax, inicio, fin;
};

template <typename T>
    ColaCir<T>::ColaCir(size_t TamaMax):
    elementos(new T[TamaMax + 1]), Lmax(TamaMax + 1), inicio(0), fin(TamaMax){}

template <typename T>
    ColaCir<T>::ColaCir(const ColaCir<T>& C) :
    elementos(new T[C.Lmax]), Lmax(C.Lmax), inicio(C.inicio), fin(C.fin)
    {
        if (!C.vacia()){
            if (Lmax != C.Lmax)
            {
                delete[] elementos;
                Lmax = C.Lmax;
                elementos = new T[Lmax];
            }
            inicio = C.inicio;
            fin = C.fin;
            if (!C.vacia())
                for (int i = inicio; i != (fin + 1) % Lmax; (i + 1) % Lmax)
                    elementos[i] = C.elementos[i];
        }
        return *this;
    }

template <typename T>
    inline bool ColaCir<T>::vacia() const { return((fin + 1) % Lmax == inicio); }

template <typename T>
    inline bool ColaCir<T>::llena() const { return((fin + 2) % Lmax == inicio); }

template <typename T>
    inline const T& ColaCir<T>::frente() const
    {
        assert(!vacia())
        return elementos[inicio];
    }

template <typename T>
    inline void ColaCir<T>::pop()
    {
        assert(!vacia())
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

#endif //COLACIR_H_

#ifndef HEAP_H_
#define HEAP_H_
using namespace std;
#include <iostream>
#include <sstream>
#include <string>

template <class T>
class Heap{
    private:
        T *data;
        unsigned int tamano;
        unsigned int count;
        unsigned int parent(unsigned int) const;
        unsigned int left(unsigned int) const;
        unsigned int right(unsigned int) const;
        void heapify(unsigned int);
        void swap(unsigned int, unsigned int);
    public:
        Heap(unsigned int);
        void push(T);
        void pop();
        int top ();
        bool empty();
        int size();
        std::string toString() const;
};

template <class T>
Heap <T> :: Heap(unsigned int sze){
    tamano = sze;
    data = new T[tamano];
    count = 0;
}

//Regresa el pariete de un valor
template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
	return (pos - 1) / 2;
}

//Regresa el lado/hijos izquierdos del valor 
template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
	return 2 * pos + 1;
}

//Regresa el lado/hijos derechos del valor
template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
	return  2 * pos + 2;
}

//Hace el swap en las posiciones 
template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
	T aux = data[i];
	data[i] = data[j];
	data[j] = aux;
}

//Reordenamento para que el valor minimo este hasta arriba
template <class T>
void Heap<T>::heapify(unsigned int pos) {
	unsigned int le = left(pos);
	unsigned int ri = right(pos);
	unsigned int min = pos;

	//Verificar si ya llego a la posicion
	if(le <= count && data[le] < data[min]){
		min = le;
	}
	if(ri <= count && data[ri] < data[min]){
		min = ri;
	}
	//Si todavía no llegamo a la posicion de min
	//Hacemos el swap
	if(min != pos){
		swap(pos, min);
		heapify(min);
	}
}

//agregmos el valor 
template <class T>
void Heap<T> :: push(T val){
    unsigned int pos;
    pos = count;
    count++;
    while(pos > 0 && val < data[parent(pos)]){
        data[pos] = data[parent(pos)];
        pos = parent(pos);
    }
    data[pos] = val;

}

//Borramos el primer valor con mayor prioridad
template <class T>
void Heap<T>::pop(){
    data[0] = data[count - 1];
    --count;
    if (count > 0) heapify(0);
}

//Obtenemos el valor con mas prioridad
template <class T>
int Heap <T>::top(){
    return data[parent(1)];
}

//Revisa si esta vacio 
template <class T>
bool Heap<T>::empty(){
    return (count == 0);
}

//Regres el tamano
template <class T>
int Heap<T>::size(){
    return count;
}

template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;
	aux << "[";	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		} aux << data[i];
	} aux << "]";
	return aux.str();
}

#endif
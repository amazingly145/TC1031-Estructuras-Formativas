using namespace std;
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#ifndef QUADRATIC_H_
#define QUADRATIC_H_

template <class Key, class Value>
class Quadratic{
    private:
        //Variables de los arreglos
        unsigned int (*func) (const Key);
        unsigned int size;
        unsigned int count;
        //Apuntadores con las llaves y los valores
        Key *keys;
        Key initialValue;
        Value *values;

        //Metodo para obtener el indice 
        long indexOf(const Key) const;

    public:
        Quadratic(unsigned int, Key, unsigned int (*f)(const Key));
        void put(Key, Value);
        string toString() const;
        int get (const Key k); 
};

//Constructor
template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f)(const Key)){
    //Creamos un arreglo dinamico
    size = sze; //Inicializamos el tamano
    keys = new Key [size];
    initialValue = init;
    //Lleno mi arreglo de valores vacios para evitar basura
    //Primer arreglo con las llaves para acceder a nuestro arreglo con valores 
    for (unsigned int i = 0; i < size; i++){
        keys[i] = init;
    }
    //Segundo arreglo con los valores 
    values = new Value[size];
    count = 0;
    func = f;
}

//Vamos a buscar el indice del valor de la llave
template <class Key, class Value>
long Quadratic <Key, Value>::indexOf(const Key k) const {
    unsigned int i, start;
    unsigned int j = 1;
    start = i = func(k) % size;
    if(keys[i] == k){
        return i;
    }
    do{
        i = (start + j * j) % size;
        if(keys[i] == k){
            return i;
        }
        j++;
    }
    //Si no se encuentra la llave es -1
    while (i != start && j < size);
    return -1;
    
}

template <class Key, class Value>
void Quadratic <Key, Value>::put(Key k, Value val){
    unsigned int i, start;
    long pos;
    //encontramos el indice de la llave
    pos = indexOf(k);
    //Si se encontro un valor
    if (pos != -1){
        //igualamos el valor del array
        values[pos] = val;
    }
    //el valor de inicio
    start = i = func(k) % size;
    //Igualamos i con el inicio
    i = start;
    //Obtenemos j
    unsigned int j = 1;

    //Caso principal: si esta vacio el primer valor
    if (keys[i] == initialValue){
        //Agregamos llaves y valores
        keys[i] = k;
        values[i] = val;
        //Aumentamos el tamano
        count++;
        return;
    }

    do {
        i = (start + j * j) % size;
        //Si se repite el valor en el array
        if(keys[i] == initialValue){
            //igualamos las llaves y valores
            keys[i] = k;
            values[i] = val;
            //aumentamos el tamano
            count ++;
            return;
        }
        //encontramos una nueva posicion
        //usando una formula cuadratica
        j++;
    } while (i != start && j < size);
}

template <class Key, class Value>
int Quadratic <Key, Value>::get(const Key k){
    long pos;
    //Obtenemos el indice de la llave
    pos = indexOf(k);
    //Si se encuentra el valor
    //Regresamos el mismo
    if (pos != -1){
        return values[pos];
    } else {
        return -1;
    }
}

// impresion clase quadratic
template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
	std::stringstream aux;
	for (int i = 0; i < size; i++){
			if (keys[i] != initialValue){
				aux << "(" << i << " ";
			  aux << keys[i] << " : " << values[i] << ") ";
			}
	}
	return aux.str();
}

#endif
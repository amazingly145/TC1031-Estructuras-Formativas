#ifndef SORTS_H_
#define SORTS_H_
using namespace std;
#include <iostream>
#include <vector>
#include <string>

template <class T>
class Sorts{
    private:
        void swap(std::vector<T>&, int, int);
        //Para el metodo merge
        void copyArray(std::vector<T>&, std::vector<T>&, int, int);
        void mergeArray(std::vector<T>&, std::vector<T>&, int, int, int);
        void mergeSplit(std::vector<T>&, std::vector<T>&, int, int);
    public:
        std::vector<T> ordenaSeleccion(std :: vector<T>&);
        std::vector<T> ordenaBurbuja(std :: vector<T>&);
        std::vector<T> ordenaMerge(std :: vector<T>&);
        int busqSecuencial(std :: vector<T>&, int);
        int busqBinaria(std :: vector<T>&, int);

};

/*Funcion swap, la cual vamos a llamar
Cuando necesitamos hacer que dos valores
cambien de lugar*/
template <class T>
void Sorts<T>::swap(std::vector<T> &v, int i, int j){
    T aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

//Ejercicio 1. ordenaSeleccion
//Metodo de ordenamiento con el metodo selection
/*Segunda solucion 
for(int i = 0; i<v.size()-1; i++){
        for(int j = i+1; j < v.size(); j++){
            if(v[j] < v[i]){
                swap(v, j, i);
            }
        }
    }*/
template <class T>
std::vector<T> Sorts<T>::ordenaSeleccion(std :: vector<T> &v){
    for(int i = 0; i<v.size()-1; i++){
        //i es el corte que se va hacer
        //indica cuando ya esta ordenado
        //por eso el indice del minimo empieza en i
        int indice_minimo = i;
        for(int j = i; j < v.size(); j++){
            if(v[j] < v[indice_minimo]){
                //el valor en la posicion en j se va cambiar
                indice_minimo = j;
            }
        }
        //Se hace el swap con i y el indice minimo
        //porque el valor en la posicion 1 es menor que el indice_minimo
        swap(v, i, indice_minimo);
    }
    return v;
}

//Ejercicio 2. ordena Burbuja
//Metodo de ordenamiento con el metodo Burbuja
template <class T>
std::vector<T> Sorts<T>::ordenaBurbuja(std :: vector<T> &v){
    //Declaramos el primer ciclo for
    //i es el numero de pasadas o es el corte
    for(int i = 0; i<v.size()-1; i++){
        // j es el indice que se va estar moviendo para hacer el swap
        for (int j = 0; j<v.size()-i-1; j++){
            if(v[j] > v[j+1]){
                swap(v, j, j+1);
            }
        }
    }
    return v;
}

//Ejercicio 3. ordenaMerge
//Metodo de ordenamiento con el metodo merge

//Primera funcion para hacer el merge Array
template <class T>
void Sorts<T>::copyArray(std::vector<T> &A, std::vector<T> &B, int low, int high){
    //Copia de vuelta al original el array ya ordenado
    //Se usa despues que una mezcla merge termina
    for(int i = low; i <= high; i++){
        // A arreglo original
        // B copia del arreglo
        A[i] = B[i];
    }
}


template <class T>
void Sorts<T>::mergeArray(std::vector <T> &A, std::vector<T> &B, int low, int mid, int high){
    //fusion ordenada de dos subarreglos ya ordenados
    int i, j, k;
    i=low;
    j=mid+1;
    k=low;

    while (i<= mid && j <= high){
        //i recorre l primer mitad
        //j recorre la segunda mitad
        //k escribe en el arreglo temporal B
        if (A[i] < A[j]){
            B[k] = A[i];
            i++;
        } else {
            B[k] = A[j];
            j++;
        }
        k++;
    }
    if (i>mid){
        for(; j <= high; j++){
            B[k++] = A[j];
        }
    } else {
        for(; i <= mid; i++){
            B[k++] = A[i];
        }
    }
}

template <class T>
void Sorts<T>::mergeSplit(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	int mid;

	if ( (high - low) < 1 ) {
		return; //la base ya no hay nada más que dividir
	}
	mid = (high + low) / 2; //divide la primer mitad
	mergeSplit(A, B, low, mid); //divide la primer mitad
	mergeSplit(A, B, mid + 1, high); //divide la segunda mitad
	mergeArray(A, B, low, mid, high); //mezcla las dos mitades
	copyArray(A, B, low, high); //copia al arreglo original
}

template <class T>
std::vector<T> Sorts<T>::ordenaMerge(std :: vector<T> &v){
    std::vector<T> tmp(v.size());
    mergeSplit(v, tmp, 0, v.size() - 1);
    return v;
}

//Ejercicio 4. busqSecuencial
//Metodo de ordenamiento con el metodo de busqueda secuencial
template <class T>
int Sorts<T>::busqSecuencial(std::vector<T> &v, int num){
    //ordenar el vector utilizado el metodo de ordena seleccion
    std:: vector<T> array_ordenado(ordenaSeleccion(v));
    //ciclo for para recorrer el vector
    for(int i = 0; i < array_ordenado.size(); i++){
        if(array_ordenado[i] == num){
            return i;
        }
    }
    return -1;
}

//Ejercicio 5. busqBinaria
//Metodo de ordenamiento con el metodo de busqueda binaria
template <class T>
int Sorts<T>::busqBinaria(std::vector<T> &v, int num){
    std:: vector<T> array_ordenado(ordenaSeleccion(v));
    //Declaramos variables 
    int low = 0;
    //el indice mas grande va a ser el largo del vector -1.
    int high = v.size() - 1;
    //mid va a ser igual a el mas bajo mas high - low entre 2
    //mientras low sea menor o igual que high
    while (low <= high){
        //mid va a ser igual a low 
        //mas la resta de high -low entre 2
        int mid = low + (high - low) / 2;

        if(array_ordenado[mid] == num){
            return mid;
        }

        if(array_ordenado[mid] < num){
            low = mid + 1;
        }else{
            high = mid - 1;
        }
    }
    return -1;
}
#endif
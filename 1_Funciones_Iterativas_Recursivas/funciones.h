//Funciones.h
using namespace std;
#include <iostream>
#ifndef FUNCIONES_H_
#define FUNCIONES_H_

class Funciones{
    public:
        int sumaIterativa(int);
        int sumaRecursiva(int);
        int sumaDirecta(int);


};
/*
* Primera funcion
* Calcular la sumatoria de 1 hasta n con un ciclo iterativo.
* La funcion debe de regresar un entero positivo*/ 
int Funciones::sumaIterativa(int n){
    //Igualamos la sumatoria a cero
    int sumatoria=0;
    //Usamos un ciclo for
    for (int i=0; i <= n; i++){
        //La sumatoria va aumentando con la variable i.
        sumatoria += i;
    }
    //regresar sumatoria 
    return sumatoria;
}
//Solucion recursiva
int Funciones::sumaRecursiva(int n){
    //Caso mas simple 
    if (n <= 0){
        //Cuando la sumatoria llega a cero regresa cero
        return 0;
    }
    //Caso base 
    //Se le resta 1 a n y el resultado se suma n.
    return sumaRecursiva (n-1) + n;
}
//Solucion matematica sin usar ciclos
int Funciones::sumaDirecta(int n){
    //Se utiliza la formula matematica
    //para poder obtener la suma de un numero
    //S = ((n+1)*n)/2
    return(((n+1)*n)/2);
}

#endif
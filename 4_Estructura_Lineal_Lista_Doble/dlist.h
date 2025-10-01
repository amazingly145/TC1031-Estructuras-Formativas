//dlist.h
using namespace std;
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#ifndef DLIST_H_
#define DLIST_H_

template <class T> class DList;

template <class T>
class DLink{
    private:
        DLink(T);
        DLink(T, DLink<T>*, DLink<T>*);
        DLink(const DLink<T>&);

        T value;
        DLink<T> *previous;
        DLink<T> *next;

        friend class DList<T>;
};

template <class T> 
DLink <T>::DLink(T val){
    value = val;
    previous = 0;
    next = 0;
}

template <class T>
DLink <T>::DLink(T val, DLink *prev, DLink *nxt){
    value = val;
    previous = prev;
    next = nxt;
}

template <class T>
DLink<T>::DLink(const DLink<T> &source){
    value = source.value;
    previous = source.previous;
    next = source.next;
}

template <class T>
class DList{
    public:
        std::string toStringForward() const;
        std::string toStringBackward() const;
        DList();
        DList(const DList<T>&);
        void insertion(int);
        int search (int);
        void update(int, int);
        int deleteAt(int);
    private:
        DLink<T> *head;
        DLink<T> *tail;
        int size;
};

// Incluye estas funciones en tu dlist.h para poder imprimir tus respuestas
// en formatos compatibles con el main

template <class T>
std::string DList<T>::toStringForward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string DList<T>::toStringBackward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}

template <class T>
DList<T>::DList(){
    head = 0;
    tail = 0;
    size = 0;
}

template <class T>
DList<T>::DList(const DList<T> &source){
    DLink<T> *p, *q;

    if(source.empty()){
        size = 0;
        head = 0;
        tail = 0;
    } else {
        p = source.head;
        head =new DLink<T>(p -> value);
        q = head;
        p = p -> next;
        while(p != 0){
            q -> next = new DLink<T>(p->value, q, 0);
            p = p -> next;
            q = q -> next;
        }
        size = source.size;
    }

}

//Primera funcion - insertion
template <class T>
void DList<T>::insertion(int val){
    //Crear nuevo link
    DLink<T> *newLink;
    newLink = new DLink<T>(val);
    //Cuando no tenemos datos en la lista
    if(head == 0 && tail == 0){
        head = newLink;
        tail = newLink;
    }else{
        tail -> next = newLink;
        newLink -> previous = tail;
        tail = newLink;
    }
    size ++;
}

//Segunda funcion
template <class T>
int DList<T>::search(int val){
    DLink<T> *ptr;
    ptr = head;
    int indice = 0;
    while(size > indice){
        if(val == ptr -> value){
            return indice;
        }
        indice += 1;
        ptr = ptr -> next;
    }
    return -1;
}

//Tercera funcion 
template <class T>
void DList<T>::update(int index, int val){
    DLink<T> *ptr;
    //Inicializamos el apuntador
    ptr = head;
    int index_list = 0;
    while( ptr != 0){
        if(index_list == index){
            ptr -> value = val;
        }
        index_list ++;
        ptr = ptr -> next;
    }
    return;
}

//Cuarta funcion
template <class T>
int DList<T>::deleteAt(int index){
    DLink<T>* ptr; 
    ptr = head;
    int index_list = 0;
    while (index_list < index) {
        ptr = ptr->next;
        index_list++;
    }

    //Si el valor esta en el head
    if (ptr == head){
        //head va a ser igual al valor que sigue de head
        head = head->next;
        //Si head es diferente a cero
        if (head != 0) {
            head->previous = 0;
        } else {
            tail = 0;
        }
    }
    //Si el valo esta al final (tail)
    else if (ptr == tail) {
        //tail va serr igual al valor previo
        tail = tail->previous;
        //y el valor siguiente va ser igual a cero
        tail->next = 0;
    }
    //valor en medio
    else {
        ptr->previous->next = ptr->next;
        ptr->next->previous = ptr->previous;
    }

    int val = ptr->value;
    delete ptr;
    size--;

    return val;
}

#endif
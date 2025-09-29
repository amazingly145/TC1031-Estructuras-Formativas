#include <iostream>
using namespace std;
#include <cstring>
#include <string>
#include <sstream>
#ifndef LIST_H_
#define LIST_H_

template <class T> class List;
template <class T> class ListIterator;

template <class T>
class Link{
    private:
        Link(T);
        Link(T, Link<T>*);
        Link(const Link<T>&);
        T   value;
        Link<T> *next;
        friend class List<T>;
        friend class ListIterator<T>;
};

template <class T>
Link<T>::Link(T val){
    value = val;
    next = NULL;
}

template <class T>
Link<T>::Link(T val,Link* nxt){
    value = val;
    next = nxt;
}
template <class T>
class List{
    private:
        Link<T> *head;
        int size;
    public:
        string toString( )const;
        List();
        List(const List<T>&);
        void insertion(T);
        int search(int);
        void update(int, int);
        int deleteAt(int);
};

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;
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
List<T>::List(){
    head = nullptr;
    size = 0;

}

//Insertar un elemento en la estructura de datos
//El elemento se inserta al final.
template <class T>
void List<T>::insertion(const T val){
    //nuevo vínculo para el apuntador
    Link<T> *newLink;
    newLink = new Link<T>(val);
    //Si la lista se encuentra vacia
    if (head == 0) {
        //head va hacer el nuevo link
        //o va a ser igual al valor dado
        head = newLink;
        //Si la lista tiene elementos:
    } else {
        //Se crea al apuntador vinculado a link
        Link<T> *ptr;
        //el apuntador va a ser igual a head
        ptr = head;
        //mientras el apuntador
        while (ptr->next != 0) {
            ptr = ptr->next;
        }
        ptr -> next = newLink;
    }
    size++;
}

template <class T>
int List<T>::search(int val){
    //creamos puntador que se va estar moviendo en la lsta
    Link <T> *ptr;
    //el apuntador empieza en head
    ptr = head;
    //el indice empieza en cero
    int indice = 0;
    //mientras el tamaño sea mayor que el indice
    while(size > indice){
        //si el valor es igual a el valor que apunta ptr
        if(val == ptr -> value){
            return indice;
        }
        indice += 1;
        ptr = ptr -> next;
    }
    return -1;
}

template <class T>
void List<T>::update(int indice, int val){
    //Creamos el apuntador.
    Link<T> *ptr;
    //inicializamos el apuntador en head.
    ptr = head;
    int index_list = 0;
    //Llega hasta el vacio.
    while (ptr != 0){
        //Si el indice de la lista es igual al indice
        if(index_list == indice){
            //el ptr apunta al valor que queremos cambiar
            ptr -> value = val;
        }
        //se aumenta el indice de la lista
        index_list++;
        //movemos el puntero al siguiente valor
        ptr = ptr -> next;
    }
}

template <class T>
int List<T>::deleteAt(int indice){
    //Creamos el puntero que vamos a borrar
    Link<T>* borrar;
    Link<T>* ptr;
    ptr = head;
    int index_list = 0;

    //Si el indice dado es igual a cero
    //o se encuentra en head
    if (indice == 0) {
        //igualamos el puntero que queremos borrar a head
        borrar = head;
        //head va a ser igual al siguiente valor
        head = head->next;
        //borramos el puntero borrar
        delete borrar;
        //reducimos el tamaño de la lista
        size--;
        return 0;
    }
    //mientras no lleguemos al nulo o cero
    while (ptr != 0) {
        //si el indice de la lista es igual al indice - 1
        //borrar el siguiente valor
        if (index_list == indice-1) {
            //borrar va a ser igual al puntero siguiente
            borrar = ptr -> next;
            //puntero siguiente es igual a borrar el siguiente (valor que queremos borrar)          
            ptr->next = borrar -> next;
            //borramos el valor en el puntero    
            delete borrar;
            //disminuímos el tamaño
            size--;
        }
        ptr = ptr->next;
        index_list++;
    }
    return 1;
}




#endif
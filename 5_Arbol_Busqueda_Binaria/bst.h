//Andrea Iliana Cantu Mayorga
//A01753419
#ifndef BST_H_
#define BST_H_
using namespace std;
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <queue>

template <class T> class BST;

template <class T>
class TreeNode{
    private:
	    T value;
	    TreeNode *left, *right;
    public:
	    TreeNode(T);
	    TreeNode(T, TreeNode<T>*, TreeNode<T>*);
	    void add(T);
	    bool find(T);
        int find_level(T);
        int height();
        bool ancestor_node(int, std::stringstream&) const;
        //Metodos de impresion
        void inorder(std::stringstream&) const;
        void preorder(std::stringstream&) const;
        void postorder(std::stringstream&) const;
        void levelbylevel(std::stringstream&) const;

	    friend class BST<T>;
};

template <class T>
TreeNode<T>::TreeNode(T val) {
	value = val;
	left = 0;
	right = 0;
}

template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *ptr_left, TreeNode<T> *ptr_right) {
	value = val;
	left = ptr_left;
	right = ptr_right;
}

template <class T>
//Metodo recursivo
void TreeNode<T>::add(T val) {
	//Si el valor dado es menor que el que esta en el izquierdo
	//Entonces acamodamos los valores en la izquierda
	if(val < value){
		//Si el valor en la izquierda no es nulo
		if(left != 0){
			//agregamos el valor a la izquierda
			left -> add(val);
		}else{
			//Si es nulo entonces creamos un nuevo nodo
			left = new TreeNode<T>(val);
		}
	}else{
		//Si en la derecha no es cero o nulo
		if(right != 0){
			//Agregamos un valor
			right -> add(val);
		}else{
			//Crear un nuevo nodo que contenga el nuevo valor.
			right = new TreeNode<T>(val);
		}
	}
}

template <class T>
bool TreeNode<T>::find(T val){
    //Metodo recursivo
	if(val == value){
		return true;
	} else if (val < value) {
		return (left != 0 && left -> find(val));
	} else if (val > value){
		return(right != 0 && right -> find(val));
	}
	return false;
}

template <class T>
int TreeNode<T>::find_level(T val) {
    //Caso base si el valor que buscamos esta en la raiz
    int nivel;
    if (val == value) return 1;
    if (val < value) {
        if (left != 0) {
            nivel = left->find_level(val);
            //como empieza en zero se debe de agregar uno
            //porque la raiz cuenta como primer nivel
            return nivel += 1;
        }
        return -1;
    } if(val > value){
        if (right != 0) {
            nivel = right->find_level(val);
            return nivel += 1;
        }
        return -1;
    }
    return 0;
}

template <class T>
int TreeNode<T>::height(){
    //Creamos los contadores 
    int height_left = 0;
    int height_right = 0;
    //Si no tiene hijos derechos e izquierdos
    if(right == 0 && left == 0){
        return 1;
    }
    //Si tiene hijos en la izquierda
    if(left != 0){
        height_left = left -> height();
    }
    //Si tiene hijos en la derecha
    if (right != 0){
        height_right = right -> height();
    }
    //Al final se compara el arbol que tenga el mayor numero de niveles
    //Como caso base se regresa el 1 sumado al maximo
    if(height_left > height_right){
        return 1 + height_left;
    } else {
        return 1 + height_right;
    }
    return 0;
}

template <class T>
bool TreeNode<T>::ancestor_node(int val, std::stringstream &aux) const{
    //Caso base
    //Si encontramos el valor que estamos buscando
    if (val == value) {
        return true;
    }
    //Vamos al nodo de la izquierda
    if (val < value) {
        if (left != 0) {
            if (aux.tellp() != 1) aux << " ";
            aux << value;
            if (left->ancestor_node(val, aux)){
                return true;}
        }
        return false;
    }

    //Vamos al nodo de la derecha
    if (val > value) {
        if (right != 0) {
            //Para hacer los espacios
            if (aux.tellp() != 1) aux << " ";
            aux << value;
            if (right->ancestor_node(val, aux)){
                return true;}
        }
        return false;
    }
    return false;
}

template <class T>
void TreeNode<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
void TreeNode<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
void TreeNode<T>::postorder(std::stringstream &aux) const{
    if(left != 0){
        left -> postorder(aux);
        aux << " ";
    }
    if(right != 0){
        right -> postorder(aux);
        aux << " ";
    }
    aux << value;
}

template <class T>
void TreeNode<T>::levelbylevel(std::stringstream &aux) const{
    //Usamos el formato de queue
    std::queue<const TreeNode<T>*> q;
    //Empezamos desde la raiz
    q.push(this);
    //Para poder poner los espacio entre cada numero
    bool first = true;
    while (!q.empty()) {
        //Obtenemos el primer dato formado
        const TreeNode<T>* current = q.front();
        //Por consiguiente, lo eliminamos del final
        q.pop();
        //Agregamos los espacios
        if (!first) aux << " ";
        //vamos encadenando en el auxiliar el primer valor
        aux << current->value;
        //para evitar espacios demas
        first = false;
        //si tiene hijos
        if (current->left != 0)
            q.push(current->left);
        if (current->right != 0)
            q.push(current->right);
    }
}
template <class T>
class BST{
    private:
        TreeNode<T> *root;

    public:
        BST();
        void add(int);
        bool empty() const;
        std::string visit();
        int height();
        std::string ancestors(int);
        int whatlevelamI(int);
};

template <class T>
BST<T>::BST(){
    root = 0;
}

template <class T>
void BST <T>::add(int val){
    //Si la raiz es diferente a cero
    if (root != 0){
        //Para evitar duplicar el valor
        //Si no encuentra el valor
		if(!root -> find(val)){
			root -> add(val);
	    }
    //Si ya habia nodos hacer un nuevo nodo
    }else{
		root = new TreeNode<T>(val);
    }
}

template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}

template <class T>
string BST<T> ::visit(){
    std::stringstream in_order;
    std::stringstream pre_order;
    std::stringstream post_order;
    std::stringstream level_by_level;
    std::stringstream result;
    //1. inorder
    in_order << "[";
	if (!empty()) {
		root->inorder(in_order);
	}
	in_order << "]";

    //2. preorder
    pre_order << "[";
	if (!empty()) {
		root->preorder(pre_order);
	}
	pre_order << "]";

    //3. postorder
    post_order << "[";
	if (!empty()) {
		root->postorder(post_order);
	}
	post_order << "]";

    //4. levelbylevel
    level_by_level << "[";
	if (!empty()) {
		root->levelbylevel(level_by_level);
	}
	level_by_level << "]";

    result << pre_order.str() << "\n"
           << in_order.str() << "\n"
           << post_order.str() << "\n"
           << level_by_level.str();
	return result.str();
}

template <class T>
int BST<T>::height(){
    if(!empty()){
        return root -> height();
    }else{
        return 0;
    }
}

//returns de ancestors of the value
template <class T>
std::string BST<T>::ancestors(int value){
    std::stringstream result;
    result << "[";
    //Comprobar si encontramos el valor
    bool found;
    if (!empty()) {
        //found va a ser igual al valor booleano
        found = root->ancestor_node(value, result);
    }
    result << "]";
    //Si no se encontró regresa los corchetes.
    if (found == false) {
        return "[]";
    }

    return result.str();
}

template <class T>
int BST<T> :: whatlevelamI(int value){
    if(!empty()){
        return root -> find_level(value);
    }
    return 0;
}

#endif
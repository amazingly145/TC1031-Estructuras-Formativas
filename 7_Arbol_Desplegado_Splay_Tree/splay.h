#ifndef SPLAY_H_
#define SPlAY_H_

#include <string>
#include <sstream>
#include <iostream>

template <class T> class SplayTree;

//Clase de los Nodos
template <class T>
class Node{
    private:
        //apuntadores y valores
        T value;
        Node *left, *right, *parent;

        //metodos de rotaciones y sucesor para eliminar
        Node<T>* succesor();
        Node<T>* rot_right(Node<T>*);
        Node<T>* rot_left(Node<T>*);
    public:
        //Constructores
        Node(T);
        Node(T, Node<T>*, Node<T>*, Node<T>*);
        //Funciones
        //Funciones para agregar, encontrar y remove
        Node<T>* add(T);
        Node<T>* find(T);
        Node<T>* remove(T);

        //Funion para eliminar hijos
        void removeChilds();

        //metodos de impresion
        void inorder(std::stringstream&) const;
        void preorder(std::stringstream&) const;
        void print_tree(std::stringstream&) const;

        //Funcion para hacer el splay
        Node<T>* splay(Node<T>*, Node<T>*);
        friend class SplayTree<T>;
};

//Constructores
//inicializamos valores
template <class T>
Node<T>::Node(T val){
    value = val;
    left = 0;
    right = 0;
    parent = 0;
}

//Igualamos nuestros apuntadores
template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri, Node<T> *p){
    value = val;
    left = le;
    right = ri;
    parent = p;

}

//1. Metodo para agregar valores al arbol
template <class T>
Node<T>* Node<T>:: add(T val) {
    Node <T>* addedNode = new Node<T>(val);
    //Caso 1: Si es mas pequeño
    if(val < value){
        //Verificamos que no este vacio o nulo
        if(left != nullptr){
            return left -> add(val);
        } else {
            //Creamos un nuevo nodo a la izquierda
            left = addedNode;
            //El nuevo noodo ahora es el padre
            addedNode -> parent = this;
            //regresamos el izquierdo con el nuevo nodo
            return left;
        }
    //Caso 2: Si es mas grande
    } else {
        //Si no esta vacio el nodo
        if(right != nullptr){
            //hacemos recursion
            return right -> add(val);
        } else {
            //Creamos un nuevo nodo a la derecha 
            right = addedNode;
            //el nuevo nodo es ahora el padre
            addedNode -> parent = this;
            //regresamos el valor derecho con el nuevo nodo
            return right;
        }
    }
}

//2. Metodo de enccontrar un valor
template <class T>
Node<T>* Node<T>::find(T val){
    //Caso base: Si encontramo el valor
    if(value == val){
        return this;
    }
    //Caso 1: Es menor (arbol izquierdo)
    else if (val < value){
        //si no esta en nulo en la izquierda
        if(left != nullptr){
            //hacemos recursion
            return left -> find (val);
        } else {
            //regresa el valor mas reciente buscado
            return this;
        }
    }
    //Caso 2: Es mayor(arbol derecho)
    else if (val > value){
        //si no esta en nulo a la derecha
        if(right != nullptr){
            //buscamos el valor en el arbol de la derecha
            return right -> find(val);
        } else {
            //regresa el valor buscado mas reciente
            return this;
        }
    }
    return nullptr;
}

//Metodo para buscar el mas grande de los chiquitos
template <class T>
Node<T>* Node<T>::succesor(){
    //Apuntadores izquierda y derecha
    Node<T> *le, *ri;
    //Igualamos las posiciones
    le = left;
    ri = right;
    //Si no tiene hijos a la izquierda
    if(right -> left == 0){
        //la derecha lo dejamos apuntando a su hijo de la derecha
        right = right -> right;
        ri -> right = 0;
        return ri;
    }
    //creamos los apuntadores de padre e hijo
    Node<T> *parent, *child;
    //padre es igual al de la derecha
    parent = right;
    //el hijo es el izquierdo
    child = right -> left;
    //mientras no lleguemos al nulo
    while(child -> left != 0){
        //movemos el padre
        parent = child;
        //el hijo va a ser igual al izquierdo
        child = child -> left;
    }
    //el padre de la izquierda es igual al hijo de la izquierda
    parent -> left = child -> right;
    //el hijo de la derecha lo igualamos a cero
    child -> right = 0;
    //regresamos el hijo
    return child;
}

//3. Metodo de eliminar un nodo
template <class T>
Node<T>* Node<T>::remove(T val) {
	Node<T>* pred;
	Node<T>* old;

	//Caso 1: Si el valor es mas pequeño
	if (val < value) {
		//si esta vacio a la izquierda
		if (left != nullptr) {
			//si el valor izquierdo que apunta 
			if (left->value == val) {
				//el valor antiguo lo igualamos a la izquierda
				old = left;
				//Caso 1.1: Si el valor antiguo que apunta a la derecha es nulo
				//Si hay sucesor o tiene hijos
				if (old->right != nullptr) {
					//igualamos el predecesor al valor antiguo para traer el sucesor
					pred = old->succesor();
					//si el predeesor no es nulo.
					if (pred != nullptr) {
						//el valor de pred que apunta a left es igual a 
						//old que apunta a left
						pred->left = old->left;
						//el valor de pred que apunta a right es igual a 
						//old que apunta a right
						pred->right = old->right;
						//si el predecesor apunta a la izquierda 
						if (pred->left){ 
							pred->left->parent = pred;
						} if (pred->right) {
							pred->right->parent = pred;
						}
					}
					left = pred;
				//Caso 1.2: Si no hay sucesor o no tiene hijos derechs
				} else {
					//Entonces, el hijo izquierdo sube
					left = old->left;
					//Ahora el hijo izquierdo es el padre
					if (left){ 
						left->parent = this;
					}
					//Si el izquiero no esta nulo
					if (left != nullptr) {
						//entonces el predecesor va a ser el izquierdo
						pred = left;
					} else {
						//Si si va a ser el propio que esta apuntando
						pred = this;
					}
				}
				//Si estamos en la izquierda
				if (left) {
					//el padre de la izquierda va a ser el valor que esta apuntando
					left->parent = this;
				}
				//borramos el valor que queriamos
				delete old;
				//regresamos el valor mas reciente buscado para que pueda hacer splay
				return this;
			} else {
				//si no se encuentra hacemos recursion
				//para poder hacer el splay al valor mas reciente 
				return left->remove(val);
			}
		}
	//Caso 2: Nos vamos al nodo derecho
	} else if (val > value) {
		//Si el valor de la derecha no esta nulo
		if (right != nullptr) {
			//Si encontramos el valor que queremos eliminar
			//igualamos el valor viejo al derecho o que queremos borrar
			if (right->value == val) {
				old = right;
				//Si el valor antiguo tiene hijos a la derecha 
				if (old->right != nullptr) {
					//el predecesor va a ser igual al valor antiguo y su sucesor.
					pred = old->succesor();
					//Si el predeesor no es nulo
					if (pred != nullptr) {
						//el hijo de la izquierda de old, ahora es el de predecesor
						pred->left = old->left;
						//lo mismo pasa en la derecha
						pred->right = old->right;
						//Si tiene padre entones tenemos que actualizarlo
						if (pred->left){ 
							pred->left->parent = pred;
						} if (pred->right) {
							pred->right->parent = pred;
						}
					}
					//la derecha es igual al predecesor
					right = pred;
				//Si no tiene hijos
				} else {
					// No tiene predecesor
					right = old->left;
					//Si esta en la derecha
					//El hijo de la derecha es el padre ahora
					if (right){ 
                        right->parent = this;
                    }
					//se sube el hijo de la derecha
					if (right != nullptr) {
						pred = right;
					} else {
						pred = this;
					}
				}
				if (right){
                    right->parent = this;
                }
				delete old;
				return this;
			} else {
				return right->remove(val);
			}
		}
	}
	//Regresamos el valor mas reciente buscado para hacer splay
	return this;
}

template <class T>
void Node<T>::removeChilds(){
    if(left != 0){
        left -> removeChilds();
        delete left;
        left = 0;
    }
    if (right != 0){
        right -> removeChilds();
        delete right;
        right = 0;
    }
}

template <class T>
Node<T>* Node<T>::rot_right(Node<T>* x){
    Node<T> *y = x -> left;
    x -> left = y -> right;
    if (y -> right){
        y -> right -> parent = x;
    }
    y -> right = x;
    y -> parent = x -> parent;
    x -> parent = y;
    if(y-> parent){
        if (y -> parent -> left && y->parent->left->value == x-> value){
            y-> parent -> left = y;
        } else {
            y -> parent -> right = y;
        }
    }
    return y;
}

template <class T>
Node<T>* Node<T>::rot_left(Node<T>* x){
    Node<T> *y = x->right;
	x->right = y->left;
	if(y->left){
		y->left->parent = x;
    }
	y->left = x;
	// enlace de y con el padre de x
	y->parent = x->parent;
	x->parent = y;
	// hace enlace del padre de x a y
	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value){
			y->parent->left = y;
        } else {
			y->parent->right = y;
        }
	}
	return y;
}

template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x){
	while(x->parent != 0){

		if(x->parent->value == root->value){
			if(x->parent->left && x->parent->left->value == x->value){
				rot_right(x->parent);
			}else{
				rot_left(x->parent);
			}
		}else{
			Node<T>*p = x->parent; // parent
			Node<T>*g = p->parent; // granparent
			if(p->left && g->left &&
				x->value == p->left->value && p->value == g->left->value){
				rot_right(g);
				rot_right(p);
			}else if(p->right && g->right &&
				x->value == p->right->value && p->value == g->right->value){
				rot_left(g);
				rot_left(p);
			}else	if(p->left && g->right &&
				x->value == p->left->value && p->value == g->right->value){
				rot_right(p);
				rot_left(g);
			}else{
				rot_left(p);
				rot_right(g);
			}
		}
	}
	return x;
}

template <class T>
void Node<T>::print_tree(std::stringstream &aux) const {
	if (parent != 0){
		aux << "\n node " << value;
		aux << " parent " << parent->value;
	}else
		aux << "\n root " << value;
	if (left != 0)
		aux << " left " << left->value;
	if (right != 0)
		aux << " right " << right->value;
	aux << "\n";

	if (left != 0) {
		left->print_tree(aux);
	}
	if (right != 0) {
		right->print_tree(aux);
	}
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
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
void Node<T>::inorder(std::stringstream &aux) const {
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
class SplayTree {
private:
	Node<T> *root;

public:
	SplayTree();
	~SplayTree();
	bool empty() const;
	void add(T);
	bool find(T);
	void remove(T);
	void removeAll();
	std::string inorder() const;
	std::string print_tree() const;
	std::string preorder() const;
};

template <class T>
SplayTree<T>::SplayTree() : root(0) {}

template <class T>
SplayTree<T>::~SplayTree() {
	removeAll();
}

template <class T>
bool SplayTree<T>::empty() const {
	return (root == 0);
}

template<class T>
void SplayTree<T>::add(T val) {
	if (root != 0) {
			Node<T>* added = root->add(val);
			root = root->splay(root,added);
	} else {
		root = new Node<T>(val);
	}
}

template <class T>
void SplayTree<T>::remove(T val) {
	if (root != 0) {
		if (val == root->value) {
			Node<T> *succ = root->succesor();
			if (succ != 0) {
					succ->left = root->left;
					succ->right = root->right;
					succ->parent = 0;
					if(succ->left)
						succ->left->parent = succ;
					if(succ->right)
						succ->right->parent = succ;
			}
			delete root;
			root = succ;
		} else {
			Node<T>* p = root->remove(val);
			root = root->splay(root,p);
		}
	}
}

template <class T>
void SplayTree<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

template <class T>
bool SplayTree<T>::find(T val){
	if (root != 0) {
		Node<T>* found = root->find(val);
		root = root->splay(root,found);
		return (root->value == val);
	} else {
		return false;
	}
}

template <class T>
std::string SplayTree<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string SplayTree<T>::print_tree() const {
	std::stringstream aux;

	aux << "\n ================================ ";
	if (!empty()) {
		root->print_tree(aux);
	}
	aux << " ================================ \n";
	return aux.str();
}



template <class T>
std::string SplayTree<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

#endif
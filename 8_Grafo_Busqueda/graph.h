#ifndef GRAPH_H_
#define GRAPH_H_
//librerias
using namespace std;
#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

class Graph {
private:
		//limite para la lista
		int edgesList;
		//limite para la matriz
		int edgesMat;
		int nodes;
		//Creamos un vector de enteros apuntando a la lista
    	vector<int> *adjList;
		int *adjMatrix; //un arreglo de enteros
		//vector<Type> *vect = new vector<Type>

public:
		Graph(int);
		Graph();
		//Creamos una lista de listas 
		void addEdgeAdjList(int, int);
		//O creamos una matriz con los valores
		void addEdgeAdjMatrix(int, int);
		//Funciones de impresion
		string printAdjList();
		string printAdjMat();
		string printAdjMat_clean();
		//auxiliares para hacer los reccorridos 
		string DFS(int, int);
		string depthHelper(int, int, stack<int>&, list<int>&, vector<vector<int>>&);
		string BFS(int, int);
		string breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int>>&);
		string print_visited(list<int>);
		string print_path(vector<vector<int>>&,int ,int);
		//Cargar los archivos a la estructura
		bool contains(list<int>, int);
		void sortAdjList();
		void loadGraphList(string, int);
		void loadGraphMat(string, int, int);
};


void Graph::loadGraphList(string data, int a){
    adjList = new vector<int>[a];
    nodes = a;
    stringstream full_string (data);
    string pair;
    int u, v;
    //Mientras estamos leyendo todo el string
    //con los pares
    while (full_string >> pair){
        //Par de numeros (u,v)
        //Convertimos los numeros en numericos, en lugar de string
        u = pair[1]-'0';  
        v = pair[3]-'0';
        //Agregamos los numeros a la lista
        addEdgeAdjList(u, v);
    }
    //Acomodamos los numeros
    sortAdjList();
}

void Graph::loadGraphMat(string data, int a, int b){
    //Creamos una matriz
    adjMatrix = new int[a * b];
    nodes = a;
    for (int i = 0; i < a*b; i++){
        adjMatrix[i] = 0;
    }
    stringstream full_string(data);
    string pair;
    int u, v;
    while (full_string >> pair) {
        u = pair[1] - '0';
        v = pair[3] - '0';
        addEdgeAdjMatrix(u, v);
    }
}

Graph::Graph() {
	edgesList = edgesMat = 0;
}

Graph::Graph(int n) {
	nodes = n;
	//Hay apuntadores
	adjList = new vector<int>[nodes];
	adjMatrix = new int [nodes*nodes];
	for (int i = 0; i < nodes*nodes; i++)
		adjMatrix[i] = 0;
	edgesList = edgesMat = 0;
}

void Graph::addEdgeAdjList(int u, int v){
	adjList[u].push_back(v);
	adjList[v].push_back(u);
	edgesList++;
}

void Graph::addEdgeAdjMatrix(int u, int v){
	adjMatrix[u*nodes+v] = 1;
	adjMatrix[v*nodes+u] = 1;
	edgesMat++;
}

string Graph::printAdjList(){
	  stringstream aux;
		for (int i = 0; i < nodes; i++){
	        aux << "vertex "
	             << i << " :";
	        for (int j = 0; j < adjList[i].size(); j ++){
							 aux << " " << adjList[i][j];
					}
	        aux << " ";
    }
		return aux.str();

}

void Graph::sortAdjList(){
	for (int i = 0; i < nodes; i++)
		sort(adjList[i].begin(),adjList[i].end());
}

string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
	   for (int j = 0; j < nodes; j++){
			 aux << adjMatrix[i*nodes+j] << " ";
		 }
  }
	return aux.str();
}

string Graph::printAdjMat_clean(){
	stringstream aux;
	aux << "\n nodes \t|";
	for (int i = 0; i < nodes; i++){
			aux << "\t" << i ;
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
			aux << "__________";
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
		 aux << i << "\t|";
	   for (int j = 0; j < nodes; j++){
			 aux << "\t" << adjMatrix[i*nodes+j];
		 }
	   aux << "\n";
  }
	return aux.str();
}

//Depth First Search usando stack
string Graph::DFS(int start, int goal){
	//Orden en que exploro
	stack <int> st;
	//lista de visitados
	list <int> visited;
	//Camino que va recorriendo el algoritmo
	vector <vector<int>> paths(nodes, vector<int>(1,-1));
	//Guardamos en el stack el valor con el que vamos a iniciar
	st.push(start);
	//Creamos un string con la llamada de saber en que nivel estamos 
	string ans = depthHelper(start, goal, st, visited, paths);
	ans = ans + print_path(paths, start, goal);
	return ans;
}

string Graph::depthHelper(int current,
															int goal,
															stack<int> &st,
															list<int> &visited,
															vector<vector<int>> &paths){
	//Caso base
	//Si el primer valor es el que estamos buscanso
	if (current == goal){
		return print_visited(visited);
	//Si esta vacio nuestro stack 
	} else if(st.empty()){
		return "node not found";
	} else {
		//Obtenemos el primer valor en el stack
		current = st.top();
		//Vamos sacando los valores
		st.pop();
		//En la lista de visitados vamos poniendo el camino que recorre
		visited.push_back(current);
		//vamos metiendo en la lista de adjacencia
		for (int i = 0; i < adjList[current].size(); i++){
			//Si no tiene el visitado y no se encuentra en la lista e adjacencia 
			if(!contains(visited, adjList[current][i])){
				//Vamos guardando los valores en el stack
				st.push(adjList[current][i]);
				//Actualizamos los caminos recorridos.
				paths[adjList[current][i]][0] = current;
			}
		}
		//Llamada recursiva
		return depthHelper(current, goal, st, visited, paths);
	}
}

string Graph::BFS(int start, int goal){
	//Creamos el queue 
	queue <int> qu;
    //Creamo la lista de los numeros visitados
	list <int> visited;
    //Un vector de vectores con los caminos que recorre
	vector <vector<int>> paths (nodes, vector <int>(1,-1));
    //Guardamos el primer valor que vamos a recorrer en el queue
	qu.push(start);
    //Creamos un string para saber en que nivele estamos
	string ans = breadthHelper(start, goal, qu, visited, paths);
	ans = ans + print_path(paths, start, goal);
	return ans;
}

string Graph::breadthHelper(int current,
															int goal,
															queue<int> &qu,
															list<int> &visited,
                                                            vector<vector<int>> &paths){
    //Obtenemos el primer valor del queue
	current = qu.front();
    //Y lo barramos cuando ya lo sacamos
	qu.pop();
    //Lo guardamos en el vector de los valores visitados
	visited.push_back(current);
    //Caso base si es el primer valor
    if (current == goal) {
        return print_visited(visited);
    }
    //Vamos obteniendo de la lista d adjacencia
    for (int i = 0; i < adjList[current].size(); i++) {
        //Vamos guardando el valor en el siguiente
        int next = adjList[current][i];
        //Si no se enuentra el valor
        if (!contains(visited, next)) {
            //Lo que esta en el queue es falso
            bool inQueueline = false;
            //creamos un queue temporal
            queue<int> temp = qu;
            //Mentras el temporal no este vacio
            while (!temp.empty()) {
                //Vamos sacando el valor de enfrente
                if (temp.front() == next) {
                    inQueueline = true;
                    break;
                }
                //Borramos los valores del temporal
                temp.pop();
            }
            //Si no hay nada 
            if (!inQueueline) {
                //Guardamos el siguiente
                qu.push(next);
                //Vamos guardando los caminos recorridos
                paths[next][0] = current;
            }
        }
    }
    return breadthHelper(current, goal, qu, visited, paths);
}


bool Graph::contains(list<int> ls, int node){
		list<int>::iterator it;
		it = find(ls.begin(), ls.end(), node);
		if(it != ls.end())
			return true;
		else
			return false;
}

string Graph::print_visited(list<int> q){
	stringstream aux;
	aux << "visited: ";
	while (!q.empty()){
    aux << q.front() << " ";
    q.pop_front();
  }
	return aux.str();
}

//Imprime el camino mas corto
string Graph::print_path(vector<vector <int>> &path, int start, int goal){
	int node =  path[goal][0];
	stack<int> reverse;
	reverse.push(goal);
	stringstream aux;
	aux  << "path:";
	while (node != start) {
		reverse.push(node);
    node = path[node][0];
  }
	reverse.push(start);
	while (!reverse.empty()) {
		aux << " " << reverse.top() ;
		reverse.pop();
  }
	return aux.str();
}
#endif
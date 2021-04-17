#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <stdlib.h>
#include <map>
#include <concepts>
#include <cstddef>
#include <stdarg.h>
#include <cstdarg>
#include <thread>
#include <mutex>
#include <dos.h>
#include "windows.h"
#include "list"

using namespace std;

template <typename T> class Vertex {

    T value;

};


template <typename T> class Edge {

    T weight;

};

template <typename V, typename E> class GraphADT {

    virtual Vertex<V>* addVertex(V vertex) = 0;
    virtual void removeVertex(Vertex<V>* vertex) = 0;
    virtual Edge<E>* addEdge(Vertex<V>* from, Vertex<V>* to, E weight) = 0;
    virtual void removeEdge(Edge<E>* edge) = 0;
    virtual vector<Edge<E>*> edgesFrom(Vertex<V>* vertex) = 0;
    virtual vector<Edge<E>*> edgesTo(Vertex<V>* vertex) = 0;
    virtual Vertex<V>* findVertex(V value) = 0;
    virtual Edge<E>* findEdge(V from_value, V to_value) = 0;
    virtual bool hasEdge(Vertex<V>* from, Vertex<V>* to) = 0;

};


template <typename V, typename E> class AdjacencyMatrixGraph : public GraphADT<V, E>{

};



int main() {

    

    return 0;

}

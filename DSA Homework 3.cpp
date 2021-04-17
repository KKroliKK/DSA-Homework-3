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
public:
    T value;
    int index;
    Vertex<T>* previous;
    Vertex<T>* next;

    Vertex<T>() = default;

    Vertex<T>(T value) {
        this->value = value;
    }

};


template <typename T> class Edge {
public:
    T weight;

    Edge<T>* previous;
    Edge<T>* next;

    Edge<T>() = default;

    Edge<T>(T weight) {
        this->weight = weight;
    }


};

template <typename V, typename E> class GraphADT {

public:
    virtual Vertex<V>* addVertex(V value) = 0;
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

    list<Vertex<V>> vertices;
    list<Edge<E>> edges;
    vector<vector<Edge<E>*>> adjMatr;

    Vertex<V> firstVertex_ptr;
    Vertex<V> lastVertex_ptr;

    Edge<E> firstEdge_ptr;
    Edge<E> lastEdge_ptr;

    bool verticesList_isEmpty;
    bool edgesList_isEmpty;

public:

    AdjacencyMatrixGraph<V,E>(){
        
        verticesList_isEmpty = true;
        edgesList_isEmpty = true;
    }


    Vertex<V>* addVertex(V value) {
        
        if (verticesList_isEmpty == true) {
            Vertex<V>* temp = new Vertex<V>(value);
            verticesList_isEmpty = false;
            temp->previous = &firstVertex_ptr;
            temp->next = &lastVertex_ptr;
            firstVertex_ptr.next = temp;
            lastVertex_ptr.previous = temp;
        }
        else {
            Vertex<V>* temp = new Vertex<V>(value);
            temp->previous = lastVertex_ptr.previous;
            temp->next = &lastVertex_ptr;
            lastVertex_ptr.previous->next = temp;
            lastVertex_ptr.previous = temp;
        }

    };


};



int main() {

    Vertex<int> a;
    a.index = 0;
    Vertex<int> b;
    b.index = 1;

    list<Vertex<int>> kek;

    kek.push_back(a);
    kek.push_back(b);

    //kek.back().ptr = &kek.back();

    kek.pop_front();

    Vertex<int>* x = new Vertex<int>;

    x->index = 7;

    cout << x->index;

    delete(x);



    return 0;

}
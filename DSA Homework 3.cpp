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


template <typename V, typename E> class AdjacencyMatrixGraph /*: public GraphADT<V, E>*/{

    list<Vertex<V>> vertices;
    list<Edge<E>> edges;
    vector<vector<Edge<E>*>> adjMatr;

    Vertex<V> firstVertex_ptr;
    Vertex<V> lastVertex_ptr;

    vector<int> emptyIndices;

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
        
        Vertex<V>* temp = new Vertex<V>(value);

        if (verticesList_isEmpty == true) {
            verticesList_isEmpty = false;
            temp->previous = &firstVertex_ptr;
            temp->next = &lastVertex_ptr;
            firstVertex_ptr.next = temp;
            lastVertex_ptr.previous = temp;
        }
        else {
            temp->previous = lastVertex_ptr.previous;
            temp->next = &lastVertex_ptr;
            lastVertex_ptr.previous->next = temp;
            lastVertex_ptr.previous = temp;
        }

        if (emptyIndices.empty()) {
            temp->index = adjMatr.size();

            for (int i = 0; i < adjMatr.size(); ++i) {
                adjMatr[i].push_back(nullptr);
            }
            adjMatr.push_back(vector<Edge<E>*>());
            for (int i = 0; i < adjMatr.size(); ++i) {
                adjMatr[adjMatr.size() - 1].push_back(nullptr);
            }
        }
        else {
            temp->index = emptyIndices.back();
            emptyIndices.pop_back();
        }

        return temp;
    }


    Edge<E>* addEdge(Vertex<V>* from, Vertex<V>* to, E weight) {



        return NULL;
    }

};



int main() {

    AdjacencyMatrixGraph<char, int> graph;
    graph.addVertex('A');
    graph.addVertex('B');
    graph.addVertex('C');

    return 0;

}
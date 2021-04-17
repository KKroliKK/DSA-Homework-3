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

template <typename V> class Vertex {
public:
    V value;
    int index;
    Vertex<V>* previous;
    Vertex<V>* next;

    Vertex<V>() = default;

    Vertex<V>(V value) {
        this->value = value;
    }

};


template <typename V, typename E> class Edge {
public:
    E weight;

    Edge<V, E>* previous;
    Edge<V, E>* next;

    Vertex<V>* from;
    Vertex<V>* to;

    Edge<V, E>() = default;

    Edge<V, E>(E weight) {
        this->weight = weight;
    }


};

template <typename V, typename E> class GraphADT {

public:
    virtual Vertex<V>* addVertex(V value) = 0;
    virtual void removeVertex(Vertex<V>* vertex) = 0;
    virtual Edge<V, E>* addEdge(Vertex<V>* from, Vertex<V>* to, E weight) = 0;
    virtual void removeEdge(Edge<V, E>* edge) = 0;
    virtual vector<Edge<V, E>*> edgesFrom(Vertex<V>* vertex) = 0;
    virtual vector<Edge<V, E>*> edgesTo(Vertex<V>* vertex) = 0;
    virtual Vertex<V>* findVertex(V value) = 0;
    virtual Edge<V, E>* findEdge(V from_value, V to_value) = 0;
    virtual bool hasEdge(Vertex<V>* from, Vertex<V>* to) = 0;

};


template <typename V, typename E> class AdjacencyMatrixGraph /*: public GraphADT<V, E>*/{

    list<Vertex<V>> vertices;
    list<Edge<V, E>> edges;
    vector<vector<Edge<V, E>*>> adjMatr;

    Vertex<V> firstVertex_ptr;
    Vertex<V> lastVertex_ptr;

    vector<int> emptyIndices;

    Edge<V, E> firstEdge_ptr;
    Edge<V, E> lastEdge_ptr;

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
            adjMatr.push_back(vector<Edge<V, E>*>());
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


    Edge<V, E>* addEdge(Vertex<V>* from, Vertex<V>* to, E weight) {

        Edge<V, E>* temp = new Edge<V, E>(weight);

        if (edgesList_isEmpty == true) {
            edgesList_isEmpty = false;
            temp->previous = &firstEdge_ptr;
            temp->next = &lastEdge_ptr;
            firstEdge_ptr.next = temp;
            lastEdge_ptr.previous = temp;
        }
        else {
            temp->previous = lastEdge_ptr.previous;
            temp->next = &lastEdge_ptr;
            lastEdge_ptr.previous->next = temp;
            lastEdge_ptr.previous = temp;
        }

        temp->from = from;
        temp->to = to;

        adjMatr[from->index][to->index] = temp;

        return temp;

    }

};



int main() {

    AdjacencyMatrixGraph<char, int> graph;

    Vertex<char>* a = graph.addVertex('A');
    Vertex<char>* b = graph.addVertex('B');
    Vertex<char>* c = graph.addVertex('C');

    Edge<char, int>* ab = graph.addEdge(a, b, 1);

    return 0;

}
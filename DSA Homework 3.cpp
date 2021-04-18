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
    Vertex<V>* myself;

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
    Edge<V, E>* myself;

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


template <typename V, typename E> class AdjacencyMatrixGraph : public GraphADT<V, E>{
public:
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

        temp->myself = temp;

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

        temp->myself = temp;

        return temp;
    }


    void removeEdge(Edge<V, E>* edge) {

        adjMatr[edge->from->index][edge->to->index] = nullptr;

        Edge<V, E>* previous = edge->previous;
        Edge<V, E>* next = edge->next;

        previous->next = next;
        next->previous = previous;

        delete(edge);
    }

    void removeVertex(Vertex<V>* vertex) {

        Vertex<V>* previous = vertex->previous;
        Vertex<V>* next = vertex->next;

        previous->next = next;
        next->previous = previous;

        emptyIndices.push_back(vertex->index);

        int index = vertex->index;

        for (int i = 0; i < adjMatr.size(); ++i) {
            if (adjMatr[index][i] != nullptr) {
                removeEdge(adjMatr[index][i]);
                adjMatr[index][i] = nullptr;
            }
        }

        for (int i = 0; i < adjMatr.size(); ++i) {
            if (adjMatr[i][index] != nullptr) {
                removeEdge(adjMatr[i][index]);
                adjMatr[i][index] = nullptr;
            }
        }

        delete(vertex);
    }


    vector<Edge<V, E>*> edgesFrom(Vertex<V>* vertex) {
        int index = vertex->index;
        vector<Edge<V, E>*> collection;

        for (int i = 0; i < adjMatr.size(); ++i) {
            if (adjMatr[index][i] != nullptr) {
                collection.push_back(adjMatr[index][i]);
            }
        }

        return collection;
    }

    vector<Edge<V, E>*> edgesTo(Vertex<V>* vertex) {
        int index = vertex->index;
        vector<Edge<V, E>*> collection;

        for (int i = 0; i < adjMatr.size(); ++i) {
            if (adjMatr[i][index] != nullptr) {
                collection.push_back(adjMatr[i][index]);
            }
        }

        return collection;
    }


    Vertex<V>* findVertex(V value) {
        Vertex<V>* ptr = firstVertex_ptr.next;

        while (ptr != lastVertex_ptr.myself) {
            if (ptr->value == value) {
                return ptr->myself;
            }
            else {
                ptr = ptr->next;
            }
        }
        
        return nullptr;
    }


    vector<Vertex<V>*> findVertices(V value) {

        vector<Vertex<V>*> collection;

        Vertex<V>* ptr = firstVertex_ptr.next;

        while (ptr != lastVertex_ptr.myself) {
            if (ptr->value == value) {
                collection.push_back(ptr->myself);
            }
            ptr = ptr->next;
        }

        return collection;

    }

    
    bool hasEdge(Vertex<V>* from, Vertex<V>* to) {
        return adjMatr[from->index][to->index];
    }


    Edge<V, E>* findEdge(V from_value, V to_value) {
        vector<Vertex<V>*> from = findVertices(from_value);
        vector<Vertex<V>*> to = findVertices(to_value);

        for (int i = 0; i < from.size(); ++i) {
            for (int j = 0; j < to.size(); ++j) {
                if (hasEdge(from[i], to[j])) {
                    return adjMatr[from[i]->index][to[j]->index];
                }
            }
        }

        return nullptr;
    }

};


void printAdjMatrix(AdjacencyMatrixGraph<char, int>& graph) {
    for (int i = 0; i < graph.adjMatr.size(); ++i) {
        for (int j = 0; j < graph.adjMatr.size(); ++j) {
            cout << graph.adjMatr[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

template<typename T> void printVector(vector<T>& vector) {
    for (int i = 0; i < vector.size(); ++i) {
        cout << vector[i] << ' ';
    }
    cout << "\n\n";
}

//bool kek(int* a) {
//    return a;
//}

int main() {

    AdjacencyMatrixGraph<char, int> graph;

    //cout << graph.adjMatr.size() << ' ' << graph.adjMatr[graph.adjMatr.size() - 1].size() << endl;

    Vertex<char>* a = graph.addVertex('A');
    Vertex<char>* b = graph.addVertex('B');
    Vertex<char>* c = graph.addVertex('C');

    Edge<char, int>* ab = graph.addEdge(a, b, 1);
    Edge<char, int>* ba = graph.addEdge(b, a, 7);
    Edge<char, int>* ca = graph.addEdge(c, a, 2);
    Edge<char, int>* ac = graph.addEdge(a, c, 3);
    Edge<char, int>* bc = graph.addEdge(b, c, 10);
    Edge<char, int>* cb = graph.addEdge(c, b, 6);

    printAdjMatrix(graph);

    vector<Edge<char, int>*> Afrom = graph.edgesFrom(a);
    //printVector(Afrom);
    vector<Edge<char, int>*> Ato = graph.edgesTo(a);
    //printVector(Ato);

    //graph.removeVertex(a);
    cout << graph.findEdge('A', 'C')->weight << endl;
    graph.removeEdge(ac);
    cout << graph.findEdge('A', 'C') << endl;

    //graph.removeEdge(ab);
    //printAdjMatrix(graph);

    /*cout << c << "\n" << graph.findVertex('C') << "\n\n";
    cout << graph.findVertex('D') << endl;*/

    //cout << kek(nullptr) << endl;

    return 0;

}
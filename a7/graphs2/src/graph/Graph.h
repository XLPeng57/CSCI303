//
// Created by ojcch on 4/15/2020.
//

#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <string>
#include "Vertex.h"
#include "Edge.h"

using namespace std;

/*
 * Class that represents a weighted graph.
 * It implements an adjacency map of the vertices.
 * It supports directed and undirected graphs.
 * The data elements stored in the vertices must inherit from the class Object.
 */
class Graph {
private:
    //static counter used for giving a unique ID to each new vertex added to the graph;
    //the initialization of it is below the class definition
    static int vertexId;

    //vertices indexed by a hash.
    //a map {x, y} is used, where x is the hash of the vertex data, and y is the vertex itself
    unordered_map<long, Vertex *> *vertices{};

    //vertices indexed by a vertex id.
    //a map {x, y} is used, where x is the vertex id, and y is the vertex itself
    unordered_map<int, Vertex *> *verticesById{};

    //edges (v->w) for each vertex
    //a map {x, y} is used, where x is the id of v, and y is the vectors of the edges
    unordered_map<int, vector<Edge *> *> *edges{};

    //if true, the graph is undirected, otherwise it is directed
    bool undirected = true;

    //adds the edge e=(v->w) to the list of edges of vertex v
    void addEdge(Edge *e) const {
        vector<Edge *> *vEdges;
        auto iter1 = edges->find(e->getSrc()->getId());
        if (iter1 == edges->end()) {
            vEdges = new vector<Edge *>();
            edges->insert({e->getSrc()->getId(), vEdges});
        } else
            vEdges = iter1->second;
        vEdges->push_back(e);
    }

public:

    //constructor to instantiate an undirected graph
    explicit Graph() {
        Graph(true);
    }

    //constructor
    explicit Graph(bool undirected) {
        this->undirected = undirected;
        vertices = new unordered_map<long, Vertex *>();
        verticesById = new unordered_map<int, Vertex *>();
        edges = new unordered_map<int, vector<Edge *> *>();
    }

    //destructor
    ~Graph() {
        delete edges;
        delete verticesById;
        delete vertices;
    }

    //returns all vertices (indexed by id)
    unordered_map<int, Vertex *> *getVertices() {
        return this->verticesById;
    }

    //adds an edge connecting v and w: (v->w) or (v <-> w), depending on the attribute undirected
    void addEdge(Object *v, Object *w, double weight) {
        Vertex *v1 = getVertex(v, true);
        Vertex *v2 = getVertex(w, true);
        addEdge(v1, v2, weight);
    }

    //adds an edge connecting v and w (v->w) or (v <-> w), depending on the attribute undirected
    void addEdge(Vertex *v, Vertex *w, double weight) {
        addEdge(new Edge(v, w, weight));
        if (undirected) {
            addEdge(new Edge(w, v, weight));
        }
    }

    //gets the vertex by id
    Vertex *getVertex(int id) const {
        auto iter = verticesById->find(id);
        if(iter == verticesById->end()) return nullptr;
        return iter->second;
    }

    //gets the vertex of the obj (i.e., the data);
    //it inserts a new vertex in the graph only if insertVertex = true and obj is not found in the vertices
    Vertex *getVertex(Object *obj, bool insertVertex) const {
        Vertex *v1 = nullptr;
        long vHash = obj->hash();
        auto iter1 = vertices->find(vHash);
        if (iter1 == vertices->end()) {
            if (insertVertex) {
                v1 = new Vertex(vertexId++, obj);
                vertices->insert({vHash, v1});
                verticesById->insert({v1->getId(), v1});
            }
        } else
            v1 = iter1->second;
        return v1;
    }

    //returns the number of edges
    int getNumEdges() {
        return edges->size();
    }

    //returns the number of vertices
    int getNumVertices() {
        return vertices->size();
    }

    //returns the (first) edge connecting v and w (v->w)
    Edge *getEdge(Object *v, Object *w) {
        Vertex *v1 = getVertex(v, false);
        if (v1 == nullptr) return nullptr;
        Vertex *v2 = getVertex(w, false);
        if (v2 == nullptr) return nullptr;
        return getEdge(v1, v2);
    }

    //returns the (first) edge connecting v and w (v->w)
    Edge *getEdge(Vertex *v1, Vertex *v2) {
        auto iter = edges->find(v1->getId());
        if (iter != edges->end()) {
            auto vector = iter->second;
            for (Edge *e : *vector) {
                if (e->getTarget()->getId() == v2->getId()) return e;
            }
        }
        return nullptr;
    }

    //checks if there is an edge connecting v and w (v->w)
    bool isThereEdge(Object *v, Object *w) {

        Vertex *v1 = getVertex(v, false);
        if (v1 == nullptr) return false;
        Vertex *v2 = getVertex(w, false);
        if (v2 == nullptr) return false;

        auto iter = edges->find(v1->getId());
        if (iter != edges->end()) {
            auto vector = iter->second;
            for (Edge *e : *vector) {
                if (e->getTarget()->getId() == v2->getId()) return true;
            }
        }
        return false;
    }

    //finds all edges (x, y) involving  v, i.e., x = v or y = v
    vector<Edge*> *getAllEdges(Object *v) {
        vector<Edge*> *allEdg = nullptr;

        Vertex *v1 = getVertex(v, false);
        if (v1 == nullptr) return allEdg;

        allEdg = new vector<Edge *>();
        for (pair<int, vector<Edge *> *> edgeEntry:*edges) {
            vector<Edge *> *edgeVect = edgeEntry.second;
            for (Edge *edge: *edgeVect) {
                if (edge->getSrc()->getId() == v1->getId() || edge->getTarget()->getId() == v1->getId())
                    allEdg->push_back(edge);
            }

        }
        return allEdg;
    }

    //finds all outgoing edges (x, y) of vertex v, i.e., x = v
    vector<Edge*> *getOutGoingEdges(Vertex *v) {
        auto it = edges->find(v->getId());
        if (it == edges->end()) return nullptr;
        return it->second;
    }

    //finds all outgoing edges (x, y) of v (the vertex data), i.e., x = v
    vector<Edge*> *getOutGoingEdges(Object *v) {
        vector<Edge *> *allEdg = nullptr;

        Vertex *v1 = getVertex(v, false);
        if (v1 == nullptr) return allEdg;

        long hash = v1->getData()->hash();
        v1 = vertices->at(hash);

        return getOutGoingEdges(v1);
    }

    //finds all vertices that are neighbors of object v (i.e. all vertices pointing from/to v)
    unordered_set<Vertex *> *getAllNeighbors(Object *v) {
        vector<Edge *> *allEdg = getAllEdges(v);
        if (allEdg == nullptr) return nullptr;

        auto *neighbors = new unordered_set<Vertex*>();
        for (Edge *edge: *allEdg) {
            if (v->equals(edge->getSrc()->getData()))
                neighbors->insert(edge->getTarget());
            else
                neighbors->insert(edge->getSrc());
        }

        return neighbors;
    }

    //finds all vertices x that v (vertex data) points to (v->x)
    unordered_set<Vertex *> *getOutgoingNeighbors(Object *v) {
        Vertex *v1 = getVertex(v, false);
        if (v1 == nullptr) return nullptr;

        long hash = v1->getData()->hash();
        v1 = vertices->at(hash);

        vector<Edge *> *outEdges = edges->at(v1->getId());
        auto *neighbors = new unordered_set<Vertex *>();
        for (Edge *edge: *outEdges) {
            neighbors->insert(edge->getTarget());
        }

        return neighbors;
    }

    //prints the graph in the terminal
    void print() {
        for (std::pair<long, Vertex *> vertex: *vertices) {
            vector<Edge *> *vector = nullptr;

            auto iter = edges->find(vertex.second->getId());
            if (iter != edges->end()) {
                vector = iter->second;
            }

            string stringVec = "[";

            if (vector != nullptr) {
                for (Edge *edge: *vector) {

                    //format the weight with 2 decimals only
                    stringstream  sstream;
                    sstream.setf(std::ios::fixed);
                    sstream.precision(2);
                    sstream << edge->getWeight();
                    string weightStr =sstream.str();

                    stringVec.append(edge->getTarget()->toString())
                            .append(" (w:")
                            .append(weightStr)
                            .append(")").append("; ");
                }
                if (!vector->empty())
                    stringVec.erase(stringVec.end() - 2, stringVec.end());
            }

            stringVec.append("]");
            cout << vertex.second->toString() << " -> " << stringVec << endl;;
        }
    }

    //prints the vector of edges in the terminal
    static void printEdges(vector<Edge *> *edges) {
        string stringVec = "[";

        if (edges != nullptr) {
            for (Edge *edge: *edges)
                stringVec.append(edge->toString()).append("; ");
            if (!edges->empty())
                stringVec.erase(stringVec.end() - 2, stringVec.end());
        }

        stringVec.append("]");
        cout << stringVec << endl;;
    }

    //prints the set of vertices in the terminal
    static void printVertices(unordered_set<Vertex *> *vertices) {
        string stringVec = "[";

        if (vertices != nullptr) {
            for (Vertex *vertex: *vertices)
                stringVec.append(vertex->toString()).append("; ");
            if (!vertices->empty())
                stringVec.erase(stringVec.end() - 2, stringVec.end());
        }

        stringVec.append("]");
        cout << stringVec << endl;;
    }
};

//initializing the counter with zero
int Graph::vertexId = 0;

#endif //GRAPHS_GRAPH_H

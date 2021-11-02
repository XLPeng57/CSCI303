//
// Created by ojcch on 4/24/2020.
//

#ifndef GRAPHS_DIJKSTRAOUTPUT_H
#define GRAPHS_DIJKSTRAOUTPUT_H

#include <limits>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>
#include <iostream>
#include "graph/Graph.h"

/*
 * Class that represents the output of Dijsktra's algorithm, composed of:
 * 1. the distance map
 * 2. the map that stores the shortest path tree
 */
class DijkstraOutput {
private:
    //graph that this output applies to
    Graph *graph;
    //map of distances, each vertex id maps to its shortest path distance from a source vertex
    unordered_map<int, double> *dist;
    //map that stores the shortest path tree for a source vertex.
    //each vertex id maps to its parent vertex in the tree
    unordered_map<int, int> *prev;
public:

    //constructor
    DijkstraOutput(Graph *graph, unordered_map<int, double> *dist, unordered_map<int, int> *prev) {
        this->graph = graph;
        this->dist = dist;
        this->prev = prev;
    }

    //prints the output
    void print() {
        cout << "dist[]: ";
        for (auto i: *dist){
            cout << "{" << graph->getVertex(i.first)->toString() << "->" << i.second << "},";
        }
        cout << "\b";
        cout << endl;

        cout << "prev[]: ";
        for (auto i: *prev) {
            cout << "{" << graph->getVertex(i.first)->toString() << "->" << i.second << "},";
        }
        cout << "\b";
        cout << endl;
    }

    //prints the shortest path from the source vertex to targetObj
    void printShortestPath(Object *targetObj) {

        Vertex *targetVertex = graph->getVertex(targetObj, true);
        int a = dist->at(targetVertex->getId());
        int temp_id = prev->at(targetVertex->getId());
        vector<int> print;
        print.push_back(targetVertex->getId());
        while (a!=0){
            a = dist->at(temp_id);
            print.push_back(temp_id);
            temp_id = prev->at(temp_id);

        }

        reverse(print.begin(),print.end());
        for (auto x:print){
            cout << graph->getVertex(x)->toString() << "->";
        }
        cout << "\b";
        cout << "\b";
        cout << ", Total cost: " << dist->at(targetVertex->getId());
    }


    //destructor
    ~DijkstraOutput() {
        delete (dist);
        delete (prev);
    }
};


#endif //GRAPHS_DIJKSTRAOUTPUT_H

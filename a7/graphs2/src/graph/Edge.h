//
// Created by ojcch on 4/15/2020.
//

#ifndef GRAPHS_EDGE_H
#define GRAPHS_EDGE_H

#include "Vertex.h"
#include <string>
#include <sstream>

using namespace std;

/*
 * A weighted and directed edge in a graph
 */
class Edge {
private:
    Vertex *src; //source vertex
    Vertex *target; //target vertex
    double weight = -1.0; //edge weight
public:
    Edge(Vertex *src, Vertex *target, double weight) {
        this->src = src;
        this->target = target;
        this->weight = weight;
    }

    Vertex *getSrc() const {
        return src;
    }

    Vertex *getTarget() const {
        return target;
    }

    double getWeight() const {
        return weight;
    }

    string toString() {
        stringstream  sstream;
        sstream.setf(std::ios::fixed);
        sstream.precision(2);
        sstream << weight;
        string weightStr =sstream.str();
        return "{" + src->toString() + " -> " + target->toString() + ", (w:" + weightStr + ")}";
    }

};


#endif //GRAPHS_EDGE_H

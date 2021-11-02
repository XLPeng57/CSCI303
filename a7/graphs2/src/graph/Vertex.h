//
// Created by ojcch on 4/15/2020.
//

#ifndef GRAPHS_VERTEX_H
#define GRAPHS_VERTEX_H

#include <string>
#include "entity/Object.h"

/*
 * A vertex in a graph, which stores a instance of an Object's subclass as data.
 * The id of the vertex represents it uniquely in a graph.
 */
class Vertex {
private:
    int id; //id of the vertex
    Object *data; //data stored in the vertex
public:

    Vertex(const int id, Object *data) {
        this->id = id;
        this->data = data;
    }

    int getId() const {
        return id;
    }

    Object *getData() const {
        return data;
    }

    std::string toString() {
        return std::to_string(id) + "-" + data->toString();
    }

    ~Vertex() {
        delete data;
    }
};


#endif //GRAPHS_VERTEX_H

//
// Created by ojcch on 4/18/2020.
//

#ifndef GRAPHS_OBJECT_H
#define GRAPHS_OBJECT_H

#include <string>

using namespace std;

//a method for checking if the pointer prt, of type T, is an instance of type Base
template<typename Base, typename T>
inline bool instanceOf(const T *ptr) {
    return dynamic_cast<const Base *>(ptr) != nullptr;
}

/*
 * Abstract class Object, which is the base class of all other data classes used in a Graph
 */
class Object {
public:
    virtual string toString() = 0;

    virtual long hash() = 0;

    virtual bool equals(Object *obj) = 0;

    virtual ~Object() = 0;
};

Object::~Object() {}

#endif //GRAPHS_OBJECT_H

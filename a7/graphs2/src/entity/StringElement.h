#include <utility>

//
// Created by ojcch on 4/19/2020.
//

#ifndef GRAPHS_NODE_H
#define GRAPHS_NODE_H

/*
 * A generic class for an element that stores a string
 */
class StringElement : public Object {
private:
    string data;
public:

    explicit StringElement(string elem) {
        this->data = std::move(elem);
    }

    string toString() override {
        return "[" + data + "]";
    }

    bool equals(Object *obj) override {
        if (!instanceOf<StringElement>(obj)) return false;
        auto *objCity = dynamic_cast<StringElement *>(obj);
        return this->toString() == objCity->toString();
    }

    long hash() override {
        return HashFunctions::hashString(toString());
    }

};


#endif //GRAPHS_NODE_H

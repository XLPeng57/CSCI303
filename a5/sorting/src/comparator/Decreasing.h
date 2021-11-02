//
// Created by 彭湘璐 on 4/14/20.
//

#ifndef SORTING_DECREASING_H
#define SORTING_DECREASING_H

#include "Comparator.h"

class Decreasing: public Comparator<int> {

    bool lessThan(int &x, int &y) override {
        if (x > y) return true;
    }

    bool equals(int &x, int &y) override {
        return x!=y;
    }

};


#endif //SORTING_DECREASING_H

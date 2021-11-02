//
// Created by ojcch on 4/3/2020.
//

#ifndef SORTING_COORDINATEYXCOMPARATOR_H
#define SORTING_COORDINATEYXCOMPARATOR_H

#include "Comparator.h"
#include "entity/Coordinate.h"

class CoordinateYXComparator: public Comparator<Coordinate> {

    bool lessThan(Coordinate &c1, Coordinate &c2) override {
        if (c1.y < c2.y) return true;
        return c1.y == c2.y && c1.x < c2.x;
    }


    bool equals(Coordinate &c1, Coordinate &c2) override {
        return c1.equals(c2);
    }

};


#endif //SORTING_COORDINATEYXCOMPARATOR_H

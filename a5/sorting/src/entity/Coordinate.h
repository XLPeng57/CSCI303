//
// Created by ojcch on 4/3/2020.
//

#ifndef SORTING_COORDINATE_H
#define SORTING_COORDINATE_H

#include <string>

using namespace std;

class Coordinate {
public:
    int x = -1;
    int y = -1;

    Coordinate() {}

    Coordinate(int x, int y) {
        this->x = x;
        this->y = y;
    }

    /*
     * Operator < is defined or overloaded
     */
    bool operator<(Coordinate const &coor) {
        if (this->x < coor.x) return true;
        return this->x == coor.x && this->y < coor.y;
    }

    /*
     * Operator <= is defined or overloaded
     */
    bool operator<=(Coordinate const &obj) {
        return *this < obj || this->equals(obj);
    }

    bool equals(Coordinate const &obj){
        return this->x == obj.x && this->y == obj.y;
    }

    string toString() {
        return "(" + to_string(x) + ", " + to_string(y) + ")";
    }

};


#endif //SORTING_COORDINATE_H

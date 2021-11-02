//
// Created by ojcch on 4/2/2020.
//

#ifndef SORTING_COMPARATOR_H
#define SORTING_COMPARATOR_H


template<class Comparable>
class Comparator {
public:
    virtual bool lessThan(Comparable &obj1, Comparable &obj2) = 0;

    virtual bool equals(Comparable &obj1, Comparable &obj2) = 0;

    bool lessOrEqualThan(Comparable &obj1, Comparable &obj2){
        return lessThan(obj1, obj2) || equals(obj1, obj2);
    }

};


#endif //SORTING_COMPARATOR_H

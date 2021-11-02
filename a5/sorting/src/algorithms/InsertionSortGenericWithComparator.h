//
// Created by ojcch on 4/2/2020.
//

#ifndef SORTING_INSERTIONSORTGENERICWITHCOMPARATOR_H
#define SORTING_INSERTIONSORTGENERICWITHCOMPARATOR_H

#include <utility>
#include <vector>
#include "comparator/Comparator.h"

using namespace std;

/*
 * Insertion sort implementation for vectors of Comparable objects
 * Comparable is any type of object (e.g., string, int, MailingAddress, etc)
 * The sort method uses a Comparator which is used to compare two Comparable objects
 */
template <class Comparable>
class InsertionSortGenericWithComparator {
private:
    vector<Comparable> a;
public:
    explicit InsertionSortGenericWithComparator(vector<Comparable> a) {
        this->a = std::move(a);
    }

    vector<Comparable> sort(Comparator<Comparable>* comparator) {
        for (int p = 1; p < a.size(); p++) {
            Comparable tmp = a[p];
            int j = p;
            for (; (j > 0) && (comparator->lessThan(tmp, a[j - 1])); j--) {
                a[j] = a[j - 1];
            }
            a[j] = tmp;
        }
        return a;
    }

};


#endif //SORTING_INSERTIONSORTGENERICWITHCOMPARATOR_H

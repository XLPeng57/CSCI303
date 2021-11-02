//
// Created by ojcch on 4/2/2020.
//

#ifndef SORTING_INSERTIONSORTGENERIC_H
#define SORTING_INSERTIONSORTGENERIC_H

#include <utility>
#include <vector>

using namespace std;

/*
 * Insertion sort implementation for vectors of Comparable objects
 * Comparable is any type of object (e.g., string, int, MailingAddress, etc)
 * Requirement: Comparable must overload the operator <
 */
template <class Comparable>
class InsertionSortGeneric {
private:
    vector<Comparable> a;
public:
    explicit InsertionSortGeneric(vector<Comparable> a) {
        this->a = std::move(a);
    }

    vector <Comparable> sort() {
        for (int p = 1; p < a.size(); p++) {
            Comparable tmp = a[p];
            int j = p;
            for (; (j > 0) && (tmp < a[j - 1]); j--) {
                a[j] = a[j - 1];
            }
            a[j] = tmp;
        }
        return a;
    }

};


#endif //SORTING_INSERTIONSORTGENERIC_H

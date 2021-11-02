//
// Created by ojcch on 4/2/2020.
//

#ifndef SORTING_INSERTIONSORT_H
#define SORTING_INSERTIONSORT_H

#include <utility>
#include <vector>

using namespace std;

/*
 * Insertion sort implementation for integers only
 */
class InsertionSortIntegers {
private:
    vector<int> a;
public:
    explicit InsertionSortIntegers(vector<int> a) {
        this->a = std::move(a);
    }

    vector<int> sort() {
        for (int p = 1; p < a.size(); p++) {
            int tmp = a[p];
            int j = p;
            for (; (j > 0) && (tmp < a[j-1]); j--) {
                a[j] = a[j-1];
            }
            a[j] =tmp;
        }
        return a;
    }

};


#endif //SORTING_INSERTIONSORT_H

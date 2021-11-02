//
// Created by 彭湘璐 on 4/12/20.
//

#ifndef SORTING_MERGESORTGENERICWITHCOMPARATOR_H
#define SORTING_MERGESORTGENERICWITHCOMPARATOR_H


#include <utility>
#include <vector>
#include "comparator/Comparator.h"

using namespace std;


template <class Comparable>
class MergeSortGenericWithComparator {

private:
    vector<Comparable> a;
public:
    explicit MergeSortGenericWithComparator(vector<Comparable> a) {
        this->a = std::move(a);
    }

    vector<Comparable> sort(Comparator<Comparable>* comparator) {
        vector<Comparable> temp = vector<Comparable> (this->a.size());
        mergeSort(comparator, a, temp, 0, a.size() - 1);
        return temp;
    }

    void merge(Comparator<Comparable>* comparator, vector<Comparable> &a, vector<Comparable> &tmp, int leftIdx, int rightIdx, int rightEnd) {
        int leftEnd;
        int tmpPos;
        int numElements;
        leftEnd = rightIdx - 1;
        tmpPos = leftIdx;
        numElements = rightEnd - leftIdx + 1;
        while (leftIdx <= leftEnd && rightIdx <= rightEnd)
            if (comparator -> lessThan(a[leftIdx],a[rightIdx]))
                tmp[tmpPos++] = a[leftIdx++];
            else
                tmp[tmpPos++] = a[rightIdx++];

        while (leftIdx <= leftEnd)
            tmp[tmpPos++] = a[leftIdx++];

        while (rightIdx <= rightEnd)
            tmp[tmpPos++] = a[rightIdx++];

        for (int i = 0; i < numElements; ++i, --rightEnd)
            a[rightEnd] = tmp[rightEnd];
    }

    vector<Comparable> mergeSort(Comparator<Comparable>* comparator, vector<Comparable> &a, vector<Comparable> &temp, int left, int right) {
        //IMPLEMENT THE ALGORITHM HERE
        if (left < right) {
            int center;
            center = (left + right) / 2;
            mergeSort(comparator, a, temp, left, center);
            mergeSort(comparator, a, temp, center + 1, right);
            merge(comparator, a, temp, left, center + 1, right);
        }
        return temp;
    }


};


#endif //SORTING_MERGESORTGENERICWITHCOMPARATOR_H

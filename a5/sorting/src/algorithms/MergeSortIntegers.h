//
// Created by ojcch on 3/30/2020.
//

#ifndef SORTING_MERGESORT_H
#define SORTING_MERGESORT_H

#include <utility>
#include <vector>

using namespace std;

/*
 * Mergesort implementation for integers only
 */
class MergeSortIntegers {

private:
    vector<int> a;
public:

    explicit MergeSortIntegers(vector<int> a) {
        this->a = std::move(a);
    }

    vector<int> sort() {
        vector<int> temp = vector<int>(this->a.size());
        mergeSort(a, temp, 0, a.size() - 1);
        return temp;
    }

    void merge(vector<int> &a, vector<int> &tmp, int leftIdx, int rightIdx, int rightEnd) {
        int leftEnd;
        int tmpPos;
        int numElements;
        leftEnd = rightIdx - 1;
        tmpPos = leftIdx;
        numElements = rightEnd - leftIdx + 1;
        while (leftIdx <= leftEnd && rightIdx <= rightEnd)
            if (a[leftIdx] <= a[rightIdx])
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

    vector<int> mergeSort(vector<int> &a, vector<int> &temp, int left, int right) {
        //IMPLEMENT THE ALGORITHM HERE
        if (left < right) {
            int center;
            center = (left + right) / 2;
            mergeSort(a, temp, left, center);
            mergeSort(a, temp, center + 1, right);
            merge(a, temp, left, center + 1, right);
        }
        return temp;
    }


};





#endif //SORTING_MERGESORT_H

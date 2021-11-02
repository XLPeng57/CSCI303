//
// Created by 彭湘璐 on 4/13/20.
//

#ifndef SORTING_QUICKSORTGENERIC_H
#define SORTING_QUICKSORTGENERIC_H

#include <utility>
#include <vector>
#include "comparator/Comparator.h"

using namespace std;

template <class Comparable>
class QuickSortGeneric {

private:
    vector<Comparable> a;
public:
    explicit QuickSortGeneric(vector<Comparable> a) {
        this->a = std::move(a);
    }

    vector<Comparable> sort() {
        vector<Comparable>temp = vector<Comparable>(this->a.size());
        Quicksort(a, temp ,0, a.size() - 1);
        return temp;
    }

    static Comparable median3(vector<Comparable> &a, int left, int right){
        int center = (left+right)/2;
        if(a[center]<a[left])
            std::swap(a[left],a[center]);
        if(a[right]<a[left])
            std::swap(a[left],a[right]);
        if(a[right]<a[center])
            std::swap(a[center],a[right]);
        std::swap(a[center],a[right-1]);
        return a[right-1];
    }

    vector<Comparable> Quicksort(vector<Comparable> &a,vector<Comparable> &temp, int left, int right) {

        Comparable pivot = median3(a, left, right);
        int i = left;
        int j = right;
        Comparable tmp;
        while (i <= j)
        {
            while (a[i]<pivot)
                i++;
            while (!(a[j]<=pivot))
                j--;
            if (i <= j)
            {
                tmp= a[i];
                a[i] = a[j];
                a[j] = tmp;
                i++;
                j--;
            }
        }
        if (j > left)
            Quicksort(a,temp, left, j);
        if (i < right)
            Quicksort(a,temp, i, right);
        for (int i =0; i <a.size();i++){
            temp[i] = a[i];
        }
        return a;
    }
};





#endif //SORTING_QUICKSORTGENERIC_H

//
// Created by 彭湘璐 on 4/13/20.
//

#ifndef SORTING_QUICKSORTGENERICWITHCOMPARATOR_H
#define SORTING_QUICKSORTGENERICWITHCOMPARATOR_H

//
// Created by 彭湘璐 on 4/13/20.
//


#include <utility>
#include <vector>
#include "comparator/Comparator.h"

using namespace std;

template <class Comparable>
class QuickSortGenericWithComparator {

private:
    vector<Comparable> a;
public:
    explicit QuickSortGenericWithComparator(vector<Comparable> a) {
        this->a = std::move(a);
    }

    vector<Comparable> sort(Comparator<Comparable>* comparator) {
        vector<Comparable>temp = vector<Comparable>(this->a.size());
        Quicksort(comparator, a, temp ,0, a.size() - 1);
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

    vector<Comparable> Quicksort(Comparator<Comparable>* comparator, vector<Comparable> &a,vector<Comparable> &temp, int left, int right) {

        Comparable pivot = median3( a, left, right );
        int i = left;
        int j = right;
        Comparable tmp;
        while (i <= j)
        {
            while (comparator -> lessThan(a[i], pivot))
                i++;
            while (comparator -> lessThan(pivot, a[j]))
                j--;
            //while (a[i].x<pivot)
            //i++;
            //while (a[j].x>pivot)
            //j--;
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
            Quicksort(comparator, a,temp, left, j);
        if (i < right)
            Quicksort(comparator, a,temp, i, right);
        for (int i =0; i <a.size();i++){
            temp[i] = a[i];
        }
        return a;
    }
};


#endif //SORTING_QUICKSORTGENERICWITHCOMPARATOR_H

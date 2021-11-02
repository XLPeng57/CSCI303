////
//// Created by 彭湘璐 on 4/12/20.
////

#ifndef SORTING_QUICKSORTINTEGERS_H
#define SORTING_QUICKSORTINTEGERS_H

#include <utility>
#include <vector>

using namespace std;

class QuickSortIntegers {

private:
    vector<int> a;
public:
    explicit QuickSortIntegers(vector<int> a) {
        this->a = std::move(a);
    }

    vector<int> sort() {
        vector<int> temp = vector<int>(this->a.size());
        Quicksort(a, temp ,0, a.size() - 1);
        return temp;
    }

    static int median3(vector<int> a, int left, int right){
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

    vector<int> Quicksort(vector<int> &a,vector<int> &temp, int left, int right) {

        int pivot = median3( a, left, right );
        int i = left;
        int j = right;
        int tmp;
        while (i <= j)
        {
            while (a[i] < pivot)
                i++;
            while (a[j] > pivot)
                j--;
            if (i <= j)
            {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
                i++;
                j--;
            }
        }
        if (j > left)
            Quicksort(a, temp, left, j);
        if (i < right)
            Quicksort(a,temp, i, right);
        for (int i =0; i <a.size();i++){
            temp[i] = a[i];
        }
        return a;
    }
};


#endif //SORTING_QUICKSORTINTEGERS_H
//
//
//#endif //SORTING_QUICKSORTINTEGERS_H
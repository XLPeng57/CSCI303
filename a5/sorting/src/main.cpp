#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "entity/Coordinate.h"
#include "algorithms/InsertionSortIntegers.h"
#include "algorithms/InsertionSortGeneric.h"
#include "algorithms/InsertionSortGenericWithComparator.h"
#include "algorithms/MergeSortIntegers.h"
#include "algorithms/MergeSortGeneric.h"
#include "algorithms/MergeSortGenericWithComparator.h"
#include "utilities/ArrayUtilities.h"
#include "comparator/CoordinateYXComparator.h"
#include "algorithms/QuickSortIntegers.h"
#include "algorithms/QuickSortGeneric.h"
#include "algorithms/QuickSortGenericWithComparator.h"
#include "comparator/Decreasing.h"
#include "comparator/Addr.h"
#include "entity/MailingAddress.h"


using namespace std;

void insertionSortExample(vector<int> unsortedIntArray, vector<Coordinate> unsortedCoordinates);

int main() {

    vector<int> unsortedIntArray{42, 6, 1, 56, 54, 0, 7};
    vector<Coordinate> unsortedCoordinates{Coordinate(3, 3), Coordinate(3, 1), Coordinate(2, 1),
                                           Coordinate(3, 0), Coordinate(2, 3)};
    //insertionSortExample(unsortedIntArray, unsortedCoordinates);

    vector<int> result = MergeSortIntegers(unsortedIntArray).sort();
    cout << "Sorted int array: ";
    ArrayUtilities<int>::printArray(result);


    //----------------
    //numbers
    string filePath = "/Users/xl_peng/Desktop/repo_xpeng04/a5/sorting/data/numbers.txt";
    auto File = filePath;
    std::ifstream in(File);
    string line;
    vector<int> numbers;
    if (in.is_open()) {
        while (getline(in, line)) {

            numbers.push_back(std::stoi(line));
        }
        in.close();
    }
    else{
        cout << "unable to open file";
    }

    //Merge sort
    vector<int> sortedInt_merge = MergeSortIntegers(numbers).sort();
    cout << "Unsorted int array: ";
    ArrayUtilities<int>::printArray(numbers);
    cout << "sorted int numbers by merge sort: ";
    ArrayUtilities<int>::printArray(sortedInt_merge);

    //Quick sort
    vector<int> sortedInt_quick = QuickSortIntegers(numbers).sort();
    cout << "sorted int numbers by quick sort: ";
    ArrayUtilities<int>::printArray(sortedInt_quick);

    //Merge sort in descending order
    MergeSortGenericWithComparator<int> numbers_2 = MergeSortGenericWithComparator<int>(
            numbers);
    Comparator<int> *numbers_de_2 = new Decreasing();
    vector<int> numbers_decresasing_2 = numbers_2.sort(numbers_de_2);
    cout << "Sorted int by merge sort in descending order: ";
    ArrayUtilities<int>::printArray(numbers_decresasing_2);


    //----------------
    //coordinates
    string filePath_2 = "/Users/xl_peng/Desktop/repo_xpeng04/a5/sorting/data/coordinates.txt";
    fstream newfile_2;
    newfile_2.open(filePath_2, ios::in);
    ifstream in_2(filePath_2);
    string line_2;
    vector<Coordinate> Coordinates;
    if (in_2.is_open()) {
        while (getline(in_2, line_2)) {
            string token;
            stringstream ss(line_2);
            vector<string> temp;
            while (getline(ss, token, ',')) {
                temp.push_back(token);
            }
            Coordinate tmp(stoi(temp[0]),stoi(temp[1])) ;
            Coordinates.push_back(tmp);
        }
    }

    // Merge Sort (x,y)
    vector<Coordinate> sortedCoo = MergeSortGeneric<Coordinate>(Coordinates).sort();
    cout << "Unsorted coordinates: ";
    ArrayUtilities<Coordinate>::printArray(Coordinates);
    cout << "sorted cooordinates by merge sort: ";
    ArrayUtilities<Coordinate>::printArray(sortedCoo);

    // Quick Sort (x,y)
    vector<Coordinate> sortedCoo_2 = QuickSortGeneric<Coordinate>(Coordinates).sort();
    cout << "sorted cooordinates by quick sort: ";
    ArrayUtilities<Coordinate>::printArray(sortedCoo_2);

    // Merge sort (y,x)
    MergeSortGenericWithComparator<Coordinate> algorithm_merge_2 = MergeSortGenericWithComparator<Coordinate>(
            Coordinates);
    Comparator<Coordinate> *comparator_merge_2 = new CoordinateYXComparator();
    vector<Coordinate> sortedCoordinates2_merge_2 = algorithm_merge_2.sort(comparator_merge_2);
    cout << "Sorted coordinates (first by y, and then by x) by merge sort: ";
    ArrayUtilities<Coordinate>::printArray(sortedCoordinates2_merge_2);


    //----------------
    //Mailing Address
    string filePath_3 = "/Users/xl_peng/Desktop/repo_xpeng04/a5/sorting/data/addresses.txt";
    fstream newfile_3;
    newfile_3.open(filePath_3, ios::in);
    ifstream in_3(filePath_3);
    string line_3;
    vector<MailingAddress> MailingAddr;
    if (in_3.is_open()) {
        while (getline(in_3, line_3)) {
            string token;
            stringstream ss(line_3);
            vector<string> temp;
            while (getline(ss, token, ',')) {
                temp.push_back(token);
            }
            MailingAddress tmp(temp[0],(temp[1]),(temp[2]),stoi(temp[3]));
            MailingAddr.push_back(tmp);
        }
    }

    // Quick Sort
    vector<MailingAddress> sorted_MA = QuickSortGeneric<MailingAddress>(MailingAddr).sort();
    //cout << "Unsorted MailingAddress: ";
    //ArrayUtilities<MailingAddress>::printArray(MailingAddr);
    cout << "sorted MailingAddress by quick sort: ";
    ArrayUtilities<MailingAddress>::printArray(sorted_MA);

    // Quick Sort by state
    QuickSortGenericWithComparator<MailingAddress> sorted_MA_2 = QuickSortGenericWithComparator<MailingAddress>(
            MailingAddr);
    Comparator<MailingAddress> *MA_bystate = new Addr();
    vector<MailingAddress> MA_sorted = sorted_MA_2.sort(MA_bystate);
    cout << "Sorted MailingAddress in By-state order: ";
    ArrayUtilities<MailingAddress>::printArray(MA_sorted);

    return 0;
}

//void insertionSortExample(vector<int> unsortedIntArray, vector<Coordinate> unsortedCoordinates){
//
//    //Sorting an integer array with insertion sort
//
//    vector<int> sortedIntArray = QuickSortIntegers(unsortedIntArray).sort();
//
//    cout << "Unsorted int array: ";
//    ArrayUtilities<int>::printArray(unsortedIntArray);
//
//    cout << "Sorted int array: haha";
//    ArrayUtilities<int>::printArray(sortedIntArray);
//
//    //--------------------------------------------------
//
//    //Sorting an array of coordinates with in insertion sort.
//    //The sorting is first by the x of the coordinates and then by the y part
//    //In other words, (x1, y1) goes before (x2, y2) if (x1 < x2) or (x1 == x2 && y1 < y2)
//
//    vector<Coordinate> sortedCoordinates = InsertionSortGeneric<Coordinate>(unsortedCoordinates).sort();
//    vector<Coordinate> sortedCoordinates_quick = QuickSortGeneric<Coordinate>(unsortedCoordinates).sort();
//    vector<Coordinate> sortedCoordinates_merge = MergeSortGeneric<Coordinate>(unsortedCoordinates).sort();
//
//    cout << "Unsorted coordinates: ";
//    ArrayUtilities<Coordinate>::printArray(unsortedCoordinates);
//
//    cout << "Sorted coordinates (first by x, and then by y) by quick sort: ";
//    ArrayUtilities<Coordinate>::printArray(sortedCoordinates_quick);
//
//    cout << "Unsorted coordinates: ";
//    ArrayUtilities<Coordinate>::printArray(unsortedCoordinates);
//
//    cout << "Sorted coordinates (first by x, and then by y) by merge sort: ";
//    ArrayUtilities<Coordinate>::printArray(sortedCoordinates_merge);
//
//
//    //--------------------------------------------------
//
//    //Sorting an array of coordinates with in insertion sort
//    //In this case, the order of coordinates is different:
//    //The sorting is first by the y of the coordinates and then by the x part
//    //(x1, y1) goes before (x2, y2) if (y1 < y2) or (y1 == y2 && x1 < x2)
//
////    InsertionSortGenericWithComparator<Coordinate> algorithm = InsertionSortGenericWithComparator<Coordinate>(
////            unsortedCoordinates);
////    Comparator<Coordinate> *comparator = new CoordinateYXComparator();
////    vector<Coordinate> sortedCoordinates2 = algorithm.sort(comparator);
////
////
////    cout << "Sorted coordinates (first by y, and then by x): ";
////    ArrayUtilities<Coordinate>::printArray(sortedCoordinates2);
//
//    MergeSortGenericWithComparator<Coordinate> algorithm_merge = MergeSortGenericWithComparator<Coordinate>(
//            unsortedCoordinates);
//    Comparator<Coordinate> *comparator_merge = new CoordinateYXComparator();
//    vector<Coordinate> sortedCoordinates2_merge = algorithm_merge.sort(comparator_merge);
//
//    cout << "Sorted coordinates (first by y, and then by x) by merge sort: ";
//    ArrayUtilities<Coordinate>::printArray(sortedCoordinates2_merge);
//
//
//    QuickSortGenericWithComparator<Coordinate> algorithm_quick = QuickSortGenericWithComparator<Coordinate>(
//            unsortedCoordinates);
//    Comparator<Coordinate> *comparator_quick = new CoordinateYXComparator();
//    vector<Coordinate> sortedCoordinates2_quick = algorithm_quick.sort(comparator_quick);
//
//    cout << "Sorted coordinates (first by y, and then by x) by quick sort: ";
//    ArrayUtilities<Coordinate>::printArray(sortedCoordinates2_quick);
//
//
//    MergeSortGenericWithComparator<int> numbers = MergeSortGenericWithComparator<int>(
//            unsortedIntArray);
//    Comparator<int> *numbers_de = new Decreasing();
//    vector<int> numbers_decresasing = numbers.sort(numbers_de);
//
//    cout << "Sorted int in descending order: ";
//    ArrayUtilities<int>::printArray(numbers_decresasing);
//}

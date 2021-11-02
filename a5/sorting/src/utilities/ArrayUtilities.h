//
// Created by ojcch on 4/2/2020.
//

#ifndef SORTING_ARRAYUTILITIES_H
#define SORTING_ARRAYUTILITIES_H

#include <string>
#include <entity/MailingAddress.h>

using namespace std;

template <class Object>
class ArrayUtilities {
public:
    static void printArray(vector<Object> &a) {
        string str = "[";
        for (Object item  : a) {
            str.append(toString(item));
            str.append(", ");
        }

        if (!a.empty()) {
            str.erase(str.end() - 2, str.end());
        }
        str.append("]");
        cout << str << endl;
    }

    static string toString(string& item){
        return item;
    }

    static string toString(int& item){
        return to_string(item);
    }

    static string toString(MailingAddress& item){
        return item.toString();
    }

    static string toString(Coordinate& item){
        return item.toString();
    }
};


#endif //SORTING_ARRAYUTILITIES_H

//
// Created by ojcch on 3/23/2020.
//

#ifndef HASHING_HASHFUNCTIONS_H
#define HASHING_HASHFUNCTIONS_H

/*
 * A set of hash functions
 */
class HashFunctions {
public:

    static const int M = 8191;
    static const int R = 31;

    static long long universalHashInt(int k, int a, int b, int p, int M) {
        int y = a * k + b;
        long long r = y % p;
        return r % M;
    }

    static long long universalHashIntEfficient(int k, int a, int b, int M, int i) {
        int p = (1 << i) - 1;
        int y = a * k + b;

        int quotient = y >> i;
        int reminder = y & p;
        int r = quotient + reminder;
        if (r >= p) r -= p; //this scaling is required
        return r % M;
    }

    static long hashString(const string &s) {
        unsigned long hash = 0;
        for (char w : s) {
            hash = (R * hash + w) % M;
        }
        return hash;
    }

    static long hashInt(int i) {
        return i % M;
    }
};


#endif //HASHING_HASHFUNCTIONS_H

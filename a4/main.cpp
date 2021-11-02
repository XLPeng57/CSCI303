#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
using namespace std;

class MailingAddress{

public:
    string street;
    string city;
    string state;
    int zipcode;
    string toString();
    bool equals(MailingAddress addr);
    MailingAddress(string line);
};

string MailingAddress::toString(){
    string zip = std::to_string(zipcode);
    auto string_formatted = '{' + street + ", " + city + ", " + state + ", " + zip + '}';
    return string_formatted;
}

bool MailingAddress::equals(MailingAddress addr){
    return this->toString() == addr.toString();
}

MailingAddress::MailingAddress(string line) {

    stringstream ss(line);
    string token;
    vector<string> temp;

    while (getline(ss, token, ',')) {
        temp.push_back(token);
    }
    street = temp[0];
    city = temp[1];
    state = temp[2];
    string zip = temp[3];

    zipcode = std::stoi(temp[3]);

}

class MAHashTable{


public:

    static const int M = 91;
    static const int R = 31;
    vector<MailingAddress> table[M];
    MAHashTable(){
        vector<MailingAddress> table[M];
    }
    static long hashInt(int i);
    static long hashString(string s);
    static long hashAddress(MailingAddress addr);
    void insert(MailingAddress addr);
    void print();
    bool contains(MailingAddress addr);
};


const int MAHashTable:: M;
const int MAHashTable:: R;


long MAHashTable::hashInt(int i){
    return i % M;
}

/* A ​static ​method called ​hashString ​that receives a string ​s and returns a ​long number.
 * The method should return the hash of the string using the hash function h(ci) = (R * h(ci−1) + ci) % M ,
 * where ci is the i-th character of ​s and h(c1) = c1 % M (​M and R are defined above).
 * The method should iterate over each character of the string to compute the overall string hash, i.e., h(s) = ∑i h(ci )*/

long MAHashTable::hashString(string s){

    unsigned long hash = 0;
    int temp = 0;
    int function;
    for (char c : s){
        if (temp ==0){
            int hashint = hashInt(c);
            temp = hashint;
            hash = function;
            temp++;
        }else{
            function = (R * function + c) % M;
            hash = hash + function;
        }
    }
    return hash;
}

long MAHashTable::hashAddress(MailingAddress addr){
    long int hash;
    hash = (((((hashString(addr.street) * R + hashString(addr.city)) % M) * R + hashString(addr.state)) % M) * R + hashInt(addr.zipcode)) % M;
    return hash;

}

void MAHashTable::insert(MailingAddress addr){

    int hash = hashAddress(addr);
    table[hash].push_back(addr);
}


void MAHashTable::print(){

    for (int i = 0; i < M; i++) {
        cout << i << "->";
        if ((table[i].empty())) {
            cout << "[]" << endl;
        }else{
            cout << "[";
            string print = "";
            for (auto it: table[i]) {
                print = print + it.toString() + ";";
            }
            print.pop_back();
            cout << print;
            cout<< "]" << endl;
        }
    }
}

bool MAHashTable::contains(MailingAddress addr){
    int temp = 0;
    for (int i = 0; i < M; i++) {
        for (auto it: table[i]) {
            if(it.equals(addr))
                temp++;
        }
    }
    if (temp >= 1){
        //cout << "1";
        return true;

    }else{
        //cout << "2";
        return false;

    }
}

int main(int argc, char *argv[]){
    auto file = argv[1];
    string s(file);
    //auto myFile = "/Users/xl_peng/Desktop/oscarch/hashing/addresses.txt";
    std::ifstream in(file);
    std::string line;
    MAHashTable Test;
    if (in.is_open()) {
        while (getline(in, line)) {
            MailingAddress test(line);
            Test.insert(test);
        }
        in.close();
    }else{
        cout << "Unable to open file";
    }

    Test.print();
    MailingAddress test_1("450 Highland Ave,Salem,MA,1970");
    cout << "Test result for \"450 Highland Ave,Salem,MA,1970\": "<< Test.contains(test_1) << endl;
    MailingAddress test_2("450 Highland Avenue,Salem,MA,1970");
    cout << "Test result for \"450 Highland Avenue,Salem,MA,1970\": "<< Test.contains(test_2) <<endl;
    return 0;
}
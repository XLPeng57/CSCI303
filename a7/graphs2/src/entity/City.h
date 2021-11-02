//
// Created by ojcch on 4/18/2020.
//

#ifndef GRAPHS_CITY_H
#define GRAPHS_CITY_H

#include "Object.h"
#include <iostream>
#include <utility>
#include "graph/HashFunctions.h"

/*
 * A class that represents a City
 */
class City : public Object {
private:
    string *cityName = nullptr;
    string *country = nullptr;
public:
    explicit City(string cityName){
        this->cityName = new string(std::move(cityName));
        this->country = new string("USA");
    }

    City(string cityName, string country) {
        this->cityName = new string(std::move(cityName));
        this->country = new string(std::move(country));
    }

    string *getCityName() const {
        return cityName;
    }

    string *getCountry() const {
        return country;
    }

    string toString() override {
        return "{" + *cityName + ", " + *country + "}";
    }


    bool equals(Object *obj) override {
        bool b = instanceOf<City>(obj);
        if (!b) return false;
        City *objCity = dynamic_cast<City *>(obj);
        return this->toString() == objCity->toString();
    }

    long hash() override {
        return HashFunctions::hashString(toString());
    }

    ~City() override {
        delete cityName;
        delete country;
    }

};


#endif //GRAPHS_CITY_H

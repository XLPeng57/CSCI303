//
// Created by ojcch on 2/20/2020.
//

#ifndef MAILINGADDRESS_H
#define MAILINGADDRESS_H

#include <string>
#include <utility>

using namespace std;

class MailingAddress {
private:
    string street;
    string city;
    string state;
    int zipCode = -1;

public:
    MailingAddress() {
    }

    MailingAddress(string street, string city, string state, int zipCode) {
        this->street = std::move(street);
        this->city = std::move(city);
        this->state = std::move(state);
        this->zipCode = zipCode;
    }

    bool equals(const MailingAddress &a) {
        if (this->street != a.street) return false;
        if (this->city != a.city) return false;
        if (this->state != a.state) return false;
        return zipCode == a.zipCode;
    }


    bool operator<(const MailingAddress &a) {
        if (this->street < a.street) return true;
        if (this->street == a.street && this->city < a.city) return true;
        if (this->street == a.street && this->city == a.city && this->state < a.state) return true;
        if (this->street == a.street && this->city == a.city && this->state < a.state) return true;
        if (this->street == a.street && this->city == a.city && this->state == a.state && this->zipCode < a.zipCode) return true;
    }

    bool operator<=(const MailingAddress &a) {
        return *this < a || this->equals(a);
    }

    string toString() {
        string str = "{";
        str.append(street).append(", ").append(city).append(", ").append(state).append(", ").append(
                to_string(zipCode)).append("}");
        return str;
    }

   const string &getStreet() const {
        return street;
    }

    const string &getCity() const {
        return city;
    }

    const string &getState() const {
        return state;
    }

    int getZipCode() const {
        return zipCode;
    }



};

#endif //MAILINGADDRESS_H

//
// Created by 彭湘璐 on 4/14/20.
//

#ifndef SORTING_ADDR_H
#define SORTING_ADDR_H

#include "Comparator.h"
#include "entity/MailingAddress.h"

class Addr: public Comparator<MailingAddress> {

    bool lessThan(MailingAddress &x, MailingAddress &y) override {
        if (x.getState() < y.getState()) return true;
        if (x.getState() == y.getState() && x.getCity() < y.getCity()) return true;
        if (x.getState() == y.getState() && x.getCity() == y.getCity() && x.getZipCode() < y.getZipCode()) return true;
        if (x.getState() == y.getState() && x.getCity() == y.getCity()
        && x.getZipCode() == y.getZipCode() && x.getStreet() < y.getStreet() ) return true;
    }

    bool equals(MailingAddress &x, MailingAddress &y) override {
        if (x.getStreet() != y.getStreet()) return false;
        if (x.getCity() != y.getStreet()) return false;
        if (x.getState() != y.getState()) return false;
        return x.getZipCode() == y.getZipCode();
    }

};



#endif //SORTING_ADDR_H

//
//  portfolio.cpp
//  HandIn1
//
//  Created by Mikkel Larsen on 13/09/2020.
//  Copyright © 2020 Mikkel Larsen. All rights reserved.
//

#include "portfolio.hpp"
#include <iostream>

Portfolio::Portfolio(const std::vector<ClosedformOption*>& options) : w(options.size(), 1) {
    for (auto& i : options)
        optionsVector.push_back(i->clone());
}

Portfolio::Portfolio(const std::vector<ClosedformOption*>& options, const std::vector<int>& weights) : w(weights) {
    for (auto& i : options){
        optionsVector.push_back(i->clone());
    }
}

Portfolio::~Portfolio() {
    for (auto i : optionsVector)
        delete i;
    optionsVector.clear();
}

double Portfolio::getPrice() const {
    double sum = 0;
    for (size_t i = 0; i != w.size(); ++i) {
        sum += optionsVector[i]->getPrice() * w[i];
    }
    return sum;
}

void Portfolio::addClaim(ClosedformOption& add, int nbr) {
    optionsVector.push_back(add.clone());
    w.push_back(nbr);
}

void Portfolio::removeClaim(unsigned removeNbr){
    optionsVector.erase(optionsVector.end() - ( ( optionsVector.size() - removeNbr ) + 1 ));
    w.erase(w.end() - ( (w.size() - removeNbr ) + 1 ) );
}


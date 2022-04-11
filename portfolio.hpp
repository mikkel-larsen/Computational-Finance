//
//  portfolio.hpp
//  HandIn1
//
//  Created by Mikkel Larsen on 13/09/2020.
//  Copyright © 2020 Mikkel Larsen. All rights reserved.
//

#ifndef portfolio_hpp
#define portfolio_hpp

#include <stdio.h>
#include <vector>
#include "CEVCallOption.hpp"

class Portfolio {
public:
    Portfolio() = default;
    Portfolio(const std::vector<ClosedformOption*>& options);
    Portfolio(const std::vector<ClosedformOption*>& options, const std::vector<int>& weights);
    ~Portfolio();
    double getPrice() const ;
    void addClaim(ClosedformOption& add, int nbr = 1);
    void removeClaim(unsigned removeNbr);
private:
    unsigned dim;
    std::vector<ClosedformOption*> optionsVector;
    std::vector<int> w;
};

#endif /* portfolio_hpp */

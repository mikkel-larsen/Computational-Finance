//
//  CallOption.cpp
//  HandIn1
//
//  Created by Mikkel Larsen on 09/09/2020.
//  Copyright © 2020 Mikkel Larsen. All rights reserved.
//

#include "CallOption.hpp"

CallOption::CallOption(double strike_, double expiry_) : strike(strike_), expiry(expiry_) {}

double CallOption::getExpiry() const {
    return expiry;
}

double CallOption::getStrike() const {
    return strike;
}

double CallOption::payoff(double spot) const {
    return (spot - strike > 0 ? spot - strike : 0);
}


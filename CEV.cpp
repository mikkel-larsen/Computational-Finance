//
//  CEV.cpp
//  HandIn1
//
//  Created by Mikkel Larsen on 09/09/2020.
//  Copyright © 2020 Mikkel Larsen. All rights reserved.
//

#include "CEV.hpp"
#include <cmath>

CEV::CEV(double spot_, double lambda_, double beta_) : spot(spot_), lambda(lambda_), beta(beta_) {}

double CEV::getVolatility() const {
    return lambda;
}

double CEV::getElasticity() const {
    return beta;
}

double CEV::getSpot() const {
    return spot;
}

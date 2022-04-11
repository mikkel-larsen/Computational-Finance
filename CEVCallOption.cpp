//
//  CEVCallOption.cpp
//  HandIn1
//
//  Created by Mikkel Larsen on 09/09/2020.
//  Copyright © 2020 Mikkel Larsen. All rights reserved.
//

#include "CEVCallOption.hpp"
#include "CEVprice.hpp"

CEVCallOption::CEVCallOption(const CEV& cevObj_, const CallOption& callObj_) : cevObj(cevObj_), callObj(callObj_) {}

double CEVCallOption::getPrice() const {
    return CEVprice(cevObj, callObj);
}

ClosedformOption* CEVCallOption::clone() const {
    //return std::make_unique<CEVCallOption>(*this);
    
    CEVCallOption* ret;
    ret = new CEVCallOption(*this);
    return ret;
     
}

GammaModel::GammaModel(double alpha_, double beta_) : alpha(alpha_), beta(beta_) {}

double GammaModel::getAlpha() const {
    return alpha;
}

double GammaModel::getBeta() const {
    return beta;
}

GammaCallOption::GammaCallOption(double strike_, double alpha_, double beta_) :
strike(strike_), alpha(alpha_), beta(beta_) {}

GammaCallOption::GammaCallOption(double strike_, const GammaModel& gamObj) :
strike(strike_), alpha(gamObj.getAlpha()), beta(gamObj.getBeta()) {}

ClosedformOption* GammaCallOption::clone() const {
    //return std::make_unique<GammaCallOption>(*this);
    return new GammaCallOption(*this);
}

double GammaCallOption::getPayoff(double spot) const {
    return (spot > strike ? spot - strike : 0);
}

double GammaCallOption::getPrice() const {
    return gammaPrice(strike, alpha, beta);
}



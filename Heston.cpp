//
//  Heston.cpp
//  HandIn1
//
//  Created by Mikkel Larsen on 13/09/2020.
//  Copyright © 2020 Mikkel Larsen. All rights reserved.
//

#include "Heston.hpp"
#include <iostream>

Heston::Heston(double spot_, double rate_, double kappa_, double theta_, double sigma_, double sigma0_, double rho_) :
spot(spot_), rate(rate_), kappa(kappa_), theta(theta_), sigma(sigma_), sigma0(sigma0_), rho(rho_) {}

double Heston::genPath(std::vector<double> &n, unsigned int T) const {
    double s = spot;
    unsigned size = (int)n.size();
    double dt = 2*T/(double)size;
    double v = sigma0;
    for (int i = 0; i != size/2; ++i) {
        s += s*rate*dt + s*sqrt(max0(v)*dt)*n[i];
        v += kappa*(theta-max0(v))*dt + sigma*sqrt(max0(v)*dt)*(n[i]*rho+sqrt(1-pow(rho, 2))*n[i+size/2]);
    }
    return s;
}

double Heston::getRate() const {
    return rate;
}

double monteCarlo(Heston& heston, CallOption& call, RndDevice& rndDevice, unsigned steps, unsigned paths){
    double payoff = 0;
    std::vector<double> n(steps*2, 0);
    for (int i = 0; i != paths; ++i) {
        rndDevice.genNormal(n);
        payoff += fmax(heston.genPath(n, call.getExpiry()) - call.getStrike(), 0);
    }
    return exp(-heston.getRate()*call.getExpiry()) * payoff / (double)paths;
}

//
//  Heston.hpp
//  HandIn1
//
//  Created by Mikkel Larsen on 13/09/2020.
//  Copyright © 2020 Mikkel Larsen. All rights reserved.
//

#ifndef Heston_hpp
#define Heston_hpp

#include <stdio.h>
#include <vector>
#include <cmath>
#include <random>
#include "CallOption.hpp"
#include "MSRNG.hpp"

class Heston {
public:
    Heston(double, double, double, double, double, double, double);
    double genPath(std::vector<double>& n, unsigned T) const;
    double getRate() const;
private:
    const double spot, rate, kappa, theta, sigma, sigma0, rho;
    double max0(double x) const {return ((x>0) ? x : 0);} //Implicitly inline when defined directly in class
};

double monteCarlo(Heston&, CallOption&, RndDevice&, unsigned steps, unsigned paths);

#endif /* Heston_hpp */

//
//  RandomNumber.cpp
//  HandIn1
//
//  Created by Mikkel Larsen on 06/09/2020.
//  Copyright © 2020 Mikkel Larsen. All rights reserved.
//

#include "RandomNumber.hpp"

void setSeed(unsigned i){
    minstdrand.seed(i);
}

double createUniform() {
    return minstdrand() / (double) minstdrand.max();
}

double normInv(double p){
    double y = p - 0.5;
    double x = 0;
    if (abs(y)<0.42) {
        double r = y*y;
        x = y*(((a3*r+a2)*r+a1)*r+a0)/((((b3*r+b2)*r+b1)*r+b0)*r+1);
    } else {
        double r = p;
        if (y>0)
            r = 1-p;
        r = log(-log(r));
        x = c0+r*(c1+r*(c2+r*(c3+r*(c4+r*(c5+r*(c6+r*(c7+r*c8)))))));
        if (y<0)
            x = -x;
    }
    return x;
}

double genNormal(){
    return normInv(createUniform());
}

double genNormal(double m, double var){
    return genNormal() * sqrt(var) + m;
}
void genNormal(std::vector<double> &v){
    for ( auto &i : v ){
        i = genNormal();
    }
}
/*
double monteCarlo(Heston& heston, CallOption& call, std::minstd_rand& rnd, unsigned steps, unsigned paths){
    double payoff = 0;
    std::vector<double> n(steps*2);
    for (int i = 0; i != paths; ++i) {
        payoff += max(heston.genPath(n, call.getExpiry()) - call.getStrike(), 0);
    }
    return payoff / (double)paths;
}
*/

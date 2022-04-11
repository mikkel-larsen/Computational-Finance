//
//  MSRNG.cpp
//  HandIn1
//
//  Created by Mikkel Larsen on 07/09/2020.
//  Copyright © 2020 Mikkel Larsen. All rights reserved.
//

#include "MSRNG.hpp"
#include "RandomNumber.hpp"


RndDevice::RndDevice(unsigned i) : dim(1) {
    msrng.seed(i);
}

RndDevice::RndDevice() : dim(1) {
    msrng.seed(1);
}

RndDevice::RndDevice(std::minstd_rand& gen) : dim(1) {
    msrng = gen;
}

RndDevice::RndDevice(const std::vector<double>& v) : dim(v.size()) {
    msrng.seed(1);
}

RndDevice::RndDevice(const RndDevice& orig) : msrng(orig.msrng), dim(orig.dim) {
    //msrng.seed(orig.getState());
}

void RndDevice::setSeed(unsigned seed) {
    msrng.seed(seed);
}

double RndDevice::genUniform() {
    // Make sure it cant be 1.0
    return msrng() / (double)msrng.max();
}

double RndDevice::genUniform(double lower, double upper) {
    return (msrng() / ((double)msrng.max() / (upper-lower)))+lower;
}

void RndDevice::genUniform(std::vector<double>& v){
    for ( auto &i : v ){
        i = genUniform();
    }
}

inline double RndDevice::normInv(double u) const {
    double y = u - 0.5;
    double x = 0;
    if (abs(y)<0.42) {
        double r = y*y;
        x = y*(((a3*r+a2)*r+a1)*r+a0)/((((b3*r+b2)*r+b1)*r+b0)*r+1);
    } else {
        double r = u;
        if (y>0)
            r = 1-u;
        r = log(-log(r));
        x = c0+r*(c1+r*(c2+r*(c3+r*(c4+r*(c5+r*(c6+r*(c7+r*c8)))))));
        if (y<0)
            x = -x;
    }
    return x;
}

double RndDevice::genNormal(){
    return normInv(genUniform());
}

double RndDevice::genNormal(double mean, double sd){
    return genNormal() * sd + mean;
}

void RndDevice::genNormal(std::vector<double>& v){
    for ( auto &i : v ){
        i = genNormal();
    }
}

double RndDevice::genGamma(double alpha, double beta){
    return gammaInv(genUniform(), alpha)/(double)beta;
}

void RndDevice::genGamma(std::vector<double>& v, double alpha, double beta){
    for (auto &i : v){
        i = genGamma(alpha, beta);
    }
}

std::minstd_rand& RndDevice::getState() {
    return msrng;
}

size_t RndDevice::getDim() const {
    return dim;
}


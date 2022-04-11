//
//  MSRNG.hpp
//  HandIn1
//
//  Created by Mikkel Larsen on 07/09/2020.
//  Copyright © 2020 Mikkel Larsen. All rights reserved.
//

#ifndef MSRNG_hpp
#define MSRNG_hpp

#include <stdio.h>
#include <random>
#include <cmath>
#include "Gamma.hpp"

// Class to use as a random device
class RndDevice {
public:
    RndDevice(unsigned i);
    RndDevice();
    RndDevice(std::minstd_rand& gen);
    RndDevice(const std::vector<double>& v);
    RndDevice(const RndDevice& orig);
    
    double genUniform();
    double genUniform(double lower, double upper);
    void genUniform(std::vector<double>& v);
    
    void setSeed(unsigned seed);
    
    double genNormal();
    double genNormal(double mean, double sd);
    void genNormal(std::vector<double>& v);
    
    double genGamma(double alpha, double beta);
    void genGamma(std::vector<double>& v, double alpha, double beta);
    
    std::minstd_rand& getState();
    size_t getDim() const;
private:
    std::minstd_rand msrng; // Holding MSRNG as private, encapsulation
    const size_t dim;
    double normInv(double u) const;
};

// Random number generator class template
template <typename T>
class RndTemp {
public:
    RndTemp(unsigned i) {generator.seed(i);}
    RndTemp(T inputGen) {generator = inputGen;}
    void setSeed(unsigned i) {
        generator.seed(i);
    }
    double genUniform() {
        return generator() / (double)(generator.max() + 1.0);
    }
private:
    T generator;
};

#endif /* MSRNG_hpp */

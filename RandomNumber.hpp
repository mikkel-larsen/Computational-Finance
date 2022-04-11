//
//  RandomNumber.hpp
//  HandIn1
//
//  Created by Mikkel Larsen on 06/09/2020.
//  Copyright © 2020 Mikkel Larsen. All rights reserved.
//

#ifndef RandomNumber_hpp
#define RandomNumber_hpp

#include <stdio.h>
#include <random>
#include <cmath>
#include <vector>
#include "Heston.hpp"
#include "CallOption.hpp"

static std::minstd_rand minstdrand;

static const double a0 = 2.50662823884;
static const double a1 = -18.61500062529;
static const double a2 = 41.39119773534;
static const double a3 = -25.44106049637;
static const double b0 = -8.47351093090;
static const double b1 = 23.08336743743;
static const double b2 = -21.06224101826;
static const double b3 = 3.13082909833;
static const double c0 = 0.3374754822726147;
static const double c1 = 0.9761690190917186;
static const double c2 = 0.1607979714918209;
static const double c3 = 0.0276438810333863;
static const double c4 = 0.0038405729373609;
static const double c5 = 0.0003951896511919;
static const double c6 = 0.0000321767881768;
static const double c7 = 0.0000002888167364;
static const double c8 = 0.0000003960315187;


void setSeed(unsigned i);

double createUniform();

double normInv(double p);

double genNormal();
double genNormal(double m, double var);
void genNormal(std::vector<double> &v);

//double monteCarlo(Heston&, CallOption&, std::minstd_rand&, unsigned steps, unsigned paths);


#endif /* RandomNumber_hpp */

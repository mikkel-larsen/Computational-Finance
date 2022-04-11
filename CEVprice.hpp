//
//  CEVprice.hpp
//  HandIn1
//
//  Created by Mikkel Larsen on 09/09/2020.
//  Copyright © 2020 Mikkel Larsen. All rights reserved.
//

#ifndef CEVprice_hpp
#define CEVprice_hpp

#include <stdio.h>
#include "CEV.hpp"
#include <cmath>
#include "CallOption.hpp"
#include "RandomNumber.hpp"
#include "Gamma.hpp"


static const double p0 = 0.2316419;
static const double p1 = 0.319381530;
static const double p2 = -0.356563782;
static const double p3 = 1.781477937;
static const double p4 = -1.821255978;
static const double p5 = 1.330274429;


double normPDF(double x, double mean = 0, double sd = 1);

double normCDF(double x);

double CEVvol(double spot, double strike, double lambda = 0.4, double beta = 0.8);

double CEVprice(double spot, double strike, double expiry, double lambda, double beta, double r = 0);

double CEVprice(const CEV& obj, double strike, double T, double r = 0);

double CEVprice(const CEV& cevObj, const CallOption& callObj, double r = 0);

double gammaPrice(double strike, double lambda, double beta);

#endif /* CEVprice_hpp */

//
//  CEVprice.cpp
//  HandIn1
//
//  Created by Mikkel Larsen on 09/09/2020.
//  Copyright © 2020 Mikkel Larsen. All rights reserved.
//

#include "CEVprice.hpp"
#include "CallOption.hpp"


double normPDF(double x, double mean, double sd){
    return 1/(sd*sqrt(2*pi))*exp(-pow(x-mean, 2)/(2*sd*sd));
}

double normCDF(double x) {
    if (x > 0){
        double t = 1/(1+p0*x);
        return 1-normPDF(x)*(p1*t+p2*pow(t, 2)+p3*pow(t, 3)+p4*pow(t, 4)+p5*pow(t, 5));
    }
    x = -x;
    double t = 1/(1+p0*x);
    return 1-(1-normPDF(x)*(p1*t+p2*pow(t, 2)+p3*pow(t, 3)+p4*pow(t, 4)+p5*pow(t, 5)));
    
}

double CEVvol(double spot, double strike, double lambda, double beta){
    double numerator = log(spot) - log(strike);
    double denominator = -1.0/((beta-1.0)*lambda*pow(spot, beta-1.0))+1.0/((beta-1.0)*lambda*pow(strike, beta-1.0));
    return numerator / denominator;
}

double CEVprice(double spot, double strike, double T, double lambda, double beta, double r){
    double vol =CEVvol(spot, strike, lambda, beta);
    double d1 = 1.0/(vol*sqrt(T))*(log(spot/strike)+(r+pow(vol, 2)*0.5)*T);
    double d2 = d1 - vol*sqrt(T);
    
    return normCDF(d1)*spot-normCDF(d2)*strike*exp(-r*T);
}

double CEVprice(const CEV& obj, double strike, double T, double r){
    return CEVprice(obj.getSpot(), strike, T, obj.getVolatility(), obj.getElasticity(), r);
}

double CEVprice(const CEV& cevObj, const CallOption& callObj, double r){
    return CEVprice(cevObj.getSpot(), callObj.getStrike(), callObj.getExpiry(), cevObj.getVolatility(), cevObj.getElasticity(), r);
}


double gammaPrice(double strike, double alpha, double beta){
    return (alpha/beta*(1-gammaCDF(strike, alpha+1, beta)) - strike*(1-gammaCDF(strike, alpha, beta)));
}

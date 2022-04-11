//
//  Gamma.cpp
//  HandIn1
//
//  Created by Mikkel Larsen on 16/09/2020.
//  Copyright © 2020 Mikkel Larsen. All rights reserved.
//

#include "Gamma.hpp"


double logGammaFunc(double xx){
    double x, tmp, y, ser;
    
    if (xx>0) {
        y = x = xx;
        tmp = x + 5.2421875;
        tmp = (x+0.5)*log(tmp)-tmp;
        ser = 0.999999999999997092;
        for (int j=0; j != 14; ++j)
            ser += cof[j]/++y;
        
        return (tmp+log(2.5066282746310005*ser/x));
    }
    return 0;
}

double gammaFunc(double x){
    return exp(logGammaFunc(x));
}

double gammpapprox(double a, double x, int psig){
    const int ngau = 18;
    double xu, t, sum, ans;
    double a1 = a-1.0, lna1 = log(a1), sqrta1 = sqrt(a1);
    double gln = logGammaFunc(a);
    
    if (x > a1) {
        xu = fmax(a1 + 11.5*sqrta1, x+6.0*sqrta1);
    } else {
        xu = fmax(0.0, fmin(a1 - 7.5*sqrta1, x - 5.0*sqrta1));
    }
    sum = 0;
    for (int j = 0; j != ngau; ++j) {
        t = x + (xu-x)*y[j];
        sum += w[j]*exp(-(t-a1)+a1*(log(t)-lna1));
    }
    ans = sum*(xu-x)*exp(a1*(lna1-1.0)-gln);
    return (psig ? (ans>0.0 ? 1.0 - ans : -ans) : (ans >= 0.0 ? ans : 1.0 + ans));
}

double gser(const double a, const double x){
    double sum, del, ap;
    double gln = log(gammaFunc(a));
    ap = a;
    del = sum = 1.0/a;
    while (fabs(del) > fabs(sum)*EPS) {
        del *= x/++ap;
        sum += del;
    }
    return sum*exp(-x+a*log(x)-gln);
}

double gcf(const double a, const double x){
    double an, b, c, d, del, h;
    double gln = logGammaFunc(a);
    b = x+1.0-a;
    c = 1.0/(double)FPMIN;
    d = 1.0/b;
    h = d;
    for (int i = 1; ; ++i) {
        an = -i*(i-a);
        b += 2.0;
        d = an*d+b;
        if (fabs(d) < FPMIN)
            d = FPMIN;
        c = b+an/c;
        if (fabs(c) < FPMIN)
            c = FPMIN;
        d = 1.0/d;
        del = d*c;
        h *= del;
        if (fabs(del-1.0) <= EPS)
            break;
    }
    return exp(-x+a*log(x)-gln)*h;
}

double gammp(const double a, const double x){
    if (x == 0.0) {
        return 0.0;
    } else if ((int)a >= ASWITCH) {
        return gammpapprox(a, x, 1);
    } else if (x < a+1.0) {
        return gser(a, x);
    } else {
        return 1.0-gcf(a, x);
    }
}

double gammaInv(double p, double a){
    double x, err, t, u, pp, lna1=0, afac=0, a1=a-1;
    const double EPS = 1.0e-8;
    double gln = logGammaFunc(a);
    if (p >= 1.0)
        return fmax(100.0, a+100.0*sqrt(a));
    if (p <= 0.0)
        return 0.0;
    if (a > 1.0) {
        lna1 = log(a1);
        afac = exp(a1*(lna1-1.0)-gln);
        pp = ((p<0.5) ? p : 1.0-p);
        t = sqrt(-2.0*log(pp));
        x = (2.30753+t*0.27061)/(1.0+t*(0.99229+t*0.04481))-t;
        if (p < 0.5)
            x = -x;
        x = fmax(1.0e-3, a*pow(1.0-1.0/(9.0*a)-x/(3.0*sqrt(a)),3));
    } else {
        t = 1.0 - a*(0.253+a*0.12);
        if (p < t){
            x = pow(p/t, 1.0/a);
        } else {
            x = 1.0-log(1.0-(p-t)/(1.0-t));
        }
    }
    for (int j = 0; j != 12; ++j) {
        if (x <= 0.0)
            return 0.0;
        err = gammp(a, x) - p;
        if (a > 1) {
            t = afac*exp(-(x-a1)+a1*(log(x)-lna1));
        } else {
            t = exp(-x+a1*log(x)-gln);
        }
        u = err/t;
        x -= (t = u/(1.0-0.5*fmin(1.0, u*((a-1.0)/x-1))));
        if (x <= 0.0)
            x = 0.5*(x+t);
        if (fabs(t) < EPS*x)
            break;
    }
    return x;
}

double gammaCDF(double x, double alpha, double beta){
    return gammp(alpha, x*beta);
}

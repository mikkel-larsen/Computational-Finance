//
//  main.cpp
//  HandIn1
//
//  Created by Mikkel Larsen on 06/09/2020.
//  Copyright © 2020 Mikkel Larsen. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include "RandomNumber.hpp"
#include "MSRNG.hpp"
#include "CEV.hpp"
#include "CEVprice.hpp"
#include "CallOption.hpp"
#include "CEVCallOption.hpp"
#include "portfolio.hpp"
#include "Heston.hpp"
#include "Gamma.hpp"

int main() {
    
    // Opgave 1.1
    std::cout << "-------- Q1.P1 --------" << std::endl;
    setSeed(1);
    for(int i = 0; i != 5; ++i){
        std::cout << createUniform() << std::endl;
    }
    
    // Opgave 1.2
    RndDevice rndGen(1);
    
    // Opgave 1.3
    std::cout << "\n-------- Q1.P3 --------" << std::endl;
    for(int i = 0; i != 5; ++i){
        std::cout << rndGen.genUniform() << std::endl;
    }
    
    // Opgave 1.4
    std::cout << "\n-------- Q1.P4 --------" << std::endl;
    rndGen.setSeed(10);
    std::cout << rndGen.genUniform() << std::endl;
    rndGen.setSeed(10);
    std::cout << rndGen.genUniform() << std::endl;
    
    // Opgave 1.6
    std::cout << "\n-------- Q1.P6 --------" << std::endl;
    rndGen.setSeed(1);
    for(int i = 0; i != 5; ++i){
        std::cout << rndGen.genNormal() << std::endl;
    }
    
    // Opgave 1.7
    std::cout << "\n-------- Q1.P7 --------" << std::endl;
    rndGen.setSeed(1);
    std::cout << "Normal(1,2): " << std::endl;
    for(int i = 0; i != 5; ++i)
        std::cout << rndGen.genNormal(1,sqrt(2)) << std::endl;
    
    rndGen.setSeed(1);
    std::cout << "Uniform(1,2): " << std::endl;
    for(int i = 0; i != 5; ++i)
        std::cout << rndGen.genUniform(1,2) << std::endl;
    
    
    
    // Opgave 1.8
    std::cout << "\n-------- Q1.P8 --------" << std::endl;
    rndGen.setSeed(1);
    for(int i = 0; i != 6; ++i){
        std::cout << "State " << i+1 << ": " << rndGen.getState() << std::endl;
        rndGen.genNormal();
    }
    
    // Opgave 1.9
    std::cout << "\n-------- Q1.P9 --------" << std::endl;
    RndDevice rndGen2;
    for(int i = 0; i != 5; ++i){
        std::cout << rndGen2.genUniform() << std::endl;
    }
    
    // Opgave 1.10
    std::cout << "\n-------- Q1.P10 --------" << std::endl;
    std::minstd_rand generator2;
    generator2.seed(10);
    RndDevice rndGen3(generator2);
    std::cout << "Generator as input: " << std::endl;
    for(int i = 0; i != 5; ++i){
        std::cout << rndGen3.genUniform() << std::endl;
    }
    std::cout << "Setting seed to 10 manually: " << std::endl;
    rndGen3.setSeed(10);
    for(int i = 0; i != 5; ++i){
        std::cout << rndGen3.genUniform() << std::endl;
    }
    
    // Opgave 1.12
    std::cout << "\n-------- Q1.P12 --------" << std::endl;
    std::vector<double> v(5, 0);
    rndGen.setSeed(1);
    rndGen.genNormal(v);
    std::cout << "Normals: " << std::endl;
    for(int i = 0; i != 5; ++i){
        std::cout << v[i] << std::endl;
    }
    rndGen.setSeed(1);
    std::cout << "Uniform: " << std::endl;
    rndGen.genUniform(v);
    for(int i = 0; i != 5; ++i){
        std::cout << v[i] << std::endl;
    }
    
    // Opgave 1.13
    std::cout << "\n-------- Q1.P13 --------" << std::endl;
    rndGen3.setSeed(1);
    RndDevice rndGen4(rndGen3);
    for(int i = 0; i != 5; ++i){
        std::cout << rndGen4.genUniform() << std::endl;
    }
    
    // Opgave 1.15
    std::cout << "\n-------- Q1.P15 --------" << std::endl;
    rndGen4.setSeed(1);
    std::cout << "(1.05, 2)" << std::endl;
    for(int i = 0; i != 10; ++i)
        std::cout << rndGen4.genGamma(1.05, 2) << std::endl;
    
    std::vector<double> g(10,0);
    rndGen4.setSeed(1);
    rndGen4.genGamma(g, 1.05, 2);
    std::cout << "\nOverloaded genGamma(1.05,2): " << std::endl;
    for(int i = 0; i != 10; ++i)
        std::cout << g[i] << std::endl;
    
    
    rndGen4.setSeed(1);
    std::cout << "\n(105, 2)" << std::endl;
    for(int i = 0; i != 10; ++i)
        std::cout << rndGen4.genGamma(105, 2) << std::endl;
    
    rndGen4.setSeed(1);
    rndGen4.genGamma(g, 105, 2);
    std::cout << "\nOverloaded genGamma(105, 2): " << std::endl;
    for(int i = 0; i != 10; ++i)
        std::cout << g[i] << std::endl;
    
    
    // Opgave 1.16
    std::cout << "\n-------- Q1.P16 --------" << std::endl;
    RndTemp<std::minstd_rand> RndTempObj(1);
    std::cout << "Uniform generated with templated class: \n" << RndTempObj.genUniform() << std::endl;
    
    RndTemp<std::minstd_rand> RndTempObj2(generator2);
    RndTempObj2.setSeed(1);
    std::cout << "Uniform generated using overloaded constructor: \n" << RndTempObj2.genUniform() << std::endl;
    
    RndTemp<std::mt19937> RndMersenne(1);
    std::cout << "Uniform generated with templated class and Mersenne Twister: \n" << RndMersenne.genUniform() << std::endl;
    
    std::mt19937 mersenneTwist;
    mersenneTwist.seed(1);
    RndTemp<std::mt19937> RndMersenne2(mersenneTwist);
    //RndMersenne2.setSeed(1);
    std::cout << "Uniform generated using overloaded constructor and Mersenne Twister: \n" << RndMersenne2.genUniform() << std::endl;
    
    
    std::cout << "\n-------- Q2.P3 --------" << std::endl;
    std::cout << "Call option price in CEV model: \n" << CEVprice(100, 98, 1, 0.4, 0.8) << std::endl;
    
    std::cout << "\n-------- Q2.P4 --------" << std::endl;
    CEV CEVObj(100, 0.4, 0.8);
    std::cout << "Spot: " << CEVObj.getSpot() << "\nVolatility: " << CEVObj.getVolatility()
    << "\nElasticity: " << CEVObj.getElasticity() << std::endl;
    
    std::cout << "-------- Q2.P5 --------" << std::endl;
    std::cout << CEVprice(CEVObj, 98, 1) << std::endl;
    
    std::cout << "-------- Q2.P6 --------" << std::endl;
    CallOption callObj(98,1);
    std::cout << CEVprice(CEVObj, callObj) << std::endl;
    
    std::cout << "-------- Q2.P7 --------" << std::endl;
    CEVCallOption cevCallOptionObj(CEVObj, callObj);
    std::cout << cevCallOptionObj.getPrice() << std::endl;
    
    std::cout << "-------- Q2.P10 --------" << std::endl;
    std::cout << "Gamma(3): " << exp(logGammaFunc(3))
    << "\nGamma(4.5): " << exp(logGammaFunc(4.5))
    << "\nGamma(5): " << exp(logGammaFunc(5)) << std::endl;
    
    std::cout << "-------- Q2.P11 --------" << std::endl;
    std::cout << "GammaCDF(98) (105, 1.05): " << gammaCDF(98, 105, 1.05)
    << "\nGammaCDF(100) (105, 1.05): " << gammaCDF(100, 105, 1.05)
    << "\nGammaCDF(120) (105, 1.05): " << gammaCDF(120, 105, 1.05) << std::endl;
    
    std::cout << "-------- Q2.P12 --------" << std::endl;
    GammaModel gamModel1(105, 1.05);
    GammaModel gamModel2(1.05, 0.0105);
    GammaCallOption gamCall1(98, gamModel1);
    GammaCallOption gamCall2(98, gamModel2);
    
    std::cout << "(105, 1.05): " << gamCall1.getPrice() << std::endl;
    std::cout << "(1.05, 0.0105): " << gamCall2.getPrice() << std::endl;
    
    std::cout << "-------- Q2.P13 --------" << std::endl;
    //Tester første constructor
    std::vector<ClosedformOption*> options2{&cevCallOptionObj, &gamCall1};
    std::vector<int> weights{2,1};
    Portfolio port2(options2, weights);
    std::cout << port2.getPrice() << std::endl;
    
    std::cout << "-------- Q2.P14 --------" << std::endl;
    Portfolio port4;
    port4.addClaim(cevCallOptionObj, 2);
    port4.addClaim(gamCall1);
    std::cout << "2 CEV and 1 Gamma calls: " << port4.getPrice() << std::endl;
    port4.removeClaim(2);
    std::cout << "2 CEV calls: " << port4.getPrice() << std::endl;
    
    
    std::cout << "-------- Q3.P3 --------" << std::endl;
    Heston hestObj(100, 0.04, 1.78, 0.0961, 0.863, 0.0484, -0.845);
    std::vector<double> n(200);
    rndGen.setSeed(1);
    rndGen.genNormal(n);
    std::cout << "ST: " << hestObj.genPath(n, 1) << std::endl;
    
    
    std::cout << "-------- Q3.P4 --------" << std::endl;
    rndGen.setSeed(1);
    std::cout << monteCarlo(hestObj, callObj, rndGen, 100, 10000) << std::endl;
    
    
    /*
    RndDevice rndGen(1);
    double r0 = -0.005, theta0 = 0.0291, kappa0 = 0.0325, sigma0 = 0.0069, b = 0.0259;
    int N = 12*1000;
    int K = 1e7;
    double dt = 1/(double)12;
    double r = r0;
    double E = (r-theta0)/kappa0*(1-exp(-kappa0*dt))+theta0*dt;
    double V = pow(sigma0,2)/pow(kappa0, 2)*(dt+1/(2*kappa0)*(1-exp(-2*kappa0*dt))+2/kappa0*(exp(-kappa0*dt)-1));
    double p = (pow(sigma0,2)/(2*kappa0)*(1+exp(-2*kappa0*dt)-2*exp(-kappa0*dt)))/sqrt(V*pow(sigma0,2)/(2*kappa0)*(1-exp(-2*kappa0*dt)));
    //std::vector<double> tau;
    double z;
    double temp = 1;
    double sum = 0;
    for (int j = 0; j != K; ++j) {
        for (int i = 0; i != N; ++i) {
            z = rndGen.genNormal();
            r = r + kappa0*(theta0-r)*dt+sigma0*sqrt(dt)*z;
            E = (r-theta0)/kappa0*(1-exp(-kappa0*dt))+theta0*dt;
            temp = temp*exp(-((z*p+sqrt(1-pow(p,2)*rndGen.genNormal()))*sqrt(V)+E));
            if (r >= b) {
                //tau.push_back(i*dt);
                sum += temp;
                break;
            }
        }
        r = r0;
        temp = 1;
    }
    sum = sum/(double)K;
    std::cout << sum << std::endl;
     */
    return 0;
}

//
//  CEVCallOption.hpp
//  HandIn1
//
//  Created by Mikkel Larsen on 09/09/2020.
//  Copyright © 2020 Mikkel Larsen. All rights reserved.
//

#ifndef CEVCallOption_hpp
#define CEVCallOption_hpp

#include <stdio.h>
#include "CallOption.hpp"
#include "CEV.hpp"
#include <memory>

//Abtract base class
class ClosedformOption {
public:
    virtual double getPrice() const =0;
    virtual ~ClosedformOption() {};
    //virtual std::unique_ptr<ClosedformOption> clone() const = 0;
    virtual ClosedformOption* clone() const =0;
};

class CEVCallOption : public ClosedformOption {
public:
    CEVCallOption(const CEV& cevObj, const CallOption& callObj);
    double getPrice() const override;
    ClosedformOption* clone() const override;
    //std::unique_ptr<ClosedformOption> clone() const override;
private:
    const CEV cevObj;
    const CallOption callObj;
};

class GammaModel {
public:
    GammaModel(double, double);
    double getAlpha() const;
    double getBeta() const;
private:
    const double alpha;
    const double beta;
};

class GammaCallOption : public ClosedformOption {
public:
    GammaCallOption(double strike_, double alpha, double beta);
    GammaCallOption(double strike_, const GammaModel& gamObj);
    ClosedformOption* clone() const override;
    //std::unique_ptr<ClosedformOption> clone() const override;
    double getPayoff(double spot) const;
    double getPrice() const override;
private:
    const double strike;
    const double alpha;
    const double beta;
};

#endif /* CEVCallOption_hpp */

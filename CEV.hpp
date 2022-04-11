//
//  CEV.hpp
//  HandIn1
//
//  Created by Mikkel Larsen on 09/09/2020.
//  Copyright © 2020 Mikkel Larsen. All rights reserved.
//

#ifndef CEV_hpp
#define CEV_hpp

#include <stdio.h>



class CEV {
public:
    CEV(double spot, double lambda, double beta);
    double getVolatility() const;
    double getElasticity() const;
    double getSpot() const;
private:
    const double spot;
    const double lambda;
    const double beta;
};

#endif /* CEV_hpp */

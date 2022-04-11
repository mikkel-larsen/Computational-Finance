//
//  CallOption.hpp
//  HandIn1
//
//  Created by Mikkel Larsen on 09/09/2020.
//  Copyright © 2020 Mikkel Larsen. All rights reserved.
//

#ifndef CallOption_hpp
#define CallOption_hpp

#include <stdio.h>

class CallOption {
public:
    CallOption(double strike, double expiry);
    double getExpiry() const;
    double getStrike() const;
    double payoff(double spot) const ;
private:
    const double expiry;
    const double strike;
};

#endif /* CallOption_hpp */

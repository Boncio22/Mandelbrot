//
//  complex.hpp
//  lista8
//
//  Created by Tomek on 25.05.2016.
//  Copyright © 2016 Boncio22. All rights reserved.
//

#ifndef complex_hpp
#define complex_hpp

class complex {
public:
    long double real;
    long double imaginary;
    
    complex operator +(const complex& b);
    
    complex operator *(const complex& b);
    
    complex operator ^(const unsigned& p);
};


#endif /* complex_hpp */

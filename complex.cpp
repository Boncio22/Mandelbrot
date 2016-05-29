//
//  complex.cpp
//  lista8
//
//  Created by Tomek on 25.05.2016.
//  Copyright © 2016 Boncio22. All rights reserved.
//

#include "complex.hpp"

complex complex::operator +(const complex& b)
{
    complex C;
    C.real = this->real + b.real;
    C.imaginary = this->imaginary + b.imaginary;
    return C;
}

complex complex::operator *(const complex& b)
{
    complex C;
    C.real = this->real*b.real - this->imaginary*b.imaginary;
    C.imaginary = this->real*b.imaginary + this->imaginary*b.real;
    return C;
}

complex complex::operator ^(const unsigned int& p)
{
    complex tmp;
    tmp.real = this->real;
    tmp.imaginary = this->imaginary;
    
    complex pot = tmp;
    
    for(unsigned int i=1; i<p; ++i)
        tmp  = tmp * pot;
    
    return tmp;
}


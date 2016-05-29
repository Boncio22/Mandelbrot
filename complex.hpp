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
    
    /**
     *  suma liczb zespolonych
     *
     *  @param b liczba ktora dodajemy
     *
     *  @return zwraca sume
     */
    complex operator +(const complex& b);
    
    /**
     *  iloczyn liczb zespolonych
     *
     *  @param b liczba przez ktora mnozymy
     *
     *  @return iloczyn oby liczb
     */
    complex operator *(const complex& b);
    
    /**
     *  podnoszenie liczby zespolonej do odpowiedniej potegi
     *
     *  @param p liczba calkowita do ktorej potegujemy
     *
     *  @return p-ta potega liczby
     */
    complex operator ^(const unsigned int& p);
};


#endif /* complex_hpp */

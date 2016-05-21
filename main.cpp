//
//  main.cpp
//  lista8
//
//  Created by Tomek on 17.05.2016.
//  Copyright © 2016 Boncio22. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "draw.hpp"
using namespace std;

#define R_min   0.3f
#define R_max   0.4f
#define I_min   0.5f
#define I_max   0.6f

#define R_center -0.22f
#define I_center 0.64f
#define wid 0.05f
#define zoom 0.97f
#define potega 2

#define ile_klatek 120
#define iterations  500 + ile_klatek
#define procent 5

#define picW    500
#define picH    500
#define color   255

#define uR (R_max-R_min)/picW
#define uI (I_max-I_min)/picH


struct complex {
    float real;
    float imaginary;
    
    complex operator +(const complex& b)
    {
        complex C;
        C.real = this->real + b.real;
        C.imaginary = this->imaginary + b.imaginary;
        return C;
    }
    
    complex operator *(const complex& b)
    {
        complex C;
        C.real = this->real*b.real - this->imaginary*b.imaginary;
        C.imaginary = this->real*b.imaginary + this->imaginary*b.real;
        return C;
    }
    
    complex operator ^(const unsigned& p)
    {
        complex tmp;
        tmp.real = this->real;
        tmp.imaginary = this->imaginary;
        
        complex pot = tmp;
        
        for(int i=1; i<p; ++i)
            tmp  = tmp * pot;
        
        return tmp;
    }
};

int findMandelbrot(complex num);

int main(int argc, char * argv[]) {
    
    string name;
    if (argc < 2) {
        cout <<"Podaj nazwę tworzonych plików: ";
        cin >>name;
    } else {
        name = argv[1];
    }
    
    int setki = 0, dziesiatki = 0, jednosci = 0;
    float rozrzut = wid;
    
    for (int klatki = 1; klatki <= ile_klatek; ++klatki)
    {
        float uR2 = rozrzut/picW;
        float uI2 = rozrzut/picH;
        
        cout <<"Szerokość obrazka: " <<picW <<'\t' <<"Wysokość obrazka: " <<picH <<endl;
        cout <<"Zakres części rzeczywistej: "   <<R_center - rozrzut <<" - " <<R_center + rozrzut <<endl;
        cout <<"Zakres części urojonej: "       <<I_center - rozrzut <<" - " <<I_center + rozrzut <<endl;
        
        cout.sync_with_stdio(false);
        
        string tmp = name;
        
        if (ile_klatek > 1) {
            tmp = name + setki + dziesiatki + jednosci + ".ppm";
        } else {
            tmp = name + ".ppm";
        }
        
        ofstream mandelbrot(tmp);
        
        mandelbrot <<"P3" <<endl;
        mandelbrot <<picW <<' ' <<picH <<endl;
        mandelbrot <<color <<endl;
        
        float postep = 0;
        for (int y=0; y<picH; ++y) {
            for (int x=0; x<picW; ++x) {
                complex C;
                C.real = R_center - rozrzut + 2*x*uR2;
                C.imaginary = I_center - rozrzut + 2*y*uI2;
                
                //int n = findMandelbrot(C);
                
                draw pixel(findMandelbrot(C), mandelbrot, iterations);
                //mandelbrot <<pixel.R <<' ' <<pixel.G <<' ' <<pixel.B <<'\n';
            }
            
            if (y % (picH / 100 * procent) == 0) {
                cout <<"Klatka " << klatki <<'\\' <<ile_klatek <<" - Rysowanie: "<<postep <<'%' <<'\n';
                postep += procent;
            }
        }
        cout <<endl;
        
        mandelbrot.close();
        
        rozrzut *= zoom;
        jednosci++;
        if (jednosci == 58) {
            jednosci -= 10;
            dziesiatki++;
        }
        if (dziesiatki == 58) {
            dziesiatki -= 10;
            setki++;
        
    }
    
    cout.sync_with_stdio(true);
    
    cout <<"Kuniec" <<endl;
    
    return 0;
}

int findMandelbrot(complex num)
{
    int i = 0;
    complex z;
    z.real =0;
    z.imaginary = 0;
    
    while (i < iterations && z.real*z.real + z.imaginary*z.imaginary < 2) {
//        float tmp = z.real*z.real - z.imaginary*z.imaginary + num.real;
//        z.imaginary = 2.f * z.real * z.imaginary + num.imaginary;
//        z.real = tmp;
        z = (z^potega) + num;
        ++i;
    }
    
    return i;
}








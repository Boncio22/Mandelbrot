//
//  main.cpp
//  lista8
//
//  Created by Tomek on 17.05.2016.
//  Copyright © 2016 Boncio22. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <string>

#include "draw.hpp"
using namespace std;

#define R_min   0.3
#define R_max   0.4
#define I_min   0.5
#define I_max   0.6

#define R_center 0.001643721971153
#define I_center 0.822467633298876
#define wid 0.05
#define zoom 0.98
#define potega 2

#define szybkosc 24
#define dlugosc 30

#define ile_klatek szybkosc * dlugosc
#define iterations  500 + ile_klatek
#define procent 5

#define picW    500
#define picH    500
#define color   255

// #define uR (R_max-R_min)/picW
// #define uI (I_max-I_min)/picH


struct complex {
    double real;
    double imaginary;

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

        for(unsigned int i=1; i<p; ++i)
            tmp  = tmp * pot;

        return tmp;
    }
};

unsigned int findMandelbrot(complex num)
{
    unsigned int i = 0;
    complex z;
    z.real =0;
    z.imaginary = 0;

    while (i < iterations && z.real*z.real + z.imaginary*z.imaginary < 2) {
        z = (z^potega) + num;
        ++i;
    }

    return i;
}

int main(int argc, char * argv[]) {

    string name;
    if (argc < 2) {
        cout <<"Podaj nazwę tworzonych plików: ";
        cin >>name;
    } else {
        name = argv[1];
    }

    char setki = 48, dziesiatki = 48, jednosci = 48;
    double rozrzut = wid;

    for (int klatki = 1; klatki <= ile_klatek; ++klatki)
    {
        double uR2 = rozrzut/picW/2;
        double uI2 = rozrzut/picH/2;

        cout <<"Szerokość obrazka: " <<picW <<'\t' <<"Wysokość obrazka: " <<picH <<endl;
        cout <<"Zakres części rzeczywistej: "   <<setprecision(20) <<R_center - rozrzut <<" - " <<R_center + rozrzut <<endl;
        cout <<"Zakres części urojonej: "       <<setprecision(20) <<I_center - rozrzut <<" - " <<I_center + rozrzut <<endl;

        cout.sync_with_stdio(false);

        string tmp = name;

        if (ile_klatek > 1) {
            tmp = "Grafiki/" + name + setki + dziesiatki + jednosci + ".ppm";
        } else {
            tmp = "Grafiki/" + name + ".ppm";
        }

        ofstream mandelbrot(tmp.c_str());

        mandelbrot <<"P3" <<endl;
        mandelbrot <<picW <<' ' <<picH <<endl;
        mandelbrot <<color <<endl;

        double postep = 0;
        for (int y=0; y<picH; ++y) {
            for (int x=0; x<picW; ++x) {
                complex C;
                C.real = R_center - rozrzut + x*uR2;
                C.imaginary = I_center - rozrzut + y*uI2;

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

    }

    cout.sync_with_stdio(true);

    cout <<"Kuniec" <<endl;
    system("./konwersja.sh");

    return 0;
}

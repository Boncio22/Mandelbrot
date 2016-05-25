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

#define picW    1920.0
#define picH    1080.0
#define color   255

#define R_min   0.3
#define R_max   0.4
#define I_min   0.5
#define I_max   0.6

#define R_start 0.001643721971153
#define I_start 0.822467633298876

#define R_end   0.001643721971153
#define I_end   0.822467633298876

#define widR    0.05
#define widI    widR*(picH/picW)
#define zoom    0.99
#define potega  2


#define animacja    true
#define szybkosc    60
#define dlugosc     30

#define iterations  500 + ile_klatek
#define procent     5

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
        cin >> name;
    } else {
        name = argv[1]; // pierwszy argument po nazwie
    }

    char setki = 48, dziesiatki = 48, jednosci = 48;
    double rozrzutR = widR;
    double rozrzutI = widI;

    unsigned int = szybkosc * dlugosc;
    if (animacja)
	limit = 1;

    for (unsigned int klatki = 1; klatki <= limit; ++klatki)
    {
        double uR2 = 2*rozrzutR/picW;
        double uI2 = 2*rozrzutI/picH;

        cout <<"Szerokość obrazka: " <<picW <<'\t' <<"Wysokość obrazka: " <<picH <<'\t';
        cout <<"Zakres części rzeczywistej: "   <<setprecision(20) <<R_center - rozrzutR <<" - " <<R_center + rozrzutR <<'\t';
        cout <<"Zakres części urojonej: "       <<setprecision(20) <<I_center - rozrzutI <<" - " <<I_center + rozrzutI <<endl;

        cout.sync_with_stdio(false);

        string tmp = name;

        if (animacja) {
            tmp = "Grafiki/" + name + setki + dziesiatki + jednosci + ".ppm";
        } else {
            tmp = "Grafiki/" + name + ".ppm";
        }

        ofstream mandelbrot(tmp.c_str());

        mandelbrot <<"P3" <<endl;
        mandelbrot <<picW <<' ' <<picH <<endl;
        mandelbrot <<color <<endl;

        for (int y=0; y<picH; ++y) {
            for (int x=0; x<picW; ++x) {
                complex C;
                C.real = R_start - rozrzutR + x*uR2;
                C.imaginary = I_start - rozrzutI + y*uI2;

                draw pixel(findMandelbrot(C), mandelbrot, iterations);
            }
        }
        cout <<"\033[32m"<<"Rysowanie klatki " <<klatki <<'/' <<ile_klatek <<"\033[0m" <<endl;

        mandelbrot.close();

        rozrzutR *= zoom;
        rozrzutI *= zoom;
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

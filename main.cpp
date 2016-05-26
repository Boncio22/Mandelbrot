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
#include "complex.hpp"

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

#define animacja    false
#define szybkosc    60
#define dlugosc     20

#define iterations  500 + szybkosc * dlugosc

#define debug false

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

    char tysiace = 48, setki = 48, dziesiatki = 48, jednosci = 48;
    long double rozrzutR = widR;
    long double rozrzutI = widI;
    

    unsigned int limit = szybkosc * dlugosc;
    if (!animacja)
    {
        limit = 1;
    }
    
    long double krok_R = (R_end - R_start) / limit;
    long double krok_I = (I_end - I_start) / limit;
    
    long double R_mid = R_start;
    long double I_mid = I_start;

    for (unsigned int klatki = 1; klatki <= limit; ++klatki)
    {
        long double uR2 = 2*rozrzutR/picW;
        long double uI2 = 2*rozrzutI/picH;

        if (debug) {
            cout <<"Szerokość: " <<picW <<'\t' <<"Wysokość: " <<picH <<'\t';
            cout <<"R_mid: "   <<setprecision(10) <<R_mid <<'\t';
            cout <<"I_mid: "       <<setprecision(10) <<I_mid <<endl;
        }

        cout.sync_with_stdio(false);

        string tmp = name;

        if (animacja) {
            tmp = "Grafiki/" + name + tysiace + setki + dziesiatki + jednosci + ".ppm";
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
                C.real = R_mid - rozrzutR + x*uR2;
                C.imaginary = I_mid - rozrzutI + y*uI2;

                draw pixel(findMandelbrot(C), mandelbrot, iterations);
            }
        }
        cout <<"\033[32m"<<"Rysowanie klatki " <<klatki <<'/' <<limit <<"\033[0m" <<endl;

        mandelbrot.close();

        rozrzutR *= zoom;
        rozrzutI *= zoom;
        
        R_mid += krok_R;
        I_mid += krok_I;
        
        jednosci++;
        if (jednosci == 58) {
            jednosci -= 10;
            dziesiatki++;
        }
        if (dziesiatki == 58) {
            dziesiatki -= 10;
            setki++;
        }
        if (setki == 58) {
            setki -= 10;
            tysiace++;
        }

    }

    cout.sync_with_stdio(true);

    cout <<"Kuniec" <<endl;

    if (animacja) {
        system("./konwersja.sh");
    }

    return 0;
}

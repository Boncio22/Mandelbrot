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
#include <thread>

#include "draw.hpp"
#include "complex.hpp"

using namespace std;

#define picW    1920.0
#define picH    1080.0
#define color   255

#define R_start 0.001643721971153
#define I_start 0.822467633298876

#define R_end   0.001643721971153
#define I_end   0.822467633298876

#define widR    0.05
#define widI    widR*(picH/picW)
#define zoom    0.98
#define potega  2

#define animacja    true
#define szybkosc    60
#define dlugosc     20

#define iterations  500 + szybkosc * dlugosc

#define debug false

inline unsigned int findMandelbrot(complex num);
inline void update(const long double krok_R, const long double krok_I,
                   long double &R_mid, long double &I_mid, long double &rozrzutR, long double &rozrzutI,
                   char &tysiace, char &setki, char &dziesiatki, char &jednosci);

void watek1(const string nazwa, const long double R_mid, const long double I_mid,
            const long double rozrzutR, const long double rozrzutI);
void watek2(const string nazwa, const long double R_mid, const long double I_mid,
            const long double rozrzutR, const long double rozrzutI);
void watek3(const string nazwa, const long double R_mid, const long double I_mid,
            const long double rozrzutR, const long double rozrzutI);
void watek4(const string nazwa, const long double R_mid, const long double I_mid,
            const long double rozrzutR, const long double rozrzutI);
void watek5(const string nazwa, const long double R_mid, const long double I_mid,
            const long double rozrzutR, const long double rozrzutI);

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
    
    cout.sync_with_stdio(false);
    string tmp = name;

    for (unsigned int klatki = 0; klatki < limit; klatki+=5)
    {
        // THREAD 1 //
        tmp = "Grafiki/" + name + tysiace + setki + dziesiatki + jednosci + ".ppm";
        
        thread watek_1(watek1, tmp, R_mid, I_mid, rozrzutR, rozrzutI);
        update(krok_R, krok_I, R_mid, I_mid, rozrzutR, rozrzutI, tysiace, setki, dziesiatki, jednosci);
        
        // THREAD 2 //
        tmp = "Grafiki/" + name + tysiace + setki + dziesiatki + jednosci + ".ppm";
        
        thread watek_2(watek2, tmp, R_mid, I_mid, rozrzutR, rozrzutI);
        update(krok_R, krok_I, R_mid, I_mid, rozrzutR, rozrzutI, tysiace, setki, dziesiatki, jednosci);
        
        // THREAD 3 //
        tmp = "Grafiki/" + name + tysiace + setki + dziesiatki + jednosci + ".ppm";
        
        thread watek_3(watek3, tmp, R_mid, I_mid, rozrzutR, rozrzutI);
        update(krok_R, krok_I, R_mid, I_mid, rozrzutR, rozrzutI, tysiace, setki, dziesiatki, jednosci);
    
        // THREAD 4 //
        tmp = "Grafiki/" + name + tysiace + setki + dziesiatki + jednosci + ".ppm";
        
        thread watek_4(watek4, tmp, R_mid, I_mid, rozrzutR, rozrzutI);
        update(krok_R, krok_I, R_mid, I_mid, rozrzutR, rozrzutI, tysiace, setki, dziesiatki, jednosci);
    
        // THREAD 5 //
        tmp = "Grafiki/" + name + tysiace + setki + dziesiatki + jednosci + ".ppm";
        
        thread watek_5(watek5, tmp, R_mid, I_mid, rozrzutR, rozrzutI);
        update(krok_R, krok_I, R_mid, I_mid, rozrzutR, rozrzutI, tysiace, setki, dziesiatki, jednosci);
        
        
        watek_1.join();
        watek_2.join();
        watek_3.join();
        watek_4.join();
        watek_5.join();

        cout <<"Narysowano " <<klatki+5 <<'/' <<limit <<" klatek." <<endl;
    }

    cout.sync_with_stdio(true);

    cout <<"Kuniec" <<endl;

    if (animacja) {
        system("./konwersja.sh");
    }

    return 0;
}


inline unsigned int findMandelbrot(complex num)
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

inline void update(const long double krok_R, const long double krok_I,
                   long double &R_mid, long double &I_mid, long double &rozrzutR, long double &rozrzutI,
                   char &tysiace, char &setki, char &dziesiatki, char &jednosci)
{
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

void watek1(const string nazwa, const long double R_mid, const long double I_mid,
                                const long double rozrzutR, const long double rozrzutI)
{
    long double uR2 = 2*rozrzutR/picW;
    long double uI2 = 2*rozrzutI/picH;
    
    ofstream mandelbrot1(nazwa.c_str());
    
    mandelbrot1 <<"P3" <<endl;
    mandelbrot1 <<picW <<' ' <<picH <<endl;
    mandelbrot1 <<color <<endl;
    
    for (int y=0; y<picH; ++y) {
        for (int x=0; x<picW; ++x) {
            complex C;
            C.real = R_mid - rozrzutR + x*uR2;
            C.imaginary = I_mid - rozrzutI + y*uI2;
            
            draw pixel(findMandelbrot(C), mandelbrot1, iterations);
        }
    }
    
    mandelbrot1.close();
}

void watek2(const string nazwa, const long double R_mid, const long double I_mid,
            const long double rozrzutR, const long double rozrzutI)
{
    long double uR2 = 2*rozrzutR/picW;
    long double uI2 = 2*rozrzutI/picH;
    
    ofstream mandelbrot2(nazwa.c_str());
    
    mandelbrot2 <<"P3" <<endl;
    mandelbrot2 <<picW <<' ' <<picH <<endl;
    mandelbrot2 <<color <<endl;
    
    for (int y=0; y<picH; ++y) {
        for (int x=0; x<picW; ++x) {
            complex C;
            C.real = R_mid - rozrzutR + x*uR2;
            C.imaginary = I_mid - rozrzutI + y*uI2;
            
            draw pixel(findMandelbrot(C), mandelbrot2, iterations);
        }
    }
    
    mandelbrot2.close();
}

void watek3(const string nazwa, const long double R_mid, const long double I_mid,
            const long double rozrzutR, const long double rozrzutI)
{
    long double uR2 = 2*rozrzutR/picW;
    long double uI2 = 2*rozrzutI/picH;
    
    ofstream mandelbrot3(nazwa.c_str());
    
    mandelbrot3 <<"P3" <<endl;
    mandelbrot3 <<picW <<' ' <<picH <<endl;
    mandelbrot3 <<color <<endl;
    
    for (int y=0; y<picH; ++y) {
        for (int x=0; x<picW; ++x) {
            complex C;
            C.real = R_mid - rozrzutR + x*uR2;
            C.imaginary = I_mid - rozrzutI + y*uI2;
            
            draw pixel(findMandelbrot(C), mandelbrot3, iterations);
        }
    }
    
    mandelbrot3.close();
}

void watek4(const string nazwa, const long double R_mid, const long double I_mid,
            const long double rozrzutR, const long double rozrzutI)
{
    long double uR2 = 2*rozrzutR/picW;
    long double uI2 = 2*rozrzutI/picH;
    
    ofstream mandelbrot4(nazwa.c_str());
    
    mandelbrot4 <<"P3" <<endl;
    mandelbrot4 <<picW <<' ' <<picH <<endl;
    mandelbrot4 <<color <<endl;
    
    for (int y=0; y<picH; ++y) {
        for (int x=0; x<picW; ++x) {
            complex C;
            C.real = R_mid - rozrzutR + x*uR2;
            C.imaginary = I_mid - rozrzutI + y*uI2;
            
            draw pixel(findMandelbrot(C), mandelbrot4, iterations);
        }
    }
    
    mandelbrot4.close();
}

void watek5(const string nazwa, const long double R_mid, const long double I_mid,
            const long double rozrzutR, const long double rozrzutI)
{
    long double uR2 = 2*rozrzutR/picW;
    long double uI2 = 2*rozrzutI/picH;
    
    ofstream mandelbrot5(nazwa.c_str());
    
    mandelbrot5 <<"P3" <<endl;
    mandelbrot5 <<picW <<' ' <<picH <<endl;
    mandelbrot5 <<color <<endl;
    
    for (int y=0; y<picH; ++y) {
        for (int x=0; x<picW; ++x) {
            complex C;
            C.real = R_mid - rozrzutR + x*uR2;
            C.imaginary = I_mid - rozrzutI + y*uI2;
            
            draw pixel(findMandelbrot(C), mandelbrot5, iterations);
        }
    }
    
    mandelbrot5.close();
}









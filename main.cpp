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
#define wid  1.f   // 0.05f
#define zoom 0.97f
#define potega 6

#define ile_klatek 1
#define iterations  100 + ile_klatek
#define procent 1.f

#define picW    1000
#define picH    1000
#define color   255

#define uR (R_max-R_min)/picW
#define uI (I_max-I_min)/picH


struct complex {
    float real;         // czesc rzeczywista
    float imaginary;    // czesc urojona
    
    inline complex operator +(const complex& b) //operator dodawania
    {
        complex C;
        C.real = this->real + b.real;
        C.imaginary = this->imaginary + b.imaginary;
        return C;
    }
    
    inline complex operator *(const complex& b) // operator mnozenia
    {
        complex C;
        C.real = this->real*b.real - this->imaginary*b.imaginary;
        C.imaginary = this->real*b.imaginary + this->imaginary*b.real;
        return C;
    }
    
    inline complex operator ^(const unsigned& p)    // operator potegowy
    {
        complex C;
        C.real = this->real;
        C.imaginary = this->imaginary;
        
        complex pot = C;
        
        for(unsigned int i=1; i<p; ++i)
            C  = C * pot;
        
        return C;
    }
};

int findMandelbrot(complex num);    // funkcja sprawdzajaca ile iteracji przechodzi dany punkt

int main(int argc, char * argv[]) {
    
    string name;    // nazwa tworzonych plikow
    if (argc < 2) { // jesli nie podano w argumencie to popros uzytkownika o zdefiniowanie
        cout <<"Podaj nazwę tworzonych plików: ";
        cin >>name;
    } else {
        name = argv[1]; // pierwszy argument po nazwie
    }
    
    char setki = 48, dziesiatki = 48, jednosci = 48;    // ustawione na znak '0'
    float rozrzut = wid;    // potrzeba zdefiniowania tego jako zmiennej dzieki czemu mozna przyblizac obraz w animacji
    
    for (int klatki = 1; klatki <= ile_klatek; ++klatki)
    {
        float uR2 = rozrzut/picW/2;   // jednostka rzeczywista
        float uI2 = rozrzut/picH/2;   // jednostka urojona
        
        // Info generowania
        cout <<"Szerokość obrazka: " <<picW <<'\t' <<"Wysokość obrazka: " <<picH <<'\n';
        cout <<"Zakres części rzeczywistej: "   <<R_center - rozrzut <<" : " <<R_center + rozrzut <<'\n';
        cout <<"Zakres części urojonej: "       <<I_center - rozrzut <<" : " <<I_center + rozrzut <<'\n';
        cout.flush();
        
        cout.sync_with_stdio(false);    // wylaczenie synchronizacji ze standardowym wyjsciem w celu przyspieszenia pisania
        
        // dostosowanie nazwy pliku do wymogow generowania
        string tmp = name;
        if (ile_klatek > 1) {
            tmp = name + setki + dziesiatki + jednosci + ".ppm";
        } else {
            tmp = name + ".ppm";
        }
        
        ofstream mandelbrot(tmp);   // wyrzucanie do pliku o danej nazwie
        
        // naglowek PPM
        mandelbrot <<"P3" <<endl;
        mandelbrot <<picW <<' ' <<picH <<endl;
        mandelbrot <<color <<endl;
        
        float postep = 0;   // procentowy wskaznik postepu generowania obrazu
        
        for (int y=0; y<picH; ++y) {    // petla ogarniajaca kolejne pixele
            for (int x=0; x<picW; ++x) {
                complex C;
                C.real = R_center - rozrzut + x * uR2;  // ustalenie pozycji rzeczywistej
                C.imaginary = I_center - rozrzut + y * uI2; // ustalenie pozycji urojonej

                draw pixel(findMandelbrot(C), mandelbrot, iterations); // wyznaczenie koloru pixela
            }
            
            if (y % (int)(picH / 100 * procent) == 0) {  // info o postepie
                cout <<"Klatka " << klatki <<'\\' <<ile_klatek <<" - Rysowanie: "<<postep <<'%' <<'\n';
                postep += procent;
            }
        }
        cout <<endl;
        
        mandelbrot.close(); // zamkniecie pliku z grafika
        
        rozrzut *= zoom;    // przyblizenie obrazu
        
        // kontorola nazwy pliku
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
    
    cout.sync_with_stdio(true); // przywrocenie synchronizacji

    cout <<"Kuniec" <<endl; // info o zakonczeniu pracy
    
    return EXIT_SUCCESS;
}

int findMandelbrot(complex num)
{
    int i = 1;
    complex z = num;    // pominiecie zerowej iteracji
    
    while (i < iterations && z.real*z.real + z.imaginary*z.imaginary < 2) {
        z = (z^potega) + num;
        ++i;
    }
    
    return i;
}









//
//  main.cpp
//  lista8
//
//  Created by Tomek on 17.05.2016.
//  Copyright © 2016 Boncio22. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;

#define R_min   0.3f
#define R_max   0.4f
#define I_min   0.5f
#define I_max   0.6f

#define R_center -0.07f
#define I_center 0.6f
#define wid 0.2f

#define ile_klatek 1
#define iterations  1000
#define procent 100

#define picW    2560
#define picH    2000
#define color   255

#define uR (R_max-R_min)/picW
#define uI (I_max-I_min)/picH


struct complex {
    float real;
    float imaginary;
    
    complex operator +(const complex& b)
    {
        return complex{this->real + b.real, this->imaginary + b.imaginary};
        //return c;
    }
    
    complex operator *(const complex& b)
    {
        return complex{this->real*b.real - this->imaginary*b.imaginary, this->real*b.imaginary + this->imaginary*b.real};
    }
};

class draw {
public:
    int R;
    int G;
    int B;
    
public:
    draw(float num)
    {
        //num *= color;
        num = (int)num % 16;
        if (num < 0.5f) {
            this->R = 0;
            this->G = 0;
            this->B = 0;
        } else if (num < 1.f) {
            this->R = 66;
            this->G = 30;
            this->B = 15;
        } else if (num < 2.f) {
            this->R = 25;
            this->G = 7;
            this->B = 26;
        } else if (num < 3.f) {
            this->R = 9;
            this->G = 1;
            this->B = 47;
        } else if (num < 4.f) {
            this->R = 4;
            this->G = 4;
            this->B = 73;
        } else if (num < 5.f) {
            this->R = 0;
            this->G = 7;
            this->B = 100;
        } else if (num < 6.f) {
            this->R = 12;
            this->G = 44;
            this->B = 138;
        } else if (num < 7.f) {
            this->R = 24;
            this->G = 82;
            this->B = 177;
        } else if (num < 8.f){
            this->R = 57;
            this->G = 125;
            this->B = 209;
        } else if (num < 9.f) {
            this->R = 134;
            this->G = 181;
            this->B = 229;
        } else if (num < 10.f) {
            this->R = 211;
            this->G = 236;
            this->B = 248;
        } else if (num < 11.f) {
            this->R = 241;
            this->G = 233;
            this->B = 191;
        } else if (num < 12.f) {
            this->R = 248;
            this->G = 201;
            this->B = 95;
        } else if (num < 13.f) {
            this->R = 255;
            this->G = 170;
            this->B = 0;
        } else if (num < 14.f) {
            this->R = 204;
            this->G = 128;
            this->B = 0;
        } else if (num < 15.f) {
            R = 153;
            G = 87;
            B = 0;
        } else {
            R = 106;
            G = 52;
            B = 3;
        }
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
    float uR2 = rozrzut/picW;
    float uI2 = rozrzut/picH;
    
    for (int i = 0; i < ile_klatek; ++i) {
        
//        int histogram[iterations]= {0};
//        
//        float postep = 0;
//        for (int y=0; y<picH; ++y) {
//            for (int x=0; x<picW; ++x) {
//                complex C;
//                C.real = R_center - rozrzut + x*2.f*uR2;
//                C.imaginary = I_center - rozrzut + y*2.f*uI2;
//                
//                int n = findMandelbrot(C);
//                
//                histogram[n]++;
//            }
//            if (y % (picH / procent) == 0) {
//                cout <<"Liczenie: "<<postep <<'%' <<'\n';
//                postep += 100.f/procent;
//            }
//        }
//        
//        int total = 0;
//        for (int i=0; i<iterations; ++i) {
//            total += histogram[i];
//        }
//        cout <<total <<endl;
        
        cout <<picW <<'\t' <<picH <<endl;
        cout <<R_min <<'\t' <<R_max <<endl;
        cout <<I_min <<'\t' <<I_max <<endl;
        
        cout.sync_with_stdio(false);
        
        ofstream mandelbrot( name.c_str() + to_string(setki) + to_string(dziesiatki) + to_string(jednosci) + ".ppm");
        
        mandelbrot <<"P3" <<endl;
        mandelbrot <<picW <<' ' <<picH <<endl;
        mandelbrot <<color <<endl;
        
        float postep = 0;
        for (int y=0; y<picH; ++y) {
            for (int x=0; x<picW; ++x) {
                complex C;
                C.real = R_center - rozrzut + x*2.f*uR2;
                C.imaginary = I_center - rozrzut + y*2.f*uI2;
                
                int n = findMandelbrot(C);
                
//                float hue = 0.f;
//                for (int i=0; i<n; ++i) {
//                    hue += histogram[i] / (float)total;
//                }
//                draw pixel(hue);
                draw pixel(n);
                mandelbrot <<pixel.R <<' ' <<pixel.G <<' ' <<pixel.B <<'\n';
            }
            
            if (y % (picH / procent) == 0) {
                cout <<"Rysowanie "<<postep <<'%' <<'\n';
                postep += 100.f/procent;
            }
        }
        cout <<endl;
        
        mandelbrot.close();
        
        rozrzut *= 0.9f;
        jednosci++;
        if (jednosci == 10) {
            jednosci = 0;
            dziesiatki++;
        }
        if (dziesiatki == 10) {
            dziesiatki = 0;
            setki++;
        }
    }
    
    cout.sync_with_stdio(true);
    
    cout <<"Kuniec" <<endl;
    
    return 0;
}

int findMandelbrot(complex num)
{
    int i = 0;
    complex z{0, 0};
    
    while (i < iterations && z.real*z.real + z.imaginary*z.imaginary < 4) {
        float tmp = z.real*z.real - z.imaginary*z.imaginary + num.real;
        z.imaginary = 2.f * z.real * z.imaginary + num.imaginary;
        z.real = tmp;
        ++i;
    }
    
    return i;
}








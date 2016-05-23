//
//  draw.hpp
//  lista8
//
//  Created by Tomek on 20.05.2016.
//  Copyright © 2016 Boncio22. All rights reserved.
//

#ifndef draw_hpp
#define draw_hpp

class draw {
public:
    double R;    // red
    double G;    // green
    double B;    // blue
    // float A;    // = max_value    // alpha  // przyszlosciowe - potrzebne do PNG
    
public:
    draw(float num, std::ofstream& mandelbrot, const int iterations)
    {
        if (num == iterations) {
            this->R = 0;
            this->G = 0;
            this->B = 0;
        } else {
            num = (int)num % 16;
            if (num < 1.f) {
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
        
        
        mandelbrot <<this->R <<' ' <<this->G <<' ' <<this->B <<'\n';
    }
    
    draw(float num, const int iterations)
    {
        if (num == iterations) {
            this->R = 0;
            this->G = 0;
            this->B = 0;
        } else {
            num = (int)num % 16;
            if (num < 1.f) {
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
        
        this->R /= 255.0;
        this->G /= 255.0;
        this->B /= 255.0;
    }

};

#endif /* draw_hpp */

//
//  draw.hpp
//  lista8
//
//  Created by Tomek on 20.05.2016.
//  Copyright © 2016 Boncio22. All rights reserved.
//

#ifndef draw_hpp
#define draw_hpp

#include <fstream>

class draw {    // klasa nadajaca kolor pixelom
public:
    unsigned short int R;    // red
    unsigned short int G;    // green
    unsigned short int B;    // blue

public:
    draw(float num, std::ofstream &mandelbrot, const int iterations, const int paleta)
    {  
		switch (paleta)
		{
		case 1:		  // domyslna paleta by tomek
		{
			if (num == iterations) {    // tu zaczyna sie paleta kolorow
				this->R = 0;            // ktorej nie bede komentowal bo
				this->G = 0;            // bo to nie ma sensu
				this->B = 0;			// ale jesli pixel przetrwal wszystkie iteracje to koloruje go na czarno
			}
			else {
				num = (int)num % 16;
				if (num < 1.f) {
					this->R = 66;
					this->G = 30;
					this->B = 15;
				}
				else if (num < 2.f) {
					this->R = 25;
					this->G = 7;
					this->B = 26;
				}
				else if (num < 3.f) {
					this->R = 9;
					this->G = 1;
					this->B = 47;
				}
				else if (num < 4.f) {
					this->R = 4;
					this->G = 4;
					this->B = 73;
				}
				else if (num < 5.f) {
					this->R = 0;
					this->G = 7;
					this->B = 100;
				}
				else if (num < 6.f) {
					this->R = 12;
					this->G = 44;
					this->B = 138;
				}
				else if (num < 7.f) {
					this->R = 24;
					this->G = 82;
					this->B = 177;
				}
				else if (num < 8.f) {
					this->R = 57;
					this->G = 125;
					this->B = 209;
				}
				else if (num < 9.f) {
					this->R = 134;
					this->G = 181;
					this->B = 229;
				}
				else if (num < 10.f) {
					this->R = 211;
					this->G = 236;
					this->B = 248;
				}
				else if (num < 11.f) {
					this->R = 241;
					this->G = 233;
					this->B = 191;
				}
				else if (num < 12.f) {
					this->R = 248;
					this->G = 201;
					this->B = 95;
				}
				else if (num < 13.f) {
					this->R = 255;
					this->G = 170;
					this->B = 0;
				}
				else if (num < 14.f) {
					this->R = 204;
					this->G = 128;
					this->B = 0;
				}
				else if (num < 15.f) {
					R = 153;
					G = 87;
					B = 0;
				}
				else {
					R = 106;
					G = 52;
					B = 3;
				}
			}
			break;
		};
		
		case 2:			   // prostsza testowa paleta
		{
			if (num == iterations) {
				this->R = 0;
				this->G = 0;
				this->B = 0;
			}
			else {
				num = (int)num % 5;
				if (num < 1.f) {
					this->R = 93;
					this->G = 183;
					this->B = 222;
				}
				else if (num < 2.f) {
					this->R = 208;
					this->G = 83;
					this->B = 83;
				}
				else if (num < 3.f) {
					this->R = 249;
					this->G = 154;
					this->B = 187;
				}
				else if (num < 4.f) {
					this->R = 22;
					this->G = 168;
					this->B = 199;
				}
				else {
					R = 107;
					G = 120;
					B = 147;
				}
		
			}
			break;
		}

		case 3:		  // LSD Mark I
		{
			if (num == iterations) {    
				this->R = 0;            
				this->G = 0;            
				this->B = 0;			
			}
			else {
				num = (int)num % 16;
				if (num < 1.f) {
					this->R = 177;
					this->G = 204;
					this->B = 81;
				}
				else if (num < 2.f) {
					this->R = 150;
					this->G = 153;
					this->B = 137;
				}
				else if (num < 3.f) {
					this->R = 255;
					this->G = 237;
					this->B = 127;
				}
				else if (num < 4.f) {
					this->R = 198;
					this->G = 207;
					this->B = 255;
				}
				else if (num < 5.f) {
					this->R = 104;
					this->G = 204;
					this->B = 86;
				}
				else if (num < 6.f) {
					this->R = 72;
					this->G = 153;
					this->B = 58;
				}
				else if (num < 7.f) {
					this->R = 24;
					this->G = 82;
					this->B = 177;
				}
				else if (num < 8.f) {
					this->R = 238;
					this->G = 255;
					this->B = 133;
				}
				else if (num < 9.f) {
					this->R = 221;
					this->G = 204;
					this->B = 255;
				}
				else if (num < 10.f) {
					this->R = 93;
					this->G = 86;
					this->B = 204;
				}
				else if (num < 11.f) {
					this->R = 255;
					this->G = 94;
					this->B = 38;
				}
				else if (num < 12.f) {
					this->R = 119;
					this->G = 210;
					this->B = 111;
				}
				else if (num < 13.f) {
					this->R = 131;
					this->G = 255;
					this->B = 38;
				}
				else if (num < 14.f) {
					this->R = 204;
					this->G = 51;
					this->B = 68;
				}
				else if (num < 15.f) {
					R = 153;
					G = 87;
					B = 0;
				}
				else {
					R = 255;
					G = 255;
					B = 255;
				}
			}
			break;
		};
	
		case 4:		  // LSD Mark II
		{
			if (num == iterations) {
				this->R = 0;
				this->G = 0;
				this->B = 0;
			}
			else {
				num = (int)num % 16;
				if (num < 1.f) {
					this->R = 255;
					this->G = 229;
					this->B = 38;
				}
				else if (num < 2.f) {
					this->R = 102;
					this->G = 95;
					this->B = 42;
				}
				else if (num < 3.f) {
					this->R = 111;
					this->G = 174;
					this->B = 210;
				}
				else if (num < 4.f) {
					this->R = 204;
					this->G = 154;
					this->B = 55;
				}
				else if (num < 5.f) {
					this->R = 177;
					this->G = 177;
					this->B = 25;
				}
				else if (num < 6.f) {
					this->R = 126;
					this->G = 126;
					this->B = 58;
				}
				else if (num < 7.f) {
					this->R = 120;
					this->G = 156;
					this->B = 231;
				}
				else if (num < 8.f) {
					this->R = 25;
					this->G = 113;
					this->B = 177;
				}
				else if (num < 9.f) {
					this->R = 93;
					this->G = 112;
					this->B = 253;
				}
				else if (num < 10.f) {
					this->R = 126;
					this->G = 134;
					this->B = 190;
				}
				else if (num < 11.f) {
					this->R = 169;
					this->G = 179;
					this->B = 253;
				}
				else if (num < 12.f) {
					this->R = 65;
					this->G = 78;
					this->B = 177;
				}
				else if (num < 13.f) {
					this->R = 46;
					this->G = 65;
					this->B = 126;
				}
				else if (num < 14.f) {
					this->R = 204;
					this->G = 51;
					this->B = 68;
				}
				else if (num < 15.f) {
					R = 95;
					G = 165;
					B = 210;
				}
				else {
					R = 255;
					G = 255;
					B = 255;
				}
			}
			break;
		};

		case 5:		  //  Monochrom Mark I
		{
			if (num == iterations) {
				this->R = 0;
				this->G = 0;
				this->B = 0;
			}
			else {
				num = (int)num % 16;
				if (num < 1.f) {
					this->R = 37;
					this->G = 16;
					this->B = 71;
				}
				else if (num < 2.f) {
					this->R = 147;
					this->G = 110;
					this->B = 208;
				}
				else if (num < 3.f) {
					this->R = 104;
					this->G = 46;
					this->B = 199;
				}
				else if (num < 4.f) {
					this->R = 50;
					this->G = 38;
					this->B = 71;
				}
				else if (num < 5.f) {
					this->R = 49;
					this->G = 36;
					this->B = 69;
				}
				else if (num < 6.f) {
					this->R = 139;
					this->G = 104;
					this->B = 196;
				}
				else if (num < 7.f) {
					this->R = 184;
					this->G = 171;
					this->B = 206;
				}
				else if (num < 8.f) {
					this->R = 62;
					this->G = 57;
					this->B = 69;
				}
				else if (num < 9.f) {
					this->R = 103;
					this->G = 77;
					this->B = 145;
				}
				else if (num < 10.f) {
					this->R = 90;
					this->G = 67;
					this->B = 127;
				}
				else if (num < 11.f) {
					this->R = 180;
					this->G = 135;
					this->B = 255;
				}
				else if (num < 12.f) {
					this->R = 228;
					this->G = 211;
					this->B = 255;
				}
				else if (num < 13.f) {
					this->R = 114;
					this->G = 106;
					this->B = 127;
				}
				else if (num < 14.f) {
					this->R = 228;
					this->G = 111;
					this->B = 255;
				}
				else if (num < 15.f) {
					R = 186;
					G = 181;
					B = 232;
				}
				else {
					R = 255;
					G = 255;
					B = 255;
				}
			}
			break;
		};
		
		case 6:		  //  Monochrom Mark II
		{
			if (num == iterations) {
				this->R = 20;
				this->G = 20;
				this->B = 220;
			}
			else {
				num = (int)num % 16;
				if (num < 1.f) {
					this->R = 17;
					this->G = 122;
					this->B = 235;
				}
				else if (num < 2.f) {
					this->R = 76;
					this->G = 60;
					this->B = 240;
				}
				else if (num < 3.f) {
					this->R = 33;
					this->G = 69;
					this->B = 212;
				}
				else if (num < 4.f) {
					this->R = 37;
					this->G = 171;
					this->B = 212;
				}
				else if (num < 5.f) {
					this->R = 70;
					this->G = 125;
					this->B = 235;
				}
				else if (num < 6.f) {
					this->R = 147;
					this->G = 116;
					this->B = 246;
				}
				else if (num < 7.f) {
					this->R = 81;
					this->G = 88;
					this->B = 212;
				}
				else if (num < 8.f) {
					this->R = 85;
					this->G = 164;
					this->B = 212;
				}
				else if (num < 9.f) {
					this->R = 101;
					this->G = 202;
					this->B = 249;
				}
				else if (num < 10.f) {
					this->R = 75;
					this->G = 150;
					this->B = 185;
				}
				else if (num < 11.f) {
					this->R = 49;
					this->G = 99;
					this->B = 121;
				}
				else if (num < 12.f) {
					this->R = 23;
					this->G = 47;
					this->B = 58;
				}
				else if (num < 13.f) {
					this->R = 90;
					this->G = 181;
					this->B = 223;
				}
				else if (num < 14.f) {
					this->R = 124;
					this->G = 111;
					this->B = 255;
				}
				else if (num < 15.f) {
					R = 150;
					G = 181;
					B = 232;
				}
				else {
					R = 255;
					G = 255;
					B = 255;
				}
			}
			break;
		};
		}

        mandelbrot <<this->R <<' ' <<this->G <<' ' <<this->B <<'\n';    // wypisanie koloru do pliku
    }
};

#endif /* draw_hpp */

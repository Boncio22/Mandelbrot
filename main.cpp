//
//  main.cpp
//  lista8
//
//  Created by Tomek on 17.05.2016.
//  Copyright © 2016 Boncio22. All rights reserved.
//

#include <iostream>     // komunikacja terminalem
#include <fstream>      // wyrzucanie do pliku
#include <stdlib.h>     // naprawienie generowania strumieni plikow wyjsciowych
#include <string>       // w czyms trzeba te napisy trzymac a binbows nie potrafi sam sobie dac biblioteki
#include <thread>       // wielowatkowosc!!! :D

#include "draw.hpp"     // paleta kolorow
#include "complex.hpp"  // klasa liczb zespolonych

using namespace std;

#define picW    1920.0      // rozdzielczosc w poziomie
#define picH    1080.0      // rozdzielczosc w pionie
#define color   255         // glebia koloru

#define R_start 0.001643721971153   // poczatek animacji bedzie mial taka wspolrzedna rzeczywista na srodku obrazu
#define I_start 0.822467633298876   // poczatek animacji bedzie mial taka wspolrzedna zespolona na srodku obrazu

#define R_end   0.001643721971153   // koniec animacji bedzie mial taka wspolrzedna rzeczywista na srodku obrazu
#define I_end   0.822467633298876   // koniec animacji bedzie mial taka wspolrzedna zespolona na srodku obrazu

#define widR    1.25                // odleglosc od srodka do krawedzi obrazu
#define widI    widR*(picH/picW)    // zachowanie proporcji
#define zoom    0.99                // jaka czesc poprzedniego obrazu bedzei generowana w nastepnej klatce
#define potega  3                   // do ktorej potegi podnosic liczby zespolone

#define animacja    true        // robic animacje czy pojedyncza klatke
#define szybkosc    60          // ilosc fps w animacji
#define dlugosc     20          // dlugosc animacji w sekundach

#define iterations  500 + szybkosc * dlugosc    // tak ustalilem aby nie bylo zbyt malo iteracji
                                                // co skutkowaloby jednolitym kolorem na koniec animacji

#define ile_watkow 4        // ilosc klatek generowanych jednoczesnie preferowana
                            // ilosc to ilosc watkow jakie jednoczesnie jest przetwarzac twoj komputer

inline unsigned int findMandelbrot(complex num);    // wyliczanie koloru i eksportowanie go do pliku
inline void update(const long double krok_R, const long double krok_I,
                   long double &R_mid, long double &I_mid, long double &rozrzutR, long double &rozrzutI,
                   char &tysiace, char &setki, char &dziesiatki, char &jednosci);

void rysowanie(const string nazwa, const long double R_mid, const long double I_mid,
            const long double rozrzutR, const long double rozrzutI);

int main(int argc, char * argv[]) {

    string name;    // zmienna przechowujaca nazwe wspolna dla plikow
    if (argc < 2) { // jesli nie podano argumentu przy wywolywaniu funkcji
        cout <<"Podaj nazwę tworzonych plików: ";
        cin >> name;
    } else {
        name = argv[1]; // pierwszy argument po nazwie
    }

    char tysiace = 48, setki = 48, dziesiatki = 48, jednosci = 48;  // zera
    long double rozrzutR = widR;    // zadeklarowany rozrzut poczatkowy czesci rzeczywistej
    long double rozrzutI = widI;    // zadeklarowany rozrzut poczatkowy czesci urojonej
    

    unsigned int limit = szybkosc * dlugosc;    // ilosc klatek jaka ma byc wygenerowana
    if (!animacja)  // jesli nie masz zamiaru robic animacji
    {               // to po prostu wygeneruje tyle klatek ile masz ustalonych watkow
        limit = 1;
    }
    
    long double krok_R = (R_end - R_start) / limit; // liczy przesuniecie czesci rzeczywistej
    long double krok_I = (I_end - I_start) / limit; // liczy przesuniecie czesci urojonej
    
    long double R_mid = R_start;    // ustala srodek czesci rzeczywistej na ta zadeklarowana
    long double I_mid = I_start;    // ustala srodek czesci urojonej na ta zadeklarowana
    
    cout.sync_with_stdio(false);    // wylaczenie synchronizacji ze standardowym wyjsciem - przyspiesza
    string tmp = name;              // to bedzie na biezaco zmieniane przez dodawanie numeru

    for (unsigned int klatki = 0; klatki < limit; klatki+=ile_watkow)   // ile obiegow petli ma byc wygenerowanych, najwyzej
    {                                                                   // wygeneruje kilka klatek wiecej przy wielu watkach
        thread generacja[ile_watkow];   // tablica watkow do generowania plikow
        
        for (int i=0; i<ile_watkow; ++i) {  // przydzielenie zadania wszystkim watkom
            tmp = "Grafiki/" + name + tysiace + setki + dziesiatki + jednosci + ".ppm"; // ustalenie nazwy pliku
            
            generacja[i] = thread(rysowanie, tmp, R_mid, I_mid, rozrzutR, rozrzutI);    // watek ma przydzielone zadanie
                                                                                        // i zaczyna prace
            
            update(krok_R, krok_I, R_mid, I_mid, rozrzutR, rozrzutI, tysiace, setki, dziesiatki, jednosci); // aktualizacja zmiennych
        }
        
        for (int i=0; i<ile_watkow; ++i) {  // przelec po wszystkich watkach
            generacja[i].join();            // i czekaj na zakonczenie kazdego po kolei
        }

        cout <<"Narysowano " <<klatki+ile_watkow <<'/' <<limit <<" klatek." <<endl; // wypisz ile klatek
                                                                                    // zostalo juz wygenerowanych
    }

    cout.sync_with_stdio(true); // po zakonczeniu generacji wlacz synchro ze standardowym wyjsciem

    cout <<"Kuniec" <<endl; // i radosnie oglos koniec generowania plikow

    if (animacja) {     // jesli byla generowana animacja to lepiej to miec w png
        system("./konwersja.sh");   // skrypt konwersji do png
    }

    return 0;
}

/**
 *  wyliczanie kolory i eksportowanie go do pliku
 *
 *  @param num liczba zespolona o odpowiednich wspolrzednych
 *
 *  @return zwraca ilosc iteracji jaka przetrwal podany punkt
 */
inline unsigned int findMandelbrot(complex num) // funkcja inline do zwiekszenia wydajnosci
{
    unsigned int i = 0; // bo tak
    complex z;  // deklaracja w 3 liniach
    z.real =0;  // bo kompilator wczesniej sie
    z.imaginary = 0;    // burzyl ze mu sie nie podoba od razu
    
    while (i < iterations && z.real*z.real + z.imaginary*z.imaginary < 2) { // petla sprawdzajaca ile obiegow
                                                                            // przetrwa liczba zespolona
        z = (z^potega) + num;   // podnoszenie do konkretnej potegi
        ++i;    // zwiekszenie licznika przezytych obiegow
    }
    
    return i;   // zwraca ilosc przetrwanych obiegow
}

/**
 *  uaktualnienie wszystkich parametrow animacji
 *
 *  @param krok_R     przesuniecie skladowej rzeczywistej
 *  @param krok_I     przesuniecie skladowej urojonej
 *  @param R_mid      aktualny srodek wspolrednej rzeczywistej
 *  @param I_mid      aktualny srodek wspolrzenej urojonej
 *  @param rozrzutR   odleglosc srodka od krawedzi rzeczywistej
 *  @param rozrzutI   odleglosc srodka od krawedzi urojonej
 *  @param tysiace    licznik tysiecy
 *  @param setki      licznik setek
 *  @param dziesiatki licznik dziesiatek
 *  @param jednosci   licznik jednosci
 */
inline void update(const long double krok_R, const long double krok_I,
                   long double &R_mid, long double &I_mid, long double &rozrzutR, long double &rozrzutI,
                   char &tysiace, char &setki, char &dziesiatki, char &jednosci)
{
    rozrzutR *= zoom;   // tu nastepuje przyblizenie rzeczywiste
    rozrzutI *= zoom;   // tu nastepuje przyblizenie zespolone
    
    R_mid += krok_R;    // przesuniecie czesci rzeczywistej
    I_mid += krok_I;    // przesuniecie czesci urojonej
    
    jednosci++;         // inkrementacja jednosci
    if (jednosci == 58) {   // jesli jednosci = 10
        jednosci -= 10;     // to obniz do 0
        dziesiatki++;       // i zwieksz dziesiatki o 1
    }
    if (dziesiatki == 58) { // analogicznie jak w jednosciach
        dziesiatki -= 10;
        setki++;
    }
    if (setki == 58) {      // =||=
        setki -= 10;
        tysiace++;
    }
}

/**
 *  tu zaczyna sie zabawa i eksport do pliku
 *
 *  @param nazwa    nazwa pliku do jakiego bedziemy generowac
 *  @param R_mid    aktualny srodek czesci rzeczywistej
 *  @param I_mid    aktualny srodek czesci urojonej
 *  @param rozrzutR odleglosc srodka od krawedzi rzeczywistej
 *  @param rozrzutI odleglosc srodka od krawedzi urojonej
 */
void rysowanie(const string nazwa, const long double R_mid, const long double I_mid,
            const long double rozrzutR, const long double rozrzutI)
{
    long double R_unit = 2*rozrzutR/picW;   // jak szeroki jest pixel
    long double I_unit = 2*rozrzutI/picH;   // jak wysoki jest pixel
    
    ofstream mandelbrot(nazwa.c_str()); // utworzenie strumienia plikow wyjsciowych o podanej wczesniej nazwie
    
    mandelbrot <<"P3" <<endl;               // informacja o formacie pliku
    mandelbrot <<picW <<' ' <<picH <<endl;  // informacja o wymiarach pliku
    mandelbrot <<color <<endl;              // inforrmacja o glebi koloru
    
    for (int y=0; y<picH; ++y) {        // przewijanie od gory w dol
        for (int x=0; x<picW; ++x) {    // przewijanie od lewej do prawej
            complex C;  // utworzenie liczby zespolonej
            C.real = R_mid - rozrzutR + x * R_unit; // nadanie jej odpowiednich wartosci
            C.imaginary = I_mid - rozrzutI + y * I_unit;    // na podstawie wspolrzednych na obrazie
            
            draw pixel(findMandelbrot(C), mandelbrot, iterations);  // rysowanie odpowiedniego pixela
        }
    }
    
    mandelbrot.close(); // zamkniecie strumienia wyjsciowego plikow
}








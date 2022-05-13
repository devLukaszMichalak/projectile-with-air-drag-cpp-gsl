//
//  rownanie.hpp
//  rownanie
//
//  Created by Łukasz Michalak on 31/05/2019.
//  Copyright © 2019 Łukasz Michalak. All rights reserved.
//

#ifndef rownanie_hpp
#define rownanie_hpp

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "gsl/gsl_errno.h"
#include "gsl/gsl_matrix.h"
#include "gsl/gsl_odeiv2.h"
#include <vector>
#include <cmath>

struct data{
    float k;
    float mass;
    float g;
};
struct rozwiazanie{
    std::vector<float> x;
    std::vector<float> y;
    std::vector<float> predkosc_x;
    std::vector<float> predkosc_y;
    std::vector<float> time;
    int liczba_wartosc;
    int error;
};

int func (double t, const double y[], double f[], void *params);

rozwiazanie solwer(int x);//do błędów

rozwiazanie solwer(float predkosc_paczatkowa,float kat_w_stopniach,float masa_obiektu,float przyspieszenie_grawitacyjne,float predkosc_wiatru_x,float predkosc_wiatru_y,float wspolczynnik_do_oporu_powietrza);

//instrukcja
//predkosc_paczatkowa to jest ta pod katem obiektu ktory rzucamy, nie trzeba jej rozbiajc na skłądowe tak jak predkosci wiatru (linijka 43-47)
//
//kierunek predkosci wiatru jest jak osie na ukladzie wspolrzednych, jak wiatr wieje ze obiektem czyli mu pomaga to jest dodatni a jak przed (przeszkada) to ujemny
//plus trzeba rozbic wiart na składowa x i y wiec tam z kata pod jakim wieje policzyc np v*cos alfa = v_x gdzie alfa kat pod jakim wieje v predkosc wiatru v_x predkosc składowa w kierunu x
//
//  solwer(30*sqrt(2), 45, 10, 9.81,1,0,0.2);     wiatr pomaga na x a na y 0
//  solwer(30*sqrt(2), 45, 10, 9.81,-1,0,0.2);     waitr przeszkadza na x a na y 0
//
//wspolczynnika do oporu powietrza nie trzba podawac jest liczony automatycznie, chyba ze uzytwkonik chce zmienic to wtedy podaje wartosc przy wywoływaniu i zmienia sie na wartosc podana przez urzytkownika, wiec trzeba zaimplementowac dwa wywołania w interfejsie,spytac sie urzytkownika czy chce podawac wlasny wspolczynnik czy nie no i jedno bez podawania wspolczynnika i drugie z podawaniem
//
//  solwer(30*sqrt(2), 45, 10, 9.81,-1,0,0.2);     z wspolczynnikiem urzytkownika
//
//funkcja zwraca strukture w ktorej sa wektory z danymi x y predkosc na x oraz y oraz czasie i liczbie elementow
//zeby odczytac to tworzymy zmienna typu "rozwiazanie"; cały przykład linijka 63
//
//rozwiazanie moje_dane = solwer(bla bla bla)
//moje_dane.x[0]    pierwszy element polozenia x
//
//w srodku tez jest pole liczba wartosc (ona sie zmienia) wiec zeby przeleciec po wszystkich wartosciach
//for(int i=0;i<moje_dane.liczba_wartosc;i++)
//
/*  przykłądowy program wyswietla wszystkie x
 
 int main ()
 {
 rozwiazanie moje_dane=solwer(30*sqrt(2), 45, 10, 9.81,-1,0,0.2);
 for(int i=0;i<moje_dane.liczba_wartosc;i++){
 cout<<moje_dane.x[i]<<endl;
 }
 return 0;
 }

 */
//jesli moje_dane.error == 0 to wszystko poszło okej a jesli jest równe moje_dane.error == 1 lub 2 to sie gdzies wyłorzyl i nalerzy odpalic go drugi raz i cos zmienic z danymi, raczej trzeba to sprawdzic przed wypisywaniem wartosci

#endif /* rownanie_hpp */

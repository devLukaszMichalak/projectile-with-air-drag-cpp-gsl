//
//  main.cpp
//  rownanie rozniczkowe
//
//  Created by Łukasz Michalak on 31/05/2019.
//
//
#include <iostream>
#include "rownanie.hpp"
#include "interface.h"
#include <fstream>


int main ()
{

    Interface menu;
    rozwiazanie dane=menu.pokaz();//wartosci podanych przez solver
    if(dane.error==20){
        std::cout<<"Zamykanie programu"<<std::endl;
        return 0;
    }
    else if(dane.error!=0){
        std::cout<<"Wystąpił bład z kodem: "<<dane.error;
    }
    else{
        
        std::ofstream fout;                //zapis do pliku wartosci
        fout.open("result.txt");
        fout << "t\tx\ty\tV_x\tV_y\t"<<std::endl; //nagłówek
        for(int i = 0; i < dane.liczba_wartosc; i++)
            fout <<std::setprecision(5)<< dane.time[i] << "\t" << dane.x[i] <<"\t"<< dane.y[i]<<"\t"<<dane.predkosc_x[i]<<"\t"<<dane.predkosc_y[i]<< "\t"<<std::endl;
        fout.close();
        std::cout<<"Plik z rozwiazaniami zostal utworzony"<<std::endl;
    }
    
    
    return 0;
}

/* ✔ */

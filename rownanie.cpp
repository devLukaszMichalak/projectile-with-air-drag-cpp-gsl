//
//  rownanie.cpp
//  rownanie
//
//  Created by Łukasz Michalak on 31/05/2019.
//  Copyright © 2019 Łukasz Michalak. All rights reserved.
//

#include "rownanie.hpp"

int func (double t, const double y[], double f[], void *params){
    data* my_params=(data*)params;
    float k=my_params->k;
    float mass=my_params->mass;
    float g=my_params->g;
    f[0] = -k/mass*sqrt(y[0]*y[0]+y[1]*y[1])*y[0]-g;
    f[1] =-k/mass*sqrt(y[0]*y[0]+y[1]*y[1])*y[1];
    return GSL_SUCCESS;
}
rozwiazanie solwer(int x){
    rozwiazanie temp;
    temp.error=x;
    return temp;
}

rozwiazanie solwer(float predkosc_paczatkowa,float kat_w_stopniach,float masa_obiektu,float przyspieszenie_grawitacyjne,float predkosc_wiatru_x,float predkosc_wiatru_y,float wspolczynnik_do_oporu_powietrza){
    
    rozwiazanie rozwiazanie;
    float rad=kat_w_stopniach*2*4*atan(1.0)/360;//4*atan1.0 to pi
    float v_0_x=predkosc_paczatkowa*cos(rad)+predkosc_wiatru_x;
    float v_0_y=predkosc_paczatkowa*sin(rad)+predkosc_wiatru_y;
    const int dim = 2;
    data my_params;
    my_params.mass=masa_obiektu;
    my_params.g=przyspieszenie_grawitacyjne;
    if(wspolczynnik_do_oporu_powietrza==-999){
        my_params.k=my_params.mass*my_params.g/v_0_y/v_0_y; //mg=|kv^2|
    }else{
        my_params.k=wspolczynnik_do_oporu_powietrza;
    }
    
    gsl_odeiv2_system sys = {func, NULL, dim, &my_params};
    gsl_odeiv2_driver * d = gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rkf45, 1e-6, 1e-6, 0.0);
    
    double ti=0,t=0;
    double y[2] = {v_0_y,v_0_x};  //wartosci poczatkowe
    
    
    float delta_t=0.01; //co tylke nowy punkt polozenia bedzie
    
    for (int i = 1;; i++){
        ti += delta_t; //co 0.01 bo dokładnie ale za to duzo wartosci
        int status = gsl_odeiv2_driver_apply (d, &t, ti, y);
        if (status != GSL_SUCCESS){
            std::cout<<"Error, return value= "<<status<<std::endl;
            rozwiazanie.error=1;
            return rozwiazanie;
        }
        
        rozwiazanie.time.push_back(ti);
        rozwiazanie.predkosc_x.push_back(y[1]);
        rozwiazanie.predkosc_y.push_back(y[0]);
        if(i==1){
            rozwiazanie.x.push_back(rozwiazanie.predkosc_x.back()*delta_t); //y[1] = Vx    y[0]=Vy
            rozwiazanie.y.push_back(rozwiazanie.predkosc_y.back()*delta_t);
            rozwiazanie.liczba_wartosc=i;
        }
        else{
            float a=rozwiazanie.y[i-2]+rozwiazanie.predkosc_y[i-1]*delta_t;//zeby dwa razy nie liczyc to raz i potem warunek i do pushbacka
            if(a>0){
                rozwiazanie.x.push_back(rozwiazanie.x[i-2]+rozwiazanie.predkosc_x[i-1]*delta_t);
                rozwiazanie.y.push_back(a);
                rozwiazanie.liczba_wartosc=i;
            }
            else{
                rozwiazanie.time.pop_back();
                rozwiazanie.predkosc_x.pop_back();
                rozwiazanie.predkosc_y.pop_back();//to juz tw wartosci z minusa wiec sie pozbywam
                gsl_odeiv2_driver_free (d);
                rozwiazanie.error=0;
                return rozwiazanie;
            }
        }
    }
    gsl_odeiv2_driver_free (d);
    rozwiazanie.error=2;
    return rozwiazanie;
}


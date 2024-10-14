/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 4 de octubre de 2024, 16:46
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Paquete{
    int ganancia;
    int peso;
};

int compara(Paquete paq1,Paquete paq2){
    return (paq1.ganancia/paq1.peso) < (paq2.ganancia/paq2.peso);
}

int gananciaExportacion(Paquete paquetes[],int capacidad){
    int n = (&paquetes[5])-(&paquetes[0]);
    sort(paquetes,n+paquetes,compara);
    vector<Paquete> solu;
    int ganancia=0;
    for (int i=0; i<n ;i++){
        if(paquetes[i].peso<=capacidad){
            ganancia += paquetes[i].ganancia;
            capacidad-=paquetes[i].peso;
        }
    }
    
    return ganancia;
}
    
int main(int argc, char** argv) {
    Paquete paquetes[] = {{10,2},
                          {15,3},
                          {10,5},
                          {24,12},
                          {8,2}};
    int capacidad = 15;
    cout << gananciaExportacion(paquetes,capacidad);
                          
    return 0;
}


/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 4 de octubre de 2024, 22:45
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define N 8

struct Punto{
    int punto;
    int distancia;
};

int compara(struct Punto p1,struct Punto p2){
    return p1.distancia < p2.distancia;
}

int rutaMin(int mapa[][N],int ini,int fin){
    Punto punto;
    int total=0;
    for(int i=0; i<N ;i++){
        vector<Punto> vecinos;
        for(int k=0;k<N;k++){
            if(mapa[ini][k]){
                punto.distancia = mapa[ini][k];
                punto.punto = k;
                vecinos.push_back(punto);
            }
        }
        if(!vecinos.empty()){
            sort(vecinos.begin(),vecinos.end(),compara);
            total+=vecinos[0].distancia;
            ini = vecinos[0].punto;
            if(ini==fin) break;
        }else{
            cout << "No hay solucion";
            return -1;
        }
        
    }
    return total;
}

int main(int argc, char** argv) {
    int mapa[][N] = {{0,4,5,6,0,0,0,0},
                     {0,0,0,0,2,0,0,0},
                     {0,0,0,0,0,0,0,3},
                     {0,0,0,0,0,3,0,0},
                     {0,0,0,0,0,0,10,0},
                     {0,0,0,0,0,0,2,0},
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0}};
    
    
    cout << endl << rutaMin(mapa,2,6);
    return 0;
}


/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 1 de octubre de 2024, 14:40
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX 4
struct nodo{
    int distancia;
    int punto;
};

bool compara(nodo a, nodo b){
    return a.distancia<b.distancia;
}

int minruta(int ini,int fin, int mapa[][MAX]){
    int total = 0;
    int ciudad = ini;
    while(1){
        vector<nodo> vecinos;
        nodo paso;
        //cargando vecis
        for(int i=0; i<MAX ;i++){
            if(mapa[ciudad][i]>0){
                paso.punto=i;
                paso.distancia=mapa[ciudad][i];
                vecinos.push_back(paso);
            }
        }
        if(not vecinos.empty()){
            sort(vecinos.begin(),vecinos.end(),compara);
            ciudad = vecinos[0].punto;
            total+=vecinos[0].distancia;
        }else{
            cout << "No se encontro la solucion";
            return -1;
        }

        if(ciudad==fin) break;
        
        vecinos.clear();
    }
    
    return total;wdw
}


int main(int argc, char** argv) {
    
    return 0;
}


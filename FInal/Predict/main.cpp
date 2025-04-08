/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 9 de diciembre de 2024, 17:35
 */

#include <iostream>
#include <ctime>
#include <climits>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
#define NITERACIONES 100
#define alpha 0.3


struct Paquete{
    int id;
    int bloques;
    int inicio;
};

int compara(Paquete pa1, Paquete pa2){
    return pa1.bloques<pa2.bloques;
}

int verifica(double RCL,const vector<Paquete> &vpaq){
    int cont=0;
    for (int i = 0; i < vpaq.size(); i++) {
        if(RCL<=vpaq[i].bloques)
            cont++;
        
    }

    return cont;
}

int entra(const Paquete &paq,int arregloAux[]){
//    bool lleno = false;
//    for (int i = paq.inicio; i < paq.inicio+paq.bloques; i++) 
//        if(arregloAux[i]!=0)
//            lleno = true;
//    if(!lleno)
//        for (int i = paq.inicio; i < paq.inicio+paq.bloques; i++)
//            arregloAux[i] = paq.id;
//    return !lleno;
    int contLibres=0;
    bool ini=true;
    int inicioLibre,finlibre=-1;
    for(int i=paq.inicio; i< 7;i++){
        if(!arregloAux[i] && ini){
            inicioLibre = i;
            ini = false;
        }
        if(!ini && arregloAux[i]){
            finlibre = i;
            break;
        }
    }
    if(finlibre == -1)
        finlibre = 7;

    if(finlibre-inicioLibre>=paq.bloques){
        for(int i=inicioLibre; i<paq.bloques+inicioLibre ;i++)
            arregloAux[i] = paq.id;
        return true;
    }
    return false;
}

void grasp(const vector<Paquete> &paquetes){
    srand(time(NULL));
    int mejorNum = -1;
    int arregloMax[7] = {};
    for (int i = 0; i < NITERACIONES; i++) {
        vector<Paquete> vpaq = paquetes;
        sort(vpaq.begin(),vpaq.begin()+vpaq.size(),compara);
        int arregloAux[7] = {};
        int numPaq = 0;
        
        while(not vpaq.empty()){
            int betha = vpaq[0].bloques;
            int tau = vpaq.back().bloques;
            double RCL = betha + alpha*(tau-betha);
            int ind = verifica(RCL,vpaq);
            int indA = rand()%ind;
            
            if(entra(vpaq[indA],arregloAux))
                numPaq++;
            
            vpaq.erase(vpaq.begin()+indA);
        }
        if(mejorNum < numPaq){
            for (int h = 0; h < 7; h++)
                arregloMax[h] = arregloAux[h];
            mejorNum = numPaq;
        }
    }
    for(int i=0; i<7;i++)
        cout << arregloMax[i] << "  ";
    
    cout << endl << mejorNum << endl; 
}
    
int main(int argc, char** argv) {
    vector<Paquete> paquetes = {{1,2,1},
                                {2,3,2},
                                {3,1,5},
                                {4,3,3}};
    
    grasp(paquetes);
    
    return 0;
}


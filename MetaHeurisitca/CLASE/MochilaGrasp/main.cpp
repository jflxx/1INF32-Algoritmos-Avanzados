/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 22 de octubre de 2024, 15:05
 */

#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_IT 10000
#define ALPHA 0.3
using namespace std;

bool cmp(int a, int b){
    return a>b;
}
int verifica(vector <int> &paq,int rcl){
    
}

void cargamochila(int paq[],int peso,int n){
    int residual;
    int mejorResidual = 99999;
    for(int k=0; k<MAX_IT ;k++){
        srand(time(NULL));
        vector<int> soluciones;
        sort(paq,paq+n,cmp);
        vector<int> paquetes;
        paquetes.insert(paquetes.begin(),paq,paq+n);
        residual = peso;
        
        while(not paquetes.empty()){
            int beta=paquetes[0];
            int tau=paquetes[paquetes.size()-1];
            double rcl = beta - ALPHA*(beta - tau);
            int ind = verifica(paquetes,rcl);
            int inda = rand()%ind;
            if(residual-paquetes[inda]>=0){
                soluciones.push_back(paquetes[inda]);
                residual-=paquetes[inda];
            }
            paquetes.erase(paquetes.begin()+inda);
        }
        if(mejorResidual>residual)
            mejorResidual = residual;
    }
    
    cout << mejorResidual;
}

int main(int argc, char** argv) {
    int paq[] = {10,2,1,5,9,8};
    int n=sizeof(paq)/sizeof(int);
    
    cargamochila(paq,14,n);
    
    return 0;
}


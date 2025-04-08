/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 8 de noviembre de 2024, 22:24
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <ctime>
using namespace std;
#define ITERACIONES 100000
#define alpha 0.3


int cmp(int a, int b){
    return a>b;
}

int verificar(vector<int> &vpaq,int RCL){
    int cont = 0;
    for(int i=0; i<vpaq.size() ;i++){
        if(RCL<=vpaq[i]) cont++;
    }
    return cont;
}

void mochilaGrasp(int paquetes[],int peso,int n){
    int PESOa = peso,min = 999999;
    vector<int> menor;
    
    for(int i=0; i<ITERACIONES ;i++){
        srand(time(NULL));
        sort(paquetes,paquetes+n,cmp);
        peso = PESOa;
        vector<int> vpaq;
        vpaq.insert(vpaq.begin(),paquetes,paquetes+n);
        vector<int> resultado;
        while(not vpaq.empty()){
            int betha = vpaq[0];
            int tau = vpaq.back();
            double RCL = betha - alpha*(betha-tau);
            int ind = verificar(vpaq,RCL);
            int indA = rand()%ind;
            
            if(peso-vpaq[indA]>=0){
                peso-=vpaq[indA];
                resultado.push_back(vpaq[indA]);
            }
            vpaq.erase(vpaq.begin()+indA);
        }
        
        if(peso<min){
            min = peso;
            menor = resultado;
        }
        
    }
    
    for(int i=0; i<menor.size() ;i++){
        cout << menor[i] << "  ";
    }
    
}

int main(int argc, char** argv) {
    int paquetes[5]={9,2,3,5,1};
    int peso = 14;
    
    
    mochilaGrasp(paquetes,peso,5);
    return 0;
}


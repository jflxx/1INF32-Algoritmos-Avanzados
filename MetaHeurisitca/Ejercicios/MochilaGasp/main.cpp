/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 4 de noviembre de 2024, 23:58
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;
#define ITER 10000
#define alpha 0.3

int compara(int a,int b){
    return a>b;
}

int verifica(vector<int> vpaq,int RCL){
    
    int cont=0;
    
    for(int i=0;i<vpaq.size();i++)
        if(RCL<=vpaq[i])cont++;
    return cont;
}

void cargamochila(int paq[],int peso,int n){
    sort(paq,paq+n,compara);
    int mejor=99999;
    vector<int> soluMejor;
    for(int i=0; i<ITER ;i++){
        int residual = peso;
        vector<int> solucion;
        vector<int> vpaq;
        vpaq.insert(vpaq.begin(),paq,paq+n);
        srand(time(NULL));
        
        while(not vpaq.empty()){
            int betha = vpaq[0];
            int tau = vpaq[vpaq.size()-1];
            double RCL = betha - alpha*(betha-tau);
            int ind = verifica(vpaq,RCL);
            int indA = rand()%ind;
            if(residual-vpaq[indA]>=0){
                residual-=vpaq[indA];
                solucion.push_back(vpaq[indA]);
            }
            vpaq.erase(vpaq.begin()+indA);
            for(int i=0; i<vpaq.size() ;i++)
                cout << vpaq[i] << "  ";
            cout << endl;
        }
        if(residual<mejor){
            mejor = residual;
            soluMejor = solucion;
        }
    }
    
    
    for(int i=0; i<soluMejor.size() ;i++)
        cout << soluMejor[i] << "  ";
}

int main(int argc, char** argv) {
    int paq[]={10,2,1,5,9,8};
    int n=sizeof(paq)/sizeof(paq[0]);
    int peso=14;
    cargamochila(paq,peso,n);
    return 0;
}


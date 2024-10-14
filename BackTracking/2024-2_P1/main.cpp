/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 5 de octubre de 2024, 19:44
 */

#include <iostream>
#include <vector>
#include <map>
using namespace std;
struct Lavadora{
    int internos;
    int capacidad;
    int costo;
};

int CalcularLavadora(Lavadora lavadora,vector<int> ropaSucia,int i,int &max,int &pesoR,
        map<int,bool> &utilizado,map<int,bool> &utilizadoMax){
    if(pesoR <= lavadora.capacidad && max < pesoR){
        max = pesoR;
        for(auto u:utilizado){
            utilizadoMax[u.first] = u.second;
        }
    }
    if(pesoR>lavadora.capacidad or i==ropaSucia.size())
        return 0;
    
    pesoR+=ropaSucia[i];
    utilizado[i] = true;
    if(CalcularLavadora(lavadora,ropaSucia,i+1,max,pesoR,utilizado,utilizadoMax))
        return 1;
    else{
        pesoR-=ropaSucia[i];
        utilizado[i] = false;
        return CalcularLavadora(lavadora,ropaSucia,i+1,max,pesoR,utilizado,utilizadoMax);
    }
    
}


int main(int argc, char** argv) {
    Lavadora lavadoras[]={{0,0,0},
                     {6,50,5},
                     {7,50,6},
                     {4,50,6},
                     {5,50,5},
                     {2,50,9}};
    map<int,vector<int>> ropaSucia;
    ropaSucia[1].insert(ropaSucia[1].begin(),{14,11,10,19,14,11});
    ropaSucia[2].insert(ropaSucia[2].begin(),{20,11,11,10,15,17,8});
    ropaSucia[3].insert(ropaSucia[3].begin(),{15,16,15,16});
    ropaSucia[4].insert(ropaSucia[4].begin(),{11,4,19,12,10});
    ropaSucia[5].insert(ropaSucia[5].begin(),{18,12});
    int max=0,pesoR=0;
    map<int,bool> utilizado,utilzMax;
//    map<int,bool> 
    CalcularLavadora(lavadoras[1],ropaSucia[1],0,max,pesoR,utilizado,utilzMax);
    cout << endl <<  max << endl;
    
    for(auto x:utilzMax){
        cout << x.first +1 << ": " << x.second << endl;
    }
    
    
    return 0;
}


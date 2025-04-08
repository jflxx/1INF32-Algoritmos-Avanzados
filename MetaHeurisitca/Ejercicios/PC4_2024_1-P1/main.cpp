/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 6 de noviembre de 2024, 17:51
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
using namespace std;
#define ITER 10000
#define alpha 0.3

struct schema{
    int id;
    int capacidad;
    int velocidad;
    vector<int> asignados;
};

int cmp(schema a,schema b){
    return a.velocidad > b.velocidad;
}

int verificar(vector<schema> vtablas,int RCL1){
    int cont = 0;
    for(int i=0; i<vtablas.size() ;i++){
        if(RCL1<=vtablas[i].velocidad) cont++;
    }
    return cont;    
}

void grasp(schema tablas[],schema discos[],int n,int m){
    int minGlobal=0;
    
    vector<schema> mejor;
    for(int i=0; i<ITER ;i++){
        int minLocal=99999;
        vector<schema> vtablas,vdiscos;
        vtablas.insert(vtablas.begin(),tablas,tablas+n);
        vdiscos.insert(vdiscos.begin(),discos,discos+m);
        sort(vtablas.begin(),vtablas.begin()+n,cmp);
        srand(time(NULL));
        while(not vtablas.empty()){
            sort(vdiscos.begin(),vdiscos.end(),cmp);
            int betha1 = vtablas[0].velocidad;
            int tau1 = vtablas.back().velocidad;
            int RCL1 = round(betha1 - alpha*(betha1-tau1));
            int ind1 = verificar(vtablas,RCL1);
            int indA1 = rand()%ind1;
            
            int betha2 = vdiscos[0].velocidad;
            int tau2 = vdiscos.back().velocidad;
            int RCL2 = round(betha2 - alpha*(betha2-tau2));
            int ind2 = verificar(vdiscos,RCL2);
            int indA2 = rand()%ind2;
            
            if(vdiscos[indA2].velocidad-vtablas[indA1].velocidad>=0){
                vdiscos[indA2].velocidad -= vtablas[indA1].velocidad;
                vdiscos[indA2].asignados.push_back(vtablas[indA1].id);
            }
            vtablas.erase(vtablas.begin()+indA1);
            
        }
        
        sort(vdiscos.begin(),vdiscos.begin()+m,cmp);
        if(minGlobal<vdiscos.back().velocidad){
            minGlobal = vdiscos.back().velocidad;
            mejor = vdiscos;
        }
    }
    
    for(auto x:mejor){
        cout << "disco: " << x.id << "  Tablas: ";
        for(auto a:x.asignados)
            cout << a << "  ";
        cout << endl;
    }
    cout << minGlobal;
}

int main(int argc, char** argv) {
    schema tablas[6] =  {{1,20,150},
                         {2,10,100},
                         {3,15,80},
                         {4,100,50},
                         {5,50,120},
                         {6,100,10}};
    schema discos[3] =  {{1,800,250},
                         {2,750,200},
                         {3,850,200}};
    
    grasp(tablas,discos,6,3);
    return 0;
}


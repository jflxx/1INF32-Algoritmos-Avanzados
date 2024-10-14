/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 9 de octubre de 2024, 19:50
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Proyecto{
    int idProyecto;
    int Costo;
    int Ganancia;
    int beneficio;
    vector<int> predecesores;
};

int compara(Proyecto p1,Proyecto p2){
    return p1.Ganancia*p1.beneficio/p1.Costo > p2.Ganancia*p2.beneficio/p2.Costo;
}

bool estanPredecesores(Proyecto proy,bool usados[],int N){
    int cantPredecesores,cont=0;
    cantPredecesores = proy.predecesores.size();
    for(int x:proy.predecesores){
        if(usados[x-1])
            cont++;
    }
    
    if(cont == cantPredecesores)
        return true;
    return false;
}

void elegirProyectos(Proyecto proyectos[],int N,int P){
    sort(proyectos,proyectos+N,compara);
    vector<Proyecto> temp;
    int presupuesto = P;
    int ganancia =0;
    bool usados[N]={};
    
    vector<int>seleccionados;
    for(auto it =temp.begin();it!=temp.end();){
        int restante = presupuesto-(*it).Costo;
        if(restante >=0 && estanPredecesores(*it,usados,N)){
            usados[(*it).idProyecto-1] = true;
            seleccionados.push_back((*it).idProyecto);
            ganancia+=(*it).Ganancia;
            presupuesto -= (*it).Costo;
            temp.erase(it);
            it = temp.begin();
        }else{
            ++it;
        }
    }
    
    if(!seleccionados.empty()){
        cout << "Proyectos seleccionados: ";
        for(auto it=seleccionados.begin();it!=seleccionados.end();it++){
            cout << (*it) << "  ";
        }
        cout << endl;
    }
    
    cout << "Ganancia = " << ganancia;
    
}

int main(int argc, char** argv) {
    Proyecto proyectos[]{{1,80,150,2},
                         {2,20,80,5},
                         {3,100,300,1},
                         {4,80,150,4},
                         {5,50,80,2},
                         {6,10,50,1},
                         {7,50,120,2},
                         {8,50,150,4}};
    proyectos[2-1].predecesores.push_back(4);
    proyectos[3-1].predecesores.push_back(1);
    proyectos[3-1].predecesores.push_back(2);
    proyectos[6-1].predecesores.push_back(2);
    proyectos[7-1].predecesores.push_back(6);
    proyectos[8-1].predecesores.push_back(6);
    
    elegirProyectos(proyectos,8,250);
  
    return 0;
}


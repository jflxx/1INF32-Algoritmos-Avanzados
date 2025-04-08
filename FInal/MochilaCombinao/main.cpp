/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 8 de diciembre de 2024, 21:17
 */

#include <iostream>

#include "Paquete.h"
#include "mochilaGrasp.h"
#include <cmath>
#include <map>
using namespace std;
#define NITERACIONES 100
#define NIND 10
#define Tseleccion 0.5
#define Pcasamiento 0.5
#define Tmutacion 0.8
Paquete *gpaq;

void muestrapoblacion(vector<vector<int>> poblacion,Paquete paquetes[]){
    
    for(int i=0;i<poblacion.size();i++){
        int peso = 0 ;
        for(int j=0;j<poblacion[i].size();j++){
            cout << poblacion[i][j] << "  ";
            peso += poblacion[i][j]*paquetes[j].peso;
        }
        cout << " peso: " << peso << endl;
//        cout <<" fo="<< calculafitness(poblacion[i],assetPool) <<endl;
    }
}

void generapoblacioninicial(vector<vector<int>> &poblacion,Paquete Paquetes[],int n,int peso){
    for (int i = 0; i < NIND; i++) {
        vector<Paquete> vpaq = grasp(Paquetes,n,peso);
        vector<int> solo;
        for (int j = 0; j < n; j++) 
            solo.push_back(0);
        for (Paquete v:vpaq)
            solo[v.id-1] = 1;
        poblacion.push_back(solo);
    }
}

int calculafitness(const vector<int> cromo,Paquete assetPool[]){
    double sumaPOP=0;
    int cont=0;
    for(int i=0;i<cromo.size();i++){
        // suma de precios optimistas
        sumaPOP += cromo[i] * assetPool[i].valor/assetPool[i].peso;
    }

    return sumaPOP;
}

void calculasupervivencia(const vector<vector<int>>poblacion,
    vector<int>&supervivencia,Paquete assetPool[]){
    int suma=0;
    
    for(int i=0;i<poblacion.size();i++)
        suma+=calculafitness(poblacion[i],assetPool);
    for(int i=0;i<poblacion.size();i++){
        int fit= round(100*(double)calculafitness(poblacion[i],assetPool)/suma);
        supervivencia.push_back(fit);
    }
}

void cargaruleta(vector<int>supervivencia,int *ruleta){
    int ind=0;
    for(int i=0;i<supervivencia.size();i++)
        for(int j=0;j<supervivencia[i];j++)
            ruleta[ind++]=i;
}

void seleccion(vector<vector<int>>&padres,vector<vector<int>>poblacion,
    Paquete assetPool[],int n,int maxInv){
    int ruleta[100]{-1};
    vector<int>supervivencia;
    calculasupervivencia(poblacion,supervivencia,assetPool);
    cargaruleta(supervivencia,ruleta);
    int nseleccionados= poblacion.size()*Tseleccion;        
    for(int i=0;i<nseleccionados;i++){
        int ind=rand()%100;
        if(ruleta[ind]>-1)
            padres.push_back(poblacion[ruleta[ind]]);
            
    } 

}

bool aberracion(vector<int>cromo,Paquete assetPool[],int peso){
    int total=0;
    
    for(int i=0;i<cromo.size();i++)
        total+=cromo[i]*assetPool[i].peso;
    
    return total>peso;
}

void generahijo(vector<int>padre,vector<int>madre,
        vector<int>&hijo){
    int pos=round(padre.size()*Pcasamiento);
    
    for(int i=0;i<pos;i++)
        hijo.push_back(padre[i]);
    for(int i=pos;i<madre.size();i++)
        hijo.push_back(madre[i]);
}

void casamiento(vector<vector<int>>padres,
        vector<vector<int>>&poblacion,Paquete assetPool[],int peso){
    for(int i=0;i<padres.size();i++)
        for(int j=0;j<padres.size();j++)
            if(i!=j){
                vector<int>cromo;
                generahijo(padres[i],padres[j],cromo);
                if(!aberracion(cromo,assetPool,peso))
                    poblacion.push_back(cromo);
            }
}

int compacta(vector<int>cromo){
    int num=0;
    for(int i=0;i<cromo.size();i++)
        num+=pow(2,i)*cromo[i];
    
    return num;
    
}

void eliminaaberraciones(vector<vector<int>> &poblacion,Paquete assetPool[]){
    map<int,vector<int>> municos;
    
    for(int i=0;i<poblacion.size();i++){
        int num=compacta(poblacion[i]);
        municos[num]=poblacion[i];
    }
    poblacion.clear();
    for(map<int,vector<int>>::iterator it=municos.begin();
            it!=municos.end();it++){
        poblacion.push_back(it->second);
    }
        
    
}

bool compara2(vector<int>a,vector<int>b){
    int suma=0,sumb=0;
   
    for(int i=0;i<a.size();i++)
        suma+=calculafitness(a,gpaq);
    for(int i=0;i<b.size();i++)
        sumb+=calculafitness(b,gpaq);
    return suma>sumb;
}

void generarpoblacion(vector<vector<int>> &poblacion,
        Paquete assetPool[],int peso){
    
    gpaq = assetPool;
    sort(poblacion.begin(),poblacion.end(),compara2);
    if(poblacion.size()>NIND){
        poblacion.erase(poblacion.begin()+NIND,poblacion.end());
        
    }
    
}

double muestramejor(const vector<vector<int>> &poblacion,
       Paquete assetPool[] ,int peso){
    int mejor=0;
    int mejorV = 0;
    for(int i=0;i<poblacion.size();i++)
        if(calculafitness(poblacion[mejor],assetPool)<calculafitness(poblacion[i],assetPool))
            mejor=i;
    cout << endl<<"La mejor solucion es:" << calculafitness(poblacion[mejor],assetPool)<<endl;
    for(int i=0;i<poblacion[mejor].size();i++){
        cout << poblacion[mejor][i] << "  ";
        mejorV += assetPool[i].valor*poblacion[mejor][i];
    }
    cout << endl << "Mejor valor: " << mejorV << endl;
    return calculafitness(poblacion[mejor],assetPool);
}

void mochilaGenetico(Paquete Paquetes[],int n,int peso){
    int cont=0;
    vector<vector<int>> poblacion;
    srand(time(NULL));
    
    generapoblacioninicial(poblacion,Paquetes,n,peso);
    muestrapoblacion(poblacion,Paquetes);  
    double suma=0;
    while(1){
        vector<vector<int>> padres;
        seleccion(padres,poblacion,Paquetes,n,peso);
        casamiento(padres,poblacion,Paquetes,peso);
        
        
//        mutacion(poblacion,padres,assetPool,maxInversion);
//        //elimino abrerraciones
//        cout << "eliminando ... " << endl;
        eliminaaberraciones(poblacion,Paquetes);
//        muestrapoblacion(poblacion,Paquetes);
        
        // genero la nueva poblacion
//        cout << "generando poblacion ..." << endl;
        generarpoblacion(poblacion,Paquetes,peso);
//        muestrapoblacion(poblacion,Paquetes);
        
        cont++;
        if(cont==NITERACIONES) break;
    }
    
    muestramejor(poblacion,Paquetes,peso);
}

int main(int argc, char** argv) {
    Paquete Paquetes[] = {{1,20,10},
                        {2,3,40},
                        {3,5,20},
                        {4,10,1},
                        {5, 20, 100},
                        {6, 30, 120},
                        {7, 5, 30},
                        {8, 8, 40},
                        {9, 15, 70},
                        {10, 25, 90},
                        {11, 12, 50},
                        {12, 18, 80},
                        {13, 22, 110},
                        {14, 7, 35},
                        {15, 16, 75},
                        {16, 9, 45},
                        {17, 14, 65},
                        {18, 19, 85}};
    int n = sizeof(Paquetes)/sizeof(Paquete);
    
    mochilaGenetico(Paquetes,n,50);
    
//    
//    for (int i = 0; i < 10; i++) {
//        vector<Paquete> solu = grasp(Paquetes,n,50);
//        for(auto x:solu){
//            cout << x.id << "  ";
//        }
//        cout << endl;
//        Sleep(1000);
//    }

    
    
    return 0;
}


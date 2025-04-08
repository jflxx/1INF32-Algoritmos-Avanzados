/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 9 de diciembre de 2024, 20:56
 */

#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;
#define NIND 10
#define NITERACIONES 1000
#define Tseleccion 0.5
#define Pcasamiento 0.5
#define Tmutacion 0.8

struct Paquete{
    int id;
    int bloques;
    int inicio;
};

vector<Paquete> gpaq;



void muestrapoblacion(vector<vector<int>> poblacion,const vector<Paquete>& paquetes){
    
    for(int i=0;i<poblacion.size();i++){
        int peso = 0 ;
        for(int j=0;j<poblacion[i].size();j++){
            cout << poblacion[i][j] << "  ";
//            peso += poblacion[i][j]*paquetes[j].bloques;
        }
        cout << endl;
//        cout << " peso: " << peso << endl;
//        cout <<" fo="<< calculafitness(poblacion[i],assetPool) <<endl;
    }
}


bool aberracion(vector<int>cromo,const vector<Paquete>& paq){
//    int total=0;
//    
//    for(int i=0;i<cromo.size();i++)
//        total+=cromo[i]*paq[i].;
//    
//    return total>peso;
    int arregloAux[7] = {};
    
//    for (int i = 0; i < cromo.size(); i++) {
//        cout << cromo[i] << "  ";
//    }
//    cout << endl;
    
    for (int i = 0; i < cromo.size(); i++) {
        //llenar cada paquete en el arreglo
        bool ini=true;
        int contLibres=0;
        int inicioLibre,finlibre=-1;
        if(cromo[i]){
            for(int j=paq[i].inicio; j < 7;j++){
                if(!arregloAux[j] && ini){
                    inicioLibre = j;
                    ini = false;
                }
                if(!ini && arregloAux[j]){
                    finlibre = j;
                    break;
                }
            }
            if(finlibre == -1)
                finlibre = 7;
            if(finlibre-inicioLibre>=paq[i].bloques){
                for(int k=inicioLibre; k<paq[i].bloques+inicioLibre ;k++)
                    arregloAux[k] = paq[i].id;
            }else{
                return true;
            }
        }
    }
    return false;
}

void generapoblacioninicial(vector<vector<int>> &poblacion,const vector<Paquete>& paquetes){
    int cont=0;
    
    while(cont<NIND){
        vector <int> vaux;
        for(int i=0; i<paquetes.size() ;i++)
            vaux.push_back(rand()%2);
        if(not aberracion(vaux,paquetes)){
            poblacion.push_back(vaux);
            cont++;
        }
    }
}

int calculafitness(const vector<int> cromo,const vector<Paquete> &assetPool){
    double sumaPOP=0;
    int cont=0;
    for(int i=0;i<cromo.size();i++){
        // suma de precios optimistas
        sumaPOP += cromo[i];
    }
    return sumaPOP;
}

bool compara2(vector<int>a,vector<int>b){
    int suma=0,sumb=0;
   
    for(int i=0;i<a.size();i++)
        suma+=calculafitness(a,gpaq);
    for(int i=0;i<b.size();i++)
        sumb+=calculafitness(b,gpaq);
    return suma>sumb;
}

void calculasupervivencia(const vector<vector<int>>poblacion,
    vector<int>&supervivencia,const vector<Paquete> & assetPool){
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
    const vector<Paquete> & assetPool){
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

void generahijo(vector<int>padre,vector<int>madre,
        vector<int>&hijo){
    int pos=round(padre.size()*Pcasamiento);
    
    for(int i=0;i<pos;i++)
        hijo.push_back(padre[i]);
    for(int i=pos;i<madre.size();i++)
        hijo.push_back(madre[i]);
}

void casamiento(vector<vector<int>>padres,
        vector<vector<int>>&poblacion,const vector<Paquete> & assetPool){
    for(int i=0;i<padres.size();i++)
        for(int j=0;j<padres.size();j++)
            if(i!=j){
                vector<int>cromo;
                generahijo(padres[i],padres[j],cromo);
                if(!aberracion(cromo,assetPool))
                    poblacion.push_back(cromo);
            }
}

int compacta(vector<int>cromo){
    int num=0;
    for(int i=0;i<cromo.size();i++)
        num+=pow(2,i)*cromo[i];
    return num;
}

void eliminaaberraciones(vector<vector<int>> &poblacion,const vector<Paquete> & assetPool){
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

void generarpoblacion(vector<vector<int>> &poblacion,
        const vector<Paquete>& assetPool){
    gpaq = assetPool;
    sort(poblacion.begin(),poblacion.end(),compara2);
    if(poblacion.size()>NIND){
        poblacion.erase(poblacion.begin()+NIND,poblacion.end());
    }
}

double muestramejor(const vector<vector<int>> &poblacion,
       const vector<Paquete>& assetPool){
    int mejor=0;
    int mejorV = 0;
    for(int i=0;i<poblacion.size();i++)
        if(calculafitness(poblacion[mejor],assetPool)<calculafitness(poblacion[i],assetPool))
            mejor=i;
    cout << endl<<"La mejor solucion es:" << calculafitness(poblacion[mejor],assetPool)<<endl;
    for(int i=0;i<poblacion[mejor].size();i++){
        cout << poblacion[mejor][i] << "  ";
//        mejorV += assetPool[i].valor*poblacion[mejor][i];
    }
//    cout << endl << "Mejor valor: " << mejorV << endl;
    return calculafitness(poblacion[mejor],assetPool);
}



void genetico(const vector<Paquete> &paquetes){
    int cont=0;
    vector<vector<int>> poblacion;
    srand(time(NULL));
    
    generapoblacioninicial(poblacion,paquetes);
//    muestrapoblacion(poblacion,paquetes);  
    double suma=0;
    
    while(1){
        vector<vector<int>> padres;
        seleccion(padres,poblacion,paquetes);
        casamiento(padres,poblacion,paquetes);
        
        
//        mutacion(poblacion,padres,assetPool,maxInversion);
//        //elimino abrerraciones
//        cout << "eliminando ... " << endl;
        eliminaaberraciones(poblacion,paquetes);
//        muestrapoblacion(poblacion,Paquetes);
        
        // genero la nueva poblacion
//        cout << "generando poblacion ..." << endl;
        generarpoblacion(poblacion,paquetes);
        cont++;
        if(cont==NITERACIONES) break;
    }
    muestramejor(poblacion,paquetes);
}


//void mutacion(vector<vector<int>> &poblacion,vector<vector<int>> padres){
//    int cont=0;
//    int nmuta=round(padres[0].size()*Tmutacion);
//    cout << nmuta << endl;
//    for(int i=0;i<padres.size();i++){
//        while(cont<nmuta){
//            int ind=rand()%padres[0].size();
//            if(padres[i][ind]==0){
//                padres[i][ind]=1;
//            }
//            else
//                padres[i][ind]=0;
//            cont++;
//        }
//        poblacion.push_back(padres[i]);     
//    }
//}
//void inversion(vector<vector<int>> &poblacion,vector<vector<int>> padres){
//    
//    for(int i=0;i<padres.size();i++){
//        for(int j=0;j<padres[i].size();j++){
//            if(padres[i][j]==0)
//                padres[i][j]=1;
//            else
//                padres[i][j]=0;
//        }
//        poblacion.push_back(padres[i]);     
//    }    
//    
//}

int main(int argc, char** argv) {
    vector<Paquete> paquetes = {{1,2,1},
                                {2,3,2},
                                {3,1,5},
                                {4,3,3}};
    
    genetico(paquetes);
    
    
    
    return 0;
}


/* 
 * File:   main.cpp
 * Author: cueva.r
 *
 * Created on 29 de octubre de 2024, 02:37 PM
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <limits.h>
#define iteraciones 10000
#define alfa 0.3
struct tobjeto{
    int cod;
    int capacidad;
    int rendimiento;
};
struct tresult{
    int disco;
    int tabla;
};


using namespace std;

bool compara(tobjeto a,tobjeto b){
    return a.rendimiento > b.rendimiento;
}

int verifica(vector<tobjeto>dato,int maxrcl){
    int cont=0;
    for(int i=0;i<dato.size();i++)
        if(maxrcl<=dato[i].rendimiento)cont++;
    return cont;        
}


int cargadiscos(tobjeto *tabla,tobjeto *disco,
        int n,int m){
    int mejoriop=INT_MIN;
    vector<tresult> mejorv;
    
    for(int k=0;k<iteraciones;k++){
        vector<tobjeto>vtabla;
        vector<tobjeto>vdisco;
        vector<tresult>vresultado;
        
        vtabla.insert(vtabla.begin(),tabla,tabla+n);
        vdisco.insert(vdisco.begin(),disco,disco+m);
        sort(vtabla.begin(),vtabla.begin()+n,compara);
        srand(time(NULL));
        while(not vtabla.empty()){
            
            sort(vdisco.begin(),vdisco.begin()+m,compara);
            int beta1=vtabla[0].rendimiento;
            int tau1=vtabla[vtabla.size()-1].rendimiento;
            int maxrcl1= round(beta1- alfa*(beta1-tau1));
            int indrcl1=verifica(vtabla,maxrcl1);
            int indtabla=rand()%indrcl1;
            
            int beta2=vdisco[0].rendimiento;
            int tau2=vdisco[vdisco.size()-1].rendimiento;
            int maxrcl2= round(beta2- alfa*(beta2-tau2));
            int indrcl2=verifica(vdisco,maxrcl2);
            int inddisco=rand()%indrcl2;
            
            if(vdisco[inddisco].rendimiento>=vtabla[indtabla].rendimiento){
                vresultado.push_back({vdisco[inddisco].cod,vtabla[indtabla].cod});
                vdisco[inddisco].rendimiento-=vtabla[indtabla].rendimiento;
            }
            vtabla.erase(vtabla.begin()+indtabla);
        }
        sort(vdisco.begin(),vdisco.begin()+m,compara);
        int residual= vdisco[vdisco.size()-1].rendimiento;
        if(residual>mejoriop){
            mejoriop = residual;
            mejorv.clear();
            mejorv = vresultado;
        }
    }
    for(int i=0;i<mejorv.size();i++)
        cout << mejorv[i].disco<<" "<<mejorv[i].tabla<<endl;
    
    return mejoriop;
}
int main(int argc, char** argv) {
    tobjeto tabla[]={{1,20,150},{2,10,100},{3,15,80},{4,100,50},
        {5,50,120},{6,100,10}};
    tobjeto disco[]={{1,800,250},{2,750,200},{3,850,200}};
    
    int n=sizeof(tabla)/sizeof(tabla[0]);
    int m=sizeof(disco)/sizeof(disco[0]);
    
    cout <<"Residual:"<<cargadiscos(tabla,disco,n,m);
    
    return 0;
}


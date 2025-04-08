#include "Paquete.h"
#include "mochilaGrasp.h"
#include<windows.h>
#define ITER 100
#define alpha 0.3

int compara(Paquete paq1,Paquete paq2){
    return (double)paq1.peso/paq1.valor > (double)paq2.peso/paq2.valor;
}

int verifica(const vector<Paquete> &vpaquetes,double RCL){
    int cont = 0;
    for (int i = 0; i < vpaquetes.size(); i++) {
        double ratio = (double)vpaquetes[i].valor/vpaquetes[i].peso; 
        if(ratio >= RCL)
            cont ++;
    }
    return cont;
}

vector<Paquete> grasp(Paquete paqs[],int n,int peso){
    srand(time(NULL));
    int mejorV = 0;
    
    vector<Paquete> paquetes;
    for (int i = 0; i < n ; i++) {
        paquetes.push_back(paqs[i]);
    }
    sort(paquetes.begin(),paquetes.begin()+n,compara);
    
    vector<Paquete> mejorSolu;
    for (int i = 0; i < ITER; i++) {
        vector<Paquete> vpaquetes = paquetes;
        vector<Paquete> soluParcial;
        int pesoTemp=peso;
        int valor=0;
        while(not vpaquetes.empty()){
            int betha = vpaquetes[0].valor/vpaquetes[0].peso;
            int tau = vpaquetes.back().valor/vpaquetes.back().peso;
            double RCL = betha - alpha*(betha-tau);
            int ind = verifica(vpaquetes,RCL);
            int indA = rand()%ind;
            
            if(pesoTemp - vpaquetes[indA].peso>0){
                pesoTemp-=vpaquetes[indA].peso;
                valor+=vpaquetes[indA].valor;
                soluParcial.push_back(vpaquetes[indA]);
            }
            vpaquetes.erase(vpaquetes.begin()+indA);
        }

        if(mejorV<valor){
            mejorV = valor;
            mejorSolu = soluParcial;
        }
    }
    Sleep(800);
    return mejorSolu;
}

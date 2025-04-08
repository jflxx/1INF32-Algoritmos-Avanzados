#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;
#define ITER 10000
#define alpha 0.3
struct Paquete{
    int id;
    int peso;
    int valor;
};

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

void grasp(Paquete paquetes[],int n,int peso){
    srand(time(NULL));
    int mejorV = 0;
    sort(paquetes,paquetes+n,compara);
    vector<Paquete> mejorSolu;
    for (int i = 0; i < ITER; i++) {
        vector<Paquete> vpaquetes;
        vector<Paquete> soluParcial;
        for (int j = 0; j < n; j++)
            vpaquetes.push_back(paquetes[j]);
        
        int valor=0;
        while(not vpaquetes.empty()){
            int betha = vpaquetes[0].valor/vpaquetes[0].peso;
            int tau = vpaquetes.back().valor/vpaquetes.back().peso;
            double RCL = betha - alpha*(betha-tau);
            int ind = verifica(vpaquetes,RCL);
            int indA = rand()%ind;
            
            if(peso - vpaquetes[indA].peso>0){
                peso-=vpaquetes[indA].peso;
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
    int tot = 0;
    for(auto x:mejorSolu){
        cout << x.id << " "; 
        tot+=x.peso;
    }
    
    cout << endl << tot;
}

int main(int argc, char** argv) {
    Paquete Paquetes[] = {{1,20,10},
                        {2,3,40},
                        {3,5,20},
                        {4,10,1},
                        {2, 20, 100},
                        {3, 30, 120},
                        {4, 5, 30},
                        {5, 8, 40},
                        {6, 15, 70},
                        {7, 25, 90},
                        {8, 12, 50},
                        {9, 18, 80},
                        {10, 22, 110},
                        {11, 7, 35},
                        {12, 16, 75},
                        {13, 9, 45},
                        {14, 14, 65},
                        {15, 19, 85}};
    
    int n = sizeof(Paquetes)/sizeof(Paquete);
    
    grasp(Paquetes,n,50);
    
    
    return 0;
}


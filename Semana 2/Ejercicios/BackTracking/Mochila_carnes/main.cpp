/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 6 de setiembre de 2024, 17:21
 */

#include <iostream>

using namespace std;
void imprimerSolu(int solu[],int n){
    int i=0;
    cout << "{";
    for(int i=0; i<n ;i++){
        if(i!=0 && solu[i]!=0){
            if(i)
                cout <<",";
        
        }
        if(solu[i]!=0){
            cout << solu[i];
            if(!i)
                i=1;
        }
    }
    cout << "}" << endl;
    
//    for(int i=0; i<n ;i++){
//        cout << solu[i] << "  ";
//    }
//    cout << endl;
            
}

int verifica(int n,int estado[]){
    for(int i=0; i<n ;i++){
        if(!estado[i])
            return 1;
    }
    return 0;
}
int vaciaSolu(int n,int solu[]){
    for(int i=0;i<n;i++)
        solu[i] = 0;
}

int verificarCorte(int k,int n,int solu[]){
    int x=0;
    
    for(int i=0; i<n ;i++){
        if(solu[i]){
            for(int j=0; j<n ;j++){
                if(solu[j]){
                    if(i!=j){
                        if(solu[j]-solu[i]<=k && solu[j]-solu[i]>=0 && solu[i]!=0){
                            x++;
                            break;
                        }
                    }
                }
            }
        }
    }
    int m=0;
    for(int b=0;b<n;b++){
        if(solu[b])
            m++;
    }
//    for (int q = 0; q < n; q++) {
//        for (int i = q+1; i < n; i++) {
//            if(solu[q]-solu[i]<=k and solu[q]-solu[i]>= -k){
//                break;
//            }
//        }
//
//    }
    if(x>=m){
        return 1;
    }
    return 0;
}

int despachaCarnes(int id,int n,int pesoA,int pesos[],int pesoObj,int solu[],int estado[],int k){
    if(id>n || pesoA>pesoObj)
        return 0;
    if(pesoA==pesoObj){  
        if(verificarCorte(k,n,solu)){
            imprimerSolu(solu,n);
            return 1;
        }
        return 0;
    }
    
    if(!estado[id]){
        solu[id] = pesos[id];
        estado[id] = 1;
        if(despachaCarnes(id+1,n,pesoA+pesos[id],pesos,pesoObj,solu,estado,k)){
            
            if(verifica(n,estado)){
                vaciaSolu(n,solu);
                despachaCarnes(0,n,0,pesos,pesoObj,solu,estado,k);
            }
            return 1;
            
        }
        solu[id] = 0;
        estado[id] =0;
    }
//    imprimerSolu(solu,n);
    return despachaCarnes(id+1,n,pesoA,pesos,pesoObj,solu,estado,k);
}

int main(int argc, char** argv) {
    int t[]={2,8,9,6,7,6};
    int P=15, k=3, n=sizeof(t)/sizeof(int);
    int estado[n]={},solu[n]={};
    
    cout << despachaCarnes(0,n,0,t,P,solu,estado,k);
    
    return 0;
}


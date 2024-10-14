/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 10 de octubre de 2024, 11:27
 */

#include <iostream>
#include <cstring>
using namespace std;
#define N 4
#define monto 7
void imprimirSolu(int pd[N+1][monto+1]){
    for(int i=0; i<N+1 ;i++){
        for(int j=0;j<monto+1;j++){
            cout << pd[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl<<endl;
}

int formas(int dinares[N]){
    int pd[N+1][monto+1]={{}};
    memset(pd,0,sizeof(pd));
    for(int i=0;i<N+1;i++){
        pd[i][0] = 1;
    }
    
    for(int y=1; y<monto+1 ;y++){
        for(int x=1; x<N+1 ;x++){
            for(int k=y; k>=0 ; k-=dinares[x-1]){
                pd[x][y]+=pd[x-1][k];
            }
            imprimirSolu(pd);
        }
    }
    
    return pd[N][monto];
}

int main(int argc, char** argv) {
    int dinares[N] ={1, 2, 10, 20};
//    int monto = 13;    

    cout << formas(dinares);

    return 0;
}


/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 6 de setiembre de 2024, 23:26
 */

#include <iostream>

using namespace std;
#define N 5
#define M 5
int mov1[8][2];
int mov2[4][2];


void inicializarMovimientos(){
    mov1[0][0] = 1 ; mov1[0][1] = 0;
    mov1[1][0] = 1 ; mov1[1][1] = 1;
    mov1[2][0] = 0 ; mov1[2][1] = 1;
    mov1[3][0] =-1 ; mov1[3][1] = 1;
    mov1[4][0] =-1 ; mov1[4][1] = 0;
    mov1[5][0] =-1 ; mov1[5][1] =-1;
    mov1[6][0] = 0 ; mov1[6][1] =-1;
    mov1[7][0] = 1 ; mov1[7][1] =-1;
    
    mov2[0][0] = 1 ; mov2[0][1] = 0;
    mov2[1][0] = 0 ; mov2[1][1] = 1;
    mov2[2][0] =-1 ; mov2[2][1] = 0;
    mov2[3][0] = 0 ; mov2[3][1] =-1;

}

int valida(int campo[N][M],int x,int y,int n,int m){
    if(x<n && y<m && x>=0 && y>=0 && campo[x][y]==0)
        return 1;
    return 0;
}

void imprimir(int n,int m, int campo[N][M]){
    for(int i=0; i<n ;i++){
        for(int j=0; j<m ;j++){
            cout << campo[i][j] << " ";
        }
        cout << endl;
    }
}

int noTieneSalida(int campo[N][M],int x,int y){
    int xn,yn;
    for(int i=0; i<8 ;i++){
        xn = x + mov1[i][0];
        yn = y + mov1[i][1];
        if(valida(campo,xn,yn,N,M))
            return 0;
    }
    return 1;
}

int robotPodador(int x,int y,int n,int m,int cont,int campo[N][M],int c){
    if(x>=n || y>=m || y<0 || x<0) return 0;
    
    if(noTieneSalida(campo,x,y)){
        imprimir(n,m,campo);
        return 1;
    }
    
    
    int xn,yn,k;
    bool nopudo;
    for(int i=0; i<8 ;i++){
        if(cont!=1){
            xn = x + mov1[i][0];
            yn = y + mov1[i][1];
        }else{
            xn = x;
            yn = y;
        }
        if(valida(campo,xn,yn,n,m)){
            for(int j=0; j<4 ;j++){
                nopudo=false;
                for(k=0; k<c;k++){
                    campo[xn][yn] = cont;
                    if(k!=c-1){
                        xn = xn + mov2[j][0];
                        yn = yn + mov2[j][1];
                    }
                }
//                if(nopudo){
//                    for(int l=0; l<k;l++){
//                        campo[xn][yn] = 0;
//                        xn = -mov2[j][0];
//                        yn = -mov2[j][1];
//                    }
//                }
//                if(!nopudo){
                imprimir(n,m,campo);
                cout << endl;
                if(robotPodador(xn,yn,n,m,cont+1,campo,c)){
                    return 1;
                }
//                }
                for(int l=0; l<k;l++){
                    campo[xn][yn] = 0;
                    xn = xn - mov2[j][0];
                    yn = yn - mov2[j][1];
                }
                
                
            }
        }
    }
    return 0;
}

int main(int argc, char** argv) {
    int c=3,campo[N][M]={{0,0,0,0,0},
                        {0,0,0,0,0},
                        {0,0,0,0,0},
                        {0,0,0,0,0},
                        {0,0,0,0,0}};
    inicializarMovimientos();
    cout << robotPodador(0,0,N,M,1,campo,c);
    
    return 0;
}


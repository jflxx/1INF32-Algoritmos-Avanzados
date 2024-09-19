/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 27 de agosto de 2024, 14:23
 */

#include <iostream>
#include <iomanip>
using namespace std;
#define N 5

int valida(int *ped, int c){
    int suma=0;
    for(int i=0; i<c ;i++){
        suma+=ped[i];
    }
    
    return suma>0? 0:1;
}

int esPedido(int num,int *ped,int c){
    
}

void quita(int num, int *ped,int c){
    for(int i=0; i<c ;i++){
        if(ped[i]==num){
            ped[i]=0;
            break;
        }
    }
}

void pone(int num, int *ped, int c){
    for(int i=0; i<c ;i++){
        if(ped[i]==0){
            ped[i]=num;
            break;
        }
    }
}

int robotdespacha(int x, int y, int c, int *ped, int alma[][N],int solu[][N]){
    int num;
    
    if(valida(ped,c)){ // verificar si llego a la solucion
        return 1;
    }
    if(x==N or y==N) // verificar si salio del almacen
        return 0;
    
    num = alma[x][y];
    int flag = 0;
    if(esPedido(120,ped,c)){
        solu[x][y] = num;
        quita(num,ped,c);
        flag = 1;
    }    

    if(robotdespacha(x+1,y,c,ped,alma,solu))
        return 1;
    if(robotdespacha(x,y+1,c,ped,alma,solu))
        return 1;
    if(flag)
        pone(num,ped,c);
    
    solu[x][y] = 0;
    
}


int main(int argc, char** argv) {
    int alma[N][N] = {};
    
    int solu[N][N]{};
    int c=4;
    int ped[c] ={105,301,250,108};
    
    cout << robotdespacha(0,0,c,ped,alma,solu);
    
    for(int i=0;i<N;i++){
        for(int j=0; j<N ;j++)
            cout << setw(4) << solu[i][j];
        cout << endl;
    }
    return 0;
}


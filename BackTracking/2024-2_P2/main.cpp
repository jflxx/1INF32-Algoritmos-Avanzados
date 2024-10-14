/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 6 de octubre de 2024, 12:00
 */

#include <iostream>
#include <cstring>

using namespace std;

bool todosUsados(bool usados[],int N){
    bool estanTodos=true;;
    for(int i=0;i<N;i++){
        if(!usados[i]){
            estanTodos = false;
        }
    }
    return estanTodos;
}
bool verificar(int solucion[],int rack[],int M){
    for(int i=0; i<M ;i++){
        if(solucion[i]>rack[i])
            return false;
    }
    return true;
}
bool verificarSuma(int solucion[],int M,int productos[],int N,int rack[]){
    if(verificar(solucion,rack,M)){
        int sumaSol=0;
        for(int i=0; i<M ;i++){
            sumaSol+=solucion[i];
        }
        int sumaProd=0;
        for(int i=0; i<N ;i++){
            sumaProd+=productos[i];
        }
        if(sumaProd==sumaSol){
            return true;
        }
    }
    return false;
}
int imprimirTodos(bool usados[],int solucion[],int N,int M,int productos[],int rack[]){
    if(verificarSuma(solucion,M,productos,N,rack)){
        if(todosUsados(usados,N)){
            for(int i=0;i<M;i++){
                cout << solucion[i] << "  ";
            }
            cout << endl<<endl;
        }
    }
}


int productosAgrupados(int i,int productos[],int N,int rack[],int M,int k,
        int solucion[],bool usados[]){
    imprimirTodos(usados,solucion,N,M,productos,rack);
    if(i>=N && todosUsados(usados,N)){
        return 0;
    }
    if(!usados[i] && k>M){
        return 0;
    }
    if(!verificar(solucion,rack,M)){
        return 0;
    }
    
    solucion[k]+=productos[i];
    usados[i] = true;
    productosAgrupados(i+1,productos,N,rack,M,0,solucion,usados);
    solucion[k]-=productos[i];
    usados[i] = false;
    productosAgrupados(i,productos,N,rack,M,k+1,solucion,usados);
    
    return 0;
}

int main(int argc, char** argv) {
    int productos[] = {2,3,1,4};
    int rack[] = {3,2,5,1,3};
    int N = sizeof(productos)/sizeof(int),M = sizeof(rack)/sizeof(int);
    int solucion[M]={};
    bool usados[N] ={};

    productosAgrupados(0,productos,N,rack,M,0,solucion,usados);
    
    return 0;
}


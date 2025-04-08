/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 14 de octubre de 2024, 08:15
 */

#include <iostream>
#include <string>
#include <math.h>
using namespace std;

int verificar(char solu[],int k){
    int num=0;
    for(int i=0; solu[k-i]!='.' && i<=k ;i++)
        num+= (solu[k-i]-48)*pow(10,i);
    
    if(num<=255 && num>=0)
        return 1;
    return 0;
}
void imprimirSolu(char solu[],int n){
    
    for(int i=0; i<n ;i++){
        cout << solu[i] << "  ";
    }
    cout << endl;
}
void GenerarIP(char s[],int n,char solu[],int i,int k,int numeroPuntos){
    if(i>=n || k>n+3){
        if(verificar(solu,k-1))
            imprimirSolu(solu,n+3);
        return;
    }
    if(!verificar(solu,k-1))
        return;
    solu[k] = s[i];
    
    GenerarIP(s,n,solu,i+1,k+1,numeroPuntos);
    solu[k] = ' ';
    if(solu[k-1]!='.' && numeroPuntos+1<=3 && k>0){
        solu[k] = '.';
        numeroPuntos++;
        GenerarIP(s,n,solu,i,k+1,numeroPuntos);
    }
    return;
}

int main(int argc, char** argv) {
    char s[] = "25525511169";
    int n = sizeof(s)/sizeof(char);
    char solu[n+3]{};
    int numeroPuntos=0;
    GenerarIP(s,n-1,solu,0,0,numeroPuntos);
        
    return 0;
}


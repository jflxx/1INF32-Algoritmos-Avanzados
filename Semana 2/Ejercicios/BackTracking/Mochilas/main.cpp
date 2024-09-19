/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 5 de setiembre de 2024, 21:02
 */

#include <iostream>

using namespace std;

int empaca(int i,int n,int peso,int paq[],int k,int *solu){
    if(i==n or peso<0) return 0;
    if(peso==paq[i]){
        solu[k]=paq[i];
        return 1;
    }
    int nk = k+1;
    solu[k] = paq[i];
    if(empaca(i+1,n,peso-paq[i],paq,k+1,solu)){
        return 1;
    }
    solu[k] = 0;
    return empaca(i+1,n,peso,paq,k,solu);
    
    
}

int main(int argc, char** argv) {
    int n=4,peso=9;
    int paq[]={1,3,12,5};
    int solu[n]{};
    
    if(empaca(0,n,peso,paq,0,solu)){
        for(int i=0;i<n;i++)
            cout << solu[i] << " ";
    }else
        cout << "aaa";
    
    
    return 0;
}



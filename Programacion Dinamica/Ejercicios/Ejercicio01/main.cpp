/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 18 de setiembre de 2024, 21:24
 */

#include <iostream>

using namespace std;

int solu(int nums[],int n){
    int numeros[n],suma=0;
    for(int i=0; i<n;i++){
        suma+=nums[i];
    }
    int matriz[n][suma+1]={};
    
    for(int i=0; i<n ;i++)
        matriz[i][0] = 1;
    for(int i=1; i<=suma ;i++)
        matriz[0][i] = 0;
    
    for(int i=1; i<n ;i++){
        for(int j=1; j<=suma;j++){
            if(j-nums[i]>=0){
                if(matriz[i-1][j-nums[i]] 
                        || matriz[i-1][j]){
                    matriz[i][j]=1;
                }else{
                    matriz[i][j]=0;
                }
            }else
                matriz[i][j] = matriz[i-1][j];
        }
    }
    
//    for(int i=0; i<n ;i++){
//        for(int j=0; j<=suma;j++){
//            cout << matriz[i][j] << "   ";
//        }
//        cout << endl;
//    }
    
    if(suma%2!=0){
        return 0;
    }
    
    return matriz[n][suma] && matriz[n][suma/2]? 1:0;
    
    
}

int main(int argc, char** argv) {
    int nums[] ={0,2,5,4,1};
    int n=sizeof(nums)/sizeof(int);
    
    
    cout << solu(nums,n);
    return 0;
}


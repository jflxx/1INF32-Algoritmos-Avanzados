/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 19 de setiembre de 2024, 08:54
 */

#include <iostream>
#include <iomanip>
using namespace std;
#define N 5
#define M 2

int robotCortador(int present[N][M],int beneficio[N]){
    int suma = 10;
    
    for(int i=0; i<N ;i++){
        suma+=beneficio[i];
    }
    suma/=10;
    int dp[N][suma];
    for(int i=0; i<N ;i++){
        dp[i][0] = 0;
        beneficio[i] = beneficio[i]/10;
    }
    for(int i=0; i<suma ;i++)
        dp[0][i] = 0;
    

    int ant;
    for(int i=1; i<N ;i++){
        for(int j=1; j<suma ;j++){
            ant = j-beneficio[i];
            if(ant>=0){
                if(beneficio[i]+dp[i-1][ant]>dp[i-1][j])
                    dp[i][j] = beneficio[i]+dp[i-1][ant];
                else
                    dp[i][j]=dp[i-1][j];
            }else
                dp[i][j]=dp[i-1][j];
        }
    }
    
    for(int i=0; i<N ;i++){
        for(int j=0; j<suma ;j++){
            cout << setw(2) << dp[i][j] << " ";
        }
        cout << endl;
    }
    
    return suma;
}

int main(int argc, char** argv) {
    int present[N][M] = {{0,0},{5,10},{2,4},{6,12},{4,15}};
    int beneficio[N]={0,30,40,80,100};
    
    cout << robotCortador(present,beneficio);
    
    return 0;
}


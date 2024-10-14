/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: alulab14
 *
 * Created on 21 de septiembre de 2024, 08:45 AM
 */

#include <iostream>

using namespace std;

int calcularGanaciaMax(int *precios,int n){
    
    int dp[n+1][n+1];
    for(int i=0;i<=n;i++){
        dp[0][i]=0;
    }
    for(int i=0;i<=n;i++){
        dp[i][0]=0;
    }
    
    for(int i=1;i<n+1;i++){
        for(int j=1;j<n+1;j++){
            if(i<=j){
                dp[i][j] = max(dp[i-1][j],precios[i-1]+dp[i-1][1]);
            }
            else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    
    for(int i=0;i<n+1;i++){
        for(int j=0;j<n+1;j++){
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }
    
    return dp[n][n];
    
}

/*
 * 
 */
int main(int argc, char** argv) {
    int n = 4;
    int precios[n]{2,5,7,8};
    
    cout<<"Ganancia Maxima: "<<calcularGanaciaMax(precios,n);
    
    return 0;
}


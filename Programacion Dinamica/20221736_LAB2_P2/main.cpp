/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: alulab14
 *
 * Created on 21 de septiembre de 2024, 08:02 AM
 */

#include <iostream>
#include <iomanip>
using namespace std;
int maximo(int num1,int num2){
    return num1>num2? num1:num2;
}
int maxGanacia(int p[],int n){
    int dp[n][n] = {};
   
    for(int i=1; i<n ;i++){
        for(int j=1; j<=i ;j++)
            dp[i][j] = max( p[j]+dp[i-j][i-j], dp[i][j-1]);
    }
    
//    for(int i=0; i<n ;i++){
//        for(int j=0; j<n ;j++)
//            cout << setw(3) << dp[i][j] << "  ";
//        cout << endl;
//    }
//    cout << endl;
    
    return dp[n-1][n-1];
}

int main(int argc, char** argv) {
    int p[]= {0,2,5,7,8};
    int n = sizeof(p)/sizeof(int);
    
    cout << " La maxima ganacia es: "<< maxGanacia(p,n);
    
    return 0;
}


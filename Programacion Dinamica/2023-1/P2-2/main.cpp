/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 19 de setiembre de 2024, 22:36
 */

#include <iostream>

using namespace std;

int combinatoriaCanarios(int n){
    int dp[2][n];
    dp[0][0] = 1;
    dp[1][0] = 2;
    for(int i=1; i<n ;i++){
        dp[0][i] = dp[0][i-1]*3; //canarios
        dp[1][i] = dp[1][i-1]*2; //agaponis
    }
    
    return dp[0][n-1] + dp[1][n-1];
}

int main(int argc, char** argv) {
    int n=3;
    
    cout << combinatoriaCanarios(n);
    return 0;
}


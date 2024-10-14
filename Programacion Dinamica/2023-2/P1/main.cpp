/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 20 de setiembre de 2024, 13:02
 */

#include <iostream>

using namespace std;

int evalularDentro(int arr[],int j,int i){
    j++;
    i--;
    while(j<i){
        if(arr[j]!=arr[i]){
            return 0;
        }
        j++;
        i--;
    }
    return 1;
}

int cortes(int arr[],int n){
    int dp[n]={};
    int dp2[n]={};
    dp[0] = 1;
    bool solo;
    for(int i=1; i<n ;i++){
        solo = true;
        for(int j=0; j<i ;j++){
            if(arr[i]==arr[j]){
                if(evalularDentro(arr,j,i)){
                    if(!dp2[j]){ 
                        dp2[i] = 1;
                        dp[i] = dp[j]; 
                        solo = false;
                        break;
                    }
                }
            }
        }
        if(solo)
           dp[i] = dp[i-1] + 1; 
    }
    for(int k=0;k<n;k++){
        cout << dp[k] << "  ";
    }
    cout << endl;
    return dp[n-1] - 1;
}

int main(int argc, char** argv) {
    int arr[] = {16,22,22,52,11,11,11,4,28,19,28,28};
//    int arr[] = {10,20,20,10,11,23,13,23,30,25};
    int n = sizeof(arr)/sizeof(int);
    
    cout << cortes(arr,n);
    
    return 0;
}


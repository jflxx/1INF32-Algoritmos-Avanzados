/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 8 de setiembre de 2024, 17:59
 */

#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char** argv) {
    int X[]={-7,10,9,2,3,8,8,1};
    int n = sizeof(X)/sizeof(int);
    int LIS[n] = {};
    for(int i=0; i<n ;i++){
        LIS[i] = 1;
    }
    int aux; 
    for(int i=1; i<n ;i++){
        for(int j=0; j<i ;j++){
            if(X[i]>X[j]){
                aux = LIS[j]+1;
                if(LIS[i]<aux)
                    LIS[i] = LIS[j]+1;
            }
        }
    }
    for(int i=0; i<n ;i++){
        cout << LIS[i] << "  ";
    }
    return 0;
}


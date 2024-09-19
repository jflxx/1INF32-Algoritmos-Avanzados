/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 8 de setiembre de 2024, 16:02
 */

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    int coins[6]={5,1,2,10,6,2},c=6;
    int Fn[c+1]={};
    
    Fn[0] = 0;
    Fn[1] = coins[0];
    
    for(int i=2; i<=c ;i++){
        int max = Fn[i-1];
        int aux = coins[i-1] + Fn[i-2];
        if(max<aux)
            max= aux;
        Fn[i] = max;
    }
    
    for(int i=0; i<=c ;i++)
        cout << Fn[i] << " ";
    
    return 0;
}


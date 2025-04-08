/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 14 de octubre de 2024, 11:16
 */

#include <iostream>
#include <vector>
using namespace std;

struct Control{
    int inversion;
    vector<int> requisitos;
    int beneficio;
};

int pesoMaximo(int pavos[],int n){
    
    
}

int main(int argc, char** argv) {
    int pavos[]={3,25,18,15,4,12,6};
    int n = sizeof(pavos)/sizeof(int);
    
    cout << pesoMaximo(pavos,n);
    
    return 0;
}


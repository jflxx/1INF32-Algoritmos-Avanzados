/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 8 de setiembre de 2024, 21:41
 */

#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;
#define N 5
#define M 6

int main(int argc, char** argv) {
    int matriz[N][M];
    int mochilas[4][2] = {{2,12},
                          {1,10},
                          {3,20},
                          {2,15}};
    memset(matriz,0,sizeof(matriz));
    
    int id;
    for(int i=1; i<M ;i++){
        for(int j=1; j<N ;j++){
            id = i-mochilas[j-1][0];
            if(id>=0){
                if(matriz[j-1][i] < matriz[j-1][id]+mochilas[j-1][1]){
                    matriz[j][i] = matriz[j-1][id]+mochilas[j-1][1];
                }else{
                    matriz[j][i] = matriz[j-1][i];
                }
            }else{
                matriz[j][i] = matriz[j-1][i];
            }
        }
    }
    
    
    for(int i=0; i<N ;i++){
        for(int j=0; j<M ;j++){
            cout << setw(3)<< matriz[i][j] << "  ";
        }
        cout << endl;
    }
    
    return 0;
}


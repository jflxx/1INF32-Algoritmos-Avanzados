/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 9 de octubre de 2024, 21:21
 */

#include <iostream>
#include <cstring>

using namespace std;
#define N 5
#define M 4
int generarMatrizMov(int mov[M][2]){
    mov[0][0] = 1; mov[0][1] = 0;
    mov[1][0] = 0; mov[1][1] = 1;
    mov[2][0] = -1; mov[2][1] = 0;
    mov[3][0] = 0; mov[3][1] = -1;
}

void imprimirSolu(int solucion[][N]){
    for(int i=0; i<N ;i++){
        for(int j=0; j<N ;j++){
            cout << solucion[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

int esValido(int x,int y,int laberinto[][N],int solucion[][N]){
    if(laberinto[x][y]!=0 && x<N && y<N && x>=0 && y>=0 && solucion[x][y]==0)
        return 1;
    return 0;
}

int buscarLab(int laberinto[][N],int mov[M][2],int x,int y,int &min,int parcial,int solucion[][N]){
    int xn,yn;
    if(x==N-1 && y == N-1){
        if(parcial<min)
            min=parcial;
        return 1;
    }
    
    for(int i=0; i<M ;i++){
        xn = x+mov[i][0];
        yn = y+mov[i][1];
        if(esValido(xn,yn,laberinto,solucion)){
            solucion[xn][yn] = 1;
            parcial+=laberinto[xn][yn];
            imprimirSolu(solucion);
            buscarLab(laberinto,mov,xn,yn,min,parcial,solucion);
            parcial-=laberinto[xn][yn];   
            solucion[xn][yn] = 0;
        }
    }
    return min;
}

int main(int argc, char** argv) {
    int laberinto[][N]={{1,2,0,1,0},
                        {3,2,3,1,1},
                        {0,1,2,0,0},
                        {3,1,1,2,3},
                        {0,1,3,0,1}};
    int solucion[N][N];
    for(int i=0; i<N ;i++){
        for(int j=0; j<N ;j++)
            solucion[i][j] = 0;
           
    }
    int mov[M][2],min;
    generarMatrizMov(mov);             
    cout << buscarLab(laberinto,mov,0,0,min,laberinto[0][0],solucion);
    
    return 0;
}


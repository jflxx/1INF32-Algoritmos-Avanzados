/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 6 de setiembre de 2024, 10:18
 */

#include <iostream>

using namespace std;
#define N 9
#define M 5
int mov[8][2];
int cantidadGenerada=0;

void generarMovimientos(){
    mov[0][0] = 1; mov[0][1] = 0;
    mov[1][0] = 1; mov[1][1] = 1;
    mov[2][0] = 0; mov[2][1] = 1;
    mov[3][0] = -1; mov[3][1] = 1;
    mov[4][0] = -1; mov[4][1] = 0;
    mov[5][0] = -1; mov[5][1] = -1;
    mov[6][0] = 0; mov[7][1] = -1;
    mov[7][0] = 1; mov[7][1] = -1;
}


int valida(int x, int y, char solu[N][M]){
    if(x<N and y<M and x>=0 and y>=0 and solu[x][y]=='0')
        return 1;
    return 0;
}

void descubre(int x,int y,char terreno[N][M],char solu[N][M]){
    int nx,ny;
    for(int i=0; i<8 ;i++){
        nx = x + mov[i][0];
        ny = y + mov[i][1];
        if(valida(nx,ny,solu)){
            if(terreno[nx][ny]=='*')
                solu[nx][ny] = '*';
        }
    }
}

void imprime(char terreno[N][M]){
    for(int i=0; i<N ;i++){
        for(int j=0; j<M ;j++)
            cout << terreno[i][j] << " | ";
        cout << endl;
    }
    cout << endl;
}

int robot(int x,int y,char terreno[N][M],char solu[N][M],char ini){
    int nx,ny;
    if(x==N-1 && y==M-1){
        imprime(solu); 
        return 1;
    }
    descubre(x,y,terreno,solu);
    for(int i=0; i<8 ;i++){
        nx = x + mov[i][0];
        ny = y + mov[i][1];
        if(valida(nx,ny,solu)){
            solu[nx][ny] = ini+1;
            if(robot(nx,ny,terreno,solu,ini+1)){
                cout << cantidadGenerada << ")" << endl;
                cantidadGenerada++;
                imprime(solu);
                i++;
            }
            if(cantidadGenerada==10)
                return 1;
            solu[nx][ny] = '0';
        }
    }
    
    return 0;
}

int main(int argc, char** argv) {
    char terreno[N][M]={{'0','0','0','0','*'},
                        {'0','0','0','0','0'},
                        {'0','0','*','0','0'},
                        {'0','0','0','0','0'},
                        {'0','*','*','0','*'},
                        {'0','*','*','0','*'},
                        {'0','*','0','*','0'},
                        {'*','*','*','*','0'},
                        {'0','0','0','0','0'}};
    
    char solu[N][M] =  {{'A','0','0','0','0'},
                        {'0','0','0','0','0'},
                        {'0','0','0','0','0'},
                        {'0','0','0','0','0'},
                        {'0','0','0','0','0'},
                        {'0','0','0','0','0'},
                        {'0','0','0','0','0'},
                        {'0','0','0','0','0'},
                        {'0','0','0','0','0'}};
    char ini = 'A';
    generarMovimientos();
    cout << robot(0,0,terreno,solu,ini);
    
    
    return 0;
}


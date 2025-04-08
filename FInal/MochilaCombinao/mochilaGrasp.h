/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   mochilaGrasp.h
 * Author: Afedo
 *
 * Created on 8 de diciembre de 2024, 23:39
 */

#ifndef MOCHILAGRASP_H
#define MOCHILAGRASP_H
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

int compara(Paquete paq1,Paquete paq2);
vector<Paquete> grasp(Paquete paquetes[],int n,int peso);
int verifica(const vector<Paquete> &vpaquetes,double RCL);
#endif /* MOCHILAGRASP_H */


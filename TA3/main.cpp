/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/* 
 * File:   main.cpp
 * Author: Afedo JF
 *
 * Created on 15 de noviembre de 2024, 18:59
 */

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath> // Para cálculos matemáticos como fabs
using namespace std;

#define cstRelaj 0.3
#define NumIter 1000

struct Destinatario {
    string nombreDestinatario;
    string descripcion;
    int ancho, largo, alto;
    double peso;
    bool entregado = false; // Nuevo atributo para seguimiento
};

struct Vehiculo {
    int id;
    int largo, ancho, alto, peso;
    int capacidadRestante; // Capacidad restante del vehículo
    vector<string> ruta;   // Ruta de entrega
};

struct Ciudad {
    string id;
    int distancia;
};

void generarGrafo(map<string, vector<Ciudad>>& grafo) {
    grafo["1"] = { {"2", 10}, {"3", 15}, {"4", 20} };
    grafo["2"] = { {"3", 25}, {"4", 30} };
    grafo["3"] = { {"4", 35} };
    grafo["4"] = {};
}
bool noEntregadoTodosLosPaquetes(const vector<Destinatario>& destinatarios) {
    for (const auto& d : destinatarios) {
        if (!d.entregado) {
            return true;
        }
    }
    return false;
}



vector<Vehiculo> GRASPCVRPConstruccion(map<string, vector<Ciudad>>& grafo, vector<Vehiculo>& vehiculos, vector<Destinatario>& destinatarios) {
    vector<Vehiculo> nuevaListaVehiculos = vehiculos;
    int indiceVehiculo = 0;

    while (noEntregadoTodosLosPaquetes(destinatarios)) { // Cambio en el while
        Vehiculo& vehiculo = nuevaListaVehiculos[indiceVehiculo];

        while (vehiculo.capacidadRestante > 0) {
            vector<Ciudad> rcl;
            for (const auto& ciudad : grafo[vehiculo.ruta.empty() ? "1" : vehiculo.ruta.back()]) {
                if (rand() / (double)RAND_MAX < cstRelaj) {
                    rcl.push_back(ciudad);
                }
            }

            if (rcl.empty()) break;

            Ciudad nodoElegido = rcl[rand() % rcl.size()];
            vehiculo.ruta.push_back(nodoElegido.id);
            vehiculo.capacidadRestante -= 10;
        }

        indiceVehiculo = (indiceVehiculo + 1) % nuevaListaVehiculos.size();
    }

    return nuevaListaVehiculos;
}

int main() {
    srand(time(NULL));

    // Crear el grafo virtual
    map<string, vector<Ciudad>> grafo;
    generarGrafo(grafo);

    // Crear los vehículos
    vector<Vehiculo> vehiculos = {
        {1, 10, 10, 10, 100, 100, {}},
        {2, 10, 10, 10, 100, 100, {}}
    };

    // Crear los destinatarios
    vector<Destinatario> destinatarios = {
        {"2", "Paquete A", 5, 5, 5, 10},
        {"3", "Paquete B", 5, 5, 5, 15},
        {"4", "Paquete C", 5, 5, 5, 20}
    };

    for (int i = 0; i < NumIter; ++i) {
        vector<Vehiculo> nuevosVehiculos = GRASPCVRPConstruccion(grafo, vehiculos, destinatarios);
//        nuevosVehiculos = twoOptCVRP(grafo, nuevosVehiculos);
//
//        if (i == 0 || costoCVRP(nuevosVehiculos) < costoCVRP(vehiculos)) {
//            actualizarVehiculos(vehiculos, nuevosVehiculos);
//        }
    }

    for (const auto& vehiculo : vehiculos) {
        cout << "Vehiculo " << vehiculo.id << " ruta: ";
        for (const auto& nodo : vehiculo.ruta) {
            cout << nodo << " ";
        }
        cout << endl;
    }

    return 0;
}


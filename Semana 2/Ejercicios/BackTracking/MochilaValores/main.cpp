#include <iostream> 
#include <vector> 
#include <algorithm> 
using namespace std;
// Función de backtracking para el problema de la mochila 0/1 
void mochilaBacktracking(int i, int pesoActual, int valorActual, int capacidad, int& valorMaximo, 
    const vector<int>& peso, const vector<int>& valor) { 
    if (pesoActual > capacidad) { 
        return; // Si excedemos la capacidad, no es una solución válida 
    } 
    if (i == peso.size()) { 
        // Si hemos considerado todos los elementos, actualizar el valor máximo si es necesario 
        valorMaximo = std::max(valorMaximo, valorActual); 
        return;
    } 
    // No incluir el elemento i 
    mochilaBacktracking(i + 1, pesoActual, valorActual, capacidad, valorMaximo, peso, valor); 
    // Incluir el elemento i 
    mochilaBacktracking(i + 1, pesoActual + peso[i], valorActual + valor[i], capacidad, valorMaximo, 
        peso, valor); 
} 
int iniciarMochilaBacktracking(int capacidad,const vector<int>&peso,vector<int>& valor) { 
    int valorMaximo = 0; 
    mochilaBacktracking(0, 0, 0, capacidad, valorMaximo, peso, valor); 
    return valorMaximo; 
} 

int main(int argc, char** argv){ 
    vector<int> valor = {600, 100, 120}; // Valores de los elementos 
    vector<int> peso = {10, 20, 30};    // Pesos de los elementos 
    int capacidad = 50; // Capacidad de la mochila 
    int maxValor = iniciarMochilaBacktracking(capacidad, peso, valor); 
    cout << "El valor máximo que se puede obtener en la mochila es: " << maxValor << std::endl; 
    return 0; 
} 
#include <iostream>
#include <iomanip>
using namespace std;
#define K 3  // Numero de compras + 1
#define N 8

void imprimirDP(int dp[K][N],int n,int k){
    for(int i=0;  i<K ; i++){
        for(int j=0; j<N ; j++){
            cout << setw(4)<< dp[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

int calcularGananciaMaxima(int fechas[],int n,int k){
    
    // COMENTARIO: La logica del algoritmo esta bien, pero al momento de asignar el valor
    //             dentro de la matriz dp (Linea 60 y 62) el valor se duplica en otro casillero y 
    //             borra la respuesta de un casillero aleatorio algo ilogico ya que solo hago una asignacion.
    //             No se si es error de la computadora pero por favor considere la logica :D
    //             Si el error le aparece, puede darse cuenta en las impresiones que se asiga dos veces y
    //             cambia los valores correctos anteriores.
    int dp[K][N]={};
    //asignamos 0's a la matriz dp
    for(int i=0;  i<k ; i++){
        for(int j=0; j<n ; j++){
            dp[i][j] = 0;
        }
    }
    int resta;
    //recorre las filas
    for(int i=1; i<k ;i++){
        //recorre las columnas
        for(int j=1; j<n ;j++){
            int maximaG = -1;
            //buscar la maxima ganancia
            for(int m=0; m<j; m++){
                resta = fechas[j]-fechas[m];
                if(resta>0){
                    // compara el maximo actual sumando la resta hallada y el valor de la fila y columna anterior (este es el maximo para la numero de compras anterior)
                    if(m>0 && maximaG<resta+dp[i-1][m-1]){
                        maximaG = resta+dp[i-1][m-1];
                    }
                    // si m es 0 no se considera la fila y columna anterior
                    if(m==0 && maximaG<resta)
                        maximaG = resta;
                        
                }
            }
            int maximoAnterior = dp[i][j-1];
            // compara el maximo hallado con el maximo de la columna anterior (el maximo del caso anterior)
            if(maximaG > maximoAnterior){
                dp[i][j] = maximaG;
            }else{
                dp[i][j] = maximoAnterior;
            }
            imprimirDP(dp,n,k);
        }
    }
    
    return dp[k-1][n-1];
}

int main(int argc, char** argv) {
    int fechas[] = {120,100,150,125,120,150,200,250};
    int n = N;
    int k = K;
    
    
    cout << "La ganancia maxima sera: " << calcularGananciaMaxima(fechas,n,k) << " soles" << endl;
    
    
    return 0;
}
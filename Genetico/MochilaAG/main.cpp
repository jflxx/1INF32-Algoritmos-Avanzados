#include <iostream>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <complex>
using namespace std;


#define NITERACIONES 100
#define NIND 10
#define Tseleccion 0.5
#define Pcasamiento 0.5
#define Tmutacion 0.8
/*
 * 
 */
struct Activo{
    double precio_actual;
    double precio_futuro_optimista;
    double precio_futuro_pesimista;
    
    Activo(double pa, double pfo, double pfp) : precio_actual(pa), precio_futuro_optimista(pfo), precio_futuro_pesimista(pfp) {}
    
};
vector<Activo> gpaq;

bool aberracion(vector<int>cromo,vector<Activo>assetPool,int maxInversion){
    int total=0;
    
    for(int i=0;i<cromo.size();i++)
        total+=cromo[i]*assetPool[i].precio_actual;
    
    return total>maxInversion;
}

void generapoblacioninicial(vector<vector<int>>&poblacion,vector<Activo>assetPool,
        int n,int maxInversion){
    int cont=0;
    
    while(cont<NIND){
        vector <int> vaux;
        for(int i=0;i<n;i++)
            vaux.push_back(rand()%2);
        if(not aberracion(vaux,assetPool,maxInversion)){
            poblacion.push_back(vaux);
            cont++;
        }
    }
} 
int calculafitness(vector<int> cromo,vector<Activo>assetPool){
    double sumaPOP=0;
    double PrecioActual=0;
    double PrecioPPP=0;
    int cont=0;
    for(int i=0;i<cromo.size();i++){
        // suma de precios optimistas
        sumaPOP += cromo[i] * assetPool[i].precio_futuro_optimista;
        //precio actual portafolio
        PrecioActual += cromo[i] * assetPool[i].precio_actual;
        //precio pesimista 
        PrecioPPP += cromo[i] * assetPool[i].precio_futuro_pesimista;
    }
    
    cont += fabs(sumaPOP - PrecioActual) - fabs(PrecioPPP - PrecioActual);
    return cont;
}
void muestrapoblacion(vector<vector<int>> poblacion,vector<Activo>assetPool){
    for(int i=0;i<poblacion.size();i++){
        for(int j=0;j<poblacion[i].size();j++){
            cout << poblacion[i][j] << "  ";
        }
        cout <<" fo="<< calculafitness(poblacion[i],assetPool) <<endl;
    }
}
void calculasupervivencia(vector<vector<int>>poblacion,
    vector<int>&supervivencia,vector<Activo>assetPool ){
    int suma=0;
    
    for(int i=0;i<poblacion.size();i++)
        suma+=calculafitness(poblacion[i],assetPool);
    for(int i=0;i<poblacion.size();i++){
        int fit= round(100*(double)calculafitness(poblacion[i],assetPool)/suma);
        supervivencia.push_back(fit);
    }

}

void cargaruleta(vector<int>supervivencia,int *ruleta){
    int ind=0;
    for(int i=0;i<supervivencia.size();i++)
        for(int j=0;j<supervivencia[i];j++)
            ruleta[ind++]=i;
}

void seleccion(vector<vector<int>>&padres,vector<vector<int>>poblacion,
    vector<Activo>assetPool,int n,int maxInv){
    int ruleta[100]{-1};
    vector<int>supervivencia;
    calculasupervivencia(poblacion,supervivencia,assetPool);
    cargaruleta(supervivencia,ruleta);
    int nseleccionados= poblacion.size()*Tseleccion;        
    for(int i=0;i<nseleccionados;i++){
        int ind=rand()%100;
        if(ruleta[ind]>-1)
            padres.push_back(poblacion[ruleta[ind]]);
            
    } 

}

void generahijo(vector<int>padre,vector<int>madre,
        vector<int>&hijo){
    int pos=round(padre.size()*Pcasamiento);
    
    for(int i=0;i<pos;i++)
        hijo.push_back(padre[i]);
    for(int i=pos;i<madre.size();i++)
        hijo.push_back(madre[i]);
}

void casamiento(vector<vector<int>>padres,
        vector<vector<int>>&poblacion,vector<Activo>assetPool,int maxInversion){
    for(int i=0;i<padres.size();i++)
        for(int j=0;j<padres.size();j++)
            if(i!=j){
                vector<int>cromo;
                generahijo(padres[i],padres[j],cromo);
                if(!aberracion(cromo,assetPool,maxInversion))
                    poblacion.push_back(cromo);
            }
}
void mutacion(vector<vector<int>> &poblacion,vector<vector<int>> padres,
         vector<Activo>assetPool ,int maxInver){
    int cont=0;
    int nmuta=round(padres[0].size()*Tmutacion);
    for(int i=0;i<padres.size();i++){
        while(cont<nmuta){
            int ind=rand()%padres[0].size();
            if(padres[i][ind]==0){
                padres[i][ind]=1;
            }
            else
                padres[i][ind]=0;
            cont++;
        }
        if(!aberracion(padres[i],assetPool,maxInver))
            poblacion.push_back(padres[i]);     
    }
}
int compacta(vector<int>cromo){
    int num=0;
    for(int i=0;i<cromo.size();i++)
        num+=pow(2,i)*cromo[i];
    
    return num;
    
}

void eliminaaberraciones(vector<vector<int>> &poblacion,const vector<Activo>& assetPool){
    map<int,vector<int>> municos;
    
    for(int i=0;i<poblacion.size();i++){
        int num=compacta(poblacion[i]);
        municos[num]=poblacion[i];
    }
    poblacion.clear();
    for(map<int,vector<int>>::iterator it=municos.begin();
            it!=municos.end();it++){
        poblacion.push_back(it->second);
    }   
    
}
bool compara(vector<int>a,vector<int>b){
    int suma=0,sumb=0;
   
    for(int i=0;i<a.size();i++)
        suma+=calculafitness(a,gpaq);
    for(int i=0;i<b.size();i++)
        sumb+=calculafitness(b,gpaq);
    return suma>sumb;
}

void generarpoblacion(vector<vector<int>> &poblacion,
        vector<Activo>assetPool,int maxInversion){
    
    gpaq=assetPool;
    sort(poblacion.begin(),poblacion.end(),compara);
    poblacion.erase(poblacion.begin()+NIND,poblacion.end());
    
}
double muestramejor(vector<vector<int>> &poblacion,
       vector<Activo>assetPool ,int maxInversion){
    int mejor=0;
    for(int i=0;i<poblacion.size();i++)
        if(calculafitness(poblacion[mejor],assetPool)<calculafitness(poblacion[i],assetPool))
            mejor=i;
    
    cout << endl<<"La mejor solucion es:" << calculafitness(poblacion[mejor],assetPool)<<endl;
    for(int i=0;i<poblacion[mejor].size();i++){
        cout << poblacion[mejor][i] << "  ";        
    }
    cout << endl;
    return calculafitness(poblacion[mejor],assetPool);
}

void mochilaAG(vector<Activo> &assetPool,int n,int maxInversion){
    int cont=0;
    vector<vector<int>> poblacion;
    srand(time(NULL));
    generapoblacioninicial(poblacion,assetPool,n,maxInversion);
    muestrapoblacion(poblacion,assetPool);  
    
    double suma=0;
    // itero
    while(1){
        vector<vector<int>> padres;
        seleccion(padres,poblacion,assetPool,n,maxInversion);
        casamiento(padres,poblacion,assetPool,maxInversion);
        mutacion(poblacion,padres,assetPool,maxInversion);
        //elimino abrerraciones
        eliminaaberraciones(poblacion,assetPool );
        // genero la nueva poblacion
        generarpoblacion(poblacion,assetPool,maxInversion);
        cout<<endl;
        muestrapoblacion(poblacion,assetPool);
        suma = muestramejor(poblacion,assetPool,maxInversion);
        cont++;
        if(cont==NITERACIONES) break;
    }
    double promedio = suma/NITERACIONES;
    cout<<"El promedio para "<<Tmutacion<<" es :"<<suma<<endl;
}
int main(int argc, char** argv) {
    vector<Activo> assetPool = {
        {100, 150, 80},
        {200, 250, 180},
        {150, 220, 130},
        {120, 180, 100},
        {180, 230, 160},
        {110, 170, 90},
        {130, 200, 110},
        {160, 210, 140},
        {140, 190, 120},
        {210, 270, 190},
        {170, 240, 150},
        {190, 260, 170},
        {220, 300, 200},
        {200, 280, 180},
        {180, 250, 160},
        {195, 260, 175},
        {205, 275, 185},
        {215, 285, 195},
        {225, 295, 205},
        {235, 305, 215}
    };

    int n = assetPool.size();

    int maxInversion = 1000;
    
    mochilaAG(assetPool,n,maxInversion);

    return 0;
}

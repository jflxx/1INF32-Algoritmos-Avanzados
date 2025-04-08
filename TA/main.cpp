#include <cstdlib>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <ctime>
using namespace std;

#define numit  10
#define alphaP 0.203
#define alphaM 0.261
#define alpha 0.3
#define beta 0.4
#define lamda 0.5
#define omega 0.0022
//#define teta 1.5
#define teta 2
#define numP 3
#define numM 4
#define numEspecialidades 4
/*
 * 
 */
struct Paciente{
    string Nombre;
    int Edad;
    int CargaFamiliar;
    int Ingresos;
    int EspRequerida;
    int CargaPorEnfermedad;
    string CMP;
    double bondad;
};

struct Medico{
    string Nombre;
    string CMP;
    int Experiencia;
    int Especialidad;
    vector<int> vTurnos;
    vector<int> vDisp;
    double bondad;
};
void leerDatos(vector<Paciente> &listaPacientes,vector<Medico> &listaMedicos){
    
    //pacientes
    Paciente paciente0={"Paciente0",6,0,1,2,310,"0",0};
    Paciente paciente1={"Paciente1",27,4,1200,1,110,"0",0};
    Paciente paciente2={"Paciente2",54,4,1900,2,1,"0",0};
//    Paciente paciente3={"Paciente3",3,0,1,1,1,"0",0};
//    Paciente paciente4={"Paciente4",67,0,300,1,1,"0",0};
//                      Nombre,edad,CargaFamiliar,Ingresos,EspReequerida,CargaPorEnfermedad
///     Paciente paciente0={"Paciente1",3,0,0,2,390,"0",0};
//    Paciente paciente1={"Paciente2",70,0,400,2,300,"0",0};
//    Paciente paciente2={"Paciente3",30,2,1500,2,40,"0",0};
    
    
    //insertarlos
    listaPacientes.push_back(paciente0);
    listaPacientes.push_back(paciente1);
    listaPacientes.push_back(paciente2);
//    listaPacientes.push_back(paciente3);
//    listaPacientes.push_back(paciente4);
    //insertar medicos
    Medico medico0={"Medico0","M-0",35,2,{19,15,14,11,10,16,15},{},0};
    Medico medico1={"Medico1","M-1",3,1,{14,14,18,11,18,10,15},{},0};
    Medico medico2={"Medico2","M-2",4,4,{11,18,16,10,18,15,17},{},0};
    Medico medico3={"Medico3","M-3",29,3,{2,17,14,18,16,15,17},{},0};
//    Medico medico4={"Medico4","M-4",10,2,{16,17,14,16,19,18,0},{},0};
//    Medico medico5={"Medico5","M-5",19,2,{1,19,19,10,19,19,17},{},0};
//                     Nombre, CMP, Experiencia, Especialidad, vTurnos,vDIsp
//    Medico medico0={"Medico1","M-1",40,2,{1,0,0,0,0,0,0},{},0};
//    Medico medico1={"Medico2","M-2",10,2,{1,0,0,0,0,0,0},{},0};
   
    //insertarlos
    listaMedicos.push_back(medico0);
    listaMedicos.push_back(medico1);
    listaMedicos.push_back(medico2);
    listaMedicos.push_back(medico3);
//    listaMedicos.push_back(medico4);
//    listaMedicos.push_back(medico5);



    for(auto &x: listaMedicos){
        x.vDisp = x.vTurnos;
    }
    
    //calcular la bondad para los pacieentes
    for(auto &x: listaPacientes){
        //calcular bondad
        if(x.Ingresos!=0)
        x.bondad = (alpha*(0.015*pow(x.Edad,2) - x.Edad + 20)+
                beta*x.CargaPorEnfermedad + lamda*x.CargaFamiliar)/(omega*x.Ingresos);
        else{
            x.bondad = (alphaP*(0.015*pow(x.Edad,2) - x.Edad + 20)+
                beta*x.CargaPorEnfermedad + lamda*x.CargaFamiliar)/omega;
        }
        
    }
//    
//    //calcular la bondad para los medicos
//    for(auto x: listaMedicos){
//        
//        x.bondad = (alpha*x.Experiencia*teta*((double)x.vDisp[0]/x.vTurnos[0]))/(beta*x.TiempoCita);
//        cout<<x.bondad<<endl;
//    }
        
}

void inicializar(vector<vector<int>> &MT,vector <Medico> &listaMedicos){
    for(int j=0; j<listaMedicos.size() ;j++){
        for(int i=0; i<7 ;i++){
            MT[i][j] = listaMedicos[j].vDisp[i];
        }
    }
}

int cmp(Paciente a,Paciente b){
    return a.bondad < b.bondad;
}

int sumaTurnos(const vector<int> &vgenerico){
    int suma = 0;
    for(int x:vgenerico){
        suma+=x;
    }
    return suma;
}

vector<Paciente> OrdenarAscendenteBondad(const vector<Paciente> &listaPacientes){
    vector<Paciente> copia = listaPacientes;
    sort(copia.begin(),copia.begin()+numP,cmp);
    return copia;
}

int calcularTiempoCita(const vector<int> &vDisp){
    int cont=0;
    
    for(int x:vDisp){
        if(x!=0) cont++;
    }
    return cont!=0? cont:1;
}

int cmpM(Medico a,Medico b){
    return a.bondad < b.bondad;
}

vector<Medico> OrdenarAscendenteBondad(vector<Medico> &listaMedicos){
        //calcular la bondad para los medicos
    vector<Medico> copia = listaMedicos;
    
    for(auto &x: copia){
        int TD = sumaTurnos(x.vDisp);
        int TT = sumaTurnos(x.vTurnos);
        int TC = calcularTiempoCita(x.vDisp);
        x.bondad = (((double)alpha*x.Experiencia)/(beta*TC))*teta*((double)TD/TT);
    }
    sort(copia.begin(),copia.begin()+copia.size(),cmpM);
    return copia;
}

Medico SeleccionarCoincidencias(Paciente paciente,const vector<Medico> &listaPendientesM){
    for(int i=0;i<listaPendientesM.size();i++){
        if(listaPendientesM[i].CMP.compare(paciente.CMP) == 0 ){
            return listaPendientesM[i];
        }
    }
    Medico med;
    return med;
}

int obtenerIndiceM(const vector<Medico> &listaMedicos,Medico Melegido){
    for(int i=0; i<listaMedicos.size() ;i++){
        if(Melegido.CMP.compare(listaMedicos[i].CMP)==0)
            return i;
    }
    return -1;
}

int obtenerIndiceP(const vector<Paciente> &listaPaciente,Paciente Pelegido){
    for(int i=0; i<listaPaciente.size() ;i++){
        if(Pelegido.Nombre.compare(listaPaciente[i].Nombre)==0)
            return i;
    }
    return -1;
}

int obtenerDiaSemanaLibre(vector<vector<int>> &MTCopia,int idM){
    for(int i=0; i<7 ;i++){
        if(MTCopia[i][idM]!=0){
            return i;
        }
    }
    return -1;
}

int turnoDisponibles(int idM,vector<vector<int>> &MTcopia){
    int cont = 0;
    for(int i=0; i<7 ;i++){
        cont+=MTcopia[i][idM];
    }
    return cont;
}

void removerM(vector<Medico> &listaGenerica,Medico Med){
    for(int i=0; i<listaGenerica.size() ;i++){
        if(listaGenerica[i].CMP.compare(Med.CMP)==0)
            listaGenerica.erase(listaGenerica.begin()+i);
    }
}

void removerP(vector<Paciente> &listaGenerica,Paciente Pac){
    for(int i=0; i<listaGenerica.size() ;i++){
        if(listaGenerica[i].Nombre.compare(Pac.Nombre)==0)
            listaGenerica.erase(listaGenerica.begin()+i);
    }
}


void imprimirMejorSolucion(const vector<pair<int, int>> &mejorSolucion,double mejorBondad,
        vector<Paciente> &listaPacientes,vector<Medico> &listaMedicos){
    cout << "\n=== Mejor Solución Encontrada ===" << endl;
    cout << "Bondad total: " << mejorBondad << endl;
    for (const auto& asignacion : mejorSolucion) {
        int idP = asignacion.first;
        int idM = asignacion.second;
        cout << "Paciente: " << listaPacientes[idP].Nombre 
             << " -> Médico: " << listaMedicos[idM].Nombre << endl;
    }
}

vector<pair<int, int>> Algoritmo_GRASP_Construccion(vector<vector<int>> &MA, vector<vector<int>> &MTCopia, vector<int> S,
                                                    const vector<Paciente> &listaPacientes,
                                                    vector<Medico> &listaMedicos, vector<vector<int>> &MT,
                                                    int MO[numP][numM]) {
   
    vector<Paciente> listaPendientesP = OrdenarAscendenteBondad(listaPacientes);
    vector<Medico> listaPendientesM = OrdenarAscendenteBondad(listaMedicos);
    
    vector<pair<int, int>> asignaciones; // Para almacenar las asignaciones (paciente, médico)
    srand(time(NULL));
    int listaOrdenAt[listaMedicos.size()] = {};
    
    for (int i = 0; i < numEspecialidades; i++) {
        
        vector<Paciente> PCL = {};
        vector<Medico> MCL = {};

        listaPendientesM = OrdenarAscendenteBondad(listaMedicos);
        while ((not listaPendientesM.empty()) and (not listaPendientesP.empty())) {
            double minP = listaPendientesP[0].bondad;
            double maxP = listaPendientesP.back().bondad;
//            cout << "----------------------" << endl;
//            //imprimir Lista antes;
//            cout << "Pacientes antes:" << endl; 
//            for(auto P: listaPendientesP){
//                cout << P.Nombre << " " << P.bondad << endl;
//            }
//            cout << "Medicos antes:" << endl; 
//            for(auto P: listaPendientesM){
//                cout << P.Nombre << " " << P.bondad << endl;
//            }
            
            // Llenar la lista de candidatos PCL
            for (Paciente itemP : listaPendientesP) {
                double bondadItem = itemP.bondad;
                double parametro = maxP - alphaP * (maxP - minP);
                if (bondadItem <= maxP and (bondadItem >= parametro)) {
                    PCL.push_back(itemP);
                }
            }

            // Seleccionar un paciente aleatorio de PCL
            int indA = rand() % PCL.size();
            Paciente Pelegido = PCL[indA];

            // Llenar la lista de candidatos MCL
            double minM = listaPendientesM[0].bondad;
            double maxM = listaPendientesM.back().bondad;
            Medico Melegido;
//            for(auto P: listaPendientesM){
//                cout << P.Nombre << " " << P.CMP << " " << P.bondad << endl;
//            }
            
                    
            if (Pelegido.CMP == "0") {
                for (Medico itemM : listaPendientesM) {
                    double bondadItem = itemM.bondad;
                    double parametro = maxM - alpha * (maxM - minM);
                    if ((bondadItem <= maxM) and (bondadItem >= maxM - alphaP * (maxM - minM))) {
                        MCL.push_back(itemM);
                    }
                }
//              Seleccionar un médico aleatorio de MCL
                if(MCL.size() != 0){
                    int indAlMed = rand() % MCL.size();
                    Melegido = MCL[indAlMed];
                }
            } else {
                Melegido = SeleccionarCoincidencias(Pelegido, listaPendientesM);
//                cout << Melegido.Nombre << " " << Melegido.bondad << endl;
            }
            
            
            
            // Asignar turno
            int idM = obtenerIndiceM(listaMedicos, Melegido);
            int idP = obtenerIndiceP(listaPacientes, Pelegido);
            int diaLibre = obtenerDiaSemanaLibre(MTCopia, idM);  
            
            if (diaLibre != -1) { // Solo asignar si hay disponibilidad
//                MT[idP][idM] = diaLibre + 1;
                MTCopia[diaLibre][idM]--; // Reducir disponibilidad
                listaOrdenAt[idM]++;
                MO[idP][idM] = listaOrdenAt[idM];
                // Guardar asignación
                asignaciones.emplace_back(idP, idM);
            }
            
            if (turnoDisponibles(idM, MTCopia) == 0) {
                removerM(listaPendientesM, Melegido);
            }
            // Actualizar listas
            removerM(MCL, Melegido);
            removerP(listaPendientesP, Pelegido);
            removerP(PCL, Pelegido);
            
//            //imprimir Lista antes;
//            cout << "Pacientes Despues" << endl; 
//            for(auto P: listaPendientesP){
//                cout << P.Nombre << " " << P.CMP << endl;
//            }
//            cout << "Medicos Despues:" << endl; 
//            for(auto P: listaPendientesM){
//                cout << P.Nombre << " " << P.CMP << endl;
//            }
        }
//        imprimirMejorSolucion(asignaciones,0,listaPacientes,listaMedicos);
    }
    return asignaciones;
}

void Algoritmo_GRASP_Mejora(vector<vector<int>> &MA, vector<vector<int>> &MT, int MO[numP][numM], 
                            const vector<Paciente> &listaPacientes, const vector<Medico> &listaMedicos) {
    // Recorrer columnas de MA (médicos)
    for (int c = 0; c < numM; c++) {
        // Recorrer filas de MA (pacientes)
        for (int f = 0; f < numP; f++) {
            if (MA[f][c] != 0) { // Si el paciente está asignado a ese médico
                // Intentar intercambio con otros pacientes
                for (int t = f + 1; t < numP; t++) {
                    if (MA[t][c] != 0) { // Si hay otro paciente asignado al mismo médico
                        // Evaluar si el intercambio mejora la solución
                        double bondadActual = (alpha * listaPacientes[f].bondad + 
                                               beta * listaMedicos[c].bondad) / 
                                               (1 + MT[f][c]);

                        double bondadIntercambio = (alpha * listaPacientes[t].bondad + 
                                                    beta * listaMedicos[c].bondad) / 
                                                    (1 + MT[t][c]);

                        if (bondadIntercambio > bondadActual) {
                            // Hacer el intercambio si mejora
                            swap(MA[f][c], MA[t][c]);
                            swap(MT[f][c], MT[t][c]);
                            swap(MO[f][c], MO[t][c]);
                        }
                    }
                }
            }
        }
    }
}

vector<Medico> obtenerBondadActual(vector<Medico> &listaMedicos){
        //calcular la bondad para los medicos
    vector<Medico> copia = listaMedicos;
    for(auto &x: copia){
        int TD = sumaTurnos(x.vDisp);
        int TT = sumaTurnos(x.vTurnos);
        int TC = calcularTiempoCita(x.vDisp);
        x.bondad = (((double)alpha*x.Experiencia)/(beta*TC))*teta*((double)TD/TT);
    }
    return copia;
}

int main(int argc, char** argv) {
    vector<Paciente> listaPacientes;
    vector<Medico> listaMedicos;
    leerDatos(listaPacientes, listaMedicos);
    listaMedicos = obtenerBondadActual(listaMedicos);
    
//    for(auto x:listaMedicos){
//        cout << x.CMP << "  " << x.bondad << endl;
//    }
    
    
    vector<int> S = {1, 1, 1, 1}; // Semana de trabajo (puedes ajustar según contexto)
    // Inicializar matrices
    int MO[numP][numM]{}; // Matriz de ocupación médico-paciente
    vector<vector<int>> MT(7, vector<int>(numM, 0)); // Disponibilidad semanal de médicos
    vector<vector<int>> MA(numP, vector<int>(numM, 0)); // Matriz de asignaciones paciente-médico

    // Inicializar la matriz MT con los turnos iniciales de los médicos
    inicializar(MT, listaMedicos);
    // Variables para guardar la mejor solución y sus métricas
    vector<pair<int, int>> mejorSolucion; // Almacena las asignaciones (paciente, médico)
    double mejorBondad = -1;

    for (int cont = 0; cont < numit; cont++) {
        // Copiar la matriz MT (estado inicial de disponibilidad para esta iteración)
        vector<vector<int>> MTCopia = MT;

        // Fase de construcción (crear una solución inicial)
        vector<pair<int, int>> solucionActual = Algoritmo_GRASP_Construccion(MA, MTCopia, S, listaPacientes, listaMedicos, MT, MO);
        
        for(auto x:solucionActual){
            cout << x.first << "   " << x.second << endl;
        }
        
        // Calcular bondad total de la solución actual
        double bondadActual = 0;
        for (const auto& asignacion : solucionActual) {
            int idP = asignacion.first;
            int idM = asignacion.second;
//            cout << listaMedicos.size() << " "<< listaPacientes.size() << endl;
//            cout << listaPacientes[idP].bondad << "  " << listaMedicos[idM].bondad << endl;
            bondadActual += (alpha * listaPacientes[idP].bondad + beta * listaMedicos[idM].bondad);
        }
        
//        cout << "Bondad Actual: " << bondadActual << endl;

        // Actualizar la mejor solución si la actual es superior
        if (bondadActual > mejorBondad) {
            mejorBondad = bondadActual;
            mejorSolucion = solucionActual;
        }

        // Fase de mejora (opcional, dependiendo de la lógica de GRASP)
        Algoritmo_GRASP_Mejora(MA, MT, MO, listaPacientes, listaMedicos);

        // Salida intermedia para verificar progreso (puedes comentar esto si no es necesario)
        cout << "Iteración: " << cont + 1 << ", Bondad actual: " << bondadActual << endl;
        imprimirMejorSolucion(solucionActual,mejorBondad,listaPacientes,listaMedicos);
//        break;
    }
    

    return 0;
}
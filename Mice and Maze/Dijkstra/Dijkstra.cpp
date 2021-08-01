#include <iostream>
#include <fstream>

#define V 100
#define INF 99999

using namespace std;


void transpuesta(int M[][V], int n){
    int temp;
    for(int i=0; i<n; i++){
        for(int j=0; j<i; j++){
            temp=M[i][j];
            M[i][j]=M[j][i];
            M[j][i]=temp;
        }
    }
}

//Llenar un grafo matriz
void llenarGrafoMatriz(int M[][V], int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i==j)
                M[i][j] = 0;
            else
                M[i][j] = INF;
        }
    }
}

//Mostrar matriz
void mostrarMatriz(int M[][V], int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout<<M[i][j]<<" ";
        }
        cout<<endl;
    }
}



int obtenerMinDist(int * menores_caminos, bool verificador[], int N){
    int min = INF;
    int indice_min;
 
    for (int i = 0; i < N; i++)
        if (verificador[i] == false && menores_caminos[i] <= min){
            min = menores_caminos[i];
            indice_min = i;
        }
 
    return indice_min;
}

int * dijkstra(int grafo[][V], int N, int src){
    int *menores_caminos = new int[N];     //Arreglo con las menores distancias desde todos los nodos a un nodo en especial
    bool verificador[N];             // Arreglo que verificará que vértices ya tienen menor camino
 
    for (int i = 0; i < N; i++){
        menores_caminos[i] = INF;
        verificador[i] = false;
    }
 
    //Menor camino del nodo elegido es 0
    menores_caminos[src] = 0;
 
    //Algoritmo de Dijkstra
    for (int i = 0; i < N - 1; i++) {

        int min = obtenerMinDist(menores_caminos, verificador, N);
 
        verificador[min] = true;
 
        for (int j = 0; j < N; j++){
            if (!verificador[j] && 
            grafo[min][j] && 
            menores_caminos[min] != INF &&
            menores_caminos[min] + grafo[min][j] < menores_caminos[j]){

                menores_caminos[j] = menores_caminos[min] + grafo[min][j];
            }
                
        }
    }
 
    return menores_caminos;
}

int main(){

    //Variables usadas
    int N=0, E=0, T=0, M=0;
    int cases=0;

    //Leer archivo entrada
    ifstream entrada;
    entrada.open("input.txt");

    //Abrir archivo de salida
    ofstream salida;
    salida.open("output.txt");

    string linea;
    getline(entrada,linea);
    cases = stoi(linea);
    entrada.ignore();

    //Para cada caso
    for(int i=0; i<cases; i++){
        entrada.ignore();

        //N: Numero de células (tamaño grafo - matriz) 
        getline(entrada,linea);
        N = stoi(linea);

        //E: Número que identifica a la célula de salida
        getline(entrada,linea);
        E = stoi(linea);
        
        //T: Contador regresivo
        getline(entrada,linea);
        T = stoi(linea);


            
        //Creamos un grafo representado por una matriz
        int grafo[N][V];
        //M: Nro Conexiones del grafo
        getline(entrada,linea);
        M = stoi(linea);
        llenarGrafoMatriz(grafo,N);
        
        //cout<<N<<endl<<E<<endl<<T<<endl<<M<<endl;

        //Para cada conexión
        for(int j=0; j<M; j++){
            getline(entrada,linea);

            int a = stoi(linea.substr(0,linea.find(" ")));  //Posición a del grafo para la conexión
            linea.erase(0,linea.find(" ")+1);
            int b = stoi(linea.substr(0,linea.find(" ")));  //Posición b del grafo para la conexión
            linea.erase(0,linea.find(" ")+1);
            int t = stoi(linea);                            //Tiempo que toma viajar de "a" a "b" 

            grafo[a-1][b-1] = t;                            //Se asigna al grafo el valor t. En el grafo a está en la posición a-1 y b igual

        }

        cout<<"GRAFO: "<<i+1<<endl<<endl;
        mostrarMatriz(grafo, N);
        cout<<endl;
        transpuesta(grafo, N);  //Invertimos matriz para que en vez de calcular los mínimos caminos de un nodo a los demás
                                //se calculen los mínimos camino de todos los nodos a uno solo (salida)
        
        int *caminos_minimos = dijkstra(grafo, N, E-1);
        
        int nratones = 0;
        cout<<"Nodo  -   Distancia minima desde ese nodo hasta el nodo "<<E<<endl;
        for(int i=0; i<N;i++){
            cout<<" "<<i+1<<"         "<<caminos_minimos[i]<<endl;
            
            //Predecir si ese ratón salió de acuerdo al tiempo del contador
            if(caminos_minimos[i]<=T){
                nratones++;
            }
        }

        salida<<nratones<<endl;
        cout<<endl<<"Ratones que lograran salir: "<<nratones<<endl;
        cout<<endl<<endl;

        delete[] caminos_minimos;
    }

    return 0;
}
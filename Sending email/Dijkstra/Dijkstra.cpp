#include <iostream>
#include <fstream>

#define V 100
#define INF 99999

using namespace std;

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
    int n=0, m=0, S=0, T=0;
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

    //Para cada caso
    for(int i=0; i<cases; i++){

        getline(entrada,linea);

        //n: Numero de nodos (servidores)
        n = stoi(linea.substr(0,linea.find(" ")));
        linea.erase(0,linea.find(" ")+1);

        //m: Numero de conexiones (aristas)
        m = stoi(linea.substr(0,linea.find(" ")));
        linea.erase(0,linea.find(" ")+1);

        //Servidor S
        S = stoi(linea.substr(0,linea.find(" ")));
        linea.erase(0,linea.find(" ")+1);

        //Servidor T
        T = stoi(linea);
            
        //Creamos un grafo representado por una matriz
        int grafo[n][V];
        //M: Nro Conexiones del grafo
        llenarGrafoMatriz(grafo,n);

        //Para cada conexión
        for(int j=0; j<m; j++){
            getline(entrada,linea);

            int s1 = stoi(linea.substr(0,linea.find(" ")));  //Servidor s1 del grafo para la conexión
            linea.erase(0,linea.find(" ")+1);
            int s2 = stoi(linea.substr(0,linea.find(" ")));  //Servidor s2 del grafo para la conexión
            linea.erase(0,linea.find(" ")+1);
            int t = stoi(linea);                            //Tiempo: Milisegundos que toma enviar un mensaje desde s1 hasta s2

            grafo[s1][s2] = t;                            //Se asigna al grafo el valor t. En el grafo a está en la posición s1 y s2
            grafo[s2][s1] = t;
        }

        cout<<"GRAFO: "<<i+1<<endl<<endl;
        mostrarMatriz(grafo, n);
        cout<<endl;
        
        int *caminos_minimos = dijkstra(grafo, n, S);
        
        cout<<"Nodo  -   Distancia minima desde el nodo "<<S<<endl;
        for(int i=0; i<n;i++){
            cout<<" "<<i+1<<"         "<<caminos_minimos[i]<<endl;            
        }

        cout<<endl;

        int camino = caminos_minimos[T];

        

        if(camino == INF){
            cout<<"Distancia minima desde el nodo "<<S<<" hasta el nodo "<<T<<":"<<endl;
            cout<<"unreachable"<<endl<<endl;
            salida<<"Case #"<<i+1<<": unreachable"<<endl;
        }
        else{
            cout<<"Distancia minima desde el nodo "<<S<<" hasta el nodo "<<T<<":"<<endl;
            cout<<camino<<endl<<endl;
            salida<<"Case #"<<i+1<<": "<<camino<<endl;
        }

        delete[] caminos_minimos;
    }

    return 0;
}
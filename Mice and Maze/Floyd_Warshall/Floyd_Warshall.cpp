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

int ** floydWarshall(int graph[][V], int N){

    int **resultado;

    //Matriz que guardará los menores caminos
    resultado = new int*[N];
    for(int i=0; i<N; i++){
        resultado[i] = new int[N];
    }
 
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            resultado[i][j] = graph[i][j];

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (resultado[i][j] > (resultado[i][k] + resultado[k][j])
                    && (resultado[k][j] != INF
                    && resultado[i][k] != INF))
                    {
                        resultado[i][j] = resultado[i][k] + resultado[k][j];
                    }
            }
        }
    }
    
    return resultado;
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
        
        int **resultados = floydWarshall(grafo, N);
        int *caminos_minimos = new int[N];

        cout<<"Matriz de Floyd Warshall con todos los menores caminos de todos los nodos: "<<endl;
        //Mostraremos la matriz y copiaremos todos los caminos desde todos los nodos hasta el nodo indicado
        for(int k=0; k<N; k++){
            for(int l=0; l<N; l++){
                if(l==E-1){
                    caminos_minimos[k] = resultados[k][l];
                }
                cout<<resultados[k][l]<<" ";
            }
            cout<<endl;
        }
        
        int nratones = 0;
        cout<<endl<<"Nodo  -   Distancia minima desde ese nodo hasta el nodo "<<E<<endl;
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

        //Liberar memoria
        delete[] caminos_minimos;
        for(int j=0; j<N; j++){
            delete[] resultados[j];
        }
    }

    return 0;
}
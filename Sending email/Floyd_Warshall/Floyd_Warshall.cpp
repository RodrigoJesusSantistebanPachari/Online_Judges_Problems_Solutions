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

        cout<<"GRAFO: "<<i+1<<"---------------------"<<endl<<endl;
        mostrarMatriz(grafo, n);
        cout<<endl;
        
        int **resultados = floydWarshall(grafo, n);
        
        cout<<"Matriz de Floyd Warshall con todos los menores caminos de todos los nodos: "<<endl;
        for(int k=0; k<n; k++){
            for(int l=0; l<n; l++){
                cout<<resultados[k][l]<<" ";
            }
            cout<<endl;
        }

        cout<<endl;
            
        int camino_minimo = resultados[S][T];

        if(camino_minimo == INF){
            cout<<"Distancia minima desde el nodo "<<S<<" hasta el nodo "<<T<<":"<<endl;
            cout<<"unreachable"<<endl<<endl;
            salida<<"Case #"<<i+1<<": unreachable"<<endl;
        }
        else{
            cout<<"Distancia minima desde el nodo "<<S<<" hasta el nodo "<<T<<":"<<endl;
            cout<<camino_minimo<<endl<<endl;
            salida<<"Case #"<<i+1<<": "<<camino_minimo<<endl;
        }

        //Liberar memoria
        for(int j=0; j<n; j++){
            delete[] resultados[j];
        }
    }

    return 0;
}
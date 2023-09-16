#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros

using namespace std;


int Buscar( int** v,int contador, int nodo){
    int  sol=-1,cont, maximo=0;
    for (int i = 0; v[nodo][i] != -1; i++) {
        if(v[nodo][i] != -2 ) {
            int l;
            cont = 0;
            for ( l= 0; v[v[nodo][i]-1][l] != -1; l++) {
                if (v[v[nodo][i]-1][l] != -2 ){cont++;}

            }
            if (maximo <= cont) {
                maximo = cont;
                sol = v[nodo][i];
            }
         }
    }

    return sol;
}


int main(int argc, char *argv[]) {

    int ** v, *sol, *candidatos;
    int n, i, j, argumento, k=0;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
    unsigned long  tejecucion; // tiempo de ejecucion del algoritmo en ms
    unsigned long int semilla;
    ifstream fentrada;
    ofstream fsalida;

    if (argc <= 2) {
        cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
        cerr<<argv[0]<<" NombreFicheroEntrada NombreFicheroSalida\n\n";
        return 0;
    }
    cout << "Abirmos fichero entrada " << endl;
    // Abrimos fichero de entrada
    fentrada.open(argv[1]);
    if (!fentrada.is_open()) {
        cerr<<"Error: No se pudo abrir fichero para lectura "<<argv[1]<<"\n\n";
        return 0;
    }
    // Inicializamos generador del grafo
    char valorcogido;
    int cuidado;
    int contador=0, valornum;
    fentrada >> valorcogido;
    valornum = (int)valorcogido;
    //Tamaño del vector con los datos y cada uno con un vector con sus conexiones
    v = new int* [valornum];
    for (i = 0; i < valornum ; i++) {
        v[i] = new int [valornum];
    }
    cuidado=(int)valornum;

    fentrada >> valorcogido;
    while (valorcogido != '#' ){
        for(i=0; valorcogido != '*' ;i++){
            //GUARDO NUMEROS DEL FICHERO AL VECTOR
            valornum = (int)valorcogido - '0';
            v[contador][i] = valornum;
            k++;
            fentrada >> valorcogido;

        }
        v[contador][i] = -1;
        contador++;
        fentrada >> valorcogido;
    }
    //Vector donde irán las soluciones
    int maximacantidadearistas = (contador * (contador+1))/2;
    sol = new int [maximacantidadearistas];

    fentrada.close();

    cout << "Abirmos fichero salida " << endl;
    // Abrimos fichero de salida
    fsalida.open(argv[2]);

    //SI NO HAY CAMINO VÁLIDO
    if (!fsalida.is_open()) {
        cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
        return 0;
    }

    // BUSQUEDAD DEL CAMINO
    cout << "Entramos al código" << endl;

    t0 = std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo

    int pos=0;
    int nodollegar,nodo;


    //elegimos un punto para empezar
    int nodoinicial=1  -1;
    nodo=nodoinicial;
    fsalida<<nodo+1 << "  " ;
    sol[pos]=nodo+1;
    pos++;

    bool caminodirecto=false;
    //k Es la cantidad de conexiones que tienen las aristas (aristas * 2)
    while (k!=0){
        //BUSCAMOS EL NODO MAYOR CON EL MAYOR GRADO DE ARISTAS CONECTADAS
        nodollegar = Buscar(v,contador,nodo);

        if (nodollegar == -1 ) {
            cerr<<"Error: NO SE PUEDE ENCONTRAR UN CAMINO  VÁLIDO"<<"\n\n";
            return 1;
        }
        fsalida<<nodollegar << "  " ;
        //BUSCA EL NODO PARA ELIMINARLO Y GUARDARLO EN LA SOLUCIÓN
        for (int f=0; v[nodo][f] != -1 && caminodirecto==false ; f++){

           if(v[nodo][f] == nodollegar){
                caminodirecto=true;
                v[nodo][f]=-2;
           }
        }
        sol[pos]=nodollegar;
        pos++;
        //ELIMINAMOS EL NODO EN EL REGISTRO DEL NUEVO
        int guardar3 = nodo+1;
        nodo = nodollegar-1;

        for (int f=0; v[nodo][f] != -1 ; f++){
            if(v[nodo][f] == guardar3){
                v[nodo][f]=-2;
            }
        }
        //ELIMINO LOS DOS PUNTOS DE CONEXIÓN DE K
        k= k -2;
        caminodirecto=false;

    }
    //INDICO EL FINAL DEL ARRAY CON -1
    sol[pos]=-1;

    tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo

     tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

    cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n<<endl;

        // Guardamos tam. de caso y t_ejecucion a fichero de salida


    delete [] v;
    delete [] sol;


    // Cerramos fichero de salida
    fsalida.close();

    return 0;
}

// ALGORITMO B�SICO

#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros

using namespace std;


int main(int argc, char *argv[]) {

    int ** v, ** sol;
    int n, i, j, argumento, k = 1;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
    double tejecucion; // tiempo de ejecucion del algoritmo en ms
    unsigned long int semilla;
    ofstream fsalida;

    if (argc <= 3) {
        cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
        cerr<<argv[0]<<" NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
        return 0;
    }

    // Abrimos fichero de salida
    fsalida.open(argv[1]);
    if (!fsalida.is_open()) {
        cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
        return 0;
    }

    // Inicializamos generador de no. aleatorios
    semilla= atoi(argv[2]);
    srand(semilla);

    // Pasamos por cada tamaÒo de caso
    for (argumento= 3; argumento<argc; argumento++) {

        // Cogemos el tamanio del caso
        n = atoi(argv[argumento]);

        // Reservamos memoria para el vector
        v = new int * [n];

        // Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
        for (i = 0; i < n; i++) {
            v[i] = new int [k];
            for (j = 0; j < k; j++) {

                v[i][j] = rand() % n;

                // cout << v[i][j] << endl;

            }

        }

        t0 = std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo

        int l,cont;

        sol = new int *[n];

        for (i = 0; i < n; i++) {


            sol[i] = v[i];

            for (l = 0,cont = 0;(l < n) && (cont != k); l++) {

                for (j = 0 ; (j < k) && (cont != k); j++){

                    if (v[i][j] < v[l][j]) {
                        cont++;
                    }
                }

            }

            if (cont == k) {

                sol[i] = nullptr;
            }
        }

        tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo

//        cout << "solucion" << endl;
//        for (i = 0; i < n; i++) {
//           for (j = 0; j < k; j++) {
//
//              if (sol[i] != nullptr)
//                  cout << sol[i][j] << endl;
//            }
//        }

        unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

        cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n<<endl;

        // Guardamos tam. de caso y t_ejecucion a fichero de salida
        fsalida<<n<<" "<<tejecucion<<"\n";


        // Liberamos memoria del vector
        delete [] v;
        delete [] sol;
    }

    // Cerramos fichero de salida
    fsalida.close();

    return 0;
}


#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros

    using namespace std;


    int** Rellenartabla( int* v,int* w, int cantobj, int tammochila,int ** tabla ){
        if(tammochila==0){
            //CASO BASE
            for(int i = 0; i < cantobj; i++){
                tabla[i][tammochila]=0;
            }
        }else{
            //CASO GENERAL
            int valorarrastre, valornuevo;
            tabla = Rellenartabla( v, w,  cantobj,  tammochila-1, tabla);
            for(int i = 0; i < cantobj; i++){
                //BUSCAMOS EL VALOR DE ARRASTRE
                if(i!=0) {

                    valorarrastre = tabla[i - 1][tammochila];
                }else{
                    valorarrastre = 0;
                }
                //BUSCAMOS EL VALOR NUEVO

                if(i!=0 && tammochila-w[i] >= 0 ) {
                    valornuevo = tabla[i - 1][tammochila-w[i]]+v[i];
                }else{
                    valornuevo = 0;
                }
                if (i==0 && tammochila-w[i] >= 0 ) {
                    valornuevo = v[i];
                }

                //COMPARAMOS
                if(valorarrastre >= valornuevo){
                    tabla[i][tammochila] = valorarrastre;
                }else{
                    tabla[i][tammochila] = valornuevo;
                }

            }

        }

        return tabla;
    }


    int main(int argc, char *argv[]) {

        int *w, *v,**tabla, *sol, *candidatosl, tammochila, cantobj;
        int n, i, j, argumento, k=0;
        chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
        unsigned long  tejecucion; // tiempo de ejecucion del algoritmo en ms
        ifstream fentrada;

        if (argc <= 1) {
            cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
            cerr<<argv[0]<<" NombreFicheroEntrada \n\n";
            return 0;
        }



        cout << "Abirmos fichero entrada " << endl;
        // Abrimos fichero de entrada
        fentrada.open(argv[1]);
        if (!fentrada.is_open()) {
            cerr<<"Error: No se pudo abrir fichero para lectura "<<argv[1]<<"\n\n";
            return 0;
        }
        // Cogemos el tamaño de la mochila y la cantidad de objetos
        int contador=0, valornum;
        fentrada >> tammochila;
        fentrada >> cantobj;

        //Tamaño del vector con los datos y cada uno con un vector con sus conexiones
        v = new int [cantobj];
        w = new int [cantobj];
        tabla  = new int* [cantobj];
        for (i = 0; i < cantobj ; i++) {
            tabla[i] = new int [tammochila+1];
        }


        fentrada >> valornum;
        while (valornum!= -2 ){
            while( valornum!= -1){
                //GUARDO NUMEROS DEL FICHERO A LOS VECTOR
                v[contador] = valornum;
                fentrada >> valornum;
                w[contador] = valornum;
                contador++;
                fentrada >> valornum;

            }
            fentrada >> valornum;

        }

        fentrada.close();



        // BUSQUEDAD DEL CAMINO
        cout << "Entramos al codigo" << endl;

        t0 = std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo

        //Rellenar
        tabla = Rellenartabla(v,w,cantobj,tammochila, tabla);


        //Buscar  solución
//        cout << "Solución" << endl;
        int max=tabla[0][tammochila], pos=0 ;

        for (i = 1; i < cantobj ; i++) {
            if( max < tabla[i][tammochila] ) {
                max=tabla[i][tammochila];
                pos=i;
            }
        }
//        cout << "LA SOLUCIÓN ES "<< tabla[pos][tammochila] << endl;
//        cout << "CON LOS OBJETOS  " <<  endl;
//        cout << "Peso  " << w[pos] <<" Beneficio  " << v[pos] << endl;
        int buscar=pos;

        tammochila-=w[pos];
        while(buscar > 0 && tammochila > 0 ){

            while (tabla[pos][tammochila]==tabla[pos-1][tammochila]){
                pos--;

            }
//            cout << "Peso  " << w[pos] <<" Beneficio  " << v[pos] << endl;
            tammochila-=w[pos];
            pos--;
        }
        tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo

        tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

        cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n<<endl;

        // Guardamos tam. de caso y t_ejecucion a fichero de salida


        delete [] v;
        delete [] w;

        // Cerramos fichero de salida

        return 0;
    }


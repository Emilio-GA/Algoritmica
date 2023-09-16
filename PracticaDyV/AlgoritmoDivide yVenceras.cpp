// ALGORITMO DIVIDE Y VENCERAS

#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
using namespace std;


// ALGORTIMO BASICO Y DIVIDE Y VENCERAS QUE EL PROFESOR NOS PASO POR CORREO
/*bool dominaA(const int *A, const int *B, int k){
    bool res = true;
    int aux = 0;

    for (int i=0; i<k && res; i++){
        if (A[i] < B[i])
            res = false;
        else if (A[i] > B[i])
            aux++;
    }
    if (aux == 0)
        res = false;

    return res;
}
int** puntosNoDominadosBasico(int **M, int n, int k, int &nRes){
    bool noDominado;
    nRes = 0;
    int **Mres = new int*[n];
    for (int i=0; i<n; i++)
        Mres[i] = new int [k];

    for (int i=0; i<n; i++){
        noDominado = true;
        for (int j=0; j<n && noDominado; j++){
            if (i!=j && dominaA(M[j], M[i], k))
                noDominado = false;
        }
        if (noDominado){
            for (int w=0; w<k; w++)
                Mres[nRes][w] = M[i][w];
            nRes++;
        }
    }
    return Mres;
}

int** DyVpuntosNoDominados(int **P, int ini, int n, int k, int &nS){
    int** S = new int*[n];
    for (int i=0; i<n; i++)
        S[i] = new int [k];
    nS = 0;

    int** S1;
    int nS1 = 0;

    int** S2;
    int nS2 = 0;

    bool noDominado;

    if(n == 1){
        for (int i=0; i<k; i++)
            S[nS][i] = P[ini][i];
        nS++;
    }
    else{
        if(n%2 == 0){
            S1 = DyVpuntosNoDominados(P, ini, n/2, k, nS1);
            S2 = DyVpuntosNoDominados(P, ini+n/2, n/2, k, nS2);
        }
        else{
            S1 = DyVpuntosNoDominados(P, ini, n/2, k, nS1);
            S2 = DyVpuntosNoDominados(P, ini+n/2, n/2 + 1, k, nS2);
        }

        for(int i = 0; i < nS1; i++){
            noDominado = true;
            for(int j = 0; j < nS2 && noDominado; j++){
                if(dominaA(S2[j],S1[i],k))
                    noDominado = false;
            }
            if(noDominado){
                for (int j=0; j<k; j++)
                    S[nS][j] = S1[i][j];
                nS++;
            }
        }

        for(int i = 0; i < nS2; i++){
            noDominado = true;
            for(int j = 0; j < nS1 && noDominado; j++){
                if(dominaA(S1[j],S2[i],k))
                    noDominado = false;
            }
            if(noDominado){
                for (int j=0; j<k; j++)
                    S[nS][j] = S2[i][j];
                nS++;
            }
        }
    }

    return S;

}  */


// COMIENZO DE NUESTRO ALGORITMO DIVIDE Y VENCER�S
int ** fusion(int ** s1, int ** s2, int tam1, int tam2, int k, int &tam){

    int cont,j,l ;
    tam = tam1 + tam2;
    int pos = 0;
    int ** s = new int * [tam];
    
    for (int f = 0; f < tam1 ; f++) {
            for (int m = 0 ; m < tam2 &&  s1[f]!= nullptr; m++) {
                    for (j = 0, cont = 0; j < k && cont != k ; j++) {

                        if (s1[f][j] < s2[m][j]) {
                            cont++;
                        }
                    }

                    if (cont == k) {
                        s1[f] = nullptr;
                        tam--;
                    }

            }
            if (s1[f] != nullptr) {
                s[pos]= s1[f];
                pos++;
            }
        }

    for (int f = 0; f < tam2 ; f++) {
        for (int m = 0 ; m < tam1 && s2[f]!= nullptr && s1[m]!= nullptr; m++) {
            for (j = 0, cont = 0; j < k  && cont != k; j++) {

                if (s2[f][j] < s1[m][j]) {
                    cont++;
                }
            }

            if (cont == k) {
                s2[f] = nullptr;
                tam--;

            }
        }

        if (s2[f] != nullptr) {
            s[pos]= s2[f];
            pos++;
        }
    }

    return s;
}


int ** comparamitad( int **v, int i, int n, int k,int &tam){
    int cont,j,l;
    tam = 2 ;
    bool nodominado = false;

    for (l = i; l < n  ; l++) {
        for (j = 0, cont = 0; j < k && nodominado == false; j++) {
            if (v[l][j] < v[n][j]) {
                cont++;
            }else {
                nodominado = true;
            }
        }

        if (cont == k) {

            tam --;
            v[i] = nullptr;

        } else if (cont == 0) {

            tam --;
            v[n] = nullptr;

        }
    }

    int ** s = new int * [tam];
    int pos;
    for (l=i, pos= 0; (l <= n) && pos < tam  ; l++ ) {
        if (v[l] != nullptr){

            s[pos]= v [l];
            pos ++;
        }
    }

    return s;
}


int ** divideyvenceras( int **v, int i, int n, int k, int &tam) {
    int ** s;
    if ((n-i) == 1) {

        s = comparamitad( v, i, n, k, tam);

    }else if (i<n){
        int ** s1, ** s2;
        int tam1, tam2;
        int q =  (n+i) / 2;
        s1 =divideyvenceras( v, i, q, k, tam1);

        s2 = divideyvenceras(v, q + 1, n, k, tam2);

        s =  fusion(s1,s2, tam1 , tam2, k, tam);



    }else if (n==i){
        s = new int * [1];
        s[0] = new int  [k];
        for (int f = 0; f < k; f++) {
            s[0][f] = v[i][f];
        }
        tam = 1;
    }
    return s;

}


// FUNCI�N PRINCIPAL
int main(int argc, char *argv[]) {

    int ** v, **sol;
    int n, i, j, argumento, k = 10;
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
//               cout <<  v[i][j] << endl;

            }

        }
        // HACEMOS QUE EL VECTOR SOLUCION APUNTE A TODO EL VECTOR CON LOS DATOS

        // cout << "entramos al codigo  "<< n << endl;
        sol = new int *[n];
        for (i = 0; i < n; i++) {
            sol[i] = v[i];
        }
        t0 = std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo

// Codigo base
//        int l,cont;
//
//         sol = new int *[n];
//        for (i = 0; i < n; i++) {
//
//
//            sol[i] = v[i];
//
//            for (l = 0,cont = 0;(l < n) && (cont != k); l++) {
//
//                for (j = 0 ; (j < k) && (cont != k); j++){
//
//                    if (v[i][j] < v[l][j]) {
//                        cont++;
//                    }
//                }
//
//            }
//            if (cont == k) {
//
//                sol[i] = nullptr;
//            }
//        }



// Codigo base que nos paso el profesor , con este comparamos el divide y venceras

//       int tam;
//       int ** s;
//       s = puntosNoDominadosBasico( v, n, k, tam);



// CODIGO DIVIDE Y VENCERAS

      int  posini = 0, posfinal = n-1, tam;

      int ** s;
      s = divideyvenceras(  v, posini, n-1, k, tam );


        tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
//        cout << "solucion "<< tam << endl;
//        for (i = 0; i < tam; i++) {
//            for (j = 0; j < k; j++) {
//                cout << s[i][j] << endl;
//
//            }
//
//        }



        unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

        cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n<<endl;

        // Guardamos tam. de caso y t_ejecucion a fichero de salida
        fsalida<<n<<" "<<tejecucion<<"\n";


        // Liberamos memoria del vector
        delete [] v;
//        delete [] s;
    }

    // Cerramos fichero de salida
    fsalida.close();

    return 0;
}

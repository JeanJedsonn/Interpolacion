/*
Alumno: Jeanmarco Alarcon
Curso: Calculo Computacional
Fecha: 26-03-2025
Descripción: [Interpolacion, parte 2]
*/
#include "config.hpp"   //depende de la libreria config
#include "spline.hpp"   //usara la libreria spline

float N = 0;                //cantidad de puntos
float desplazamiento = -7;
float rango = 14;            //dominio a cubrir

//vector de puntos a interpolar
vector<double> xi;

/*vectores de incognitas "a" a "d"*/
vector<double> a;   //carga directa con f(xi)
vector<double> b;   //carga mediante ingocnitas a y c
vector<double> c;   //carga mediante la solucion a la RHS
vector<double> d;   //carga con forma de incongnitas c

int main(){
    double t;
    double segmento;      //14 por el rango a evaluar
    enum {terminar, evaluarPuntos, imprimirSP, variables, imprimirPuntosInterpolados};
    int i,opcion;

    cout << "N: ";
    cin >> N;

    cout << "dominio: " << desplazamiento << " a " << desplazamiento+rango << endl;

    segmento = rango/N;
    cout << "el tamano de segmento es: " << segmento  << endl;
    
    //------------ cargar puntos a interpolar e inicializar vectores ------------
    for (i = 0; i <= N; i++){
        xi.push_back( (i*segmento)+desplazamiento );      //intervalo i
        a.push_back(f(xi[i]));                          //f(xi) o ingonitas "a"

        c.push_back(0);                                 //MOD: el algoritmo de libro no inicializa a C
        b.push_back(0);                                 //MOD: el algoritmo de libro no inicializa a B
        d.push_back(0);                                 //MOD: el algoritmo de libro no inicializa a D
    }

    c.pop_back();   //MOD: el algoritmo de libro no inicializa a C
    b.pop_back();   //MOD: el algoritmo de libro no inicializa a B
    d.pop_back();   //MOD: el algoritmo de libro no inicializa a D

    spline(N, xi, a, b, c, d);


    while (opcion != terminar)
    {
        system("clear");
        cout << "1. Evaluar puntos [-7,7]" << endl;
        cout << "2. Imprimir Spline" << endl;
        cout << "3. Imprimir variables" << endl;
        cout << "4. Imprimir puntos interpolados" << endl;
        cout << "5. Salir" << endl;

        cout << "Opcion: ";
        cin >> opcion;
        system("clear");

        switch (opcion)
        {
        case evaluarPuntos:
            cout << "x: ";
            cin >> t;
            cout << "y = "<< evaluar(xi, a, b, c, d, t) << endl;
            break;
        
        case imprimirSP:
            imprimirSpline(xi, a, b, c, d, "S", "x");
            cout << "\n Polinomios y dominios en formato compatible con GeoGebra"<<endl;
            break;
        case variables:
            imprimirVariables(a, b, c, d);
            break;

        case imprimirPuntosInterpolados:
            imprimirPuntos(xi,a);
            break;

        case terminar:
            cout << "Saliendo..." << endl;
            return 0;
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
        }

        cout << "\n\n\nPulse enter para continuar"<<endl;
        cin.ignore();
        cin.get();
    }

    return 0;
    
}


/*
Alumno: Jeanmarco Alarcon
Curso: Calculo Computacional
Fecha: 26-03-2025
Descripción: [Interpolacion, parte 4]
*/
#include "spline.hpp"   //usara la libreria spline
#include "config.hpp"   //depende de la libreria config

float N = 4;                //cantidad de puntos
float desplazamiento = 0;

//vector de puntos a interpolar
vector<double> ti;
//double t=0.25;

/*vectores de incognitas "a" a "d"*/
vector<double> s1a;   //carga directa con f(xi)
vector<double> s1b;   //carga mediante ingocnitas a y c
vector<double> s1c;   //carga mediante la solucion a la RHS
vector<double> s1d;   //carga con forma de incongnitas c

vector<double> s2a;   //carga directa con f(xi)
vector<double> s2b;   //carga mediante ingocnitas a y c
vector<double> s2c;   //carga mediante la solucion a la RHS
vector<double> s2d;   //carga con forma de incongnitas c

ifstream archivo("puntos.txt");

int main(){
    double t;
    double num_x;
    double num_y;
    int i=0;
    enum {terminar, evaluarPuntos, imprimirSP1, imprimirSP2, variablesSP1, variablesSP2, imprimirGeoGebraCurva, imprimirPuntosInterpolados};
    int opcion = -1;
    char ch[10];

    if (!archivo.is_open()){
        cout << "No se pudo abrir el archivo" << endl;
        return -1;
    }
    
    //------------ cargar puntos a interpolar e inicializar vectores ------------

    while (archivo >> num_x >> num_y) {
        s1a.push_back(num_x);               //puntos x
        s2a.push_back(num_y);               //puntos y
        ti.push_back(i);                    //puntos x

        s1c.push_back(0);               //MOD: el algoritmo de libro no inicializa a C
        s1b.push_back(0);               //MOD: el algoritmo de libro no inicializa a B
        s1d.push_back(0);               //MOD: el algoritmo de libro no inicializa a D

        s2c.push_back(0);               //MOD: el algoritmo de libro no inicializa a C
        s2b.push_back(0);               //MOD: el algoritmo de libro no inicializa a B
        s2d.push_back(0);               //MOD: el algoritmo de libro no inicializa a D
        i++;
    }

    N = ti.size();    

    s1c.pop_back();   //MOD: el algoritmo de libro no inicializa a C
    s1b.pop_back();   //MOD: el algoritmo de libro no inicializa a B
    s1d.pop_back();   //MOD: el algoritmo de libro no inicializa a D
    s2c.pop_back();   //MOD: el algoritmo de libro no inicializa a C
    s2b.pop_back();   //MOD: el algoritmo de libro no inicializa a B
    s2d.pop_back();   //MOD: el algoritmo de libro no inicializa a D

    spline(N, ti, s1a, s1b, s1c, s1d);  //s1 tiene el spline de los xi segun ti
    spline(N, ti, s2a, s2b, s2c, s2d);  //s2 tiene el spline de los f(xi) segun ti


    while (opcion != terminar)
    {
        system("clear");
        cout << "1. Evaluar [0,16]" << endl;
        cout << "2. Imprimir spline 1" << endl;
        cout << "3. Imprimir spline 2" << endl;
        cout << "4. Imprimir variables 1" << endl;
        cout << "5. Imprimir variables 2" << endl;
        cout << "6. Imprimir Curva (GeoGebra)" << endl;
        cout << "7. Imprimir puntos" << endl;
        cout << "0. Salir" << endl;

        cout << "Opcion: ";
        cin >> opcion;
        system("clear");

        switch (opcion)
        {
        case evaluarPuntos:
            cout << "t: ";
            cin >> t;
            cout << "t = " << "(" << evaluar(ti, s1a, s1b, s1c, s1d, t) << "," << evaluar(ti, s2a, s2b, s2c, s2d, t) << ")"<< endl;
            break;
        
        case imprimirSP1:
            imprimirSpline(ti, s1a, s1b, s1c, s1d, "Sx", "t");
            cout << "\n Polinomios y dominios en formato compatible con GeoGebra"<<endl;
            break;
        case imprimirSP2:
            imprimirSpline(ti, s2a, s2b, s2c, s2d, "Sy", "t");
            cout << "\n Polinomios y dominios en formato compatible con GeoGebra"<<endl;
            break;
        case variablesSP1:
            imprimirVariables(s1a, s1b, s1c, s1d);
            break;
        case variablesSP2:
            imprimirVariables(s2a, s2b, s2c, s2d);
            break;
        case imprimirGeoGebraCurva:
            imprimirCurva(ti, s1a, s1b, s1c, s1d, s2a, s2b, s2c, s2d, "t");
            cout << "\n Curva en formato compatible con GeoGebra"<<endl;
            cout << ""<<endl;
            break;

        case imprimirPuntosInterpolados:
            imprimirPuntos(s1a,s2a);
            break;

        case terminar:
            cout << "Saliendo..." << endl;
            return 0;
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
        }

        cout << "Pulse enter para continuar"<<endl;
        cin.ignore();
        cin.get();
    }
    
    return 0;
}


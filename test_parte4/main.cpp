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

vector<double> s3a;   //carga directa con f(xi)
vector<double> s3b;   //carga mediante ingocnitas a y c
vector<double> s3c;   //carga mediante la solucion a la RHS
vector<double> s3d;   //carga con forma de incongnitas c
int main(){
    double t;
    double segmento;      //14 por el rango a evaluar
    int i;
    
    //------------ cargar puntos a interpolar e inicializar vectores ------------
    cout << "\n-*-*-*-*-*-puntos a interpolar-*-*-*-*-*-" << endl;
    for (i = 0; i <= N; i++){
        ti.push_back(i);      //intervalo i                         //f(xi) o ingonitas "a"

        s1c.push_back(0);                                 //MOD: el algoritmo de libro no inicializa a C
        s1b.push_back(0);                                 //MOD: el algoritmo de libro no inicializa a B
        s1d.push_back(0);                                 //MOD: el algoritmo de libro no inicializa a D

        s2c.push_back(0);                                 //MOD: el algoritmo de libro no inicializa a C
        s2b.push_back(0);                                 //MOD: el algoritmo de libro no inicializa a B
        s2d.push_back(0);                                 //MOD: el algoritmo de libro no inicializa a D

        s3c.push_back(0);                                 //MOD: el algoritmo de libro no inicializa a C
        s3b.push_back(0);                                 //MOD: el algoritmo de libro no inicializa a B
        s3d.push_back(0);                                 //MOD: el algoritmo de libro no inicializa a D
    }

    
    s1a.push_back(0);
    s1a.push_back(1);
    s1a.push_back(0);
    s1a.push_back(-1);
    s1a.push_back(0);

    s2a.push_back(1);
    s2a.push_back(0);
    s2a.push_back(-1);
    s2a.push_back(0);
    s2a.push_back(1); 
    
    

    s1c.pop_back();   //MOD: el algoritmo de libro no inicializa a C
    s1b.pop_back();   //MOD: el algoritmo de libro no inicializa a B
    s1d.pop_back();   //MOD: el algoritmo de libro no inicializa a D
    s2c.pop_back();   //MOD: el algoritmo de libro no inicializa a C
    s2b.pop_back();   //MOD: el algoritmo de libro no inicializa a B
    s2d.pop_back();   //MOD: el algoritmo de libro no inicializa a D

    //s1 tiene el spline de los xi segun ti
    //s2 tiene el spline de los f(xi) segun ti
    spline(N, ti, s1a, s1b, s1c, s1d);
    spline(N, ti, s2a, s2b, s2c, s2d);

    cout <<"----- ----- S1 ----- -----" <<endl;
    imprimir( ti, s1a, s1b, s1c, s1d,"Sx","t");
    cout <<"----- ----- S2 ----- -----" <<endl;
    imprimir( ti, s2a, s2b, s2c, s2d,"Sy","t");

    
    cout << endl;
    cin >> t;

    //t = evaluar(ti, a, b, c, d,t);
    //cout << "t = " << t << endl;
    return 0;
}


/*
Alumno: Jeanmarco Alarcon
Curso: Calculo Computacional
Fecha: 26-03-2025
Descripción: [Interpolacion, parte 1]
*/

#include "iostream"
#include "math.h"
#include "vector"
#include "funcion.h"
#include "sstream"
#include "iomanip"
using namespace std;

int N = 10;
vector<double> xi;
vector<double> fxi;
vector<double> coef;

void coeficientes();
double evaluar(double t);
void polinomio();

std::stringstream ss;

int main(){
    double segmento;
    cout << "N: ";
    cin >> N;
    segmento = 14.0/N; // 14=[-7,7] y 14.0/4.0 = 3.5, 4 segmentos de 3.5 unidades

    cout << "el tamaño de segmento es: " << segmento  << endl;
    for(int i = 0; i <= N; i++){
        xi.push_back( i*segmento-7.0 );
        fxi.push_back(f(xi[i]));
    }

    vector<double>::iterator iter;
    for(iter = xi.begin(); iter != xi.end(); iter++){
        //cout << *iter << " " << fxi[iter - xi.begin()] << endl;
        ss << std::fixed << std::setprecision(11) << *iter << " " << fxi[iter - xi.begin()] << endl;
        cout << ss.str();
        ss.str("");
    }

    
    cout << endl << endl;
    coeficientes();

    
    cout << "-----------COEFICIENTES-----------" << endl;
    for(iter = coef.begin(); iter != coef.end(); iter++){
        //cout << *iter << endl;
        ss << std::fixed << std::setprecision(11) << *iter << endl;
        cout << ss.str();
        ss.str("");
    }
        
    double t;

    polinomio();
    return 0;
}

void coeficientes(){
    int i,j;

    for (i = 0; i <= N; i++){
        coef.push_back(fxi[i]); //copio las alturas al coeficiente
    }

    for (j = 1; j <= N; j++){        //j es el punto xj, xj=0 tiene f(x0) puesto es el coeficiente del 1er termino es una constante
        //cout << "j = " << j << endl;
        for (i = N; j <= i; i--){
            //cout << "\t" <<i <<" : " << coef[i] << " - " << coef[i-1] << " / " << xi[i] << " - " << xi[i-j] << " = ";
            coef[i] = (coef[i] - coef[i-1]) / (xi[i] - xi[i-j]);
            //cout << coef[i] << endl;
        }
    }
}

double evaluar(double t){
    int i;
    double temp;

    temp = coef[N]; //ultimo termino?

    for (i = N-1; i >= 0; i--){
        temp = temp * (t - xi[i]) + coef[i];
    }
    return temp;
}

void polinomio(){
    string polinomio;
    string anidado;
    polinomio = "f(x):\n\t  ";
    ss << std::fixed << std::setprecision(11) << coef[0];
    polinomio += ss.str();
    ss.str("");

    for (int i = 1; i <= N; i++){
        //polinomio += " + ";
        polinomio += "\n\t + ";
        ss << std::fixed << std::setprecision(11) << coef[i];
        polinomio += ss.str();    //coeficiente
        ss.str("");

        anidado += "(x";
        ss << std::fixed << std::setprecision(2) << xi[i-1];
        if (xi[i-1] < 0){
            anidado += ss.str().replace(0,1,"+");
        }
        else {
            anidado += "-";
            anidado += ss.str();
        }
        ss.str("");
        anidado += ")";
        polinomio += anidado;
        
    }
    cout << polinomio << endl;
}
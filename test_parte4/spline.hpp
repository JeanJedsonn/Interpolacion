#ifndef SPLINE_HPP
#define SPLINE_HPP

#include "config.hpp"   //depende de la libreria config
//#include "funcion.hpp"  //usara la libreria funcion

int spline(int N, 
vector<double> xi, vector<double> &a, vector<double> &b, vector<double> &c, vector<double> &d);

double evaluar(vector<double> xi, vector<double> a, vector<double> b, vector<double> c, vector<double> d, double t);
void imprimir(vector<double> xi, vector<double> a, vector<double> b, vector<double> c, vector<double> d);

int spline(int N, 
vector<double> xi, vector<double> &a, vector<double> &b, vector<double> &c, vector<double> &d)
    
    {
    int i;
    double temp1,temp2;
    double temp;


    vector<double> l;
    vector<double> u;
    vector<double> z;
    vector<double> RHS;
    vector<double> intervalo;

    /*N puntos, N-1 intervalos*/
    //------------------ cargar intervalos ------------------
    for (i = 0; i < N; i++){
        intervalo.push_back(xi[i+1] - xi[i]);
    }

    //------------ cargar vector RHS (b?) ------------
    RHS.push_back(0);   //VALOR ADIVINADO DEL PDF (empieza y termina en 0)
    cout << "\n-*-*-*-*-*-vector b-*-*-*-*-*-" << endl;
    cout << RHS[0] << endl;
    for (i = 1; i < N; i++){
        temp1 = 0;
        temp2 = 0;

        temp1 = a[i+1] - a[i];
        temp1 = 3.0*temp1;
        temp1 = temp1/intervalo[i];

        temp2 = a[i] - a[i-1];
        temp2 = 3.0*temp2;
        temp2 = temp2/intervalo[i-1];

        RHS.push_back(temp1 - temp2);
        
        printf("%.11lf\n", RHS[i]);
    }
    RHS.push_back(0);
    cout << RHS[N] << endl;


    l.push_back(1);
    u.push_back(0);
    z.push_back(0);


    /*----- paso 4 -----*/
    cout << "\nl\t\tu\t\tz" << endl;
    cout << l[0] << "\t\t" << u[0] << "\t\t" << z[0] << endl;

    for (i = 1; i < N; i++){
        temp = 0;
        temp = 2*( xi[i+1] - xi[i-1]) - intervalo[i-1]*u[i-1];      //COMPROBADO
        l.push_back(temp);

        u.push_back( intervalo[i]/l[i] );
        z.push_back((RHS[i]-intervalo[i-1]*z[i-1])/l[i]) ;

        printf("%.11lf\t%.11lf\t%.11lf\n", l[i], u[i], z[i]);
    }

    /*----- paso 5 -----*/
    l.push_back(1);                 //siempre son el mismo valor al final
    u.push_back(0);                 //
    c[N]=0;                         //

    cout << l[N] << "\t\t" << u[N] << "\t\t" << z[N] << endl;

    /*calculo del valor de las incognitas*/
    /*----- paso 6 -----*/
    cout << "\na\t\tb\t\tc\t\td" << endl;
    for (i = N-1; i >= 0; i--){
        c[i] = z[i] - u[i]*c[i+1];
        b[i] = (a[i+1] - a[i])/intervalo[i] - intervalo[i]*(c[i+1] + 2*c[i])/3.0;
        d[i] = (c[i+1] - c[i])/(3.0*intervalo[i]);

        printf("%.11lf\t%.11lf\t%.11lf\t%.11lf\n",a[i], b[i], c[i], d[i]);
    }

    return 0;
}

void imprimir(vector<double> xi, vector<double> a, vector<double> b, vector<double> c, vector<double> d,string nombreFunc,string var){

    //imprime el polinomio cubico y su dominio, compatible con geogebra
    for (int i = 0; i < b.size(); i++){
        cout << nombreFunc << i <<"("<<var<<")";
        printf(" = %.11lf + %.11lf(", a[i], b[i]);
        cout << var;
        printf("-%.2f) + %.11lf(", xi[i], c[i]);
        cout << var;
        printf("-%.2f)^2 + %.11f(", xi[i], d[i]);
        cout << var;
        printf("-%.2f)^3\n", xi[i]);
        //printf("-%.2f)^3\n", a[i], b[i], xi[i], c[i], xi[i], d[i], xi[i]);
        //printf(" x-%.2f) + %.11lf(x-%.2f)^2 + %.11f(x-%.2f)^3\n", a[i], b[i], xi[i], c[i], xi[i], d[i], xi[i]);
    }
    
    for (int i = 0; i < b.size(); i++)
    {
        cout << "Función(" << nombreFunc << i;
        printf(",%.2f,%.2f)\n",xi[i],xi[i+1]);
    }
    
}

double evaluar(vector<double> xi, vector<double> a, vector<double> b, vector<double> c, vector<double> d, double t){
    double temp = 0;

    for (int i = 0; i < b.size(); i++){
        if (t >= xi[i] && t <= xi[i+1]){
            temp = a[i] + b[i]*(t-xi[i]) + c[i]*(t-xi[i])*(t-xi[i]) + d[i]*(t-xi[i])*(t-xi[i])*(t-xi[i]);
            break;
        }
    }
    return temp;
}
#endif
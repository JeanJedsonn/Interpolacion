#ifndef SPLINE_HPP
#define SPLINE_HPP
#include "config.hpp"   //depende de la libreria config

int spline(int N, 
vector<double> xi, vector<double> &a, vector<double> &b, vector<double> &c, vector<double> &d);

double evaluar(vector<double> xi, vector<double> a, vector<double> b, vector<double> c, vector<double> d, double t);
void imprimirSpline(vector<double> xi, vector<double> a, vector<double> b, vector<double> c, vector<double> d,string nombreFunc,string var);

void imprimirCurva(vector<double> ti, 
    vector<double> a_x, vector<double> b_x, vector<double> c_x, vector<double> d_x,
    vector<double> a_y, vector<double> b_y, vector<double> c_y, vector<double> d_y, string var
);

void imprimirVariables(vector<double> a, vector<double> b, vector<double> c, vector<double> d);
void imprimirPuntos(vector<double> xi,vector<double> yi);

int spline(int N, 
vector<double> xi, vector<double> &a, vector<double> &b, vector<double> &c, vector<double> &d){
    int i;
    double temp1,temp2,temp;
    vector<double> l,u,z,RHS,intervalo;


    /*N puntos, N-1 intervalos*/
    //------------------ cargar intervalos ------------------
    for (i = 0; i < N; i++){
        intervalo.push_back(xi[i+1] - xi[i]);
    }

    //------------ cargar vector RHS (b?) ------------
    RHS.push_back(0);   //VALOR ADIVINADO DEL PDF (empieza y termina en 0)

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

    }

    RHS.push_back(0);
    l.push_back(1);
    u.push_back(0);
    z.push_back(0);

    /*----- paso 4 -----*/

    for (i = 1; i < N; i++){
        temp = 0;
        temp = 2*( xi[i+1] - xi[i-1]) - intervalo[i-1]*u[i-1];      //COMPROBADO
        l.push_back(temp);

        u.push_back( intervalo[i]/l[i] );
        z.push_back((RHS[i]-intervalo[i-1]*z[i-1])/l[i]) ;
    }

    /*----- paso 5 -----*/
    l.push_back(1);                 //siempre son el mismo valor al final
    u.push_back(0);                 //
    c[N]=0;                         //


    /*----- paso 6 -----*/

    for (i = N-1; i >= 0; i--){
        c[i] = z[i] - u[i]*c[i+1];
        b[i] = (a[i+1] - a[i])/intervalo[i] - intervalo[i]*(c[i+1] + 2*c[i])/3.0;
        d[i] = (c[i+1] - c[i])/(3.0*intervalo[i]);
    }

    return 0;
}

void imprimirSpline(vector<double> xi, vector<double> a, vector<double> b, vector<double> c, vector<double> d,string nombreFunc,string var){
    for (int i = 0; i < b.size(); i++){
        cout << nombreFunc << i <<"("<<var<<")";
        printf(" = %.2lf + %.11lf(", a[i], b[i]);
        cout << var;
        printf("-%.2f) + %.11lf(", xi[i], c[i]);
        cout << var;
        printf("-%.2f)^2 + %.11f(", xi[i], d[i]);
        cout << var;
        printf("-%.2f)^3, (%.11f≤", xi[i], xi[i]);
        cout << var;
        printf("≤%.11f)\n", xi[i+1]);
    }
}

void imprimirCurva(vector<double> ti, 
    vector<double> a_x, vector<double> b_x, vector<double> c_x, vector<double> d_x,
    vector<double> a_y, vector<double> b_y, vector<double> c_y, vector<double> d_y, string var){

    for (int i = 0; i < b_x.size(); i++){
        printf("Curva(%.2lf+%.11lf(", a_x[i], b_x[i]);
        cout << var;
        printf("-%.2f)+%.11lf(", ti[i], c_x[i]);
        cout << var;
        printf("-%.2f)^2+%.11f(", ti[i], d_x[i]);
        cout << var;
        printf("-%.2f)^3", ti[i]);

        cout << ",";

        printf("%.2lf+%.11lf(", a_y[i], b_y[i]);
        cout << var;
        printf("-%.2f)+%.11lf(", ti[i], c_y[i]);
        cout << var;
        printf("-%.2f)^2+%.11f(", ti[i], d_y[i]);
        cout << var;
        printf("-%.2f)^3", ti[i]);
        cout << "," << var << "," << i << ","<< i+1 <<")\n";
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

void imprimirVariables(vector<double> a, vector<double> b, vector<double> c, vector<double> d){
    cout << "a\t\tb\t\tc\t\td" << endl;
    for (int i = 0; i < b.size(); i++){
        printf("%.11lf\t%.11lf\t%.11lf\t%.11lf\n", a[i], b[i], c[i], d[i]);
    }
}

void imprimirPuntos(vector<double> xi,vector<double> yi){
    cout << "x\ty" << endl;
    for (int i = 0; i < xi.size(); i++){
        printf("%.2lf\t%.2lf\n", xi[i], yi[i]);
    }
}
#endif
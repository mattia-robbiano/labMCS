// g++ -o main main.cpp `root-config --cflags --libs` -lMinuit
#include <iostream>
#include <cmath>

#include <TGraph.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TStyle.h>

using namespace std;

int main(){
    TApplication app("app", 0, NULL);

    double k = 0.2;
    double F = 0.2;
    double tau = 400;
    double w = 0.5;

    double x1 = 1; double v1 = 0;
    double x2,v2;
    double h = 0.5;
    TGraph gr;
    double t = 0;
    double a1 =0; double a2 =0;

    while(t<400){

        a1 = -k*x1 + F*(1-exp(-t/tau))*sin(w*t);
        x2 = x1 + h*v1 + pow(h,2)*(a1)/2;
        a2 = -k*x2 + F*(1-exp(-t/tau))*sin(w*t);
        v2 = v1 + h*(a1+a2)/2;


        gr.SetPoint(gr.GetN(),t,x2);
        gr.Draw("APL");


        v1 = v2;
        x1 = x2;
        t = t+h;
    }

    app.Run(true);

    return 0;
}
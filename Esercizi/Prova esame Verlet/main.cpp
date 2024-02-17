#include <iostream>
#include <cmath>

#include <TGraph.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TApplication.h>
#include <TStyle.h>

using namespace std;

int main(){
    TApplication app("app", 0, NULL);

    double delta,m,k;
    cout << "Inserire Delta:" << endl;
    cin >> delta;
    cout << "Inserire m:" << endl;
    cin >> m;
    cout << "Inserire k:" << endl;
    cin >> k;
    double B = sqrt(delta*pow(m,2)+4*k*m);
    cout << B << endl;

    double x1 = 10; double v1 = 0;
    double x2,v2;
    double h = 0.5;
    TGraph gr;

    for(int i=0; i < 1500; i++){
        x2 = x1 + h*v1 - pow(h,2) * (B*v1+k*x1) / (2*m);
        v2 = (v1-h*(B*v1+k*(x1+x2)/(2*m))/(2*m)) / (1+B*h/(2*m));
        gr.SetPoint(gr.GetN(),i,x2);
        gr.Draw("APL");

    v1 = v2;
    x1 = x2;
    }

    app.Run(true);

    return 0;
}
//Si volaaaaaaaaaaaaaaaaaa
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TH1D.h>
#include <TMinuit.h>
#include <TApplication.h>

//Definisco funzioni di fit
TF1 f1("f1", "[0]*exp(-((x-[1])^2)/[2])", 0, 10);
TF1 f2("f2", "[3]*exp(-((x-[1]+[3])^2)/[4])", 0, 10);
TF1 f3("f3", "[5]*exp(-((x-[1]+[3]*[7])^2)/[6])", 0, 10);

void chi2(int &npar, double *gin, double &f, double *par, int iflag){
    f=0;

}

using namespace std;
int main() {
    TApplication app("app", 0, NULL);
//Riempo istogramma
    ifstream file("Millikan.dat");
    TH1D Mil("data_1","Millikan",40,1,9);
    double data;
    while (file >> data) {
        Mil.Fill(double(data), 1);
    }


    Mil.Draw("");
    app.Run(true);
    return 0;
}
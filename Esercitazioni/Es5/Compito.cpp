#include <iostream>
#include <cmath>
#include <TF1.h>
#include <TH1D.h>
#include <TGraphErrors.h>
#include <TRandom3.h>
#include <TApplication.h>
#include <vector>
#include <stdio.h>
#include <string.h>
using namespace std;

namespace ex {
    double th0   = 1.5701;
    double alpha = M_PI / 3;
    double eth   = 0.0005/sqrt(3);
    double emth  = 0.0005;
    double A     = 1.7298;
    double errA  = 0.0003;
    double B     = 13460;
    double errB  = 58;
    double rho   = -0.876394;
    vector<double> th{2.6773, 2.7324, 2.7651, 2.7846};
}

double Lam(double th0, double th, double A, double B){
    double d = th - th0;
    double n = sin(d/2+ex::alpha/2)/sin(ex::alpha/2);
    return sqrt(B/(n-A))*1e-9;
}

//Punto 1 calcolo di media ed errore su lambda tenendo conto solo degli errori su th e th0, usando metodo monte carlo e una distribuzione uniforme di th e th0.
void err_Lambda_Theta(double th0, double th, double &Lambda, double &errLambda){
    TRandom3 rnd;
    rnd.SetSeed(time(0));
    int n = 1000;
    TH1D lambda_dist("lambda_dist","lambda_dist",100,0.0,0);
    for(int i = 0; i < n; i++){
        lambda_dist.Fill(Lam(2 * ex::emth * rnd.Rndm() + th0 - ex::emth, 2 * ex::emth * rnd.Rndm() + th - ex::emth, ex::A, ex::B));
    }
    Lambda = lambda_dist.GetMean();
    errLambda = lambda_dist.GetRMS();
}

//Punto 2 calcolo di media ed errore su lambda tenendo conto  degli errori o su A o su B, usando metodo monte carlo e una distribuzione gaussiana del parametro.
/*
void err_Lambda_Par(double th, string nome, double Par, double errPar, double &Lambda, double &errLambda){
    TRandom3 rnd;
    rnd.SetSeed(time(0));
    int n = 1000;
    TH1D lambda_dist("lambda_dist","lambda_dist",100,0.0,0);
    for(int i = 0; i < n; i++){
        if(nome.compare("A")==0)      lambda_dist.Fill(Lam(ex::th0, th, rnd.Gaus(Par, errPar),ex::B));
        else if(nome.compare("B")==0) lambda_dist.Fill(Lam(ex::th0, th, rnd.Gaus(Par, errPar),ex::B));
        else{ cout << "Nome parametro invalido" <<endl; break; }
    }
    Lambda = lambda_dist.GetMean();
    errLambda = lambda_dist.GetRMS();
}*/

int main(){
    TApplication app("app", 0, NULL);
    TGraphErrors gr, gr1, gr2, gr3;
    double Lambda = 0; double errLambda = 0;

    //Parte 1
    for(int i=3; i < 7; i++){
        err_Lambda_Theta(ex::th0, ex::th[i-3], Lambda ,errLambda);
        gr.SetPoint(i-3, i, Lambda);
        gr.SetPointError(i-3, 0, errLambda);
    }
    TF1 f("f", "1/([0]*(0.25-1/(x*x)))",-10,10);
    f.SetParameter(0,1e7);
    gr.Fit("f");
    gr.Draw("A*");
    double Rh = f.GetParameter(0);
    double errRh_theta = f.GetParError(0);

//Parte 2
    for(int i=3; i < 7; i++){
        Lam(ex::th0, ex::th[i-3], ex::A, ex::B);
        gr1.SetPoint(i-3, i, Lambda);
        gr1.SetPointError(i-3, 0, errLambda);
    }
    gr1.Fit("f");
    double Rh0 = f.GetParameter(0);
    for(int i=3; i < 7; i++){
        Lam(ex::th0, ex::th[i-3], ex::A+ex::errA, ex::B);
        gr2.SetPoint(i-3, i, Lambda);
        gr2.SetPointError(i-3, 0, errLambda);
    }
    gr2.Fit("f");
    double RhA = f.GetParameter(0);

    for(int i=3; i < 7; i++){
        Lam(ex::th0, ex::th[i-3], ex::A, ex::B + ex::errB);
        gr3.SetPoint(i-3, i, Lambda);
        gr3.SetPointError(i-3, 0, errLambda);
    }
    gr3.Fit("f");
    double RhB = f.GetParameter(0);
    double errRh_AB = sqrt(pow(RhA-Rh0,2) + pow(RhB-Rh0,2) + 2 * ex::rho * (RhA-Rh0) * (RhB-Rh0));

    double errRh = sqrt(errRh_AB * errRh_AB + errRh_theta * errRh_theta);
    cout << endl << "Rh = " << Rh <<" /pm " << errRh << endl;
    app.Run(true);
    return 0;
}
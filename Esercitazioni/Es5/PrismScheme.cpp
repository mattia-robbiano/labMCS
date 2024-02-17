#include <iostream>
#include <cmath>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TApplication.h>

using namespace std;

namespace ex{
    double alpha   = M_PI/3;
    double lambda1 = 579.1;
    double lambda2 = 404.7;
    double th0   = 1.5701;
    double th1   = 2.6958;
    double th2   = 2.7904;
    double eth   = 0.0005/sqrt(3);
    double emth  = 0.0005;
}

void GetAB(double th0, double th1, double th2, double &A, double &B){
    double d1 = th1 - th0;
    double d2 = th2 - th0;
    double n1 = sin(d1/2+ex::alpha/2)/sin(ex::alpha/2);
    double n2 = sin(d2/2+ex::alpha/2)/sin(ex::alpha/2);
    B = (n2 - n1) * pow(ex::lambda1,2) * pow(ex::lambda2,2) / (pow(ex::lambda1,2) - pow(ex::lambda2,2));
    A = n1 - B / pow(ex::lambda1,2);
}

void ErrAB(double th0, double th1, double th2, double &A, double &B,double &errA, double &errB) {
    double eA0; double eB0; double eA1; double eB1; double eA2; double eB2;

    GetAB(th0 + ex::eth, th1, th2, A, B);
    GetAB(th0, th1 + ex::eth, th2, eA0, eB0);
    GetAB(th0, th1, th2, eA1, eB1);
    GetAB(th0, th1, th2 + ex::eth, eA2, eB2);

    errA = sqrt(pow(eA0 - A,2) + pow(eA1 - A,2) + pow(eA2 - A,2));
    errB = sqrt(pow(eB0 - B,2) + pow(eB1 - B,2) + pow(eB2 - B,2));
}

void MC_ErrAB(double &th0, double &th1, double &th2, double &A, double &B, double &errA, double &errB, double &rho) {
    TApplication app("app", 0, NULL);

    TRandom3 rnd;
    rnd.SetSeed(time(0));
    int n = 1000;
    TH1D A_dist("A_dist","A_dist",100,0.0,0);
    TH1D B_dist("B_dist","B_dist",100,0,0);
    TH2D AvsB_dist("AvsB_dist","AvsB_dist",100,0.0,0.0,100,0,0);
    for(int i = 0; i < n; i++){
        GetAB(rnd.Gaus(ex::th0,ex::eth),rnd.Gaus(ex::th1,ex::eth),rnd.Gaus(ex::th2,ex::eth),A,B);
        A_dist.Fill(A);
        B_dist.Fill(B);
        AvsB_dist.Fill(A,B);
    }
    TCanvas c("1c", "", 10, 10, 1000, 800);
    c.Divide(0, 3);
    c.cd(1);
    A_dist.Draw("");
    c.cd(2);
    B_dist.Draw("");
    c.cd(3);
    AvsB_dist.Draw("");
    A = A_dist.GetMean();
    errA = A_dist.GetRMS();
    B = B_dist.GetMean();
    errB = B_dist.GetRMS();
    rho = AvsB_dist.GetCorrelationFactor();
    app.Run(true);
}

void Uniform_ErrAB(double &th0, double &th1, double &th2, double &A, double &B, double &errA, double &errB, double &rho) {
    TApplication app("app", 0, NULL);

    TRandom3 rnd;
    rnd.SetSeed(time(0));
    int n = 1000;
    TH1D A_dist("A_dist","A_dist",100,0.0,0);
    TH1D B_dist("B_dist","B_dist",100,0,0);
    TH2D AvsB_dist("AvsB_dist","AvsB_dist",100,0.0,0.0,100,0,0);
    for(int i = 0; i < n; i++){
        GetAB(2*ex::emth*rnd.Rndm()+th0-ex::emth,2*ex::emth*rnd.Rndm()+th1-ex::emth,2*ex::emth*rnd.Rndm()+th2-ex::emth,A,B);
        A_dist.Fill(A);
        B_dist.Fill(B);
        AvsB_dist.Fill(A,B);
    }
    TCanvas c("1c", "", 10, 10, 1000, 800);
    c.Divide(0, 3);
    c.cd(1);
    A_dist.Draw("");
    c.cd(2);
    B_dist.Draw("");
    c.cd(3);
    AvsB_dist.Draw("");
    A = A_dist.GetMean();
    errA = A_dist.GetRMS();
    B = B_dist.GetMean();
    errB = B_dist.GetRMS();
    rho = AvsB_dist.GetCorrelationFactor();
    app.Run(true);
}

int main() {
    //TApplication app("app", 0, NULL);

    double A; double B; double errA = 0; double errB = 0; double rho;
    //ErrAB(ex::th0, ex::th1, ex::th2, A, B, errA, errB);
    //MC_ErrAB(ex::th0, ex::th1, ex::th2, A, B, errA, errB,rho);
    Uniform_ErrAB(ex::th0, ex::th1, ex::th2, A, B, errA, errB,rho);

    cout << "A: "<< A << " " << errA << endl << "B: " << B << " " << errB << endl <<"Coefficiente di correlazione: " << rho <<endl;

    //app.Run(true);
    return 0;
}
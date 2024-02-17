#include <time.h>
#include <iostream>
#include <cmath>
#include <TRandom3.h>
using namespace std;

int main (){
    TRandom3 rnd;
    rnd.SetSeed(int(time(0)));

    double T = 0;
    double F = 0;
    double r1 = 0.1; //rapporto tra i raggi
    double r2 = 0.2;
    double r3 = 0.3;
    double condizione = pow(sin(T)*cos(F),2)+pow(sin(T)*sin(F),2);//x^2+y^2>Rcil^2
    int tot = 1000000;
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;

    for(int i; i<tot; i++) {
        T = rnd.Rndm() * 2*M_PI; //estraggo gli angoli in modo casuale
        F = rnd.Rndm() * 2*M_PI;
        if (condizione > pow(r1,2)) {
            count1++;
            cout <<"ok"<<endl;
        }
        if (condizione > pow(r2,2)) {
            count2++;
            cout <<"ok"<<endl;
        }
        if (condizione > pow(r3,2)) {
            count3++;
            cout <<"ok"<<endl;
        }
    }
    double A = count1/tot; //area complementare normalizzata, cioè Acompl/Asfera = countx/tot
    double B = count2/tot;
    double C = count3/tot;

    cout << A <<endl;
    cout << B <<endl;
    cout << C <<endl;

    return 0;
}
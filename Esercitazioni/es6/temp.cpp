#i n c l u d e <i o s t r e a m >
#i n c l u d e <f s t r e a m >
#i n c l u d e <TH1D . h>
#i n c l u d e <TF1 . h>
#i n c l u d e <TMath . h>
#i n c l u d e <T A p p l i c a t i o n . h>
#i n c l u d e <cmath>
using namespace std;
int main( ) {
    TApplication app ( ”app” , 0 , NULL) ;
    ifstream file ;
    file.open ( ”gaus1.dat”) ;
    TH1D hexp (”hexp” , ”Histogramma sperimentale” , 20 , 0 , 20) ;
    double tmp ;
    while (file >> tmp ) {
        hexp.Fill(tmp);
    }
    hexp.SetMarkerStyle(20) ;
    hexp.Draw(”E”);
    app.Run(true);
}
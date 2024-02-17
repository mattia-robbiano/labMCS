from ROOT import *
from numpy import *
from math import *

gr_v = TGraphErrors()
gr_r = TGraphErrors()
gr_a = TGraphErrors()
gr_b = TGraphErrors()

# Riempio i 4 grafici con i punti per le 4 frequenze
for line in open("verde_IV.dat"):
    riga = line.split()
    if len(riga)!=4 or float(riga[1]) < exp(-11):
        continue
    gr_v.SetPoint(gr_v.GetN(), float(riga[0]), log(float(riga[1])) )
    gr_v.SetPointError(gr_v.GetN()-1, float(riga[2]), float(riga[3])/float(riga[1]) )

for line in open("rosso_IV.dat"):
    riga = line.split()
    if len(riga)!=4 or float(riga[1]) < exp(-11):
        continue
    gr_r.SetPoint(gr_r.GetN(), float(riga[0]), log(float(riga[1])) )
    gr_r.SetPointError(gr_r.GetN()-1, float(riga[2]), float(riga[3])/float(riga[1]) )

for line in open("arancione_IV.dat"):
    riga = line.split()
    if len(riga)!=4 or float(riga[1]) < exp(-11):
        continue
    gr_a.SetPoint(gr_a.GetN(), float(riga[0]), log(float(riga[1])) )
    gr_a.SetPointError(gr_a.GetN()-1, float(riga[2]), float(riga[3])/float(riga[1]) )

for line in open("blu_IV.dat"):
    riga = line.split()
    if len(riga)!=4 or float(riga[1]) < exp(-11):
        continue
    gr_b.SetPoint(gr_b.GetN(), float(riga[0]), log(float(riga[1])) )
    gr_b.SetPointError(gr_b.GetN()-1, float(riga[2]), float(riga[3])/float(riga[1]) )

#Definisco la funzione per il fit V/I
fun = TF1("fun", "[0]*(x-[1])", -5, 5)
fun.SetParameter(0,1)
fun.SetParameter(1,2.8)

#Fitto sui vari set di dati
print "PRIMO FIT VERDE"
gr_v.Fit("fun")
V_verde = fun.GetParameter(1)
Verr_verde = fun.GetParError(1)

print "PRIMO FIT ROSSO"
gr_r.Fit("fun")
V_rosso = fun.GetParameter(1)
Verr_rosso = fun.GetParError(1)

print "PRIMO FIT ARANCIONE"
gr_a.Fit("fun")
V_arancione = fun.GetParameter(1)
Verr_arancione = fun.GetParError(1)

print "PRIMO FIT BLU"
gr_b.Fit("fun")
V_blu = fun.GetParameter(1)
Verr_blu = fun.GetParError(1)


"""
c = TCanvas("1c", "", 10, 10, 1000, 800)
c.Divide(2,2)
c.cd(1)
gr_v.Draw("AP")
c.cd(2)
gr_r.Draw("AP")
c.cd(3)
gr_a.Draw("AP")
c.cd(4)
gr_b.Draw("AP")"""


Verr = array([Verr_blu, Verr_verde, Verr_arancione, Verr_rosso])
V = array([V_blu, V_verde, V_arancione, V_rosso])
c = 3e8
lam = array([468e-9, 524e-9, 586e-9, 623e-9])
nu_err = array([c*2e-8/(sqrt(3)*lam[0]**2), c*2e-8/(sqrt(3)*lam[1]**2), c*2e-8/(sqrt(3)*lam[2]**2), c*2e-8/(sqrt(3)*lam[3]**2)])
gr2 = TGraphErrors(); gr2_a = TGraphErrors(); gr2_b = TGraphErrors(); gr2_r = TGraphErrors(); gr2_v = TGraphErrors();
i = 0

#Definisco la funzione di fit
f = TF1("f", "x*[1]+[0]", -5, 5)
f.SetParameter(0,1e10)
f.SetParameter(1,2.4e14)

#Riempo gr con i punti senza errore sulla frequenza
while i < 4:
    gr2.SetPoint(gr2.GetN(), V[i], c/lam[i])
    gr2.SetPointError(gr2.GetN()-1, Verr[i],nu_err[i] )
    i=i+1
i = 0
print "SECONDO FIT GENERALE"
gr2.Fit("f")
gr2.Draw("AP")
rapp = f.GetParameter(1)

#Metodo variazione della funzione: blu
while i < 4:
    gr2_b.SetPoint(gr2_b.GetN(), V[i], c/lam[i])
    if i==0:
        gr2_b.SetPoint(gr2_b.GetN(), V[i], c/lam[i]+nu_err[i])
    gr2_b.SetPointError(gr2_b.GetN()-1, Verr[i],0 )
    i=i+1
i = 0
print "SECONDO FIT BLU"
gr2_b.Fit("f")
rapp_b = f.GetParameter(1)

#Metodo variazione della funzione: verde
while i < 4:
    if i==1:
        gr2_v.SetPoint(gr2_v.GetN(), V[i], c/lam[i]+nu_err[i])
    else:
        gr2_v.SetPoint(gr2_v.GetN(), V[i], c / lam[i])
    gr2_v.SetPointError(gr2_v.GetN()-1, Verr[i],0 )
    i=i+1
i = 0
print "SECONDO FIT VERDE"
gr2_v.Fit("f")
rapp_v = f.GetParameter(1)


#Metodo variazione della funzione: arancione
while i < 4:
    if i==2:
        gr2_a.SetPoint(gr2_a.GetN(), V[i], c/lam[i]+nu_err[i])
    else:
        gr2_a.SetPoint(gr2_a.GetN(), V[i], c / lam[i])
    gr2_a.SetPointError(gr2_a.GetN()-1, Verr[i],0 )
    i=i+1
i = 0
print "SECONDO FIT ARANCIONE"
gr2_a.Fit("f")
rapp_a = f.GetParameter(1)


#Metodo variazione della funzione: rosso
while i < 4:
    if i==3:
        gr2_r.SetPoint(gr2_r.GetN(), V[i], c/lam[i]+nu_err[i])
    else:
        gr2_r.SetPoint(gr2_r.GetN(), V[i], c / lam[i])
    gr2_r.SetPointError(gr2_r.GetN()-1, Verr[i],0 )
    i=i+1
i = 0
print "SECONDO FIT ROSSO"
f.SetParameter(0,5.23e13)
f.SetParameter(1,2e14)
gr2_r.Fit("f")
rapp_r = f.GetParameter(1)
"""
c = TCanvas("1c", "", 10, 10, 1000, 800)
 c.Divide(2,2)
c.cd(1)
gr2_v.Draw("AP")
c.cd(2)
gr2_r.Draw("AP")
c.cd(3)
gr2_a.Draw("AP")
c.cd(4)
gr2_b.Draw("AP")"""

#Calcolo errore sul rapporto
rapp_error = sqrt( (rapp_a-rapp)**2 + (rapp_b-rapp)**2 + (rapp_r-rapp)**2 + (rapp_v-rapp)**2 )
#Calcolo errori dovuti a ciascuna frequenza
rapp_error_r = abs(rapp_r-rapp)
rapp_error_a = abs(rapp_a-rapp)
rapp_error_v = abs(rapp_v-rapp)
rapp_error_b = abs(rapp_b-rapp)

print ("e/h = ", "{:e}".format(rapp), "+/-", "{:e}".format(rapp_error))
print("errore dovuto alla componente rossa: ","{:e}".format(rapp_error_r))
print("errore dovuto alla componente arancione: ","{:e}".format(rapp_error_a))
print("errore dovuto alla componente verde: ","{:e}".format(rapp_error_v))
print("errore dovuto alla componente blu: ","{:e}".format(rapp_error_b))

gApplication.Run()
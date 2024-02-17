#ifndef _PUNTOMATERIALE
#define _PUNTOMATERIALE

#include "Particella.h"
#include <cmath>
#include "Vettore.h"
class PuntoMateriale: public Particella{
 public:
  PuntoMateriale (Particella particella=Particella(0,0), Vettore posizione={0,0,0}, Vettore velocita={0,0,0}): Particella(particella),PM_posizione(posizione),PM_velocita(velocita){}  
  PuntoMateriale (int massa, int carica, Vettore posizione, Vettore velocita): PuntoMateriale(Particella(massa,carica),posizione,velocita){}
  
  Vettore R() {return PM_posizione;};
  Vettore V() {return PM_velocita;};
  
  Vettore CampoGravitazionale(const Vettore& b){
    Vettore p=b-PM_posizione;
    Vettore campo=-(1/pow(p.Mod(),2))*Massa()*b.Vers(); 
    return campo;
  };
 private:
  Vettore PM_posizione;
  Vettore PM_velocita;
};
#endif


#ifndef _ELETTRONE
#define _ELETTRONE
#include "Particella.h"
#include <cmath>
class Elettrone: public Particella{
 public:
 Elettrone():Particella(){
    m_massa=  9.109383701*pow(10,-31);
    m_carica=-1.602176634*pow(10,-19);
  }
};
#endif

#ifndef ERREUR_NON_NOTE
#define ERREUR_NON_NOTE

#include "TimeDivision.h"

class Erreur_non_note
{
 private:
  TimeDivision* TD;
  
 public:
  
  Erreur_non_note(TimeDivision*);
  ~Erreur_non_note();
  
  void Traiter_Erreur(Info_Erreur);

  //3 cas possible:
  //A) Je n'exist pas.
  //B) La piece que je veut tuer n'existe pas.
  //C) Il existe une piece dans mon chemin qui ne devrait pas exister
  //Info Erreur, index timeline
  void Oublie_conscient_cas_A(Info_Erreur,int);
  void Oublie_conscient_cas_B(Info_Erreur,int);
  void Oublie_conscient_cas_C(Info_Erreur,int);
};

#endif

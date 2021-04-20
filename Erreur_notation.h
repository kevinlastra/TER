#ifndef ERREUR_NOTATION
#define ERREUR_NOTATION

#include "Info.h"
#include "TimeDivision.h"
#include "Piece.h"
#include "ArbreMovement.h"
#include <stdlib.h>
#include <iostream>

using namespace std;


class Erreur_notation
{
    private:
     TimeDivision* TD;

    public:
    Erreur_notation(TimeDivision*);
    ~Erreur_notation();

    bool Traiter_Erreur(Info_Erreur);
    
    bool Verif_eat(Info_piece*, int, int);
    Type int_to_type(int);
    bool Erreur_coord(Info_Erreur,int);
    bool Erreur_type(Info_Erreur ,int);
    std::vector<Piece*> Get_piece_from_type(Type,bool,ChessPlate*);
    std::vector<int> Get_index_from_type(Type,bool,ChessPlate*);

    //tl,coord, prof, color
    std::vector<Arbre*> Gen_Arbre(TimeLine*,Coord,int,bool);
    std::vector<Arbre*> Gen_Arbre(TimeLine*,std::vector<int>,int);
    std::vector<int> get_piece_in_path(ChessPlate*, Coord, Coord, Type);
    //coordoner, type, couleur, temps dans tl
    bool check_ambiguiter(TimeLine*, Coord, Type, bool,int);
};

#endif;
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

    //Renvoie l'erreur vers les methodes adaptées selon l'erreur.
    bool Traiter_Erreur(Info_Erreur);
    
    //Corrige une erreur de notation d'une pièce qui en mange une autre
    //Paramètres: Infos de l'erreur , Index de la timeline
    void Error_eat(Info_Erreur, int);
    void Erreur_ambiguite(Info_Erreur,int);

    //Corrige une erreur de coordonnées ou de type si possible, testant les coups possibles
    //Paramètres: Infos de l'erreur , Index de la timeline
    bool Erreur_coord(Info_Erreur,int);
    bool Erreur_type(Info_Erreur ,int);
    

    //Renvoie les indexs de pièce ou laes pièces en question d'un type donné sur le plateau passé en argument
    //Paramètres: Type de la pièce , couleur , plateau
    std::vector<Piece*> Get_piece_from_type(Type,bool,ChessPlate*);
    std::vector<int> Get_index_from_type(Type,bool,ChessPlate*);
    
    //Génère une arbre avec les paramètres suivants:
    //Timeline,coordonnées, profondeur, couleur
    std::vector<int> get_piece_in_path(ChessPlate*, Coord, Coord, Type);
    
    //Transforme un entier en un type , utile pour la methode Erreur_coord()
    Type int_to_type(int);

    //Vérifie l'ambiguité d'une pièce
    bool check_ambiguiter(TimeLine*, Coord, Type, bool,int);
};

#endif;
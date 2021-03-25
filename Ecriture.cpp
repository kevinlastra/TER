#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <map>
#include "Ecriture.h"

using namespace std;

//Dictionnaire qui associe a chaque type de pièce son écriture en pgn. 
std::map<Type, string> type_to_pgn ={
  {Type::roi, "K"},
  {Type::dame, "Q"},
  {Type::fous, "B"},
  {Type::cavaliers, "N"},
  {Type::tours, "R"},
  {Type::pions, ""},
  {Type::NONE, "_"}
};

Ecriture::Ecriture(){}
Ecriture::~Ecriture(){}

//Fonction d'écriture avec l'a timeline de la partie et le chemin du fichier dans lequel on écrira.
void Ecriture::Write(TimeDivision* td, string* path)
{
  //cout << "lancement de l'éctriture: " << endl;
  Piece blanc;
  Piece noire;
  string coupBlanc;
  string coupNoir;
  string nomBlanc;
  string nomNoir;
  //MultiTimeLine* mtl = td->get_TimeLine_at(0);
  TimeLine* tm;

  int tour = 1;
  

  //Ouverture du fichier en écriture/ écrase le contenu du fichier si il n'est pas vide a l'ouverture
  ofstream file(*path, ios::out | ios::trunc);
  
  if(!file)
  {
    cout <<"Erreur le fichier n'a pas été trouvé ou n'a pas pu être ouvert" << endl;
    return;
  }
  

  

    tm = td->TimeLine_at(0);
    for(int i=0;i<tm->get_size();i+=2){
      
      coupNoir= "";
      coupBlanc= "";
      pBlanche = tm->get_instant_at(i); //Piece blanche
      
      Type typeBlanc= pBlanche->p->get_Type();

      
      coupBlanc+= type_to_pgn[typeBlanc]; //string dans lequel les coups de cette ligne seront ecrits
      
      //if(pBlanche->info.ambiguous){
      // coupBlanc += intToStr(tm->get_instant_at(pBlanche->p->time_to_previous_pos_time(i))->p->get_pos_at(tm->get_instant_at(pBlanche->p->time_to_previous_pos_time(i))->i).x());
      //}
      
      //Coup joueur blanc
      if(pBlanche->info.ambiguous)
      {
        int lastTime = pBlanche->p->time_to_previous_pos_time(i);
        if(lastTime>=0){
          //cout << lastTime << endl;
          pLast = tm->get_instant_at(lastTime);
          coupBlanc += intToStr(pLast->p->get_pos_at(pLast->i).x());
          
          //cout  << coupBlanc<<" : " << lastTime << endl;
          //cout << pBlanche->p->toString() << "       lastTime: "<< lastTime << "     y:"<< pLast->p->get_pos_at(pLast->i).y() <<endl;
        
        }else{
          coupBlanc+= intToStr(pBlanche->p->get_pos_at(0).x());
        }
      }
      
      switch(pBlanche->a){
          
        case Action::eat:
          coupBlanc+="x";

        case Action::move:
            //cout <<"x: "<< pBlanche->p->get_pos_at(pBlanche->i).x() << "y: "<< pBlanche->p->get_pos_at(pBlanche->i).y()  <<endl;
            //a ajouter: gestion des coups ambigus (peut-être dans tm->get_instance_at(i))
            //On écrit le coup sous la forme : type du coup + coordonnées d'arrivées en x (transformées en string) + coordonnées d'arrivées en y
          coupBlanc += intToStr(pBlanche->p->get_pos_at(pBlanche->i).x()) + std::to_string(pBlanche->p->get_pos_at(pBlanche->i).y());
          
          break;

          //en cas de roque:
        case Action::change:
            //Si petit roque (donc le roi a été deplacé en g et la tour en f)
          coupBlanc=get_str_castling(pBlanche->p->get_pos_at(pBlanche->i).x());
          i++;
          break;

        case Action::promotion:
          //cout<< "promo" << endl;
          coupBlanc += intToStr(pBlanche->p->get_pos_at(pBlanche->i).x()) + std::to_string(pBlanche->p->get_pos_at(pBlanche->i).y()) + type_to_pgn[tm->get_instant_at(i+1)->p->get_Type()];
          i++;
          //cout << "promo effectuee" << endl;
          break;


        default:
          cout << "coordonnée x:" << pBlanche->p->get_pos_at(pBlanche->i).x() << " coordonnée y:" << pBlanche->p->get_pos_at(pBlanche->i).y() << " type blanc:" << type_to_pgn[typeBlanc] << endl;
          cout << "a:" << pBlanche->a << endl;
          cerr << "impossible de passer son tour aux echecs" << endl;

      }
      if(pBlanche->info.echec){
        coupBlanc += "+";
      }
      
      //coup joueur noir
      if(i+1!=tm->get_size()){
        pNoire = tm->get_instant_at(i+1); //Piece noire
        Type typeNoir= pNoire->p->get_Type();
        coupNoir= type_to_pgn[typeNoir];

        if(pNoire->info.ambiguous)
        {
          
          int lastTime = pNoire->p->time_to_previous_pos_time(i+1);
          if(lastTime >= 0){
            pLast = tm->get_instant_at(lastTime);
            coupNoir += intToStr(pLast->p->get_pos_at(pLast->i).x());
          }else{
            coupNoir+= intToStr(pNoire->p->get_pos_at(0).x());
          }
        }

        switch(pNoire->a){

          case Action::eat:
            coupNoir+="x";

          case Action::move:
            //a ajouter: gestion des coups ambigus (peut-être dans tm->get_instance_at(i))
            coupNoir+= intToStr(pNoire->p->get_pos_at(pNoire->i).x()) + std::to_string(pNoire->p->get_pos_at(pNoire->i).y());
            break;

          //en cas de roque:
          case Action::change:
            coupNoir=get_str_castling(pNoire->p->get_pos_at(pNoire->i).x());
            i++;
            break;

          case Action::promotion:
	    //cout << "promo" << endl;
            coupNoir= intToStr(pNoire->p->get_pos_at(pNoire->i).x()) + std::to_string(pNoire->p->get_pos_at(pNoire->i).y()) + type_to_pgn[typeNoir];
            i++;
            //cout << "promo effectuee" << endl;
          break;
          
          default:
            cout << "coordonnée x:" << pNoire->p->get_pos_at(pNoire->i).x() << " coordonnée y:" << pNoire->p->get_pos_at(pNoire->i).y() << " type noir:" << type_to_pgn[tm->get_instant_at(i+2)->p->get_Type()] << endl;
            cout << "a:" << pNoire->a << endl;
            cerr << "impossible de passer son tour aux echecs" << endl;

        }
        if(pNoire->info.echec){
          coupNoir+= "+";
        }
        
      }


      //Ecriture sur dans le fichier passé en argument
      //cout << (tour/2)+1 << ": Blanc: " << pBlanche->a << "Noir : "  << pNoire->a << endl;
      //cout << "coordonnées blanche : x : " << pBlanche->p->get_pos_at(pBlanche->i).x() << " y : " << pBlanche->p->get_pos_at(pBlanche->i).y() << " affiché: " << intToStr(pBlanche->p->get_pos_at(pBlanche->i).x()) << endl;
      file << (tour/2)+1 << ". " << coupBlanc;
      if(coupNoir!=""){
        file << " " << coupNoir;
      }
      file << endl;
      //cout << (tour/2)+1 <<": Pnoire -Est ambigue: "<< pNoire->info.ambiguous << "- Fait echec: " << pNoire->info.echec << endl;
      //cout << (tour/2)+1 <<": Pblanche -Est ambigue: "<< pBlanche->info.ambiguous << "- Fait echec: " << pBlanche->info.echec << endl;
      tour= tour+2;

    }
  


  //Fermeture du fichier
  file.close();
  
}

//transorme une coordonée d'entier en charactère : exemple pour écrire c5 on a les coordonnées 3 en x , 5 en y on transforme le 3 en c grâce à ça.
char Ecriture::intToStr(int n)
{
  char alpha[9] = "abcdefgh";
  
  return alpha[n-1];
}

//renvoie le string du roque qu'il soit petit ou grand
string Ecriture::get_str_castling(int x){
  if(x==7){
     return "O-O";
  }
  return "O-O-O";
}

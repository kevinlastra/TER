#include <string>
#include "Piece.h"
#include "TimeLine.h"

using namespace std;

class Ambiguite
{
    private:

        Timeline* tl;
        Instant* piece;
        string typePiece;

        bool estAmbigue(int, TimeLine*);
        bool risqueAmbiguite(Coord* ,Instant*);
};
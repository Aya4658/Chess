#ifndef PLATEAU_H
#define PLATEAU_H
//#include<vector>
#include <cmath> // Pour la fonction abs()
using namespace std;

class Plateau
{
    public:
        Plateau();
        ~Plateau();
        initPlateau();
        int getPiece(int x,int y);
        setPiece(int x,int y,int val);
        DeplacerPiece(int xd,int yd,int xa,int ya);
        int evalPion(int xd,int yd,int xa,int ya);
        int evalFou(int xd,int yd,int xa,int ya);
        int evalTour(int xd,int yd,int xa,int ya);
        int evalCavalier(int xd,int yd,int xa,int ya);
        int evalDame(int xd,int yd,int xa,int ya);
        //pour roi
        bool estCaseAttaquee(int x, int y, bool parBlanc);
    	bool estPieceProtegee(int x, int y, bool pieceEstBlanche);
        int evalRoi(int xd,int yd,int xa,int ya);
    private:
        int p[8][8];
};


#endif

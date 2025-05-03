#include "Plateau.h"


Plateau::Plateau()
{
	initPlateau();
}

Plateau::~Plateau()
{
}

Plateau::initPlateau()
{
	for(int i=2;i<=5;i++)
	{
		for(int j=0;j<=7;j++)
		{
			p[i][j]=0;
		}
	}
	for(int j=0;j<=7;j++)
	{
		p[6][j]=1;
		p[1][j]=-1;
	}
	p[7][0]=3;
	p[7][1]=2;
	p[7][2]=4;
	p[7][3]=5;
	p[7][4]=6;
	p[7][5]=4;
	p[7][6]=2;
	p[7][7]=3;

	p[0][0]=-3;
	p[0][1]=-2;
	p[0][2]=-4;
	p[0][3]=-5;
	p[0][4]=-6;
	p[0][5]=-4;
	p[0][6]=-2;
	p[0][7]=-3;
	
}

int Plateau::getPiece(int x,int y)
{
	return p[x][y];
}

Plateau::setPiece(int x,int y,int val)
{
	p[x][y]=val;
}


Plateau::DeplacerPiece(int xd,int yd,int xa,int ya)
{	
    int val=0;
    
    switch(abs(p[xd][yd]))
    {
        case 1:
            val=evalPion(xd,yd,xa,ya);
            break;
        case 2:
            val=evalCavalier(xd,yd,xa,ya);
            break;
        case 3:
            val=evalTour(xd,yd,xa,ya);
            break;
        case 4:
            val=evalFou(xd,yd,xa,ya);
            break;
        case 5:
            val=evalDame(xd,yd,xa,ya);
            break;
        case 6:
            val=evalRoi(xd,yd,xa,ya);
            break;
    }
    
    if(val==1) //le evaluations retournent 1 si ils sont valides
    {
        p[xa][ya]=p[xd][yd]; //mouvement reussi car la position d arrivee prend la position de depart
        p[xd][yd]=0; // on vide la position de depart
        return 1;
    }
    
    return 0;
}


int Plateau::evalPion(int xd, int yd, int xa, int ya) 
{
    int piece = p[xd][yd];
    
    if (yd == ya && p[xa][ya] == 0) //mouvement en avant yd == ya et chemin pas incline p[xa][ya] == 0
    {
        //pion blanc (vers le haut)
        if (piece == 1) 
        {
            if (xd ==8 && xa == 6 && p[7][ya] == 0) //double avance
            {
                return 1;
            }

            else if (xd - xa == 1) //un seul carre avance
            {
                return 1;
            }
        }
        //pion noir (vers le bas)
        else if (piece == -1) 
        {
            if (xd == 1 && xa == 3 && p[2][ya] == 0) // p[2][ya] == 0 => si chemin est vide
            {
                return 1;
            }

            else if (xa - xd == 1) 
            {
                return 1;
            }
        }
    }
    // CAPTURE POUR PION
    else if (abs(yd - ya) == 1)
    {
        // pion blanc
        if (piece == 1 && xd - xa == 1 && p[xa][ya] < 0) //cible doit contenir pion noir
        {
            return 1;
        }
        // pion noir
        else if (piece == -1 && xa - xd == 1 && p[xa][ya] > 0) //cible doit contenir pion blanc
        {
            return 1;
        }
    }
    
    return 0;
}


int Plateau::evalFou(int xd, int yd, int xa, int ya)
{
    // Vérifie mouvement est diagonal
    if (abs(xd - xa) != abs(yd - ya)) {
        return 0;
    }

    int diag = 0;
    for(int i = 1; i <= 7; i++)
    {
        if((xd == xa-i) && (yd == ya+i)) {
            diag = 1; // bas-gauche
            break;
        }
        else if((xd == xa-i) && (yd == ya-i)) {
            diag = 2; // bas-droit
            break;
        }
        else if((xd == xa+i) && (yd == ya+i)) {
            diag = 3; // haut-droit
            break;
        }
        else if((xd == xa+i) && (yd == ya-i)) {
            diag = 4; // haut-gauche
            break;
        }
    }

    if (diag != 0) {
        bool obstacle = false;
        int steps = abs(xa - xd) - 1; //on verifie jusque les cases intermediaires

        switch (diag) {
            case 1: // bas-gauche
                for (int step = 1; step <= steps; step++) {
                    if (p[xd + step][yd - step] != 0) {
                        obstacle = true;
                        break;
                    }
                }
                break;

            case 2: // bas-droit
                for (int step = 1; step <= steps; step++) {
                    if (p[xd + step][yd + step] != 0) {
                        obstacle = true;
                        break;
                    }
                }
                break;

            case 3: // haut-droit
                for (int step = 1; step <= steps; step++) {
                    if (p[xd - step][yd + step] != 0) {
                        obstacle = true;
                        break;
                    }
                }
                break;

            case 4: // haut-gauche
                for (int step = 1; step <= steps; step++) {
                    if (p[xd - step][yd - step] != 0) {
                        obstacle = true;
                        break;
                    }
                }
                break;
        }

        if (!obstacle) {
            // CAPTURE PAR FOU
            int pieceDepart = p[xd][yd];
            int pieceArrivee = p[xa][ya];
            
            if (pieceArrivee == 0 || (pieceDepart * pieceArrivee < 0)) { //case vide ou pieces de couleur diffrentes
                return 1;
            }
        }
    }
    
    return 0;
}


int Plateau::evalTour(int xd, int yd, int xa, int ya)
{
    // verifie mvt horizontal ou vertical
    if (xd == xa || yd == ya)
    {
        bool obstacle = false;
        int start, end;
        
        // Mvmt horizontal
        if (xd == xa) //pas de changement de lignes
        {
            if (yd < ya) {
                start = yd + 1;
                end = ya;
            } else {
                start = ya + 1;
                end = yd;
            }
            
            for (int j=start; j<end; j++)
            {
                if (p[xd][j] != 0)
                {
                    obstacle = true;
                    break;
                }
            }
        }
        // Mouvement vertical
        else
        {
            if (xd < xa) {
                start = xd + 1;
                end = xa;
            } else {
                start = xa + 1;
                end = xd;
            }
            
            for (int i = start; i < end; i++)
            {
                if (p[i][yd] != 0)
                {
                    obstacle = true;
                    break;
                }
            }
        }
        
        // cas: aucun obstacle trouve
        if (!obstacle)
        {
            int pieceDepart = p[xd][yd];   
            int pieceArrivee = p[xa][ya];  
            
            // Case vide 
            if (pieceArrivee == 0) {
                return 1;
            }
            // CAPTURE TOUR COULEUR- OPPOSEE
            else if (pieceDepart * pieceArrivee < 0) {
                return 1;
            }
        }
    }
    
    return 0;
}

int Plateau::evalCavalier(int xd, int yd, int xa, int ya) 
{
    // Verifie mvt ->L
    if ((abs(xa - xd) == 2 && abs(ya - yd) == 1) || 
        (abs(xa - xd) == 1 && abs(ya - yd) == 2)) 
    {
        int pieceDepart = p[xd][yd]; 
        int pieceArrivee = p[xa][ya];  

        // Case vide
        if (pieceArrivee == 0) {
            return 1;
        }
        // CAPTURE TOUR CAVALIER- OPPOSEE
        else if (pieceDepart * pieceArrivee < 0) {
            return 1;
        }
    }
    return 0;
}


int Plateau::evalDame(int xd,int yd,int xa,int ya)
{
    return evalTour(xd,yd,xa,ya) || evalFou(xd,yd,xa,ya);
}



bool Plateau::estCaseAttaquee(int x, int y, bool parBlanc) //estRoiNoir = false <=> parBlanc = true
{ // c est pour les cases vides
    // Parcourt tout le plateau
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int piece = p[i][j];
            
            // Verifie pieces opposees
            if ((parBlanc && piece < 0) || (!parBlanc && piece > 0)) {
                // Teste si la pièce peut attaquer la case (x,y)
                switch (abs(piece)) {
                    case 1:
                        if (evalPion(i, j, x, y)) return true;
                        break;
                    case 2: 
                        if (evalCavalier(i, j, x, y)) return true;
                        break;
                    case 3:
                        if (evalTour(i, j, x, y)) return true;
                        break;
                    case 4:
                    	if (evalFou(i, j, x, y)) return true;
                        break;
                    case 5:
                    	if (evalDame(i, j, x, y)) return true;
                        break;
                    //le roi peut attacker juste le danger direct (cas de 2 rois adjacents impossible)
                }
            }
        }
    }
    return false;
}


bool Plateau::estPieceProtegee(int x, int y, bool pieceEstBlanche) { // c est pour les cases pleines
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int piece = p[i][j];
            if ((pieceEstBlanche && piece > 0) || (!pieceEstBlanche && piece < 0)) {
                switch (abs(piece)) {
                    case 1: if (evalPion(i,j,x,y)) return true; break;
                    case 2: if (evalCavalier(i,j,x,y)) return true; break;
                    case 3: if (evalTour(i,j,x,y)) return true; break;
                    case 4: if (evalFou(i,j,x,y)) return true; break;
                    case 5: if (evalDame(i,j,x,y)) return true; break;
                }
            }
        }
    }
    return false; //auncune piece allie ne peut defendre
}


int Plateau::evalRoi(int xd, int yd, int xa, int ya) 
{
    // Verifie le deplacement est d'une case max
    if (abs(xa - xd) > 1 || abs(ya - yd) > 1) {
        return 0; // Mvt invalide
    }

    //Recupere les pieces concernees
    int roi = p[xd][yd];       
    int cible = p[xa][ya];

    // Verifie si case arrivee est sure(pas sous attaque) case VIDE
    bool estRoiNoir = (roi < 0);
    if (estCaseAttaquee(xa, ya, !estRoiNoir)) {
        return 0; 
    }

    //Conditions de deplacement/capture
    if (cible == 0) {
        return 1; // Case vide
    }
    else if (roi * cible < 0) { // Piece opposee
        // Verifie que la piece est pas protege
        if (!estPieceProtegee(xa, ya, cible > 0)) { // j utilise "estRoiNoir" c est pourquoi le test est de "cible > 0"== Pièce opposee
            return 1;
        }
    }

    return 0;
}
#include <iostream>
#include <string>
#include "Plateau.h"

using namespace std;

void afficherPlateau(Plateau p) {
    string val;
    cout << "   1    2    3    4    5    6    7    8" << endl;
    for(int i = 0; i <= 7; i++) {
        for(int j = 0; j <= 7; j++) {
            switch (p.getPiece(i, j)) {
                case 0: val = "  "; break;
                case 1: val = "PB"; break;
                case 2: val = "CB"; break;
                case 3: val = "TB"; break;
                case 4: val = "FB"; break;
                case 5: val = "DB"; break;
                case 6: val = "RB"; break;
                case -1: val = "PN"; break;
                case -2: val = "CN"; break;
                case -3: val = "TN"; break;
                case -4: val = "FN"; break;
                case -5: val = "DN"; break;
                case -6: val = "RN"; break;
            }
            cout << " | " << val;
        }
        cout << "    " << i + 1 << endl;
    }
}


void saisirDepart(int &xd, int &yd, Plateau &p, bool tourBlanc) {
    do {
        cout << "Veuillez saisir une ligne de depart : ";
        cin >> xd;
        cout << "Veuillez saisir une colonne de depart : ";
        cin >> yd;
        xd--; yd--; // Conversion en indices 0-7

        // Verifie la piece selectionnee est de bonne couleur
        int piece = p.getPiece(xd, yd);
        bool pieceEstBlanche = (piece > 0);
        
        if ((tourBlanc && !pieceEstBlanche) || (!tourBlanc && pieceEstBlanche)) {
            cout << "Erreur : Ce n'est pas e votre tour de jouer cette piece !" << endl;
            xd = yd = -1; // Met les coordonnees en dehors des limites valides (0-7) => repetition de boucle
        }
    } while (xd < 0 || xd > 7 || yd < 0 || yd > 7);
}

void saisirArrivee(int &xa, int &ya, int xd, int yd) {								/*, Plateau &p*/
    do {
        cout << "Veuillez saisir une ligne d'arrivee : ";
        cin >> xa;
        cout << "Veuillez saisir une colonne d'arrivee : ";
        cin >> ya;
        xa--; ya--; // Conversion en indices 0-7
    } while (xa < 0 || xa > 7 || ya < 0 || ya > 7 || (xa == xd && ya == yd)); //la derniere while-condition dit que c est la meme place
}

int main() {
    Plateau p;
    int xa, xd, ya, yd;
    bool tourBlanc = true; // Les Blancs commencent

    while (true) {
        afficherPlateau(p);
        
        if (tourBlanc) {
    		cout << "Tour des Blancs" << endl;
		} else {
    		cout << "Tour des Noirs" << endl;
		}

        // Saisie des coordonnees
        saisirDepart(xd, yd, p, tourBlanc); // On passe tourBlanc pour vrifier la couleur
        saisirArrivee(xa, ya, xd, yd);													/*, p*/
		if (tourBlanc) {
    		cout << "Tour des Blancs" << endl;
		} else {
    		cout << "Tour des Noirs" << endl;
		}
        // Deplacement
        int result = p.DeplacerPiece(xd, yd, xa, ya);

        if (result == 1) {
            cout << "Mouvement reussi !" << endl;
            tourBlanc = !tourBlanc; // Changement de tour
        } else {
            cout << "Mouvement invalide !" << endl;
        }
    }
    return 0;
}
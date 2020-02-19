#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "terminalCouleur.h"

//#undef NDEBUG

#define TAILLE_PLATEAU_MIN 2
#define TAILLE_PLATEAU_MAX 8
#define VIDE 0
#define OUI 1
#define NON 0
#define NOIR 1
#define BLANC -1
#define BAS 1
#define HAUT -1
#define DROITE 1
#define GAUCHE -1
#define JOUEUR1 -1
#define JOUEUR2 1
#define EGALITE 2
#define TAILLE_MAX 128
#define REPONSE 10
#define ENTIER 10
#define TAILLE_CARRE 5
#define COULEUR_PION 6
#define PAS_TERMINE 0
#define PREMIERE 0
#define PAS_BOUGER 0
#define QUIT 0
#define NEW 1
#define RELOAD 2
#define SAVE 3
#define RETURN 4

typedef struct
{
    int *tableau;
    int n;
} plateau;

typedef struct
{
    char nomJoueur1[TAILLE_MAX];
    char nomJoueur2[TAILLE_MAX];
    int pionJoueurCourant;
    plateau *p;
} partie;

void clear_terminal();
int color_printf(COULEUR_TERMINAL fg, COULEUR_TERMINAL bg, const char *format, ...);
plateau *creerPlateau(int n);
void detruirePlateau(plateau *p);
int getCase(plateau *p, int i, int j);
void setCase(plateau *p, int i, int j, int val);
void affichage(partie *pa);
////////////////////////////////////////////////////////////////////////////////////////
void creerTableau(plateau *p);
int indiceValide(plateau *p, int indice);
int caseValide(plateau *p, int indiceLigne, int indiceColonne);
int caseVide(plateau *p, int i, int j);
int is_caseC_vide(plateau *p, int colonne);
int is_caseL_vide(plateau *p, int ligne);
int insertionPionPossible(plateau *p, int ligne, int colonne, int di, int dj, int pion);
int first_zero_column_down(plateau *p, int colonne);
int first_zero_column_up(plateau *p, int colonne);
int first_zero_line_right(plateau *p, int ligne);
int first_zero_line_left(plateau *p, int ligne);
void insertionPion(plateau *p, int ligne, int colonne, int di, int dj, int pion);
int is_column_full(plateau *p, int colonne, int joueur);
int is_line_full(plateau *p, int ligne, int joueur);
int gagne(plateau *p);
////////////////////////////////////////////////////////////////////////////////////////
void taillePlateau(partie *pa, int taille);
partie *creerPartie();
void detruirePartie(partie *pa);
void changePionJoueurCourant(partie *pa);
void lowtoup(char mot[]);
int second_letter_correct(char letter);
int convertirIndice(partie *pa, int *ligne, int *col, int *di, int *dj, char reponse[]);
int saisieJoueur(partie *pa, int *ligne, int *col, int *di, int *dj);
void possibilite(plateau *p, int ligne, int colonne, int di, int dj, int pion);
int tourJoueurCourant(partie *pa);
int jouer(partie *pa);
////////////////////////////////////////////////////////////////////////////////////////
int sauvegardePartie(partie *pa);
partie *chargementPartie();
void choisirPion(partie *pa);
int menu(partie *pa);

#endif

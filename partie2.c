/* PARTIE 2 */

#include "terminalCouleur.h"
#include "fonctions.h"

///////////////////////////////////////////////////////////////////////
// Fonction retournant 1 si l'indice est valide par rapport au plateau
// \param p : plateau
// \param indice : entier compris entre [0, n-1]
///////////////////////////////////////////////////////////////////////

int indiceValide(plateau *p, int indice)
{
    if (indice >= VIDE && indice < p->n)
        return OUI;
    else
        return NON;
}

/////////////////////////////////////////////////////////////////////////////////////
//Fonction retournant 1 si la case (indiceLigne, indiceColonne) existe sur le plateau
// \param p : plateau
// \param indiceLigne : entier correspondant à une indice de ligne
// \param indiceColonne : entier correspondant à un indice de colonne
/////////////////////////////////////////////////////////////////////////////////////

int caseValide(plateau *p, int indiceLigne, int indiceColonne)
{
    if (indiceValide(p, indiceLigne) && indiceValide(p, indiceColonne))
        return OUI;
    else
        return NON;
}

//////////////////////////////////////////////////////////////
//Fonction retournant 1 si la case (i,j) du plateau p est vide
// \param p : plateau
// \param i : entier correspondant à un indice de ligne
// \param j : entier correspondant à un indice de colonne
//////////////////////////////////////////////////////////////

int caseVide(plateau *p, int i, int j)
{
    if (getCase(p, i, j) == VIDE)
        return OUI;
    else
        return NON;
}

//////////////////////////////////////////////////////////////////
//La fonction vérifie s'il y a une case vide dans toute la colonne
//////////////////////////////////////////////////////////////////

int is_caseC_vide(plateau *p, int colonne)
{
    int i;
    for (i = 0; i < p->n; i++)
        if (getCase(p, i, colonne) == VIDE)
            return OUI;
    return NON;
}

////////////////////////////////////////////////////////////////
//La fonction vérifie s'il y a une case vide dans toute la ligne
////////////////////////////////////////////////////////////////

int is_caseL_vide(plateau *p, int ligne)
{
    int i;
    for (i = 0; i < p->n; i++)
        if (getCase(p, ligne, i) == VIDE)
            return OUI;
    return NON;
}

///////////////////////////////////////////////////////////////////////////////////
//Fonction retournant 1 si le pion peut être ajouté à partir de la case (ligne,col)
//dans la direction donnée par di,dj
// \param p : plateau
// \param ligne : ligne de la case où l’on insère le pion
// \param col : colonne de la case où l’on insère le pion
// \param di : direction sur les lignes
//							-1 si l’on insère vers le haut,
//							0 si l’on reste sur la même ligne,
//  						1 si l’on insère vers le haut
// \param dj : direction sur les colonnes
//							-1 si l’on insère vers la gauche,
//  						0 si l’on reste sur la même colonne,
//  						1 si l’on insère vers la droite
// \param pion : 1 ou -1 suivant le joueur
///////////////////////////////////////////////////////////////////////////////////

int insertionPionPossible(plateau *p, int ligne, int colonne, int di, int dj, int pion)
{
    if (caseValide(p, ligne, colonne) && (di != dj) && (pion == NOIR || pion == BLANC))
    {
        if (ligne == PREMIERE && di == BAS && (is_caseC_vide(p, colonne) || (getCase(p, p->n - 1, colonne) == pion))) //si 1e ligne, direction en bas, une case vide ou dernière case même couleur que pion
            return OUI;
        else if (colonne == PREMIERE && dj == DROITE && (is_caseL_vide(p, ligne) || (getCase(p, ligne, p->n - 1) == pion)))
            return OUI;
        else if (ligne == p->n - 1 && di == HAUT && (is_caseC_vide(p, colonne) || (getCase(p, VIDE, colonne) == pion)))
            return OUI;
        else if (colonne == p->n - 1 && dj == GAUCHE && (is_caseL_vide(p, ligne) || (getCase(p, ligne, VIDE) == pion)))
            return OUI;
    }
    return NON;
}

///////////////////////////////////////////////////////////////////////////////////
//Fonction retournant 1 si le pion peut être ajouté à partir de la case (ligne,col)
//dans la direction donnée par di,dj
//param p : plateau
// \param ligne : ligne de la case où l’on insère le pion
// \param col : colonne de la case où l’on insère le pion
// \param dj : direction sur les lignes
// 						-1 si l’on insère vers le haut,
//  						0 si l’on reste sur la même ligne,
//  						1 si l’on insère vers le haut
// \param direction sur les colonnes
// 						-1 si l’on insère vers la gauche,
//  						0 si l’on reste sur la même colonne,
//  						1 si l’on insère vers la droite
// \param pion : 1 ou -1 suivant le joueur
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////

int first_zero_column_down(plateau *p, int colonne)
{
    int nombre_zero = 0;
    while (getCase(p, nombre_zero, colonne) != VIDE)
        nombre_zero++;
    return nombre_zero;
}

int first_zero_column_up(plateau *p, int colonne)
{
    int nombre_zero = 0;
    int i;
    for (i = p->n - 1; getCase(p, i, colonne) != VIDE; i--)
        nombre_zero++;
    return nombre_zero;
}

///////////////////////////////////////////////////

int first_zero_line_right(plateau *p, int ligne)
{
    int nombre_zero = 0;
    while (getCase(p, ligne, nombre_zero) != VIDE)
        nombre_zero++;
    return nombre_zero;
}

int first_zero_line_left(plateau *p, int ligne)
{
    int nombre_zero = 0;
    int i;
    for (i = p->n - 1; getCase(p, ligne, i) != VIDE; i--)
        nombre_zero++;
    return nombre_zero;
}

////////////////////////////////////////////////////////////////////////////////

void insertionPion(plateau *p, int ligne, int colonne, int di, int dj, int pion)
{
    int i, k;
    assert(insertionPionPossible(p, ligne, colonne, di, dj, pion));
    if (ligne == PREMIERE && di == BAS)
    {
        if (is_caseC_vide(p, colonne))
        {
            for (i = first_zero_column_down(p, colonne), k = 0; k < i; i--)
                setCase(p, i, colonne, getCase(p, i - 1, colonne));
            setCase(p, ligne, colonne, pion);
        }
        else
        {
            for (ligne = p->n - 1; ligne > 0; ligne--)
                setCase(p, ligne, colonne, getCase(p, ligne - 1, colonne));
            setCase(p, ligne, colonne, pion);
        }
    }
    else if (colonne == PREMIERE && dj == DROITE)
    {
        if (is_caseL_vide(p, ligne))
        {
            for (i = first_zero_line_right(p, ligne), k = 0; k < i; i--)
                setCase(p, ligne, i, getCase(p, ligne, i - 1));
            setCase(p, ligne, colonne, pion);
        }
        else
        {
            for (colonne = p->n - 1; colonne > 0; colonne--)
                setCase(p, ligne, colonne, getCase(p, ligne, colonne - 1));
            setCase(p, ligne, colonne, pion);
        }
    }
    else if (ligne == p->n - 1 && di == HAUT)
    {
        if (is_caseC_vide(p, colonne))
        {
            for (i = first_zero_column_up(p, colonne), k = 0; k < i; i--)
                setCase(p, ligne - i, colonne, getCase(p, ligne - i + 1, colonne));
            setCase(p, ligne, colonne, pion);
        }
        else
        {
            for (ligne = PREMIERE; ligne < p->n - 1; ligne++)
                setCase(p, ligne, colonne, getCase(p, ligne + 1, colonne));
            setCase(p, ligne, colonne, pion);
        }
    }
    else if (colonne == p->n - 1 && dj == GAUCHE)
    {
        if (is_caseL_vide(p, ligne))
        {
            for (i = first_zero_line_left(p, ligne), k = 0; k < i; i--)
                setCase(p, ligne, colonne - i, getCase(p, ligne, colonne - i + 1));
            setCase(p, ligne, colonne, pion);
        }
        else
        {
            for (colonne = PREMIERE; colonne < p->n - 1; colonne++)
                setCase(p, ligne, colonne, getCase(p, ligne, colonne + 1));
            setCase(p, ligne, colonne, pion);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//Fonction retournant 1 ou -1 si l’un des joueurs a gagné, 2 si match nul et 0 si la partie
//n’est pas finie.
//
// \param p : plateau
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
//La fonction demande si toute la colonne a le même pion
////////////////////////////////////////////////////////

int is_column_full(plateau *p, int colonne, int joueur)
{
    int i, compteur = 0;
    for (i = 0; i < p->n; i++)
        if (getCase(p, i, colonne) == joueur)
            compteur++;
    if (compteur == p->n)
        return OUI;
    return NON;
}

//////////////////////////////////////////////////////
//La fonction demande si toute la ligne a le même pion
//////////////////////////////////////////////////////

int is_line_full(plateau *p, int ligne, int joueur)
{
    int i, compteur = 0;
    for (i = 0; i < p->n; i++)
        if (getCase(p, ligne, i) == joueur)
            compteur++;
    if (compteur == p->n)
        return OUI;
    return NON;
}

int gagne(plateau *p)
{
    int i;
    int nomJ1 = 0;
    int nomJ2 = 0;
    for (i = 0; i < p->n; i++)
    {
        if (is_line_full(p, i, JOUEUR1))
            nomJ1++;
        if (is_column_full(p, i, JOUEUR1))
            nomJ1++;
        if (is_line_full(p, i, JOUEUR2))
            nomJ2++;
        if (is_column_full(p, i, JOUEUR2))
            nomJ2++;
    }
    if (nomJ1 > nomJ2)
        return JOUEUR1;
    else if (nomJ1 < nomJ2)
        return JOUEUR2;
    else if (nomJ1 == nomJ2 && nomJ1 != VIDE && nomJ2 != VIDE)
        return EGALITE;
    else
        return PAS_TERMINE;
}

/* PARTIE 3*/

#include "terminalCouleur.h"
#include "fonctions.h"

////////////////////////////////////////////////////////////////////////////////
//Fonction allouant dynamiquement une partie et renvoyant l’adresse de celle-ci.
//La taille du plateau et les noms des joueurs sont saisis par l’utilisateur.
////////////////////////////////////////////////////////////////////////////////

void taillePlateau(partie *pa, int taille)
{
    pa->p = creerPlateau(taille);
    creerTableau(pa->p);
}

partie *creerPartie()
{
    int taille = 0;
    partie *pa = (partie *)malloc(sizeof(partie));
    if (NULL == pa)
    {
        printf("Problème d'allocation");
        exit(1);
    }
    printf("Saisir le nom du 1er joueur : ");
    scanf("%s", pa->nomJoueur1);
    printf("Saisir le nom du 2ème joueur : ");
    scanf("%s", pa->nomJoueur2);
    do
    {
        printf("Saisir la taille du plateau : ");
        scanf("%d", &taille);
    } while (taille <= TAILLE_PLATEAU_MIN && taille >= TAILLE_PLATEAU_MAX);
    taillePlateau(pa, taille);
    return pa;
}

//////////////////////////////////////////////////////////////////
//Fonction désallouant dynamiquement la partie passée en paramètre
// \param pa : partie à désallouer
//////////////////////////////////////////////////////////////////

void detruirePartie(partie *pa)
{
    detruirePlateau(pa->p);
    free(pa);
}

////////////////////////////////////////////////////////
//Fonction changeant le pion du joueur courant (1 ou -1)
// \param pa : partie en cours
////////////////////////////////////////////////////////

void changePionJoueurCourant(partie *pa)
{
    if (pa->pionJoueurCourant == NOIR)
        pa->pionJoueurCourant = BLANC;
    else
        pa->pionJoueurCourant = NOIR;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//Fonction modifiant les variables ligne, col, di et dj passées en paramètre avec
//les valeurs saisies par l’utilisateur. Elle retourne 0 si le joueur a appuyé
//sur la lettre M et 1 sinon.
// \param p : partie
// \param ligne : ligne du plateau où l’on souhaite insérer le pion du joueur courant de la partie
// \param col : colonne du plateau où l’on souhaite insérer le pion du joueur courant de la partie
// \param di : direction d’insertion (ligne)
// \param dj : direction d’insertion (colonne)
//////////////////////////////////////////////////////////////////////////////////////////////////

void lowtoup(char mot[])
{
    int i;
    for (i = 0; mot[i] != '\0'; i++)
        if (islower(mot[i])) //0 non 1 oui
            mot[i] = toupper(mot[i]);
}

int second_letter_correct(char letter)
{
    if (letter >= '0' && letter <= '9')
        return OUI;
    else
        return NON;
}

int convertirIndice(partie *pa, int *ligne, int *col, int *di, int *dj, char reponse[])
{
    if (reponse[0] == 'H')
    {
        *ligne = PREMIERE;
        *di = BAS;
        *dj = PAS_BOUGER;
        if (second_letter_correct(reponse[1]))
            *col = atoi(&(reponse[1])) - 1;
        else
            return NON;
    }
    else if (reponse[0] == 'B')
    {
        *ligne = pa->p->n - 1;
        *di = HAUT;
        *dj = PAS_BOUGER;
        if (second_letter_correct(reponse[1]))
            *col = atoi(&(reponse[1])) - 1;
        else
            return NON;
    }
    else if (reponse[0] == 'G')
    {
        *col = PREMIERE;
        *di = PAS_BOUGER;
        *dj = DROITE;
        if (second_letter_correct(reponse[1]))
            *ligne = atoi(&(reponse[1])) - 1;
        else
            return NON;
    }
    else if (reponse[0] == 'D')
    {
        *col = pa->p->n - 1;
        *di = PAS_BOUGER;
        *dj = GAUCHE;
        if (second_letter_correct(reponse[1]))
            *ligne = atoi(&(reponse[1])) - 1;
        else
            return NON;
    }
    else
        return NON;
    if (insertionPionPossible(pa->p, *ligne, *col, *di, *dj, pa->pionJoueurCourant))
        return OUI;
    return NON;
}

int saisieJoueur(partie *pa, int *ligne, int *col, int *di, int *dj)
{
    char reponse[REPONSE];
    printf("Souhaitez-vous retourner au menu principal (M) ou saisir une case?(H/B/G/D pour le bord du plateau et un chiffre pour numéro de ligne ou colonne) : ");
    scanf("%10s", reponse);
    lowtoup(reponse);
    if (!strcmp("M", reponse))
        return NON;
    else
    {
        while (!convertirIndice(pa, ligne, col, di, dj, reponse))
        {
            printf("Resaisir s'il vous plaît! ");
            scanf("%10s", reponse);
            lowtoup(reponse);
            if (!strcmp("M", reponse))
                return NON;
        }
        insertionPion(pa->p, *ligne, *col, *di, *dj, pa->pionJoueurCourant);
        return OUI;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
//Fonction permettant au joueur courant de jouer.
//La fonction retourne 1 si le joueur joue, et 0 sinon (s’il appuie sur la touche M).
// \param pa : partie en cours
/////////////////////////////////////////////////////////////////////////////////////
void possibilite(plateau *p, int ligne, int colonne, int di, int dj, int pion)
{
    printf("Vous pouvez inserer :\n");
    printf("-De haut en bas : ");
    for (colonne = 0; colonne < p->n; colonne++)
        if (insertionPionPossible(p, PREMIERE, colonne, BAS, PAS_BOUGER, pion))
            printf("H%d ", colonne + 1);
    printf("\n");
    printf("-De gauche à droite : ");
    for (ligne = 0; ligne < p->n; ligne++)
        if (insertionPionPossible(p, ligne, PREMIERE, PAS_BOUGER, DROITE, pion))
            printf("G%d ", ligne + 1);
    printf("\n");
    printf("-De bas en haut : ");
    for (colonne = 0; colonne < p->n; colonne++)
        if (insertionPionPossible(p, p->n - 1, colonne, HAUT, PAS_BOUGER, pion))
            printf("B%d ", colonne + 1);
    printf("\n");
    printf("-De droit à gauche : ");
    for (ligne = 0; ligne < p->n; ligne++)
        if (insertionPionPossible(p, ligne, p->n - 1, PAS_BOUGER, GAUCHE, pion))
            printf("D%d ", ligne + 1);
    printf("\n");
}

int tourJoueurCourant(partie *pa)
{
    int ligne = 0, colonne = 0, di = 0, dj = 0;
    affichage(pa);
    if (pa->pionJoueurCourant == JOUEUR1)
    {
        printf("Nom du joueur courant (BLANC) : %s\n", pa->nomJoueur1);
        possibilite(pa->p, ligne, colonne, di, dj, pa->pionJoueurCourant);
    }
    else
    {
        printf("Nom du joueur courant (NOIR): %s\n", pa->nomJoueur2);
        possibilite(pa->p, ligne, colonne, di, dj, pa->pionJoueurCourant);
    }
    return saisieJoueur(pa, &ligne, &colonne, &di, &dj);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Fonction permettant de jouer à Push over.
// \param pa : pointeur sur une partie en cours (elle doit être allouée). La partie peut ne pas être
//un début de partie.
//Retourne 0 si un joueur veut accéder au menu principal, 1 si la partie s’est terminée normalement
//(Partie gagnée ou nulle)
////////////////////////////////////////////////////////////////////////////////////////////////////

void choisirPion(partie *pa)
{
    char couleurPion[COULEUR_PION];
    printf("Choisir la couleur de votre pion (Noir ou Blanc) : ");
    scanf("%s", couleurPion);
    lowtoup(couleurPion);
    if (!strcmp("NOIR", couleurPion))
        pa->pionJoueurCourant = JOUEUR2;
    else
        pa->pionJoueurCourant = JOUEUR1;
}

int jouer(partie *pa)
{
    while (gagne(pa->p) == PAS_TERMINE)
    {
        clear_terminal();
        if (tourJoueurCourant(pa) == VIDE)
            return NON;
        changePionJoueurCourant(pa);
    }
    if (gagne(pa->p) != PAS_TERMINE)
    {
        //clear_terminal();
        affichage(pa);
        if (gagne(pa->p) == JOUEUR1)
        {
            printf("%s a gagné!!!\n", pa->nomJoueur1);
        }
        else if (gagne(pa->p) == JOUEUR2)
        {
            printf("%s a gagné!!!\n", pa->nomJoueur2);
        }
        else
            printf("Egalité T~T\n");
        return OUI;
    }
    else
        return NON;
}

/* PARTIE 1 */

#include "terminalCouleur.h"
#include "fonctions.h"

void clear_terminal()
{
    printf("\033[2J");
    printf("\033[0;0H");
}

int color_printf(COULEUR_TERMINAL fg, COULEUR_TERMINAL bg, const char *format, ...)
{
    int res;
    va_list args;
    printf("\x1B[1;%02d;%02dm", fg + 30, bg + 40);
    va_start(args, format);
    res = vprintf(format, args);
    va_end(args);
    printf("\x1B[00m");
    return res;
}

plateau *creerPlateau(int n)
{
    assert(n >= TAILLE_PLATEAU_MIN && n <= TAILLE_PLATEAU_MAX);
    plateau *p = (plateau *)malloc(sizeof(plateau));
    if (NULL == p) //Si il n'y a pas de place, le programme s'arrête
    {
        printf("Plus assez de mémoire pour l'allocation \n");
        exit(1);
    }
    p->n = n;
    p->tableau = (int *)malloc(p->n * p->n * sizeof(int));
    if (NULL == p->tableau) //Si il n'y a pas de place, le programme s'arrête
    {
        printf("Plus assez de mémoire pour l'allocation \n");
        exit(1);
    }
    return p; //retourner l'adresse de la variable
}

void detruirePlateau(plateau *p)
{
    assert(p->tableau != NULL);
    assert(p != NULL); //la fonction vérifie à l'aide de la fonction assert que le
    free(p->tableau);
    free(p); //la fonction libère la mémoire pointée par ce dernier
}

int getCase(plateau *p, int i, int j)
{
    assert(i >= VIDE && j >= VIDE && i < (p->n) && j < (p->n)); //la fonction vérifie à l'aide de la fonction assert que les 	numéros de ligne et colonne son valides
    return p->tableau[j + ((p->n) * i)];
}

void setCase(plateau *p, int i, int j, int val)
{
    assert(i >= 0 && j >= 0 && i < (p->n) && j < (p->n));
    assert(val >= -1 && val <= 1);
    p->tableau[j + ((p->n) * i)] = val;
}

void affichage(partie *pa)
{
    int i, j, l, k;
    int *p1 = pa->p->tableau;
    printf(" ");
    for (k = 0; k < pa->p->n; k++)
        printf("     %d    ", k + 1);
    printf("\n");
    for (i = 0; i < pa->p->n; i++)
    {
        for (l = 0; l < TAILLE_CARRE; l++)
        {
            if (l == 2)
                printf("%d", i + 1);
            else
                printf(" ");
            for (j = 0; j < pa->p->n; j++)
            {
                if (!((i + j) % 2))
                {
                    if (l == 2)
                    {
                        if (*p1 == JOUEUR1)
                            color_printf(WHITE, CYAN, "    ⚪️     ");
                        else if (*p1 == JOUEUR2)
                            color_printf(BLACK, CYAN, "    ⚫️     ");
                        else
                            color_printf(CYAN, CYAN, "          ");
                        p1++;
                    }
                    else
                        color_printf(CYAN, CYAN, "          ");
                }
                else
                {
                    if (l == 2)
                    {
                        if (*p1 == JOUEUR1)
                            color_printf(WHITE, RED, "    ⚪️     ");
                        else if (*p1 == JOUEUR2)
                            color_printf(BLACK, RED, "    ⚫️     ");
                        else
                            color_printf(RED, RED, "          ");
                        p1++;
                    }
                    else
                        color_printf(RED, RED, "          ");
                }
            }
            printf("\n");
        }
    }
}

void creerTableau(plateau *p)
{
    int i;
    for (i = 0; i < p->n * p->n; i++)
        p->tableau[i] = VIDE;
}

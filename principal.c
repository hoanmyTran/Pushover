#include "terminalCouleur.h"
#include "fonctions.h"

int main()
{
    clear_terminal();
    partie *pa = NULL;
    int i;
    do
    {
        i = menu(pa);
        if (i == NEW)
        {
            printf("Here we go!!!\n");
            pa = creerPartie();
            choisirPion(pa);
            jouer(pa);
        }
        if (i == RELOAD)
        {
            printf("Loading... Here we go!!!\n");
            pa = chargementPartie();
            jouer(pa);
        }
        if (i == SAVE)
        {
            sauvegardePartie(pa);
            printf("Saved.\n");
        }
        if (i == RETURN)
        {
            jouer(pa);
        }
    } while (i != QUIT);
    detruirePartie(pa);
    printf("See you again and have a good day!\n");
    return 0;
}

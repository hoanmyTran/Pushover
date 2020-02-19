/* PARTIE 4 */

#include "terminalCouleur.h"
#include "fonctions.h"

int sauvegardePartie(partie *pa)
{
    char tmp[] = "La";
    char tmp0[] = "taille";
    char tmp1[] = ":";
    char tmp2[] = ".";
    char tmp3[] = "Les";
    char tmp4[] = "joueurs";
    char tmp5[] = "actuels";
    char tmp6[] = "et";
    char tmp7[] = "Le";
    char tmp8[] = "pion";
    char tmp9[] = "courant";
    int *ptr = NULL;
    FILE *f = fopen("sauvegarde.txt", "wt");
    if (f == NULL)
    {
        fprintf(stderr, "Problème lors de l'ouverture du fichier");
        return NON;
    }
    fprintf(f, "%s ", tmp);
    fprintf(f, "%s ", tmp0);
    fprintf(f, "%s ", tmp1);
    fprintf(f, "%d ", pa->p->n);
    fprintf(f, "%s ", tmp2);
    fprintf(f, "%s ", tmp3);
    fprintf(f, "%s ", tmp4);
    fprintf(f, "%s ", tmp5);
    fprintf(f, "%s ", tmp1);
    fprintf(f, "%s ", pa->nomJoueur1);
    fprintf(f, "%s ", tmp6);
    fprintf(f, "%s ", pa->nomJoueur2);
    fprintf(f, "%s ", tmp2);
    fprintf(f, "%s ", tmp7);
    fprintf(f, "%s ", tmp8);
    fprintf(f, "%s ", tmp9);
    fprintf(f, "%s ", tmp1);
    fprintf(f, "%d ", pa->pionJoueurCourant);
    fprintf(f, "%s ", tmp2);
    for (ptr = pa->p->tableau; ptr < pa->p->tableau + (pa->p->n * pa->p->n); ptr++)
        fprintf(f, "%d ", *ptr);
    fclose(f);
    return OUI;
}

partie *chargementPartie()
{
    int i = 0;
    int taille = 0;
    char tmp[256];
    char reponse[REPONSE];
    partie *pa = (partie *)malloc(sizeof(partie));
    FILE *f = fopen("sauvegarde.txt", "rt");
    if (f == NULL)
    {
        fprintf(stderr, "Problème lors de l'ouverture du fichier");
        exit(1);
    }
    for (i = 0; i < 3; i++)
        fscanf(f, "%s", tmp);
    fscanf(f, "%d", &taille);
    if (taille < TAILLE_PLATEAU_MIN || taille > TAILLE_PLATEAU_MAX)
    {
        fclose(f);
        printf("Il n'y a pas de sauvegarde, voulez-vous créer une nouvelle partie? ");
        scanf("%s", reponse);
        lowtoup(reponse);
        if (!strcmp("OUI", reponse))
        {
            printf("OK!!! Here we go!!!\n");
            pa = creerPartie();
            choisirPion(pa);
            jouer(pa);
            sauvegardePartie(pa);
            detruirePartie(pa);
        }
        else
        {
            printf("Ah dommage\n");
            exit(1);
        }
    }
    else
    {
        taillePlateau(pa, taille);
        for (i = 0; i < 5; i++)
            fscanf(f, "%s", tmp);
        fscanf(f, "%s", pa->nomJoueur1);
        fscanf(f, "%s", tmp);
        fscanf(f, "%s", pa->nomJoueur2);
        for (i = 0; i < 5; i++)
            fscanf(f, "%s", tmp);
        fscanf(f, "%d", &(pa->pionJoueurCourant));
        fscanf(f, "%s", tmp);
        for (i = 0; i < pa->p->n * pa->p->n; i++)
            fscanf(f, "%d", &pa->p->tableau[i]);
        fclose(f);
    }
    return pa;
}

int menu(partie *pa)
{
    char reponse;
    do
    {
        printf("- Quitter le jeu/programme (Q)\n");
        printf("- Commencer une nouvelle partie (N)\n");
        printf("- Charger la dernière partie sauvegardée (C)\n");
        if (pa != NULL)
        {
            printf("- Sauvegarder la partie courante (S)\n");
            printf("- Reprendre la partie en cours (R)\n");
        }
        scanf("%s", &reponse);
        lowtoup(&reponse);
    } while (reponse != 'Q' && reponse != 'N' && reponse != 'C' && reponse != 'S' && reponse != 'R');
    switch (reponse)
    {
    case 'Q':
        return QUIT;
    case 'N':
        return NEW;
    case 'C':
        return RELOAD;
    case 'S':
        return SAVE;
    case 'R':
        return RETURN;
    default:
        return QUIT;
    }
}

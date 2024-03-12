#include "game_structures.h"
#include "lecteur_csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Token Github: 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

struct tuile_s pioche[72];
struct tuile_s grille[72];

int main(int argc, char * argv[])
{
    // Init/Melange de la pioche
    parseur_csv("tuiles_base_simplifiees.csv", pioche);
    
    // Debug tuile
    //afficher_tuile(pioche[71]);

    // Affichage tuile initiale
    grille[0].id = 0
    grille[0].cotes[0] = 'R';
    grille[0].cotes[1] = 'V';
    grille[0].cotes[2] = 'R';
    grille[0].cotes[3] = 'P';
    grille[0].centre = 'R';
    grille[0].c.x = 5;
    grille[0].c.y = 5;
    system("clear");
    affichage(grille, 5, 5);

    printf("\nFIN de la partie\n");
    return 0;
}

void afficher_tuile(struct tuile_s t){
    printf("\t%c\n%c\t%c\t%c\n\t%c\n", t.cotes[1], t.cotes[0], t.centre, t.cotes[2], t.cotes[3]);
}
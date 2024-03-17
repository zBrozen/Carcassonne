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
    system("clear");
    // Init Pioche/Melange
    parseur_csv("tuiles_base_simplifiees.csv", pioche);

    // Debug affichage tuile
    //afficher_tuile(pioche[71]);

    affichage(grille, 0, 0);
    printf("FIN de partie\n");
    return 0;
}

void afficher_tuile(struct tuile_s t){
    // Fonction de debug de tuile
    system("clear");
    printf("\t%c\n%c\t%c\t%c\n\t%c\n", t.cotes[1], t.cotes[0], t.centre, t.cotes[2], t.cotes[3]);
}
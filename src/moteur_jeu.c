#include "game_structures.h"
#include "lecteur_csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Token Github: 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

#define G 72 // Taille de la grille

struct tuile_s pioche[72];
struct tuile_s grille[G][G];

void init_grille(struct tuile_s grille[72][72]){
    for(int i = 0; i < G; i++){
        for(int j = 0; j < G; j++){
            grille[i][j].id = -1;
        }
    }
}

int main(int argc, char * argv[])
{
    system("clear");
    // Init Pioche/Melange et grille
    parseur_csv("tuiles_base_simplifiees.csv", pioche);
    init_grille(grille);

    // Debug affichage tuile
    //afficher_tuile(pioche[71]);

    // Debug affichage grille avec tuile
    grille[7][7].id = pioche[0].id;
    grille[7][7].cotes[0] = pioche[0].cotes[0];
    grille[7][7].cotes[1] = pioche[0].cotes[1];
    grille[7][7].cotes[2] = pioche[0].cotes[2];
    grille[7][7].cotes[3] = pioche[0].cotes[3];
    grille[7][7].centre = pioche[0].centre;

    affichage(grille, 0, 0);
    printf("FIN de partie\n");
    return 0;
}

void afficher_tuile(struct tuile_s t){
    // Fonction de debug de tuile
    system("clear");
    printf("\t%c\n%c\t%c\t%c\n\t%c\n", t.cotes[1], t.cotes[0], t.centre, t.cotes[2], t.cotes[3]);
}
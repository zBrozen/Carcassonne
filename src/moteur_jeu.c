#include "game_structures.h"
#include "lecteur_csv.h"
#include "affichage.h"
#include "actions.h"
#include "score.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Token Github: 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

#define G 72 // Taille de la grille

struct tuile_s pioche[72];
struct tuile_s tuiles_placees[72];
struct tuile_s grille[G][G];

void init_grille(struct tuile_s grille[72][72]){
    for(int i = 0; i < G; i++){
        for(int j = 0; j < G; j++){
            grille[i][j].id = -1;
        }
    }
}

void init_tuiles_placees(struct tuile_s tuiles_placees[72]){
    for(int i = 0; i < 72; i++)
        tuiles_placees[i].id = -1;
}

void init_joueur(struct joueur j, int id, int ia){
    j.id = id;
    j.nbm = 8;
    j.ia = ia;
}

int main(int argc, char * argv[])
{
    system("clear");
    // Init Pioche/Melange et grille
    parseur_csv("tuiles_base_simplifiees.csv", pioche);
    init_grille(grille);
    init_tuiles_placees(tuiles_placees);

    // Debug affichage tuile
    // for(int i = 0; i < 72; i++)
    // afficher_tuile(pioche[i]);

    // Debug affichage grille avec tuile
    grille[3][3].id = pioche[0].id;
    grille[3][3].cotes[0] = pioche[0].cotes[0];
    grille[3][3].cotes[1] = pioche[0].cotes[1];
    grille[3][3].cotes[2] = pioche[0].cotes[2];
    grille[3][3].cotes[3] = pioche[0].cotes[3];
    grille[3][3].centre = pioche[0].centre;

    grille[3][3].c.x = 3;
    grille[3][3].c.y = 3;

    struct joueur j1;
    init_joueur(j1, 0, 0);
    
    tuiles_placees[0].id = pioche[0].id;
    tuiles_placees[0].cotes[0] = pioche[0].cotes[0];
    tuiles_placees[0].cotes[1] = pioche[0].cotes[1];
    tuiles_placees[0].cotes[2] = pioche[0].cotes[2];
    tuiles_placees[0].cotes[3] = pioche[0].cotes[3];
    tuiles_placees[0].centre = pioche[0].centre;
    tuiles_placees[0].c.x = 3;
    tuiles_placees[0].c.y = 3;

    int index_pioche = 1;
    while(index_pioche < 72){
        tour(j1, pioche, grille, tuiles_placees, index_pioche);
        index_pioche++;
    }


    printf("FIN de partie\n");
    return 0;
}
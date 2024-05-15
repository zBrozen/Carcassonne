#include "game_structures.h"
#include "lecteur_csv.h"
#include "affichage.h"
#include "actions.h"
#include "score.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Token Github: 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

#define G 143 // Taille de la grille

struct tuile_s pioche[72];
struct tuile_s tuiles_placees[72];
struct tuile_s grille[G][G];

void init_grille(struct tuile_s grille[G][G]){
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

struct joueur * init_joueur(int nb_ia, int nb_joueurs){
    struct joueur *j;
    int n, joueur;
    j = malloc(nb_joueurs * sizeof(struct joueur));

    if(nb_joueurs > nb_ia) n = nb_joueurs-nb_ia;
    else n = nb_ia - nb_joueurs;
    for(joueur = 0; joueur < n; joueur++){
        j[joueur].id = joueur;
        j[joueur].nbm = 8;
        j[joueur].ia = 0;
        j[joueur].score = 0;
    }
    for(int ia = joueur; ia < nb_joueurs+nb_ia; ia++){
        j[ia].id = ia;
        j[ia].nbm = 8;
        j[ia].ia = 1;
        j[ia].score = 0;
    }
    return j;
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

    // Init tuile initiale
    grille[71][71].id = pioche[0].id;
    grille[71][71].cotes[0] = pioche[0].cotes[0];
    grille[71][71].cotes[1] = pioche[0].cotes[1];
    grille[71][71].cotes[2] = pioche[0].cotes[2];
    grille[71][71].cotes[3] = pioche[0].cotes[3];
    grille[71][71].centre = pioche[0].centre;
    grille[71][71].c.x = 71;
    grille[71][71].c.y = 71;
    // Init meeple
    grille[71][71].m.id = -1;
    
    tuiles_placees[0].id = pioche[0].id;
    tuiles_placees[0].cotes[0] = pioche[0].cotes[0];
    tuiles_placees[0].cotes[1] = pioche[0].cotes[1];
    tuiles_placees[0].cotes[2] = pioche[0].cotes[2];
    tuiles_placees[0].cotes[3] = pioche[0].cotes[3];
    tuiles_placees[0].centre = pioche[0].centre;
    tuiles_placees[0].c.x = 71;
    tuiles_placees[0].c.y = 71;

    int nb_joueurs, nb_ia = 0, joueur_actuel = 0;
    printf("Entrer le nombre de joueurs: ");
    scanf("%d", &nb_joueurs);
    clearBuffer();
    struct joueur * j = init_joueur(nb_ia, nb_joueurs);

    int index_pioche = 1;
    while(index_pioche < 72){
        tour(j, pioche, grille, tuiles_placees, index_pioche, nb_joueurs+nb_ia, joueur_actuel);
        index_pioche++;
        joueur_actuel = (joueur_actuel + 1) % (nb_joueurs+nb_ia);
    }

    // Score final
    


    printf("FIN de partie\n");
    return 0;
}
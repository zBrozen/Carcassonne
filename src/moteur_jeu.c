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

void init_joueur(struct joueur j[5], int nb_ia, int nb_joueurs){
    // struct joueur *j;
    // j = malloc((nb_joueurs+nb_ia) * sizeof(struct joueur));

    for(int joueur = 0; joueur < nb_joueurs; joueur++){
        j[joueur].id = joueur;
        j[joueur].nbm = 7;
        j[joueur].ia = 0;
        j[joueur].score = 0;
    }
    for(int ia = nb_joueurs; ia < nb_joueurs+nb_ia; ia++){
        j[ia].id = ia;
        j[ia].nbm = 7;
        j[ia].ia = 1;
        j[ia].score = 0;
    }
}

int main(int argc, char * argv[])
{
    system("clear");
    // Init Pioche/Melange et grille
    parseur_csv("tuiles_base_simplifiees.csv", pioche);
    init_grille(grille);
    init_tuiles_placees(tuiles_placees);

    // Init tuile initiale dans grille et dans la liste tuile_placees
    grille[71][71].id = pioche[0].id;
    grille[71][71].cotes[0] = pioche[0].cotes[0];
    grille[71][71].cotes[1] = pioche[0].cotes[1];
    grille[71][71].cotes[2] = pioche[0].cotes[2];
    grille[71][71].cotes[3] = pioche[0].cotes[3];
    grille[71][71].centre = pioche[0].centre;
    grille[71][71].c.x = 71;
    grille[71][71].c.y = 71;
    grille[71][71].m.id = -1; // Init meeple
    
    tuiles_placees[0].id = pioche[0].id;
    tuiles_placees[0].cotes[0] = pioche[0].cotes[0];
    tuiles_placees[0].cotes[1] = pioche[0].cotes[1];
    tuiles_placees[0].cotes[2] = pioche[0].cotes[2];
    tuiles_placees[0].cotes[3] = pioche[0].cotes[3];
    tuiles_placees[0].centre = pioche[0].centre;
    tuiles_placees[0].c.x = 71;
    tuiles_placees[0].c.y = 71;

    int nb_joueurs, nb_ia, joueur_actuel = 0;
    printf("Entrer le nombre de joueurs: ");
    scanf("%d", &nb_joueurs);
    clearBuffer();
    printf("Entrer le nombre d'ia: ");
    scanf("%d", &nb_ia);
    clearBuffer();
    struct joueur j[nb_ia+nb_joueurs];
    init_joueur(j, nb_ia, nb_joueurs);
    printf("info ia: %d", j[1].ia);

    int index_pioche = 1;
    while(index_pioche < 72){
        tour(j, pioche, grille, tuiles_placees, index_pioche, nb_joueurs+nb_ia, joueur_actuel);
        index_pioche++;
        joueur_actuel = (joueur_actuel + 1) % (nb_joueurs+nb_ia);
        printf("DEBUG JOUEUR ID: %d\n", joueur_actuel);
    }

    // Score final
    printf("\e[45m FIN DE TOUR FINAL\e[0m\n");
    int score = 1;
    int pion[5] = {0, 0, 0, 0, 0};
    int maxi_pion;
    for(int tuile = 0; tuile < 72; tuile++){
        printf("\e[44mTuile %d\e[0m\n", tuile);
        // Check Abbaye
        if(grille[tuiles_placees[tuile].c.y][tuiles_placees[tuile].c.x].m.id != -1 && tuiles_placees[tuile].centre == 'a'){
            score = score_abbaye(grille, tuiles_placees[tuile].c.x, tuiles_placees[tuile].c.y);
            j[grille[tuiles_placees[tuile].c.y][tuiles_placees[tuile].c.x].m.id].score += score;
            printf("DANS ABBAYE Score: %d\n", score);
        }
        
        else if(grille[tuiles_placees[tuile].c.y][tuiles_placees[tuile].c.x].m.id != -1 &&
        grille[tuiles_placees[tuile].c.y][tuiles_placees[tuile].c.x].traitee[grille[tuiles_placees[tuile].c.y][tuiles_placees[tuile].c.x].m.cotes] != -1){
            // Reset variables
            score = 1;
            for(int i = 0; i < 5; i++) pion[i] = 0;
            maxi_pion = 0;
            parcours_structure(grille, tuiles_placees[tuile], tuiles_placees[tuile].cotes[grille[tuiles_placees[tuile].c.y][tuiles_placees[tuile].c.x].m.cotes], grille[tuiles_placees[tuile].c.y][tuiles_placees[tuile].c.x].m.cotes, &score, pion);

            lock_structure(grille, tuiles_placees, -1);
            // Def maxi_pion
            for(int joueur = 0; joueur < nb_joueurs+nb_ia; joueur++){
                if (maxi_pion < pion[joueur]){
                    maxi_pion = pion[joueur];
                }
            }
            if(maxi_pion > 0){
                for(int joueur = 0; joueur < nb_joueurs+nb_ia; joueur++){
                    if(pion[joueur] == maxi_pion){
                        j[joueur].score += score;
                        printf("GAIN DE POINTS pour j%d: %d avec +%d\n", joueur, j[joueur].score, score);
                    }
                }
            }
        }
    }
    for(int joueur = 0; joueur < nb_joueurs+nb_ia; joueur++){
        printf("SCORE FINAL DE J%d: %d\n", joueur, j[joueur].score);
    }


    printf("FIN de partie\n");
    return 0;
}
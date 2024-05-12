#include "game_structures.h"
#include <stdio.h>
#include <stdlib.h>

#define G 143

void reset_traitee(struct tuile_s grille[G][G], struct tuile_s tuiles_placees[72]){
    for(int i = 0; i < 72 && tuiles_placees[i].id != -1; i++){
        if(grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[0] == 1){
            grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[0] = 0;
        }
        if(grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[1] == 1){
            grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[1] = 0;
        }
        if(grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[2] == 1){
            grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[2] = 0;
        }
        if(grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[3] == 1){
            grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[3] = 0;
        }
        if(grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[4] == 1){
            grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[4] = 0;
        }
        
    }
}

void lock_structure(struct tuile_s grille[G][G], struct tuile_s tuiles_placees[72]){
    for(int i = 0; i < 72 && tuiles_placees[i].id != -1; i++){
        if(grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[0] == 1){
            grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[0] = -1;
        }
        if(grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[1] == 1){
            grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[1] = -1;
        }
        if(grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[2] == 1){
            grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[2] = -1;
        }
        if(grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[3] == 1){
            grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[3] = -1;
        }
        if(grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[4] == 1){
            grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[4] = -1;
        }
    }
}

int parcours_structure(struct tuile_s grille[G][G], struct tuile_s tuile_actuelle, char structure, int position){
    /* Fonction qui effectue un parcours récursif dans une structure.
    Grille permet de naviguer en définissant la tuile suivante ; On précise la structure qu'on explore, et la position dans une tuile (0..5) */

    printf("\nDebut de la fonction: tuile: %d, position: %d\n", tuile_actuelle.id, position);

    // Variables qui définit si la structure est ouverte ou non
    int res_centre = 0, res0 = 0, res1 = 0, res2 = 0, res3 = 0;

    // Défini la tuile actuelle comme traitee
    grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[position] = 1;

    // Cas où l'on se situe sur le bord d'une tuile: regarde vers le centre et l'extérieur
    if(position != 4){
        printf("Position != 4\n");

        // Vérifie si le centre est déjà exploré et si il est compatible avec la structure (cas où f le village = r pris en compte)
        if(grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[4] != 1 &&
        grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[4] != -1){
            printf("Centre0 -> centre non traitee\n");
            // Centre compatible -> appel récursif pos = centre
            if(tuile_actuelle.centre == structure ||
            (tuile_actuelle.centre == 'b' && structure == 'v')){
                printf("Centre1 ok\n");
                res_centre = parcours_structure(grille, tuile_actuelle, structure, 4);
            }
            // Cul de sac pour ville
            if((tuile_actuelle.cotes[position] == 'v' ||
            tuile_actuelle.cotes[position] == 'b') &&
            tuile_actuelle.centre == 'p'){
                printf("Centre2 ok\n");
                res_centre = 1;
            }
            // Cas de route qui fait office d'entrée
            if(tuile_actuelle.cotes[position] == 'r' && 
            (tuile_actuelle.centre == 'v' || tuile_actuelle.centre == 'b' ||
            tuile_actuelle.centre == 'f' || tuile_actuelle.centre == 'a')){
                printf("Centre3 ok\n");
                res_centre = 1;
            }

        }
        else{
            printf("Centre0 -> centre déjà traitee\n");
        }
        
        // Vérifie l'état de la tuile extérieure 
        switch(position){
            // Vérif dans chaque cas si les tuiles extérieures existes et si elles sont non visités (pas besoin de vérification de compatibilité avec la tuile voisine)
            case 0:
                if(tuile_actuelle.c.x - 1 >= 0 && grille[tuile_actuelle.c.y][tuile_actuelle.c.x - 1].id != -1){
                    if(grille[tuile_actuelle.c.y][tuile_actuelle.c.x - 1].traitee[2] == 0){
                        printf("case 0\n");
                        res0 = parcours_structure(grille, grille[tuile_actuelle.c.y][tuile_actuelle.c.x - 1], structure, 2);
                    }
                    // Cas où la case est traitee
                    else{
                        printf("case 0.1\n");
                        res0 = 1;
                    }
                }
                else{
                    res0 = -1;
                    printf("else case 0: %d < %d && %d != -1\n", tuile_actuelle.c.x - 1, G, grille[tuile_actuelle.c.y][tuile_actuelle.c.x - 1].id);
                } 
                break;
            case 1:
                if(tuile_actuelle.c.y - 1 >= 0 && grille[tuile_actuelle.c.y - 1][tuile_actuelle.c.x].id != -1){
                    if(grille[tuile_actuelle.c.y - 1][tuile_actuelle.c.x].traitee[3] == 0){
                        printf("case 1\n");
                        res0 = parcours_structure(grille, grille[tuile_actuelle.c.y - 1][tuile_actuelle.c.x], structure, 3);
                    }
                    // Cas où la case est traitee
                    else{
                        printf("case 1.1\n");
                        res0 = 1;
                    }
                } 
                else{
                    res0 = -1;
                    printf("else case 1: %d < %d && %d != -1\n", tuile_actuelle.c.y - 1, G, grille[tuile_actuelle.c.y - 1][tuile_actuelle.c.x].id);
                } 
                break;
            case 2:
                if(tuile_actuelle.c.x + 1 < G && grille[tuile_actuelle.c.y][tuile_actuelle.c.x + 1].id != -1){
                    if(grille[tuile_actuelle.c.y][tuile_actuelle.c.x + 1].traitee[0] == 0){
                        printf("case 2\n");
                        res0 = parcours_structure(grille, grille[tuile_actuelle.c.y][tuile_actuelle.c.x + 1], structure, 0);
                    }
                    // Cas où la case est traitee
                    else{
                        printf("case 2.1\n");
                        res0 = 1;
                    }
                }
                else{
                    res0 = -1; 
                    printf("else case 2: %d < %d && %d != -1\n", tuile_actuelle.c.x + 1, G, grille[tuile_actuelle.c.y][tuile_actuelle.c.x + 1].id);
                } 
                break;
            case 3:
                if(tuile_actuelle.c.y + 1 < G && grille[tuile_actuelle.c.y + 1][tuile_actuelle.c.x].id != -1){
                    if(grille[tuile_actuelle.c.y + 1][tuile_actuelle.c.x].traitee[1] == 0){
                        printf("case 3\n");
                        res0 = parcours_structure(grille, grille[tuile_actuelle.c.y + 1][tuile_actuelle.c.x], structure, 1);
                    }
                    // Cas où la case est traitee
                    else{
                        printf("case 3.1\n");
                        res0 = 1;
                    }
                }
                else{
                    res0 = -1;
                    printf("else case 3: %d < %d && %d != -1\n", tuile_actuelle.c.y + 1, G, grille[tuile_actuelle.c.y + 1][tuile_actuelle.c.x].id);
                } 
                break;
            default:
                printf("Erreur position: une valeur innatendu a été entrée dans l'appel de la fonction\n");
                break;
        }
        
    }

    // Cas où l'on se situe au centre de la tuile
    else{
        printf("On est au centre\n");

        // Vérifie l'état des bords de la tuile actuelle et leur compatibilité
        if(grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[0] == 0 &&
        (tuile_actuelle.cotes[0] == structure ||
        (tuile_actuelle.cotes[0] == 'b' && structure == 'v'))){
            printf("bord gauche\n");
            res0 = parcours_structure(grille, tuile_actuelle, structure, 0);
        }
        if(grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[1] == 0 &&
        (tuile_actuelle.cotes[1] == structure ||
        (tuile_actuelle.cotes[1] == 'b' && structure == 'v'))){
            printf("bord haut\n");
            res1 = parcours_structure(grille, tuile_actuelle, structure, 1);
        }
        if(grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[2] == 0 &&
        (tuile_actuelle.cotes[2] == structure ||
        (tuile_actuelle.cotes[2] == 'b' && structure == 'v'))){
            printf("bord droit\n");
            res2 = parcours_structure(grille, tuile_actuelle, structure, 2);
        }
        if(grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[3] == 0 &&
        (tuile_actuelle.cotes[3] == structure ||
        (tuile_actuelle.cotes[3] == 'b' && structure == 'v'))){
            printf("bord bas\n");
            res3 = parcours_structure(grille, tuile_actuelle, structure, 3);
        }

        // Parcours fermé
        if(res0 != -1 && res1 != -1 && res2 != -1 && res3 != -1){
            printf("Parcours fermé centre\n");
            return 1;
        }
        // Parcours ouvert
        else{
            printf("Parcours ouvert centre\n");
            return -1;
        } 
    }


    printf("Sorties des différentes conditions -> res_centre = %d, res0 = %d, res1 = %d, res2 = %d, res3 = %d\n", res_centre, res0, res1, res2, res3);
    // Cas où la structure est ouverte (vue centre)
    if (res_centre == -1 || res0 == -1 || res1 == -1 || res2 == -1 || res3 == -1) {
        printf("Sortie ouverte\n");
        return -1;
    }

    // Sortie si fermée
    printf("Sortie fermée\n");
    return 1;
}

int poser_pion(struct joueur j, struct tuile_s grille[G][G], struct tuile_s tuile, int cotes, int res){
    /* Fonction permettant de déterminer si un pion peut être posée, donc si aucun autre n'est voisin de la tuile actuelle 
    Prend en paramètre le cotes qui déterminera le type de structure sur laquelle le pion doit être posé*/

    int sens = 0; // Indique le sens dans lequel parcourir la tuile (vers le centre: 0, vers l'extérieur: 1, vers un bord: 2)
    // Conditions qui compare le type de structure entre le bord ou le centre, avec une autre tuile, le centre, ou un bord de tuile
    if(cotes == 3 && tuile.traitee[3] == 0){
        if(sens == 1){
            if(tuile.cotes[3] == grille[tuile.c.y+1][tuile.c.x].cotes[1]){
                tuile.traitee[3] = 1;
                // res = poser_pion(j, grille, grille[tuile.c.y+1][tuile.c.x], 1, res);
            }
        }
        // else if(sens == 0){
        //     if(tuile.cotes[3] == tuile.centre){

        //     }
        // }
    }
    return res;
    // if(cotes == 1){
    //     if(tuile.cotes[1] == grille[tuile.c.y-1][tuile.c.x].cotees[3])
    // }
    
    // if(cotes == 2){
    //     if(tuile.cotes[2] == grille[tuile.c.y][tuile.c.x+1].cotees[0])
    // }
    // if(cotes == 0){
    //     if(tuile.cotes[0] == grille[tuile.c.y][tuile.c.x-1].cotees[2])
    // }
}

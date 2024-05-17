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

void lock_structure(struct tuile_s grille[G][G], struct tuile_s tuiles_placees[72], int value){
    /* Permet de vérouiller une structure avec value qui prend : -1 valeur lock et -2 valeur intermédiaire*/
    for(int i = 0; i < 72 && tuiles_placees[i].id != -1; i++){
        if(grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[0] == 1 || grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[0] == -2){
            grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[0] = value;
        }
        if(grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[1] == 1 || grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[1] == -2){
            grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[1] = value;
        }
        if(grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[2] == 1 || grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[2] == -2){
            grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[2] = value;
        }
        if(grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[3] == 1 || grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[3] == -2){
            grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[3] = value;
        }
        if(grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[4] == 1 || grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[4] == -2){
            grille[tuiles_placees[i].c.y][tuiles_placees[i].c.x].traitee[4] = value;
        }
    }
}

int parcours_structure(struct tuile_s grille[G][G], struct tuile_s tuile_actuelle, char structure, int position, int * score, int * pion, int score_final){
    /* Fonction qui effectue un parcours récursif dans une structure.
    Grille permet de naviguer en définissant la tuile suivante ; On précise la structure qu'on explore, et la position dans une tuile (0..5) */

    // printf("\nDebut de la fonction: tuile: %d, position: %d\n", tuile_actuelle.id, position);

    // printf("DEBUG Score: %d\n", *score);

    // Verif pion (si pion existe et si je suis sur la position du pion)
    if(grille[tuile_actuelle.c.y][tuile_actuelle.c.x].m.id != -1 && grille[tuile_actuelle.c.y][tuile_actuelle.c.x].m.cotes == position){
        // printf("\e[45mPion trouvé ! Utilisateur : %d\e[0m\n", grille[tuile_actuelle.c.y][tuile_actuelle.c.x].m.id);
        pion[grille[tuile_actuelle.c.y][tuile_actuelle.c.x].m.id]++; // Incrémente le nb de pion d'un joueur de 1
    }

    // Variables qui définit si la structure est ouverte ou non
    int res_centre = 0, res0 = 0, res1 = 0, res2 = 0, res3 = 0;

    // Défini la tuile actuelle comme traitee
    grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[position] = 1;

    // Cas où l'on se situe sur le bord d'une tuile: regarde vers le centre et l'extérieur
    if(position != 4){
        // printf("Position != 4\n");

        // Vérifie si le centre est déjà exploré et si il est compatible avec la structure (cas où f le village = r pris en compte)
        if(grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[4] != 1 &&
        grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[4] != -1){
            // printf("Centre0 -> centre non traitee\n");
            // Centre compatible -> appel récursif pos = centre
            if(tuile_actuelle.centre == structure ||
            (tuile_actuelle.centre == 'b' && structure == 'v') ||
            (tuile_actuelle.centre == 'v' && structure == 'b')){
                // printf("Centre1 ok\n");
                res_centre = parcours_structure(grille, tuile_actuelle, structure, 4, score, pion, score_final);
            }
            // Cul de sac pour ville
            if((tuile_actuelle.cotes[position] == 'v' ||
            tuile_actuelle.cotes[position] == 'b') &&
            tuile_actuelle.centre == 'p'){
                // printf("Centre2 ok\n");
                res_centre = 1;
            }
            // Cas de route qui fait office d'entrée
            if(tuile_actuelle.cotes[position] == 'r' && 
            (tuile_actuelle.centre == 'v' || tuile_actuelle.centre == 'b' ||
            tuile_actuelle.centre == 'f' || tuile_actuelle.centre == 'a')){
                // printf("Centre3 ok\n");
                res_centre = 1;
            }

        }
        // else{
        //     printf("Centre0 -> centre déjà traitee\n");
        // }
        
        // Vérifie l'état de la tuile extérieure 
        switch(position){
            // Vérif dans chaque cas si les tuiles extérieures existes et si elles sont non visités (pas besoin de vérification de compatibilité avec la tuile voisine)
            case 0:
                if(tuile_actuelle.c.x - 1 >= 0 && grille[tuile_actuelle.c.y][tuile_actuelle.c.x - 1].id != -1){
                    if(grille[tuile_actuelle.c.y][tuile_actuelle.c.x - 1].traitee[2] == 0 || grille[tuile_actuelle.c.y][tuile_actuelle.c.x - 1].traitee[2] == -2){
                        // printf("case 0\n");
                        // Conditions score
                        if (grille[tuile_actuelle.c.y][tuile_actuelle.c.x - 1].traitee[0] != 1 &&
                        grille[tuile_actuelle.c.y][tuile_actuelle.c.x - 1].traitee[1] != 1 &&
                        grille[tuile_actuelle.c.y][tuile_actuelle.c.x - 1].traitee[2] != 1 &&
                        grille[tuile_actuelle.c.y][tuile_actuelle.c.x - 1].traitee[3] != 1 &&
                        grille[tuile_actuelle.c.y][tuile_actuelle.c.x - 1].traitee[4] != 1){
                            if(grille[tuile_actuelle.c.y][tuile_actuelle.c.x - 1].cotes[2] == 'v' && score_final == 0) *score += 2;
                            else if(grille[tuile_actuelle.c.y][tuile_actuelle.c.x - 1].cotes[2] == 'b' && score_final == 0) *score += 4;
                            else (*score)++;
                        }
                        res0 = parcours_structure(grille, grille[tuile_actuelle.c.y][tuile_actuelle.c.x - 1], structure, 2, score, pion, score_final);
                    }
                    // Cas où la case est traitee
                    else{
                        // printf("case 0.1\n");
                        res0 = 1;
                    }
                }
                else{
                    res0 = -1;
                    // printf("else case 0: %d < %d && %d != -1\n", tuile_actuelle.c.x - 1, G, grille[tuile_actuelle.c.y][tuile_actuelle.c.x - 1].id);
                } 
                break;
            case 1:
                if(tuile_actuelle.c.y - 1 >= 0 && grille[tuile_actuelle.c.y - 1][tuile_actuelle.c.x].id != -1){
                    if(grille[tuile_actuelle.c.y - 1][tuile_actuelle.c.x].traitee[3] == 0 || grille[tuile_actuelle.c.y - 1][tuile_actuelle.c.x].traitee[3] == -2){
                        // printf("case 1\n");
                        // Conditions score
                        if (grille[tuile_actuelle.c.y - 1][tuile_actuelle.c.x].traitee[0] != 1 &&
                        grille[tuile_actuelle.c.y - 1][tuile_actuelle.c.x].traitee[1] != 1 &&
                        grille[tuile_actuelle.c.y - 1][tuile_actuelle.c.x].traitee[2] != 1 &&
                        grille[tuile_actuelle.c.y - 1][tuile_actuelle.c.x].traitee[3] != 1 &&
                        grille[tuile_actuelle.c.y - 1][tuile_actuelle.c.x].traitee[4] != 1){
                            if(grille[tuile_actuelle.c.y - 1][tuile_actuelle.c.x].cotes[3] == 'v' && score_final == 0) *score += 2;
                            else if(grille[tuile_actuelle.c.y - 1][tuile_actuelle.c.x].cotes[3] == 'b' && score_final == 0) *score += 4;
                            else (*score)++;
                        }
                        res0 = parcours_structure(grille, grille[tuile_actuelle.c.y - 1][tuile_actuelle.c.x], structure, 3, score, pion, score_final);
                    }
                    // Cas où la case est traitee
                    else{
                        // printf("case 1.1\n");
                        res0 = 1;
                    }
                } 
                else{
                    res0 = -1;
                    // printf("else case 1: %d < %d && %d != -1\n", tuile_actuelle.c.y - 1, G, grille[tuile_actuelle.c.y - 1][tuile_actuelle.c.x].id);
                } 
                break;
            case 2:
                if(tuile_actuelle.c.x + 1 < G && grille[tuile_actuelle.c.y][tuile_actuelle.c.x + 1].id != -1){
                    if(grille[tuile_actuelle.c.y][tuile_actuelle.c.x + 1].traitee[0] == 0 || grille[tuile_actuelle.c.y][tuile_actuelle.c.x + 1].traitee[0] == -2){
                        // printf("case 2\n");
                        // Conditions score
                        if (grille[tuile_actuelle.c.y][tuile_actuelle.c.x + 1].traitee[0] != 1 &&
                        grille[tuile_actuelle.c.y][tuile_actuelle.c.x + 1].traitee[1] != 1 &&
                        grille[tuile_actuelle.c.y][tuile_actuelle.c.x + 1].traitee[2] != 1 &&
                        grille[tuile_actuelle.c.y][tuile_actuelle.c.x + 1].traitee[3] != 1 &&
                        grille[tuile_actuelle.c.y][tuile_actuelle.c.x + 1].traitee[4] != 1){
                            if(grille[tuile_actuelle.c.y][tuile_actuelle.c.x + 1].cotes[0] == 'v' && score_final == 0) *score += 2;
                            else if(grille[tuile_actuelle.c.y][tuile_actuelle.c.x + 1].cotes[0] == 'b' && score_final == 0) *score += 4;
                            else (*score)++;
                        }
                        res0 = parcours_structure(grille, grille[tuile_actuelle.c.y][tuile_actuelle.c.x + 1], structure, 0, score, pion, score_final);
                    }
                    // Cas où la case est traitee
                    else{
                        // printf("case 2.1\n");
                        res0 = 1;
                    }
                }
                else{
                    res0 = -1; 
                    // printf("else case 2: %d < %d && %d != -1\n", tuile_actuelle.c.x + 1, G, grille[tuile_actuelle.c.y][tuile_actuelle.c.x + 1].id);
                } 
                break;
            case 3:
                if(tuile_actuelle.c.y + 1 < G && grille[tuile_actuelle.c.y + 1][tuile_actuelle.c.x].id != -1){
                    if(grille[tuile_actuelle.c.y + 1][tuile_actuelle.c.x].traitee[1] == 0 || grille[tuile_actuelle.c.y + 1][tuile_actuelle.c.x].traitee[1] == -2){
                        // printf("case 3\n");
                        // Conditions score
                        if (grille[tuile_actuelle.c.y + 1][tuile_actuelle.c.x].traitee[0] != 1 &&
                        grille[tuile_actuelle.c.y + 1][tuile_actuelle.c.x].traitee[1] != 1 &&
                        grille[tuile_actuelle.c.y + 1][tuile_actuelle.c.x].traitee[2] != 1 &&
                        grille[tuile_actuelle.c.y + 1][tuile_actuelle.c.x].traitee[3] != 1 &&
                        grille[tuile_actuelle.c.y + 1][tuile_actuelle.c.x].traitee[4] != 1){
                            if(grille[tuile_actuelle.c.y + 1][tuile_actuelle.c.x].cotes[1] == 'v' && score_final == 0){
                                // printf("Score avant %d\n", *score);
                                *score += 2;
                                // printf("Parcours score ville : %d\n", *score);
                            } 
                            else if(grille[tuile_actuelle.c.y + 1][tuile_actuelle.c.x].cotes[1] == 'b' && score_final == 0) *score += 4;
                            else (*score)++;
                        }
                        res0 = parcours_structure(grille, grille[tuile_actuelle.c.y + 1][tuile_actuelle.c.x], structure, 1, score, pion, score_final);
                    }
                    // Cas où la case est traitee
                    else{
                        // printf("case 3.1\n");
                        res0 = 1;
                    }
                }
                else{
                    res0 = -1;
                    // printf("else case 3: %d < %d && %d != -1\n", tuile_actuelle.c.y + 1, G, grille[tuile_actuelle.c.y + 1][tuile_actuelle.c.x].id);
                } 
                break;
            default:
                printf("Erreur position: une valeur innatendu a été entrée dans l'appel de la fonction\n");
                break;
        }
        
    }

    // Cas où l'on se situe au centre de la tuile
    else{
        // printf("On est au centre\n");

        // Vérifie l'état des bords de la tuile actuelle et leur compatibilité
        // printf("Traitee gauche: %d\n", grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[0]);
        if((grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[0] == 0 ||
        grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[0] == -2) &&
        (tuile_actuelle.cotes[0] == structure ||
        (tuile_actuelle.cotes[0] == 'b' && structure == 'v') ||
        (tuile_actuelle.cotes[0] == 'v' && structure == 'b'))){
            // printf("bord gauche\n");
            res0 = parcours_structure(grille, tuile_actuelle, structure, 0, score, pion, score_final);
        }
        // printf("Traitee haut: %d\n", grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[1]);
        if((grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[1] == 0 ||
        grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[1] == -2) &&
        (tuile_actuelle.cotes[1] == structure ||
        (tuile_actuelle.cotes[1] == 'b' && structure == 'v') ||
        (tuile_actuelle.cotes[1] == 'v' && structure == 'b'))){
            // printf("bord haut\n");
            res1 = parcours_structure(grille, tuile_actuelle, structure, 1, score, pion, score_final);
        }
        // printf("Traitee droit: %d\n", grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[2]);
        if((grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[2] == 0 ||
        grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[2] == -2) &&
        (tuile_actuelle.cotes[2] == structure ||
        (tuile_actuelle.cotes[2] == 'b' && structure == 'v') ||
        (tuile_actuelle.cotes[2] == 'v' && structure == 'b'))){
            // printf("bord droit\n");
            res2 = parcours_structure(grille, tuile_actuelle, structure, 2, score, pion, score_final);
        }
        // printf("Traitee bas: %d\n", grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[3]);
        if((grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[3] == 0 ||
        grille[tuile_actuelle.c.y][tuile_actuelle.c.x].traitee[3] == -2) &&
        (tuile_actuelle.cotes[3] == structure ||
        (tuile_actuelle.cotes[3] == 'b' && structure == 'v') ||
        (tuile_actuelle.cotes[3] == 'v' && structure == 'b'))){
            // printf("bord bas\n");
            res3 = parcours_structure(grille, tuile_actuelle, structure, 3, score, pion, score_final);
        }

        // Parcours fermé
        if(res0 != -1 && res1 != -1 && res2 != -1 && res3 != -1){
            // printf("Parcours fermé centre\n");
            return 1;
        }
        // Parcours ouvert
        else{
            // printf("Parcours ouvert centre\n");
            return -1;
        } 
    }


    // printf("Sorties des différentes conditions -> res_centre = %d, res0 = %d, res1 = %d, res2 = %d, res3 = %d\n", res_centre, res0, res1, res2, res3);
    // Cas où la structure est ouverte (vue centre)
    if (res_centre == -1 || res0 == -1 || res1 == -1 || res2 == -1 || res3 == -1) {
        // printf("Sortie ouverte\n");
        return -1;
    }

    // Sortie si fermée
    // printf("Sortie fermée\n");
    return 1;
}

struct coords verif_abbaye(struct tuile_s grille[G][G], struct tuile_s tuile_actuelle){
    struct coords c;
    c.x = tuile_actuelle.c.x; c.y = tuile_actuelle.c.y;
    for(int lig = c.y-1; lig < c.y+2; lig++){
        for(int col = c.x-1; col < c.x+2; col++){
            printf("(%d %d)\n", col, lig);
            if(grille[lig][col].centre == 'a'){
                printf("trouvé !\n");
                c.x = col; c.y = lig;
                return c;
            }
        }
    }
    return c;
}

int score_abbaye(struct tuile_s grille[G][G], int x, int y){
    int res = 0;
    for(int lig = y-1; lig < y+2; lig++){
        for(int col = x-1; col < x+2; col++){
            if(grille[lig][col].id != -1){
                // printf("AH OUI en coord x: %d et y: %d\n", col, lig);
                res++;
            } 
        }
    }
    return res;
}
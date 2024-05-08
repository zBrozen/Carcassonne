#include "game_structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tuile_s piocher(struct tuile_s pioche[72], int index){
    /* Permet de déplacer les tuiles dans les mains du joueur (et donc de la grille)
    et de supprimer la tuile de la pioche (init basique de tuile)
    Index permet de determiner quelle tuile il faut piocher (fonction non lancée si index == 72)*/

    srand(time(NULL));
    struct tuile_s tuile;

    // Init de tuile en main
    tuile.id = pioche[index].id;
    tuile.cotes[0] = pioche[index].cotes[0];
    tuile.cotes[1] = pioche[index].cotes[1];
    tuile.cotes[2] = pioche[index].cotes[2];
    tuile.cotes[3] = pioche[index].cotes[3];
    tuile.centre = pioche[index].centre;

    // Init tuile "vide" dans pioche (au cas où)
    pioche[index].id = -1;

    return tuile;
}

struct tuile_s rotation(struct tuile_s tuile, int sens){
    struct tuile_s res;
    
    // Sens horaire
    if (sens == 0){
        res.cotes[0] = tuile.cotes[3];
        res.cotes[1] = tuile.cotes[0];
        res.cotes[2] = tuile.cotes[1];
        res.cotes[3] = tuile.cotes[2];
        res.centre = tuile.centre;
    }

    // Sens anti-horaire
    else {
        res.cotes[0] = tuile.cotes[1];
        res.cotes[1] = tuile.cotes[2];
        res.cotes[2] = tuile.cotes[3];
        res.cotes[3] = tuile.cotes[0];
        res.centre = tuile.centre;
    }

    return res;
}

struct coords * def_liste_placements(struct tuile_s grille[72][72], struct tuile_s tuiles_placees[72], struct tuile_s tuile){
    /* Def une liste de possibilites qui permet de placer la tuile piochee */

    // Init liste
    struct coords * liste;
    liste = (struct coords *)malloc(72 * sizeof(struct coords));
    for(int i = 0; i < 72; i++){
        liste[i].x = -1;
        liste[i].y = -1;
    }

    struct tuile_s tuile_copie;
    tuile_copie.cotes[0] = tuile.cotes[0];
    tuile_copie.cotes[1] = tuile.cotes[1];
    tuile_copie.cotes[2] = tuile.cotes[2];
    tuile_copie.cotes[3] = tuile.cotes[3];

    // Index sert à parcourir la liste, et t le tableau "tuiles_placees" pris en paramètre
    int index = 0, t;
    
    for(t = 0; t < 72 && tuiles_placees[t].id != -1; t++){
        //printf("debug for\n");
        /* Premiere verif de chaque cotees de la tuile par rapport a la tuile placee
        On regarde d'abord si l'espace pour placer la tuile est libre et compatible */

        int c = 0, c2, nb_rota, ok = 1;
        while(c < 4){
            // printf("debug w\n");
            // int c1, c2, c3;
            // c1 = tuile.cotes[c] == tuiles_placees[t].cotes[0];
            // c2 = (tuiles_placees[t].c.x - 1) >= 0;
            // c3 = grille[tuiles_placees[t].c.x - 1][tuiles_placees[t].c.y].id == -1;
            // printf("debug %d\n", tuiles_placees[t].c.x);
            // printf("c1 = %d c2 = %d c3 = %d\n", c1, c2, c3);
            // Verif du cote c (ouest, nord, est, sud)
            
            // Def de ok qui compte la tuile comme compatible et qui permettra d'ajouter des placements
            ok = 1;

            if(tuile.cotes[c] == tuiles_placees[t].cotes[0] && (tuiles_placees[t].c.x - 1) >= 0
            && grille[tuiles_placees[t].c.y][tuiles_placees[t].c.x - 1].id == -1){
                // Init de tuile copie pour definir le nombre de rotation a faire
                tuile_copie.cotes[0] = tuile.cotes[0];
                tuile_copie.cotes[1] = tuile.cotes[1];
                tuile_copie.cotes[2] = tuile.cotes[2];
                tuile_copie.cotes[3] = tuile.cotes[3];


                // Seconde verif pour chaque cotes de la tuile piochee, a comparer avec les potentielles tuiles alentours

                c2 = c, nb_rota = 0;
                while(c2 != 2){ // Rota pour placer la tuile par rapport a ce qui est compatible sur la tuile placee
                    // printf("debut w2\n");
                    tuile_copie = rotation(tuile_copie, 0);
                    c2 = (c2 + 1) % 4;
                    nb_rota++;
                }
                // Verif de la compa autour du placement de la nouvelle tuile (donc on utilise la position de tuile placee)
                int y = tuiles_placees[t].c.y, x = tuiles_placees[t].c.x - 1;
                
                if(y+1 < 72 && grille[y+1][x].id != -1){
                    if(tuile_copie.cotes[3] != grille[y+1][x].cotes[1]){
                        ok = 0;
                        break;
                    }
                }
                if(ok == 1 && x-1 >= 0 && grille[y][x-1].id != -1){
                    if(tuile_copie.cotes[0] != grille[y][x-1].cotes[2]){
                        ok = 0;
                        break;
                    }
                }
                if(ok == 1 && y-1 >= 0 && grille[y-1][x].id != -1){
                    if(tuile_copie.cotes[1] != grille[y-1][x].cotes[3]){
                        ok = 0;
                        break;
                    }
                }

                // Def le placement 
                if(ok == 1){
                    liste[index].y = tuiles_placees[t].c.y;
                    liste[index].x = tuiles_placees[t].c.x - 1;
                    liste[index].rota = nb_rota;
                    index++;
                }
            }

            if(tuile.cotes[c] == tuiles_placees[t].cotes[1] && (tuiles_placees[t].c.y - 1) >= 0 
            && grille[tuiles_placees[t].c.y - 1][tuiles_placees[t].c.x].id == -1){
                // Init de tuile copie pour definir le nombre de rotation a faire
                tuile_copie.cotes[0] = tuile.cotes[0];
                tuile_copie.cotes[1] = tuile.cotes[1];
                tuile_copie.cotes[2] = tuile.cotes[2];
                tuile_copie.cotes[3] = tuile.cotes[3];

                // Seconde verif pour chaque cotes de la tuile piochee, a comparer avec les potentielles tuiles alentours
                
                c2 = c, nb_rota = 0;
                while(c2 != 3){ // Rota pour placer la tuile par rapport a ce qui est compatible sur la tuile placee
                    tuile_copie = rotation(tuile_copie, 0);
                    c2 = (c2 + 1) % 4;
                    nb_rota++;
                }
                int y = tuiles_placees[t].c.y - 1, x = tuiles_placees[t].c.x;
                
                if(x+1 < 72 && grille[y][x+1].id != -1){
                    if(tuile_copie.cotes[2] != grille[y][x+1].cotes[0]){
                        ok = 0;
                    }
                }
                if(x-1 >= 0 && grille[y][x-1].id != -1){
                    if(tuile_copie.cotes[0] != grille[y][x-1].cotes[2]){
                        ok = 0;
                    }
                }
                if(y-1 >= 0 && grille[y-1][x].id != -1){
                    if(tuile_copie.cotes[1] != grille[y-1][x].cotes[3]){
                        ok = 0;
                    }
                }

                // Def le placement
                if(ok == 1){
                    liste[index].y = tuiles_placees[t].c.y - 1;
                    liste[index].x = tuiles_placees[t].c.x;
                    liste[index].rota = nb_rota;
                    index++;
                }
            }

            if(tuile.cotes[c] == tuiles_placees[t].cotes[2] && (tuiles_placees[t].c.x + 1) < 72 
            && grille[tuiles_placees[t].c.y][tuiles_placees[t].c.x + 1].id == -1){
                // Init de tuile copie pour definir le nombre de rotation a faire
                tuile_copie.cotes[0] = tuile.cotes[0];
                tuile_copie.cotes[1] = tuile.cotes[1];
                tuile_copie.cotes[2] = tuile.cotes[2];
                tuile_copie.cotes[3] = tuile.cotes[3];
                
                // Seconde verif pour chaque cotes de la tuile piochee, a comparer avec les potentielles tuiles alentours
                
                c2 = c, nb_rota = 0;
                while(c2 != 0){ // Rota pour placer la tuile par rapport a ce qui est compatible sur la tuile placee
                    tuile_copie = rotation(tuile_copie, 0);
                    c2 = (c2 + 1) % 4;
                    nb_rota++;
                }
                int y = tuiles_placees[t].c.y, x = tuiles_placees[t].c.x + 1;
                
                if(y+1 < 72 && grille[y+1][x].id != -1){
                    if(tuile_copie.cotes[3] != grille[y+1][x].cotes[1]){
                        ok = 0;
                    }
                }
                if(x+1 >= 0 && grille[y][x+1].id != -1){
                    if(tuile_copie.cotes[2] != grille[y][x+1].cotes[0]){
                        ok = 0;
                    }
                }
                if(y-1 >= 0 && grille[y-1][x].id != -1){
                    if(tuile_copie.cotes[1] != grille[y-1][x].cotes[3]){
                        ok = 0;
                    }
                }

                // Def le placement
                if(ok == 1){
                    liste[index].y = tuiles_placees[t].c.y;
                    liste[index].x = tuiles_placees[t].c.x + 1;
                    liste[index].rota = nb_rota;
                    index++;
                }
            }

            if(tuile.cotes[c] == tuiles_placees[t].cotes[3] && (tuiles_placees[t].c.y + 1) < 72 
            && grille[tuiles_placees[t].c.y + 1][tuiles_placees[t].c.x].id == -1){
                // Init de tuile copie pour definir le nombre de rotation a faire
                tuile_copie.cotes[0] = tuile.cotes[0];
                tuile_copie.cotes[1] = tuile.cotes[1];
                tuile_copie.cotes[2] = tuile.cotes[2];
                tuile_copie.cotes[3] = tuile.cotes[3];
                
                // Seconde verif pour chaque cotes de la tuile piochee, a comparer avec les potentielles tuiles alentours
                
                c2 = c, nb_rota = 0;
                while(c2 != 1){ // Rota pour placer la tuile par rapport a ce qui est compatible sur la tuile placee
                    tuile_copie = rotation(tuile_copie, 0);
                    c2 = (c2 + 1) % 4;
                    nb_rota++;
                }
                int y = tuiles_placees[t].c.y + 1, x = tuiles_placees[t].c.x;
                
                if(y+1 < 72 && grille[y+1][x].id != -1){
                    if(tuile_copie.cotes[3] != grille[y+1][x].cotes[1]){
                        ok = 0;
                    }
                }
                if(x+1 >= 0 && grille[y][x+1].id != -1){
                    if(tuile_copie.cotes[2] != grille[y][x+1].cotes[0]){
                        ok = 0;
                    }
                }
                if(x-1 >= 0 && grille[y][x-1].id != -1){
                    if(tuile_copie.cotes[0] != grille[y][x-1].cotes[2]){
                        ok = 0;
                    }
                }

                // Def le placement
                if(ok == 1){
                    liste[index].y = tuiles_placees[t].c.y + 1;
                    liste[index].x = tuiles_placees[t].c.x;
                    liste[index].rota = nb_rota;
                    index++;
                } 
            }

            // Incrémentation c
            c++;
        }
    }
    return liste;
}

void add_gr(struct tuile_s grille[72][72], struct tuile_s tuile, int x, int y){
    grille[y][x].id = tuile.id;
    grille[y][x].cotes[0] = tuile.cotes[0];
    grille[y][x].cotes[1] = tuile.cotes[1];
    grille[y][x].cotes[2] = tuile.cotes[2];
    grille[y][x].cotes[3] = tuile.cotes[3];
    grille[y][x].centre = tuile.centre;
}

void rem_gr(struct tuile_s grille[72][72], int x, int y){
    grille[y][x].id = -1;
}

void previsu(struct tuile_s grille[72][72], struct tuile_s tuile, struct coords liste_compa[72], int l_index){
    /* Permet d'ajouter a la grille une tuile temporaire pour previsualiser le placement */

    // Init tuile copie qui concerve la config initiale afin d'assurer que les asserts lors de la rotation soient justes
    struct tuile_s tuile_copie;
    tuile_copie.id = tuile.id;
    tuile_copie.cotes[0] = tuile.cotes[0];
    tuile_copie.cotes[1] = tuile.cotes[1];
    tuile_copie.cotes[2] = tuile.cotes[2];
    tuile_copie.cotes[3] = tuile.cotes[3];
    tuile_copie.centre = tuile.centre;

    // Modif tuile
    tuile.id = -2;
    int x = liste_compa[l_index].x, y = liste_compa[l_index].y;
    for(int i = 0; i < liste_compa[l_index].rota; i++){
        tuile = rotation(tuile, 0);
    }

    add_gr(grille, tuile, x, y);
    affichage(grille, 0, 0);
}

void free_liste(struct coords * c){
    free(c);
}

int tour(struct joueur j, struct tuile_s pioche[72], struct tuile_s grille[72][72], struct tuile_s tuiles_placees[72], int index){
    /*Effectue un tour pour un certain joueur (ne se lance que si index < 72)
    Le paramètre "index" indique les tuiles restantes dans la pioche artificiellement*/
    
    // Pioche de tuile
    struct tuile_s tuile;
    tuile = piocher(pioche, index);
    afficher_tuile(tuile);
    
    // Manipulation tuile
    int mode = -1; // -1: debug, 0: se deplacer dans grille, 1: manipuler tuile

    // Def liste compa pour placement
    struct coords * liste_compa;
    liste_compa = def_liste_placements(grille, tuiles_placees, tuile);
    for(int e = 0; e < 72 && liste_compa[e].x != -1; e++)
        previsu(grille, tuile, liste_compa, e);
    // Debug liste
    int i = 0;
    while(i < 72 && liste_compa[i].x != -1){
        printf("%d: x%d, y%d, r%d\n", i, liste_compa[i].x, liste_compa[i].y, liste_compa[i].rota);
        i++;
    }

    index++;
    free_liste(liste_compa);

    return 1;
}
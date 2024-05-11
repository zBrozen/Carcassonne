#include "game_structures.h"
#include "affichage.h"
#include "score.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 8 // Taille de l'affichage de la grille

struct tuile_s piocher(struct tuile_s pioche[72], int index){
    /* Permet de déplacer les tuiles dans les mains du joueur (et donc de la grille)
    et de supprimer la tuile de la pioche (init basique de tuile)
    Index permet de determiner quelle tuile il faut piocher (fonction non lancée si index == 72)*/

    srand(time(NULL));
    struct tuile_s tuile;

    // Init de tuile en main
    tuile.id = -2;
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

int doublon(struct coords liste_placements[72], struct tuile_s tuiles_placees[72], int t, int add_x, int add_y, int nb_rota){
    int res = 0, i = 0;
    while(i < 72 && liste_placements[i].x != -1){
        if(liste_placements[i].x == tuiles_placees[t].c.x + add_x 
        && liste_placements[i].y == tuiles_placees[t].c.y + add_y 
        && liste_placements[i].rota == nb_rota)
            res = 1;
        i++;
    }
    return res;
}

struct coords * def_liste_placements(struct tuile_s grille[72][72], struct tuile_s tuiles_placees[72], struct tuile_s tuile){
    /* Def une liste de possibilites qui permet de placer la tuile piochee */

    // Init liste
    struct coords * liste;
    liste = (struct coords *)malloc(72 * sizeof(struct coords));
    // Init de la liste qui permettra de déterminer sa taille (le nombre de coordonnées répertoriées dans la liste)
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
        printf("debug for %d", t);
        int compteur_debug = 0;
        /* Premiere verif de chaque cotees de la tuile par rapport a la tuile placee
        On regarde d'abord si l'espace pour placer la tuile est libre et compatible */

        int c = 0, c2, nb_rota, ok = 1;
        printf("Verif pour %c:\n", tuile.cotes[c]);
        while(c < 4){
            
            // Def de ok qui compte la tuile comme compatible et qui permettra d'ajouter des placements
            ok = 1;

            // Condition vérifiant la compatibilité entre les cotes des tuiles (verif si egal, si v alors == b et inverse)
            if((((tuile.cotes[c] == 'v' && tuiles_placees[t].cotes[0] == 'b') || (tuile.cotes[c] == 'b' && tuiles_placees[t].cotes[0] == 'v'))
            || tuile.cotes[c] == tuiles_placees[t].cotes[0]) && (tuiles_placees[t].c.x - 1) >= 0
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
                    if(!((tuile_copie.cotes[3] == 'v' && grille[y+1][x].cotes[1] == 'b') || (tuile_copie.cotes[3] == 'b' && grille[y+1][x].cotes[1] == 'v'))
                        && tuile_copie.cotes[3] != grille[y+1][x].cotes[1]){
                        ok = 0;
                    }
                }
                if(x-1 >= 0 && grille[y][x-1].id != -1){
                    if(!((tuile_copie.cotes[0] == 'v' && grille[y][x-1].cotes[2] == 'b') || (tuile_copie.cotes[0] == 'b' && grille[y][x-1].cotes[2] == 'v'))
                        && tuile_copie.cotes[0] != grille[y][x-1].cotes[2]){
                        ok = 0;
                    }
                }
                if(y-1 >= 0 && grille[y-1][x].id != -1){
                    if(!((tuile_copie.cotes[1] == 'v' && grille[y-1][x].cotes[3] == 'b') || (tuile_copie.cotes[1] == 'b' && grille[y-1][x].cotes[3] == 'v'))
                        && tuile_copie.cotes[1] != grille[y-1][x].cotes[3]){
                        ok = 0;
                    }
                }

                // Def le placement 
                if(ok == 1 && doublon(liste, tuiles_placees, t, -1, 0, nb_rota) == 0){
                    liste[index].y = tuiles_placees[t].c.y;
                    liste[index].x = tuiles_placees[t].c.x - 1;
                    liste[index].rota = nb_rota;
                    index++;
                    compteur_debug++;
                }
            }

            ok = 1;
            if((((tuile.cotes[c] == 'v' && tuiles_placees[t].cotes[1] == 'b') || (tuile.cotes[c] == 'b' && tuiles_placees[t].cotes[1] == 'v'))
            || tuile.cotes[c] == tuiles_placees[t].cotes[1]) && (tuiles_placees[t].c.y - 1) >= 0 
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
                    if(!((tuile_copie.cotes[2] == 'v' && grille[y][x+1].cotes[0] == 'b') || (tuile_copie.cotes[2] == 'b' && grille[y][x+1].cotes[0] == 'v'))
                        && tuile_copie.cotes[2] != grille[y][x+1].cotes[0]){
                        ok = 0;
                    }
                }
                if(x-1 >= 0 && grille[y][x-1].id != -1){
                    if(!((tuile_copie.cotes[0] == 'v' && grille[y][x-1].cotes[2] == 'b') || (tuile_copie.cotes[0] == 'b' && grille[y][x-1].cotes[2] == 'v'))
                        && tuile_copie.cotes[0] != grille[y][x-1].cotes[2]){
                        ok = 0;
                    }
                }
                if(y-1 >= 0 && grille[y-1][x].id != -1){
                    if(!((tuile_copie.cotes[1] == 'v' && grille[y-1][x].cotes[3] == 'b') || (tuile_copie.cotes[1] == 'b' && grille[y-1][x].cotes[3] == 'v'))
                        && tuile_copie.cotes[1] != grille[y-1][x].cotes[3]){
                        ok = 0;
                    }
                }

                // Def le placement
                if(ok == 1 && doublon(liste, tuiles_placees, t, 0, -1, nb_rota) == 0){
                    liste[index].y = tuiles_placees[t].c.y - 1;
                    liste[index].x = tuiles_placees[t].c.x;
                    liste[index].rota = nb_rota;
                    index++;
                    compteur_debug++;
                }
            }

            ok = 1;
            if((((tuile.cotes[c] == 'v' && tuiles_placees[t].cotes[2] == 'b') || (tuile.cotes[c] == 'b' && tuiles_placees[t].cotes[2] == 'v')) 
            || tuile.cotes[c] == tuiles_placees[t].cotes[2]) && (tuiles_placees[t].c.x + 1) < 72 
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
                    if(!((tuile_copie.cotes[3] == 'v' && grille[y+1][x].cotes[1] == 'b') || (tuile_copie.cotes[3] == 'b' && grille[y+1][x].cotes[1] == 'v'))
                        && tuile_copie.cotes[3] != grille[y+1][x].cotes[1]){
                        ok = 0;
                    }
                }
                if(x+1 < 72 && grille[y][x+1].id != -1){
                    if(!((tuile_copie.cotes[2] == 'v' && grille[y][x+1].cotes[0] == 'b') || (tuile_copie.cotes[2] == 'b' && grille[y][x+1].cotes[0] == 'v'))
                        && tuile_copie.cotes[2] != grille[y][x+1].cotes[0]){
                        ok = 0;
                    }
                }
                if(y-1 >= 0 && grille[y-1][x].id != -1){
                    if(!((tuile_copie.cotes[1] == 'v' && grille[y-1][x].cotes[3] == 'b') || (tuile_copie.cotes[1] == 'b' && grille[y-1][x].cotes[3] == 'v'))
                        && tuile_copie.cotes[1] != grille[y-1][x].cotes[3]){
                        ok = 0;
                    }
                }

                // Def le placement
                if(ok == 1 && doublon(liste, tuiles_placees, t, 1, 0, nb_rota) == 0){
                    liste[index].y = tuiles_placees[t].c.y;
                    liste[index].x = tuiles_placees[t].c.x + 1;
                    liste[index].rota = nb_rota;
                    index++;
                    compteur_debug++;
                }
            }

            ok = 1;
            if((((tuile.cotes[c] == 'v' && tuiles_placees[t].cotes[3] == 'b') || (tuile.cotes[c] == 'b' && tuiles_placees[t].cotes[3] == 'v'))
            || tuile.cotes[c] == tuiles_placees[t].cotes[3]) && (tuiles_placees[t].c.y + 1) < 72 
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
                    if(!((tuile_copie.cotes[3] == 'v' && grille[y+1][x].cotes[1] == 'b') || (tuile_copie.cotes[3] == 'b' && grille[y+1][x].cotes[1] == 'v'))
                        && tuile_copie.cotes[3] != grille[y+1][x].cotes[1]){
                        ok = 0;
                    }
                }
                if(x+1 < 72 && grille[y][x+1].id != -1){
                    if(!((tuile_copie.cotes[2] == 'v' && grille[y][x+1].cotes[3] == 'b') || (tuile_copie.cotes[1] == 'b' && grille[y][x+1].cotes[3] == 'v'))
                        && tuile_copie.cotes[2] != grille[y][x+1].cotes[0]){
                        ok = 0;
                    }
                }
                if(x-1 >= 0 && grille[y][x-1].id != -1){
                    if(!((tuile_copie.cotes[0] == 'v' && grille[y][x-1].cotes[2] == 'b') || (tuile_copie.cotes[0] == 'b' && grille[y][x-1].cotes[2] == 'v'))
                        && tuile_copie.cotes[0] != grille[y][x-1].cotes[2]){
                        ok = 0;
                    }
                }

                // Def le placement
                if(ok == 1 && doublon(liste, tuiles_placees, t, 0, 1, nb_rota) == 0){
                    liste[index].y = tuiles_placees[t].c.y + 1;
                    liste[index].x = tuiles_placees[t].c.x;
                    liste[index].rota = nb_rota;
                    index++;
                    compteur_debug++;
                } 
            }

            // Incrémentation c
            c++;
        }
        printf("nombre de tuile ajoutée: %d\n", compteur_debug);
    }
    return liste;
}

void add_gr(struct tuile_s grille[72][72], struct tuile_s tuile, int x, int y){
    grille[y][x].id = -2;
    grille[y][x].cotes[0] = tuile.cotes[0];
    grille[y][x].cotes[1] = tuile.cotes[1];
    grille[y][x].cotes[2] = tuile.cotes[2];
    grille[y][x].cotes[3] = tuile.cotes[3];
    grille[y][x].centre = tuile.centre;
}

void rem_gr(struct tuile_s grille[72][72], int x, int y){
    grille[y][x].id = -1;
}

void previsu(struct tuile_s grille[72][72], struct tuile_s tuile, struct coords liste_placements[72], int l_index){
    /* Permet d'ajouter a la grille une tuile temporaire pour previsualiser le placement */

    // Init tuile copie qui permet de concerver la config initiale de tuile afin d'assurer que les asserts lors de la rotation soient justes
    struct tuile_s tuile_copie;
    tuile_copie.id = -2;
    tuile_copie.cotes[0] = tuile.cotes[0];
    tuile_copie.cotes[1] = tuile.cotes[1];
    tuile_copie.cotes[2] = tuile.cotes[2];
    tuile_copie.cotes[3] = tuile.cotes[3];
    tuile_copie.centre = tuile.centre;

    // Modif tuile
    int x = liste_placements[l_index].x, y = liste_placements[l_index].y;
    // Rotation de la tuile pour correspondre à la configuration de la tuile dans la liste de placements
    for(int i = 0; i < liste_placements[l_index].rota; i++){
        tuile_copie = rotation(tuile_copie, 0);
    }

    // Ajout de la tuile prévisualisée dans la grille (la tuile est fausse)
    add_gr(grille, tuile_copie, x, y);

    // Definit l'affichage de la grille selon les coordonnées
    int taille_x = x-N; int taille_y = y-N;
    if (taille_x < 0) taille_x = 0; // Limitation de la grille avec les bords à gauche
    if (taille_y < 0) taille_y = 0; // Limitation de la grille avec les bords en haut
    affichage(grille, taille_x, taille_y);
    afficher_tuile(tuile);
}

void free_liste(struct coords * c){
    free(c);
}

int tour(struct joueur j, struct tuile_s pioche[72], struct tuile_s grille[72][72], struct tuile_s tuiles_placees[72], int index){
    /*Effectue un tour pour un certain joueur (ne se lance que si index < 72)
    Le paramètre "index" indique les tuiles restantes dans la pioche artificiellement (car je ne fais que avancer dans la pioche sans retirer les tuiles)*/
    
    // Pioche de tuile
    struct tuile_s tuile;
    tuile = piocher(pioche, index);
    tuile.id = -2; // Valeur de l'id tant que la tuile n'est pas placée (permet l'affichage de la tuile car -1 bloque l'affichage)
    afficher_tuile(tuile);
    
    // Manipulation tuile
    int mode = -1; // -1: debug, 0: se deplacer dans grille, 1: manipuler tuile

    // Def liste compa pour définir les différents placements possible avec la tuile piochée
    struct coords * liste_placements;
    liste_placements = def_liste_placements(grille, tuiles_placees, tuile);

    
    // Choix du placement (parcours de la liste des placements et prévisualise la tuile sélectionnée)
    
    int e = 0; // Init e qui servira d'index pour parcourir la liste
    // Def taille de la liste des placements
    int taille_liste = 0;
    while(liste_placements[e].x != -1){
        taille_liste++;
        e++;
    }
    e = 0;

    // Condition qui vérifie si il y a bien des tuiles dans la liste des placements (sinon anormal)
    if(taille_liste != 0){
        previsu(grille, tuile, liste_placements, e);

        // Choix du joueur
        int c = -1; // Variable de choix de placement
        while(c != 2){
            printf("\nDebug e = %d et taille liste = %d id tuile = %d\n", e, taille_liste, grille[liste_placements[e].y][liste_placements[e].x].id);
            printf("\nPlacer la tuile (0: placement précédent, 1: placement suivant, 2: valide placement): ");
            scanf("%d", &c);
            fflush(stdin);
            printf("\n");
            switch(c){
                case 0:
                    rem_gr(grille, liste_placements[e].x, liste_placements[e].y);
                    if(e == 0) e = taille_liste-1;
                    else e = (e - 1) % taille_liste;
                    previsu(grille, tuile, liste_placements, e);
                    break;
                case 1:
                    rem_gr(grille, liste_placements[e].x, liste_placements[e].y);
                    e = (e + 1) % taille_liste;
                    previsu(grille, tuile, liste_placements, e);
                    break;
                case 2:
                    printf("Placement effectué (id tuile = %d)\n", index);
                    grille[liste_placements[e].y][liste_placements[e].x].id = index;
                    tuiles_placees[index].id = index;
                    tuiles_placees[index].cotes[0] = grille[liste_placements[e].y][liste_placements[e].x].cotes[0];
                    tuiles_placees[index].cotes[1] = grille[liste_placements[e].y][liste_placements[e].x].cotes[1];
                    tuiles_placees[index].cotes[2] = grille[liste_placements[e].y][liste_placements[e].x].cotes[2];
                    tuiles_placees[index].cotes[3] = grille[liste_placements[e].y][liste_placements[e].x].cotes[3];
                    tuiles_placees[index].centre = grille[liste_placements[e].y][liste_placements[e].x].centre;
                    tuiles_placees[index].c.x = liste_placements[e].x;
                    tuiles_placees[index].c.y = liste_placements[e].y;
                    break;
                default:
                    printf("Veuillez rentrer une valeur parmis cette liste [0,1,2]");
                    break;
            }
        }
    }
    else{
        printf("Erreur: liste placement vide\n");
    }

    // Placement de meeple

    // Debug de tout les placements possible en un seul affichage
    // for(int e = 0; e < 72 && liste_placements[e].x != -1; e++)
    //     previsu(grille, tuile, liste_placements, e);
    
    // Debug liste
    // int i = 0;
    // while(i < 72 && liste_placements[i].x != -1){
    //     printf("%d: x%d, y%d, r%d\n", i, liste_placements[i].x, liste_placements[i].y, liste_placements[i].rota);
    //     i++;
    // }

    index++;
    printf("\nDebug tuiles_placees:\n");
    for(int i = 0; i < 5; i++){
        printf("id %d: %d\n", i, tuiles_placees[i].id);
    }
    printf("Tuiles restantes: %d\n", 72-index);
    free_liste(liste_placements);

    return 1;
}
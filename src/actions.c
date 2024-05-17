#include "game_structures.h"
#include "affichage.h"
#include "score.h"
#include "lecteur_csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define G 143 // Taille de la grille
#define N 8 // Taille de l'affichage de la grille

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

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

struct tuile_s copie(struct tuile_s tuile){
    struct tuile_s tuile_copie;

    tuile_copie.cotes[0] = tuile.cotes[0];
    tuile_copie.cotes[1] = tuile.cotes[1];
    tuile_copie.cotes[2] = tuile.cotes[2];
    tuile_copie.cotes[3] = tuile.cotes[3];
    tuile_copie.centre = tuile.centre;
    
    return tuile_copie;
}

int doublon(struct coords liste_placements[72], struct tuile_s tuiles_placees[72], struct tuile_s tuile, int t, int add_x, int add_y, int nb_rota){
    int res = 0, i = 0;
    while(i < 72 && liste_placements[i].x != -1 && res != 1){
        if(liste_placements[i].x == tuiles_placees[t].c.x + add_x // tuiles_placees: sert à définir la position et non prendre une tuile déjà placée
        && liste_placements[i].y == tuiles_placees[t].c.y + add_y){
            if(liste_placements[i].rota == nb_rota){
                // printf("doublon\n");
                res = 1;
            }
            // printf("liste_rota = %d et nb_rota = %d\n", liste_placements[i].rota, nb_rota);
            struct tuile_s tuile1 = copie(tuile);
            struct tuile_s tuile2 = copie(tuile);
            
            int r = 0;
            while(r != liste_placements[i].rota){
                tuile1 = rotation(tuile1, 0);
                r++;
            } 
            r = 0;
            while(r != nb_rota){
                tuile2 = rotation(tuile2, 0);
                r++;
            }
            if(tuile1.cotes[0] == tuile2.cotes[0] && tuile1.cotes[1] == tuile2.cotes[1] && tuile1.cotes[2] == tuile2.cotes[2] && tuile1.cotes[3] == tuile2.cotes[3]){
                // printf("doublon\n");
                res = 1;
            }
        }    
        i++;
    }
    return res;
}

void def_liste_placements(struct coords liste[72], struct tuile_s grille[G][G], struct tuile_s tuiles_placees[72], struct tuile_s tuile){
    /* Def une liste de possibilites qui permet de placer la tuile piochee */

    // Init liste
    // struct coords liste[72];
    // liste = (struct coords *)malloc(72 * sizeof(struct coords));
    // Init de la liste qui permettra de déterminer sa taille (le nombre de coordonnées répertoriées dans la liste)
    for(int i = 0; i < 72; i++){
        liste[i].x = -1;
        liste[i].y = -1;
    }

    // Init de tuile copie pour definir le nombre de rotation a faire
    struct tuile_s tuile_copie;

    // Index sert à parcourir la liste, et t le tableau "tuiles_placees" pris en paramètre
    int index = 0, t;
    
    for(t = 0; t < 72 && tuiles_placees[t].id != -1; t++){
        // printf("debug for %d", t);
        int compteur_debug = 0;
        /* Premiere verif de chaque cotees de la tuile par rapport a la tuile placee
        On regarde d'abord si l'espace pour placer la tuile est libre et compatible */

        int c = 0, c2, nb_rota, ok = 1;
        // printf("Verif pour %c:\n", tuile.cotes[c]);
        while(c < 4){
            
            // Def de ok qui compte la tuile comme compatible et qui permettra d'ajouter des placements
            ok = 1;
            // Condition vérifiant la compatibilité entre les cotes des tuiles (verif si egal, si v alors == b et inverse)
            if((((tuile.cotes[c] == 'v' && tuiles_placees[t].cotes[0] == 'b') || (tuile.cotes[c] == 'b' && tuiles_placees[t].cotes[0] == 'v'))
            || tuile.cotes[c] == tuiles_placees[t].cotes[0]) && (tuiles_placees[t].c.x - 1) >= 0
            && grille[tuiles_placees[t].c.y][tuiles_placees[t].c.x - 1].id == -1){

                // Remet les paramètres initiaux de la tuile (tuile_copie peut subir des changements donc faut l'initialiser pour chaque côté vérifié)
                tuile_copie = copie(tuile);

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
                
                if(y+1 < G && grille[y+1][x].id != -1){
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
                if(ok == 1 && doublon(liste, tuiles_placees, tuile, t, -1, 0, nb_rota) == 0){
                    // printf("Ajout a liste\n");
                    liste[index].y = tuiles_placees[t].c.y;
                    liste[index].x = tuiles_placees[t].c.x - 1;
                    liste[index].rota = nb_rota;
                    index++;
                    compteur_debug++;
                }
            }

            ok = 1;
            if((((tuile.cotes[c] == 'v' && tuiles_placees[t].cotes[1] == 'b') || (tuile.cotes[c] == 'b' && tuiles_placees[t].cotes[1] == 'v'))
            || tuile.cotes[c] == tuiles_placees[t].cotes[1]) 
            && (tuiles_placees[t].c.y - 1) >= 0 && grille[tuiles_placees[t].c.y - 1][tuiles_placees[t].c.x].id == -1){

                // Remet les paramètres initiaux de la tuile (tuile_copie peut subir des changements donc faut l'initialiser pour chaque côté vérifié)
                tuile_copie = copie(tuile);

                // Seconde verif pour chaque cotes de la tuile piochee, a comparer avec les potentielles tuiles alentours
                
                c2 = c, nb_rota = 0;
                while(c2 != 3){ // Rota pour placer la tuile par rapport a ce qui est compatible sur la tuile placee
                    tuile_copie = rotation(tuile_copie, 0);
                    c2 = (c2 + 1) % 4;
                    nb_rota++;
                }
                int y = tuiles_placees[t].c.y - 1, x = tuiles_placees[t].c.x;
                
                if(x+1 < G && grille[y][x+1].id != -1){
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
                if(ok == 1 && doublon(liste, tuiles_placees, tuile, t, 0, -1, nb_rota) == 0){
                    // printf("Ajout a liste\n");
                    liste[index].y = tuiles_placees[t].c.y - 1;
                    liste[index].x = tuiles_placees[t].c.x;
                    liste[index].rota = nb_rota;
                    index++;
                    compteur_debug++;
                }
            }

            ok = 1;
            // printf("Debug: tuile cotes: %c == tuile placee: %c ? %d\n", tuile.cotes[c], tuiles_placees[t].cotes[2], tuile.cotes[c]==tuiles_placees[t].cotes[2]);
            if((((tuile.cotes[c] == 'v' && tuiles_placees[t].cotes[2] == 'b') || (tuile.cotes[c] == 'b' && tuiles_placees[t].cotes[2] == 'v')) 
            || tuile.cotes[c] == tuiles_placees[t].cotes[2]) && (tuiles_placees[t].c.x + 1) < 143 
            && grille[tuiles_placees[t].c.y][tuiles_placees[t].c.x + 1].id == -1){
                
                // Remet les paramètres initiaux de la tuile (tuile_copie peut subir des changements donc faut l'initialiser pour chaque côté vérifié)
                tuile_copie = copie(tuile);

                // Seconde verif pour chaque cotes de la tuile piochee, a comparer avec les potentielles tuiles alentours
                
                c2 = c, nb_rota = 0;
                while(c2 != 0){ // Rota pour placer la tuile par rapport a ce qui est compatible sur la tuile placee
                    tuile_copie = rotation(tuile_copie, 0);
                    c2 = (c2 + 1) % 4;
                    nb_rota++;
                }
                int y = tuiles_placees[t].c.y, x = tuiles_placees[t].c.x + 1;
                
                if(y+1 < G && grille[y+1][x].id != -1){
                    // printf("bizarre0\n");
                    if(!((tuile_copie.cotes[3] == 'v' && grille[y+1][x].cotes[1] == 'b') || (tuile_copie.cotes[3] == 'b' && grille[y+1][x].cotes[1] == 'v'))
                        && tuile_copie.cotes[3] != grille[y+1][x].cotes[1]){
                        // printf("bizarre1\n");
                        ok = 0;
                    }
                }
                if(x+1 < G && grille[y][x+1].id != -1){
                    // printf("bizarre2\n");
                    if(!((tuile_copie.cotes[2] == 'v' && grille[y][x+1].cotes[0] == 'b') || (tuile_copie.cotes[2] == 'b' && grille[y][x+1].cotes[0] == 'v'))
                        && tuile_copie.cotes[2] != grille[y][x+1].cotes[0]){
                        // printf("bizarre3\n");
                        ok = 0;
                    }
                }
                if(y-1 >= 0 && grille[y-1][x].id != -1){
                    // printf("bizarre4\n");
                    if(!((tuile_copie.cotes[1] == 'v' && grille[y-1][x].cotes[3] == 'b') || (tuile_copie.cotes[1] == 'b' && grille[y-1][x].cotes[3] == 'v'))
                        && tuile_copie.cotes[1] != grille[y-1][x].cotes[3]){
                        // printf("bizarre5\n");
                        ok = 0;
                    }
                }

                // Def le placement
                if(ok == 1 && doublon(liste, tuiles_placees, tuile, t, 1, 0, nb_rota) == 0){
                    // printf("Ajout a liste\n");
                    liste[index].y = tuiles_placees[t].c.y;
                    liste[index].x = tuiles_placees[t].c.x + 1;
                    liste[index].rota = nb_rota;
                    index++;
                    compteur_debug++;
                }
            }

            ok = 1;
            // printf("Debug: tuile cotes: %c == tuile placee: %c ? %d\n", tuile.cotes[c], tuiles_placees[t].cotes[3], tuile.cotes[c]==tuiles_placees[t].cotes[3]);
            if((((tuile.cotes[c] == 'v' && tuiles_placees[t].cotes[3] == 'b') || (tuile.cotes[c] == 'b' && tuiles_placees[t].cotes[3] == 'v'))
            || tuile.cotes[c] == tuiles_placees[t].cotes[3]) && (tuiles_placees[t].c.y + 1) < 143 
            && grille[tuiles_placees[t].c.y + 1][tuiles_placees[t].c.x].id == -1){
                
                // Remet les paramètres initiaux de la tuile (tuile_copie peut subir des changements donc faut l'initialiser pour chaque côté vérifié)
                tuile_copie = copie(tuile);

                // Seconde verif pour chaque cotes de la tuile piochee, a comparer avec les potentielles tuiles alentours
                
                c2 = c, nb_rota = 0;
                while(c2 != 1){ // Rota pour placer la tuile par rapport a ce qui est compatible sur la tuile placee
                    tuile_copie = rotation(tuile_copie, 0);
                    c2 = (c2 + 1) % 4;
                    nb_rota++;
                }
                int y = tuiles_placees[t].c.y + 1, x = tuiles_placees[t].c.x;
                
                if(y+1 < G && grille[y+1][x].id != -1){
                    // printf("bizarre0\n");
                    if(!((tuile_copie.cotes[3] == 'v' && grille[y+1][x].cotes[1] == 'b') || (tuile_copie.cotes[3] == 'b' && grille[y+1][x].cotes[1] == 'v'))
                        && tuile_copie.cotes[3] != grille[y+1][x].cotes[1]){
                        // printf("bizarre1\n");
                        ok = 0;
                    }
                }
                if(x+1 < G && grille[y][x+1].id != -1){
                    // printf("bizarre2\n");
                    if(!((tuile_copie.cotes[2] == 'v' && grille[y][x+1].cotes[3] == 'b') || (tuile_copie.cotes[1] == 'b' && grille[y][x+1].cotes[3] == 'v'))
                        && tuile_copie.cotes[2] != grille[y][x+1].cotes[0]){
                        // printf("bizarre3\n");
                        ok = 0;
                    }
                }
                if(x-1 >= 0 && grille[y][x-1].id != -1){
                    // printf("bizarre4\n");
                    if(!((tuile_copie.cotes[0] == 'v' && grille[y][x-1].cotes[2] == 'b') || (tuile_copie.cotes[0] == 'b' && grille[y][x-1].cotes[2] == 'v'))
                        && tuile_copie.cotes[0] != grille[y][x-1].cotes[2]){
                        // printf("bizarre5\n");
                        ok = 0;
                    }
                }

                // Def le placement
                if(ok == 1 && doublon(liste, tuiles_placees, tuile, t, 0, 1, nb_rota) == 0){
                    // printf("Ajout a liste\n");
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
        // printf("nombre de tuile ajoutée: %d\n", compteur_debug);
    }
    // return liste;
}

void add_gr(struct tuile_s grille[G][G], struct tuile_s tuile, int x, int y){
    grille[y][x].id = -2;
    grille[y][x].cotes[0] = tuile.cotes[0];
    grille[y][x].cotes[1] = tuile.cotes[1];
    grille[y][x].cotes[2] = tuile.cotes[2];
    grille[y][x].cotes[3] = tuile.cotes[3];
    grille[y][x].centre = tuile.centre;
    grille[y][x].c.y = y;
    grille[y][x].c.x = x;
}

void rem_gr(struct tuile_s grille[G][G], int x, int y){
    grille[y][x].id = -1;
}

void previsu(struct tuile_s grille[G][G], struct tuile_s tuile, struct coords liste_placements[72], int l_index){
    /* Permet d'ajouter a la grille une tuile temporaire pour previsualiser le placement */

    // Init tuile copie qui permet de concerver la config initiale de tuile afin d'assurer que les asserts lors de la rotation soient justes
    struct tuile_s tuile_copie;
    tuile_copie.id = -2;
    tuile_copie = copie(tuile);

    // Modif tuile
    int x = liste_placements[l_index].x, y = liste_placements[l_index].y;
    // Rotation de la tuile pour correspondre à la configuration de la tuile dans la liste de placements
    for(int i = 0; i < liste_placements[l_index].rota; i++){
        tuile_copie = rotation(tuile_copie, 0);
    }

    // Ajout de la tuile prévisualisée dans la grille (la tuile est fausse)
    add_gr(grille, tuile_copie, x, y);

}

int tour(struct joueur j[5], struct tuile_s pioche[72], struct tuile_s grille[G][G], struct tuile_s tuiles_placees[72], int * index, int nb_joueurs, int joueur_actuel){
    /*Effectue un tour pour un certain joueur (ne se lance que si index < 72)
    Le paramètre "index" indique les tuiles restantes dans la pioche artificiellement (car je ne fais que avancer dans la pioche sans retirer les tuiles)*/
    
    srand(time(NULL));
    // Pioche de tuile
    struct tuile_s tuile;
    tuile = piocher(pioche, *index);

    tuile.id = -2; // Valeur de l'id tant que la tuile n'est pas placée (permet l'affichage de la tuile car -1 bloque l'affichage)
    // afficher_tuile(tuile);

    // Def liste compa pour définir les différents placements possible avec la tuile piochée
    struct coords liste_placements[72];
    def_liste_placements(liste_placements, grille, tuiles_placees, tuile);
    // printf("Test liste placements: (%d,%d)\n", liste_placements[0].x, liste_placements[0].y);

    
    // Choix du placement (parcours de la liste des placements et prévisualise la tuile sélectionnée)
    
    int e = 0; // Init e qui servira d'index pour parcourir la liste
    // Def taille de la liste des placements
    int taille_liste = 0;
    while(liste_placements[e].x != -1){
        taille_liste++;
        e++;
    }
    e = 0;
    // printf("DEBUG e: %d\n", e);

    // Condition qui vérifie si il y a bien des tuiles dans la liste des placements (sinon anormal)
    if(taille_liste != 0){

        // Choix du joueur
        char c;
        if(j[joueur_actuel].ia == 1){
            // printf("OK");
            e = rand()%taille_liste;
        } 
        c = 'x'; // Variable de choix de placement
        int y = liste_placements[e].y, x = liste_placements[e].y;
        int taille_x = x-(N/2); int taille_y = y-(N/2);
        if (taille_x < 0) taille_x = 0; // Limitation de la grille avec les bords à gauche
        if (taille_y < 0) taille_y = 0; // Limitation de la grille avec les bords en haut

        previsu(grille, tuile, liste_placements, e);
        while(c != 'v'){ // v pour valider
            // printf("\e[43mEntré dans la boucle\e[0m\n");
            // Si ia, def choix placement à v
            if(j[joueur_actuel].ia == 1){
                c = 'v';
                previsu(grille, tuile, liste_placements, e);
                // printf("\e[43mIA DE MERDE\e[0m\n");
            } 

            y = liste_placements[e].y, x = liste_placements[e].x;
            taille_x = x-(N/2); taille_y = y-(N/2);
            if (taille_x < 0) taille_x = 0; // Limitation de la grille avec les bords à gauche
            if (taille_y < 0) taille_y = 0; // Limitation de la grille avec les bords en haut
            if (taille_x >= G) taille_x = G-5; // Limitation de la grille avec les bords à droite
            if (taille_y >= G) taille_y = G-5; // Limitation de la grille avec les bords en bas
            // printf("\e[42mPREMIER AFFICHAGE\e[0m\n\n");
            affichage(grille, taille_x, taille_y, tuile, joueur_actuel, j, nb_joueurs, *index);
            // printf("\nDebug e = %d et taille liste = %d id tuile = %d\nDebug coords: x->%d et y->%d taille_x->%d et taille_y->%d", e, taille_liste, grille[liste_placements[e].y][liste_placements[e].x].id, 
            // liste_placements[e].x, liste_placements[e].y, taille_x, taille_y);
            // Si c'est un joueur et non une ia
            // printf("Joueur ia (id: %d): %d", joueur_actuel, j[joueur_actuel].ia);
            if(j[joueur_actuel].ia == 0){
                // printf("Entré dans scanf\n");
                printf("\nPlacer la tuile (a: placement précédent, e: placement suivant, v: valide placement, d: visualisation de la grille): ");
                scanf("%c", &c);
                clearBuffer();
            }
            printf("\n");
            switch(c){
                case 'a':
                    rem_gr(grille, liste_placements[e].x, liste_placements[e].y);
                    if(e == 0) e = taille_liste-1;
                    else e = (e - 1) % taille_liste;
                    previsu(grille, tuile, liste_placements, e);
                    y = liste_placements[e].y, x = liste_placements[e].x;
                    taille_x = x - (N/2); taille_y = y - (N/2);
                    if (taille_x < 0) taille_x = 0; // Limitation de la grille avec les bords à gauche
                    if (taille_y < 0) taille_y = 0; // Limitation de la grille avec les bords en haut
                    if (taille_x >= G) taille_x = G-5; // Limitation de la grille avec les bords à droite
                    if (taille_y >= G) taille_y = G-5; // Limitation de la grille avec les bords en bas
                    affichage(grille, taille_x, taille_y, tuile, joueur_actuel, j, nb_joueurs, *index);
     
                    break;
                case 'e':
                    rem_gr(grille, liste_placements[e].x, liste_placements[e].y);
                    e = (e + 1) % taille_liste;
                    previsu(grille, tuile, liste_placements, e);
                    y = liste_placements[e].y, x = liste_placements[e].x;
                    taille_x = x - (N/2); taille_y = y - (N/2);
                    if (taille_x < 0) taille_x = 0; // Limitation de la grille avec les bords à gauche
                    if (taille_y < 0) taille_y = 0; // Limitation de la grille avec les bords en haut
                    if (taille_x >= G) taille_x = G-5; // Limitation de la grille avec les bords à droite
                    if (taille_y >= G) taille_y = G-5; // Limitation de la grille avec les bords en bas
                    affichage(grille, taille_x, taille_y, tuile, joueur_actuel, j, nb_joueurs, *index);

                    break;
                case 'v':
                    // printf("Placement effectué (id tuile = %d)\n", *index);
                    grille[liste_placements[e].y][liste_placements[e].x].id = *index;
                    tuiles_placees[*index].id = *index;
                    tuiles_placees[*index].cotes[0] = grille[liste_placements[e].y][liste_placements[e].x].cotes[0];
                    tuiles_placees[*index].cotes[1] = grille[liste_placements[e].y][liste_placements[e].x].cotes[1];
                    tuiles_placees[*index].cotes[2] = grille[liste_placements[e].y][liste_placements[e].x].cotes[2];
                    tuiles_placees[*index].cotes[3] = grille[liste_placements[e].y][liste_placements[e].x].cotes[3];
                    tuiles_placees[*index].centre = grille[liste_placements[e].y][liste_placements[e].x].centre;
                    tuiles_placees[*index].c.x = liste_placements[e].x;
                    tuiles_placees[*index].c.y = liste_placements[e].y;
                    // Init les valeurs par défaut des meeples
                    grille[liste_placements[e].y][liste_placements[e].x].m.id = -1;
                    break;
                // Deplacement dans la grille
                case 'd':
                    char direction;
                    affichage(grille, taille_x, taille_y, tuile, joueur_actuel, j, nb_joueurs, *index);
                    printf("Entrer 'x' pour quitter; z: monter, q: gauche, s: descendre, d: droite\nDéplacement: ");
                    scanf("%c", &direction);
                    clearBuffer();
                    if(direction == 'q') taille_x--;
                    if(direction == 'z') taille_y--;
                    if(direction == 'd') taille_x++;
                    if(direction == 's') taille_y++;

                    while(direction != 'x'){
                        affichage(grille, taille_x, taille_y, tuile, joueur_actuel, j, nb_joueurs, *index);
                        printf("\nEntrer 'x' pour quitter; z: monter, q: gauche, s: descendre, d: droite\nDéplacement: ");
                        scanf("%c", &direction);
                        clearBuffer();
                        printf("\n");
                        if(direction == 'q') taille_x--;
                        if(direction == 'z') taille_y--;
                        if(direction == 'd') taille_x++;
                        if(direction == 's') taille_y++;
                    }
                    break;
                default:
                    previsu(grille, tuile, liste_placements, e);
                    printf("\e[41mErreur: veuillez rentrer une valeur parmis cette liste [a,e,v]\e[0m\n");
                    break;
            }
        }

        // printf("ALLO 4 ???\n");
        // printf("Coordonnées de la tuile sur la grille: y: %d x: %d\nCoordonnées de la tuile dans tuile placées: y: %d x: %d\n", grille[tuiles_placees[*index].c.y][tuiles_placees[*index].c.y].c.y, grille[tuiles_placees[*index].c.y][tuiles_placees[*index].c.x].c.x, 
        // tuiles_placees[*index].c.y, tuiles_placees[*index].c.x);

        // Vérification de l'avancée des structures
        int info_structure_pion[4][5]; // Contient les info pour chaque structure, des pions (des joueurs) présents sur les parcours
        int info_structure_score[4] = {0, 0, 0, 0}; // Contient le score potentiel pour chaque côté de la tuile
        int info_structure_res[4] = {0, 0, 0, 0}; // Stocke les différents res
        // printf("DEBUG 713 %d", info_structure_res[0]);
        int pion[5] = {0, 0, 0, 0}; // Le nombre de pion d'un joueur sur une structure
        int emplacement_pion[5] = {0, 0, 0, 0, 0}; // Liste des emplacements dispo avec 1 (o, n, e, s, c)
        int liste_maxi_pion[4] = {0, 0, 0, 0};

        // Verif abbaye
        if(tuiles_placees[*index].centre == 'a'){
            emplacement_pion[4] = 1;
        }

        for(int structure = 0; structure < 4; structure++){
            // Déf du score selon la structure
            int score;
            if(tuiles_placees[*index].cotes[structure] == 'v'){
                score = 2;
                // printf("Score ville\n");
            } 
            else if(tuiles_placees[*index].cotes[structure] == 'b'){
                score = 4;
                // printf("Score blason\n");
            } 
            else score = 1;
            if(tuiles_placees[*index].cotes[structure] != 'p'){
                // Init nb_pion par joueur sur structure
                for(int i = 0; i < 5; i++) pion[i] = 0;
                
                // Init des différentes valeurs
                info_structure_res[structure] = parcours_structure(grille, tuiles_placees[*index], tuiles_placees[*index].cotes[structure], structure, &score, pion, 0);
                info_structure_score[structure] = score;
                // printf("Fin score : %d\n", score);
                // printf("STOP PARCOURS (petit debug tuile de départ %d)\n", tuiles_placees[0].m.id);
                // Donne le plus grand nombre de pion posés par un ou plusieurs joueurs
                // printf("DEBUG: AVANT init maxi pion %d\n", pion[0]);
                int maxi_pion = 0;
                // printf("DEBUG: init maxi pion %d\n", maxi_pion);
                // Def maxi_pion
                for(int joueur = 0; joueur < nb_joueurs; joueur++){
                    info_structure_pion[structure][joueur] = pion[joueur];
                    if (maxi_pion < pion[joueur]){
                        maxi_pion = pion[joueur];
                    }
                }
                liste_maxi_pion[structure] = maxi_pion;
                if(info_structure_res[structure] == 1){
                    // printf("Bien rentré dans le if\n");
                    // Cas où la structure est fermée, lock partiellement la tuile
                    lock_structure(grille, tuiles_placees, -2);
                }
                
                
                // Vérifie si aucun pion
                if(maxi_pion == 0){
                    emplacement_pion[structure] = 1;
                    // printf("DEBUG Emplacement pion: %d, structure: %d", emplacement_pion[structure], structure);
                }
                // Reset parcours
                reset_traitee(grille, tuiles_placees);
                // printf("\e[41mResultat de la vérif de la structure %c: %d et score actuel du parcours : %d\e[0m\n", tuiles_placees[*index].cotes[structure], info_structure_res[structure], score);
            }
            // else printf("\n\e[42mCas de pre non pris en compte\e[0m\n");
        }

        // Choix du joueur pour placer des pions
        // Détermine si il y a au moins un emplacement libre
        // printf("OK ??\n");
        int cond_placement = 0;
        for(int p = 0; p < 5; p++){
            if(emplacement_pion[p] != 0){
                cond_placement = 1;
            } 
        }


        // Détermine si le joueur possède au moins un pion et si oui, le propose de le placer
        if (cond_placement == 1 && j[joueur_actuel].nbm > 0){
            printf("Voulez vous poser un pion ? (O/N) ");
            char pose;  
            if(j[joueur_actuel].ia == 0){
                do {
                    scanf("%c", &pose);
                    clearBuffer();
                    printf("\n");
                }
                while(pose != 'O' && pose != 'N');
            }
            else{
                int choix_pose[2] = {'O', 'N'};
                pose = choix_pose[rand()%2];
                printf("%c\n", pose);
                sleep(1); // Pause de 1se
            }

            if(pose == 'O'){
                // Def l'id du pion
                grille[liste_placements[e].y][liste_placements[e].x].m.id = joueur_actuel;
                // Def la variable de la position du pion
                int p = 0;
                char choix;
                if(j[joueur_actuel].ia == 1){
                    // printf("OK2\n");
                    p = rand()%5;
                    int choix_direction[2] = {'a', 'e'};
                    choix = choix_direction[rand()%2];
                }
                // Place le pion uniquement a l'endre disponible le plus proche
                while(emplacement_pion[p] == 0) p = (p + 1)%5;
                // Place le pion
                grille[liste_placements[e].y][liste_placements[e].x].m.cotes = p;
                // printf("DEBUG GRILLE MEEPLE: structure %d\n", grille[liste_placements[e].y][liste_placements[e].x].m.cotes);
                affichage(grille, taille_x, taille_y, grille[liste_placements[e].y][liste_placements[e].x], joueur_actuel, j, nb_joueurs, *index);
                printf("Choisissez l'emplacement du pion (v: placer le pion, a: emplacement précédent, e: emplacement suivant): ");
                do {
                    printf("\n");
                    // printf("DEBUG 2 Emplacement_pion: %d, structure %d\n", emplacement_pion[p], p);
                    if(j[joueur_actuel].ia == 0){
                        scanf("%c", &choix);
                        clearBuffer();
                    }
                    if(choix == 'a'){
                        // printf("a selectionné\n");
                        p--;
                        if(p < 0) p = 4;
                        while(emplacement_pion[p] == 0){
                            if(p < 0) p = 4;
                            else p = (p - 1);
                        }
                        // Place le pion 
                        grille[liste_placements[e].y][liste_placements[e].x].m.cotes = p;
                        affichage(grille, taille_x, taille_y, grille[liste_placements[e].y][liste_placements[e].x], joueur_actuel, j, nb_joueurs, *index);
                        printf("Choisissez l'emplacement du pion (v: placer le pion, a: emplacement précédent, e: emplacement suivant): ");
                    }

                    if(choix == 'e'){
                        p = (p + 1)%5;
                        while(emplacement_pion[p] == 0){
                            p = (p + 1)%5;
                        } 
                        // Place le pion
                        grille[liste_placements[e].y][liste_placements[e].x].m.cotes = p;
                        affichage(grille, taille_x, taille_y, grille[liste_placements[e].y][liste_placements[e].x], joueur_actuel, j, nb_joueurs, *index);
                        printf("Choisissez l'emplacement du pion (v: placer le pion, a: emplacement précédent, e: emplacement suivant): ");
                    }

                    if(j[joueur_actuel].ia == 1) choix = 'v';
                }
                while(choix != 'v');
                // printf("Pion placée !\n");
                j[joueur_actuel].nbm--;

                // Maj du max si nécessaire
                info_structure_pion[p][joueur_actuel] ++; // Ajoute un pion a la liste
                for(int structure = 0; structure < 4; structure++){
                    int maxi_pion = 0;
                    // printf("DEBUG: init maxi pion %d\n", maxi_pion);
                    // Def maxi_pion
                    for(int joueur = 0; joueur < nb_joueurs; joueur++){
                        if (maxi_pion < info_structure_pion[structure][joueur]){
                            maxi_pion = info_structure_pion[structure][joueur];
                        }
                    }
                    liste_maxi_pion[structure] = maxi_pion;
                }
                // printf("Mise à jour nbm pour %d: %d\n", joueur_actuel, j[joueur_actuel].nbm);
            }
        }
        // Def de finitions de structure
        // Abbaye
        struct coords c_abbaye = verif_abbaye(grille, tuiles_placees[*index]);
        // printf("Vérif abbaye : %d %d %d\n", c_abbaye.x != tuiles_placees[*index].c.x, grille[c_abbaye.y][c_abbaye.x].m.id != -1, grille[c_abbaye.y][c_abbaye.x].m.cotes == 4);
        if(c_abbaye.x != tuiles_placees[*index].c.x && grille[c_abbaye.y][c_abbaye.x].m.id != -1 && grille[c_abbaye.y][c_abbaye.x].m.cotes == 4){    
            int res = score_abbaye(grille, grille[c_abbaye.y][c_abbaye.x].c.x, grille[c_abbaye.y][c_abbaye.x].c.y);
            printf("RES = %d\n", res);
            if(res == 9){
                printf("ABBAYE COMPLETE !!!\n");
                // Attribution des points de l'abbaye
                j[grille[c_abbaye.y][c_abbaye.x].m.id].score += 9;
                j[grille[c_abbaye.y][c_abbaye.x].m.id].nbm++;
                grille[c_abbaye.y][c_abbaye.x].traitee[4] = -2;
            }
        }
        // Autres
        lock_structure(grille, tuiles_placees, -1);
        for(int structure = 0; structure < 4; structure++){
            if(info_structure_res[structure] == 1){
                // printf("DEBUG LISTE MAXI : %d\n", liste_maxi_pion[structure]);
                // Si un joueur a un nombre de pion = à maxi_pion, rajoute le score
                if(liste_maxi_pion[structure] != 0){
                    for(int joueur = 0; joueur < nb_joueurs; joueur++){
                        // Attribution des points
                        if(info_structure_pion[structure][joueur] == liste_maxi_pion[structure]){
                            j[joueur].score += info_structure_score[structure];
                            // printf("DEBUG Score du joueur %d: %d\n", joueur, j[joueur].score);
                        }
                        // Redistribue les pions
                        j[joueur].nbm += info_structure_pion[structure][joueur];
                        // printf("DEBUG structure complète nb pion par joueur: (j%d) %d\n", joueur, j[joueur].nbm);
                    }
                }
            }
        }
    }
    else{
        // printf("\e[43mRepioche car aucun emplacement trouvé\e[0m\n");
        pioche[*index].id = *index;
        (*index)--;
        melange_pioche(pioche);
    }


    

    // printf("\nDebug tuiles_placees:\n");
    // for(int i = 0; i < 5; i++){
    //     printf("id %d: %d\n", i, tuiles_placees[i].id);
    // }
    // printf("Tuiles restantes: %d\n", 72-(*index));

    return 1;
}

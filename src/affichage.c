#include "game_structures.h"
#include <stdio.h>
#include <stdlib.h>

#define G 143 // Taille de la grille
#define N 8 // Taille de l'affichage de la grille

int recherche_tuile(struct tuile_s grille[G][G], int lig, int dx){
    /* Permet de faire le cas de ligne vide:
    Prend en paramètres la grille, la ligne à étudier, et la valeurs de départ de la colonne 
    (pour éviter de check toute la ligne) */

    for(int col = dx; col < dx+N; col++){
        if(grille[lig][col].id != -1){
            return 1;
        }
    }
    return 0;
}

void affichage_couleurs(char c, int id, int m, int traitee){
    if(id == -2){
        printf("\e[40m\e[0;37m%c\e[0m", c);
    }
    // Cas si il y a un pion sur la tuile
    else if(m != -1){
        if(c == 'v') printf("\e[41m%d\e[0m", m); // Rouge
        if(c == 'p') printf("\e[42m%d\e[0m", m); // Vert
        if(c == 'a') printf("\e[45m%d\e[0m", m); // Violet
        if(c == 'r') printf("\e[44m%d\e[0m", m); // Bleu foncé
        if(c == 'f') printf("\e[40m%d\e[0m", m); // Noir
        if(c == 'b') printf("\e[43m%d\e[0m", m); // Jaune
    }
    else if(traitee == -1){
        printf("\e[47m\e[30m%c\e[0m", c);
    }
    else{
        if(c == 'v') printf("\e[41m \e[0m"); // Rouge
        if(c == 'p') printf("\e[42m \e[0m"); // Vert
        if(c == 'r') printf("\e[44m \e[0m"); // Bleu foncé
        if(c == 'a') printf("\e[45m \e[0m"); // Violet
        if(c == 'f') printf("\e[40m \e[0m"); // Noir
        if(c == 'b') printf("\e[43m \e[0m"); // Jaune
    }
}

void affichage_joueurs(struct joueur * j, int nb_joueurs){
    // Affichage de l'entête
    for(int joueur = 0; joueur < nb_joueurs; joueur++){
        printf("Joueur %d\t\t", joueur);
    }
    printf("\n");
    for(int joueur = 0; joueur < nb_joueurs; joueur++){
        printf("Score: %d Meeples: %d\t", j[joueur].score, j[joueur].nbm);
    }
    printf("\n\n");
}

void afficher_tuile(struct tuile_s t){
    // Fonction de debug de tuile
    // system("clear");
    printf("\t%c\n%c\t%c\t%c\n\t%c\n", t.cotes[1], t.cotes[0], t.centre, t.cotes[2], t.cotes[3]);
    printf("\n\n");
}

void affichage(struct tuile_s grille[G][G], int dx, int dy, struct tuile_s tuile, int id_joueur, struct joueur * j, int nb_joueurs, int index){
    /* Affiche la grille qui affichera un terrain de taille 143x143.
    L'affichage ne montrera qu'un segment du terrain qui sera de taille 8x8 
    Les paramètres dx/dy placent la grille à certaines coordonnées*/

    system("clear");

    affichage_joueurs(j, nb_joueurs);
    
    printf("    "); // Espacement de base de l'axe (pour éviter de commencer au début)
    for(int col = dx; col < dx+N; col++){
        // Def coords axes x
        if(col/10 >= 1) printf("%d ", col); // Condition permettant de centrer les chiffres
        else printf(" %d ", col);
    }
    printf("\n");
    for(int lig = dy; lig < dy+N; lig++){
        printf("\n");
        
        // Véfif tuile
        if(recherche_tuile(grille, lig, dx) == 1){
            // Tête(s) de tuile(s)
            printf("     "); // Esp de 5 depuis l'axe, sinon ?
            for(int col = dx; col < dx+N; col++){
                if(grille[lig][col].id != -1){
                    // Place un pion si il en existe un sur la tuile dans la grille
                    if(grille[lig][col].traitee[1] != -1 && grille[lig][col].m.id != -1 && grille[lig][col].m.cotes == 1){
                        affichage_couleurs(grille[lig][col].cotes[1], grille[lig][col].id, grille[lig][col].m.id, 0); printf("  ");
                    }
                    else {
                        affichage_couleurs(grille[lig][col].cotes[1], grille[lig][col].id, -1, grille[lig][col].traitee[1]); 
                        printf("  ");
                    }
                    // printf("%c  ", grille[lig][col].cotes[1]);
                }
                else printf("   ");
            }
            
            // Affichage du joueur au dessus de la prévisu à droite
            if(lig == dy){
                printf("       ");
                printf("Joueur %d", id_joueur);
            }

            // Affichage tête de la tuile à droite
            if(lig == dy+1){
                // Espacement avec la grille + affichage tête
                printf("   \t%c", tuile.cotes[1]);
            }

            // Axe y
            if(lig/10 >= 1) printf("\n%d", lig);
            else printf("\n %d", lig);
            
            // Corps de tuile(s)
            printf("  "); // Esp de 4 depuis l'axe
            for(int col = dx; col < dx+N; col++){
                if(grille[lig][col].id != -1){
                    if(grille[lig][col].traitee[0] != -1 && grille[lig][col].m.id != -1 && grille[lig][col].m.cotes == 0){
                        affichage_couleurs(grille[lig][col].cotes[0], grille[lig][col].id, grille[lig][col].m.id, 0); 
                    }
                    else affichage_couleurs(grille[lig][col].cotes[0], grille[lig][col].id, -1, grille[lig][col].traitee[0]); 

                    if(grille[lig][col].traitee[4] != -1 && grille[lig][col].m.id != -1 && grille[lig][col].m.cotes == 4){
                        affichage_couleurs(grille[lig][col].centre, grille[lig][col].id, grille[lig][col].m.id, 0); 
                    }
                    else affichage_couleurs(grille[lig][col].centre, grille[lig][col].id, -1, grille[lig][col].traitee[4]); 
                    
                    if(grille[lig][col].traitee[2] != -1 && grille[lig][col].m.id != -1 && grille[lig][col].m.cotes == 2){
                        affichage_couleurs(grille[lig][col].cotes[2], grille[lig][col].id, grille[lig][col].m.id, 0);
                    }
                    else affichage_couleurs(grille[lig][col].cotes[2], grille[lig][col].id, -1, grille[lig][col].traitee[2]);
                    // printf("%c%c%c", grille[lig][col].cotes[0], grille[lig][col].centre, grille[lig][col].cotes[2]);
                }
                else printf("   ");
            }

            // Affichage corps de la tuile à droite
            if(lig == dy+1){
                // Espacement avec la grille + affichage corps
                printf("   %c\t%c\t%c", tuile.cotes[0], tuile.centre, tuile.cotes[2]);
            }

            // Pied de tuile(s)
            printf("\n     ");
            for(int col = dx; col < dx+N; col++){
                if(grille[lig][col].id != -1){
                    if(grille[lig][col].traitee[3] != -1 && grille[lig][col].m.id != -1 && grille[lig][col].m.cotes == 3){
                        affichage_couleurs(grille[lig][col].cotes[3], grille[lig][col].id, grille[lig][col].m.id, 0); printf("  ");
                    }
                    else {
                        affichage_couleurs(grille[lig][col].cotes[3], grille[lig][col].id, -1, grille[lig][col].traitee[3]);
                        printf("  ");
                    }
                    // printf("%c  ", grille[lig][col].cotes[3]);
                } 
                else printf("   ");
            }

            // Affichage pied de la tuile à droite
            if(lig == dy+1){
                // Espacement avec la grille + affichage pied
                printf("   \t%c", tuile.cotes[3]);
            }
            if(lig == dy+2){
                printf("  ");
                printf("Tuiles restantes: %d", 72-index);
            }
        }
        else{
            // Affichage du joueur au dessus de la prévisu à droite
            if(lig == dy){
                printf("\t\t\t\t    ");
                printf("Joueur %d", id_joueur);
            } 
            // Affichage tête de la tuile à droite
            if(lig == dy+1){
                // Espacement avec la grille + affichage tête
                printf("\t\t\t\t");
                printf("   \t%c", tuile.cotes[1]);
            }
            
            // Def coords axes y
            if(lig/10 >= 1) printf("\n%d", lig);
            else printf("\n %d", lig);

            // Affichage corps de la tuile à droite
            if(lig == dy+1){
                printf("\t\t\t       ");
                // Espacement avec la grille + affichage corps
                printf("%c\t%c\t%c", tuile.cotes[0], tuile.centre, tuile.cotes[2]);
            }
            
            printf("\n");


            // Affichage pied de la tuile à droite
            if(lig == dy+1){
                printf("\t\t\t\t");
                // Espacement avec la grille + affichage pied
                printf("   \t%c", tuile.cotes[3]);
            }

            if(lig == dy+2){
                printf("\t\t\t       ");
                printf("Tuiles restantes: %d", 72-index);
            }

        }
    }
    printf("\n\nLegende: \e[41m  \e[0m: Ville       \e[43m  \e[0m: Blason       \e[44m  \e[0m: Route       \e[45m  \e[0m: Abbaye       \e[42m  \e[0m: Pré       \e[40m  \e[0m: Village");
    printf("\n\n");
}
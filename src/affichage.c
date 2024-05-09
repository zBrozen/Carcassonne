#include "game_structures.h"
#include <stdio.h>
#include <stdlib.h>

#define N 16 // Taille de l'affichage de la grille

int recherche_tuile(struct tuile_s grille[72][72], int lig, int dx){
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

void affichage_couleurs(char c, int id){
    if(id == -2){
        printf("\e[40m\e[0;37m%c\e[0m", c);
    }
    else{
        if(c == 'v') printf("\e[41m%d\e[0m", id); // Rouge
        if(c == 'p') printf("\e[42m%d\e[0m", id); // Vert
        if(c == 'r') printf("\e[46m%d\e[0m", id); // Bleu cyan
        if(c == 'a') printf("\e[45m%d\e[0m", id); // Violet
        if(c == 'f') printf("\e[44m%d\e[0m", id); // Bleu foncé
        if(c == 'b') printf("\e[43m%d\e[0m", id); // Jaune
    }
}

void affichage(struct tuile_s grille[72][72], int dx, int dy){
    /* Affiche la grille qui affichera un terrain 72x72.
    L'affichage ne montrera qu'un segment du terrain qui sera de taille 16x16 
    Les paramètres dx/dy placent la grille à certaines coordonnées*/

    // system("clear");
    
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
                    affichage_couleurs(grille[lig][col].cotes[1], grille[lig][col].id); printf("  ");
                    // printf("%c  ", grille[lig][col].cotes[1]);
                }
                else printf("   ");
            }
            // Axe y
            if(lig/10 >= 1) printf("\n%d", lig);
            else printf("\n %d", lig);
            
            // Corps de tuile(s)
            printf("  "); // Esp de 4 depuis l'axe
            for(int col = dx; col < dx+N; col++){
                if(grille[lig][col].id != -1){
                    affichage_couleurs(grille[lig][col].cotes[0], grille[lig][col].id); 
                    affichage_couleurs(grille[lig][col].centre, grille[lig][col].id); 
                    affichage_couleurs(grille[lig][col].cotes[2], grille[lig][col].id);
                    // printf("%c%c%c", grille[lig][col].cotes[0], grille[lig][col].centre, grille[lig][col].cotes[2]);
                }
                else printf("   ");
            }

            // Pied de tuile(s)
            printf("\n     ");
            for(int col = dx; col < dx+N; col++){
                if(grille[lig][col].id != -1){
                    affichage_couleurs(grille[lig][col].cotes[3], grille[lig][col].id); printf("  ");
                    // printf("%c  ", grille[lig][col].cotes[3]);
                } 
                else printf("   ");
            }
        }
        else{
        // Def coords axes y
        if(lig/10 >= 1) printf("\n%d", lig);
        else printf("\n %d", lig);
        printf("\n");
        }
    }
    printf("\n\n");
}
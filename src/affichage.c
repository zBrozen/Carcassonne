#include "game_structures.h"
#include <stdio.h>
#include <stdlib.h>

void affichage(struct tuile_s * grille, int dx, int dy){
    /* Affiche la grille qui affichera un terrain 72x72.
    L'affichage ne montrera qu'un segment du terrain qui sera de taille 16x16 */
    
    for(int col = dx; col < dx+16; col++){
        // Def coords axes x
        if(col/10 >= 1) printf("%d   ", col);
        else printf(" %d   ", col);
    }
    for(int lig = dy+1; lig < dy+16; lig++){
        // Def test tuile
        printf("\n");
        printf("     "); // 2 esp pour l'axe + 3 esp pour la tête de la tuile
        printf("%c", grille[0].cotes[1]);
        // Def coords axes y
        if(lig/10 >= 1) printf("\n%d", lig);
        else printf("\n %d", lig);
        // Suite test tuile

    }
    printf("\n\n");
}
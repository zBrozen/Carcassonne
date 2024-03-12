#include "game_structures.h"
#include <stdio.h>

void affichage(struct tuile_s * grille, int dx, int dy){
    int t = 0;
    if(dx+10 < 37 && dy+10 < 37){
        // Afficher axe x
        printf("    ");
        for(int col = dx; col < dx+10; col++){
            if(col/10 >= 1) printf("%d   ", col);
            else printf(" %d   ", col);
        }
        // Afficher axe y (+ potentielles tuiles)
        printf("\n\n");
        for(int lig = dy; lig < dy+10; lig++){
            // Ex espacement (de 5)
            if(lig < dy+1){
                t = 1;
                printf("     ");
                printf("N");
            }
            else t = 0;

            // Saut de ligne 1
            if(lig/10 >= 1) printf("\n%d", lig);
            else printf("\n %d", lig);

            // Affichage ligne ECO (est, centre, ouest)
            if(lig < dy+1){
                printf("  "); // Esp de 2
                printf("ECO");
            }

            // Affichage Sud
            if(lig < dy+1){
            printf("\n     "); // Esp de 5
            printf("S");
            }

            // Fin de ligne de tuile (donc de hauteur 3)
            if(t == 0)printf("\n\n");
            else printf("\n");
        }
    }
}
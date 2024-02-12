#include "game_structures.h"
#include "lecteur_csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Token Github: 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

struct tuile_s pioche[72];

int main(int argc, char * argv[])
{
    struct tuile_s t;

    printf("\033[41m \033[0m");
    t.id = 0;
    t.cotes[0] = 'R';
    t.cotes[1] = 'V';
    t.cotes[2] = 'R';
    t.cotes[3] = 'P';
    
    // aleatoire mélange
    srand(time(NULL));
    int i, ra, temp;
    int t_ordre[16];

    for(i = 0 ; i < 16; i++){
        t_ordre[i] = i;
        printf("t_ordre[%d]=%d\n", i, t_ordre[i]);
    }

    printf("\n");

    for(i = 16; i > 0; i--){
        /* Permet de sélectionner toutes les position de la pioche sans prendre la première tuile */
        ra = (rand()% i)+1;
        temp = t_ordre[i];
        t_ordre[i] = t_ordre[ra];
        t_ordre[ra] = temp;
        printf("t_melange[%d]=%d\n", i, t_ordre[i]);
    }
    printf("t_melange[%d]=%d\n", 0, t_ordre[0]);

    parseur_csv("tuiles_base_simplifiees.csv", pioche);
    //printf("%c %c %c %c %c", pioche[0].cotes[0], pioche[0].cotes[1], pioche[0].cotes[2], pioche[0].cotes[3], pioche[0].centre);
    afficher_tuile(pioche[71]);
    printf("FIN\n");
    return 0;
}

void afficher_tuile(struct tuile_s t){
    printf("\t%c\n%c\t%c\t%c\n\t%c\n", t.cotes[1], t.cotes[0], t.centre, t.cotes[2], t.cotes[3]);
}
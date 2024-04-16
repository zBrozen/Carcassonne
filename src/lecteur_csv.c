#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "lecteur_csv.h"
#include "game_structures.h"

void parseur_csv(char * fname, struct tuile_s * pioche)
{
    FILE * fic = fopen(fname, "r");
    if(fic == NULL){
        printf("Erreur d'ouverture du fichier, veuillez entrer un autre nom/repertoire.");
    }
    char e, n, w, s, c;
    char line[100];
    int tuile = 0;
    
    while(fgets(line, sizeof(line), fic) != NULL && tuile < 72){
        // Recupere chaque mot a partir de line def dans le fgets
        char * token = strtok(line, ",");

        // Definition
        e = token[0];
        token = strtok(NULL, ",");
        n = token[0];
        token = strtok(NULL, ",");
        w = token[0];
        token = strtok(NULL, ",");
        s = token[0];
        token = strtok(NULL, ",");
        if(token[4] == 'a') c = 'f';
        else c = token[0];

        pioche[tuile].id = tuile;
        pioche[tuile].cotes[0] = e;
        pioche[tuile].cotes[1] = n;
        pioche[tuile].cotes[2] = w;
        pioche[tuile].cotes[3] = s;
        pioche[tuile].centre = c;
        tuile ++;
    }
    fclose(fic);
    melange_pioche(pioche);
}

void melange_pioche(struct tuile_s * pioche){
    srand(time(NULL));
    int i, ra, tempid;
    char tempc0, tempc1, tempc2, tempc3, tempc4;

    for(i = 71; i > 0; i--){
        /* Permet de sélectionner toutes les position de la pioche sans prendre la première tuile */
        ra = (rand()% i)+1;

        // Save des temps de i
        tempid = pioche[i].id;
        tempc0 = pioche[i].cotes[0];
        tempc1 = pioche[i].cotes[1];
        tempc2 = pioche[i].cotes[2];
        tempc3 = pioche[i].cotes[3];
        tempc4 = pioche[i].centre;

        // Permutation entre i et ra
        pioche[i].id = pioche[ra].id;
        pioche[i].cotes[0] = pioche[ra].cotes[0];
        pioche[i].cotes[1] = pioche[ra].cotes[1];
        pioche[i].cotes[2] = pioche[ra].cotes[2];
        pioche[i].cotes[3] = pioche[ra].cotes[3];
        pioche[i].centre = pioche[ra].centre;

        // Redef de ra avec les temp de i
        pioche[ra].id = tempid;
        pioche[ra].cotes[0] = tempc0;
        pioche[ra].cotes[1] = tempc1;
        pioche[ra].cotes[2] = tempc2;
        pioche[ra].cotes[3] = tempc3;
        pioche[ra].centre = tempc4;

        //printf("t_melange[%d]=%d\n", i, t_ordre[i]);
    }
}
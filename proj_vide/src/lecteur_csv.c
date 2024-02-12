#include <stdio.h>
#include <stdlib.h>
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
        c = token[0];

        pioche[tuile].id = tuile;
        pioche[tuile].cotes[0] = e;
        pioche[tuile].cotes[1] = n;
        pioche[tuile].cotes[2] = w;
        pioche[tuile].cotes[3] = s;
        pioche[tuile].centre = c;
        tuile ++;
    }
    fclose(fic);
}
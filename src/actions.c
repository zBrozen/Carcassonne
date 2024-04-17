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

struct tuile_s def_liste_placements(struct tuile_s tuiles_placees[72], struct tuile_s tuile){
    struct tuile_s liste[72];
    int index = 0, t = 0;

    for(t; t < 72 && tuile_placees[t].id != -1; t++){

    }
}

int tour(struct joueur j, struct tuile_s pioche[72], struct tuile_s grille[72][72], struct tuile_s tuiles_placees[72], int index){
    /*Effectue un tour pour un certain joueur (ne se lance que si index < 72)*/
    
    // Pioche de tuile
    struct tuile_s tuile;
    tuile = piocher(pioche, index);
    afficher_tuile()
    
    // Manipulation tuile
    int sens = 0;
    while(sens != -1){
        printf("Entrer un sens: ");
        scanf("%d", sens);
        if(sens == 0 || sens == 1) rotation(tuile, sens);
        else if (sens == -1) printf("Rotation terminée\n");
        else printf("Entrée incorrecte");
        afficher_tuile(tuile);
    }


}
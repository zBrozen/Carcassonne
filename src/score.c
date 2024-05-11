#include "game_structures.h"
#include <stdio.h>
#include <stdlib.h>

void reset_traitee(struct tuile_s tuiles_placees[72]){
    for(int i = 0; i < 72 && tuiles_placees[i].id != -1; i++){
        tuiles_placees[i].traitee[0] = 0;
        tuiles_placees[i].traitee[1] = 0;
        tuiles_placees[i].traitee[2] = 0;
        tuiles_placees[i].traitee[3] = 0;
        tuiles_placees[i].traitee[4] = 0;
        
    }
}

int poser_pion(struct joueur j, struct tuile_s grille[72][72], struct tuile_s tuile, int cotes, int res){
    /* Fonction permettant de déterminer si un pion peut être posée, donc si aucun autre n'est voisin de la tuile actuelle 
    Prend en paramètre le cotes qui déterminera le type de structure sur laquelle le pion doit être posé*/

    int sens = 0; // Indique le sens dans lequel parcourir la tuile (vers le centre: 0, vers l'extérieur: 1, vers un bord: 2)
    // Conditions qui compare le type de structure entre le bord ou le centre, avec une autre tuile, le centre, ou un bord de tuile
    if(cotes == 3 && tuile.traitee[3] == 0){
        if(sens == 1){
            if(tuile.cotes[3] == grille[tuile.c.y+1][tuile.c.x].cotes[1]){
                tuile.traitee[3] = 1;
                // res = poser_pion(j, grille, grille[tuile.c.y+1][tuile.c.x], 1, res);
            }
        }
        // else if(sens == 0){
        //     if(tuile.cotes[3] == tuile.centre){

        //     }
        // }
    }
    return res;
    // if(cotes == 1){
    //     if(tuile.cotes[1] == grille[tuile.c.y-1][tuile.c.x].cotees[3])
    // }
    
    // if(cotes == 2){
    //     if(tuile.cotes[2] == grille[tuile.c.y][tuile.c.x+1].cotees[0])
    // }
    // if(cotes == 0){
    //     if(tuile.cotes[0] == grille[tuile.c.y][tuile.c.x-1].cotees[2])
    // }
}

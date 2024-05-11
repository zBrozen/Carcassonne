#ifndef AFFICHAGE
#define AFFICHAGE
#include "game_structures.h"

int recherche_tuile(struct tuile_s grille[72][72], int lig, int dx);

void afficher_tuile(struct tuile_s t);

void affichage_couleurs(char c, int id);

void affichage(struct tuile_s grille[72][72], int dx, int dy);

#endif // Affichage

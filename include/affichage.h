#ifndef AFFICHAGE
#define AFFICHAGE
#include "game_structures.h"

#define G 143

int recherche_tuile(struct tuile_s grille[G][G], int lig, int dx);

void affichage_joueurs(struct joueur * j, int nb_joueurs);

void afficher_tuile(struct tuile_s t);

void affichage_couleurs(char c, int id);

void affichage(struct tuile_s grille[G][G], int dx, int dy, struct tuile_s tuile, int id_joueur, struct joueur * j, int nb_joueurs, int index);

#endif // Affichage

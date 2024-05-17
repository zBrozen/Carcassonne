#ifndef ACTIONS
#define ACTIONS
#include "game_structures.h"

#define G 143

void clearBuffer();

struct tuile_s piocher(struct tuile_s pioche[72], int index);

struct tuile_s rotation(struct tuile_s tuile, int sens);

struct tuile_s copie(struct tuile_s tuile);

int doublon(struct coords liste_placements[72], struct tuile_s tuiles_placees[72], int t, int add_x, int add_y, int nb_rota);

void def_liste_placements(struct coords liste[72], struct tuile_s grille[G][G], struct tuile_s tuiles_placees[72], struct tuile_s tuile);

void add_gr(struct tuile_s grille[G][G], struct tuile_s tuile, int x, int y);

void rem_gr(struct tuile_s grille[G][G], int x, int y);

void previsu(struct tuile_s grille[G][G], struct tuile_s tuile, struct coords liste_compa[72], int l_index);

int tour(struct joueur * j, struct tuile_s pioche[72], struct tuile_s grille[G][G], struct tuile_s tuiles_placees[72], int * index, int nb_joueurs, int joueur_actuel);

#endif // ACTION
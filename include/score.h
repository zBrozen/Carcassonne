#ifndef SCORE
#define SCORE
#include "game_structures.h"

#define G 143

void reset_traitee(struct tuile_s grille[G][G], struct tuile_s tuiles_placees[72]);

void lock_structure(struct tuile_s grille[G][G], struct tuile_s tuiles_placees[72]);

int parcours_structure(struct tuile_s grille[G][G], struct tuile_s tuile_actuelle, char structure, int position, int * score, int * pion);

int poser_pion(struct joueur j, struct tuile_s grille[G][G], struct tuile_s tuile, int cotes, int res);

#endif // SCORE
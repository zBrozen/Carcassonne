#ifndef SCORE
#define SCORE
#include "game_structures.h"

#define G 143

void reset_traitee(struct tuile_s grille[G][G], struct tuile_s tuiles_placees[72]);

void lock_structure(struct tuile_s grille[G][G], struct tuile_s tuiles_placees[72], int value);

int parcours_structure(struct tuile_s grille[G][G], struct tuile_s tuile_actuelle, char structure, int position, int * score, int * pion);

struct coords verif_abbaye(struct tuile_s grille[G][G], struct tuile_s tuile_actuelle);

int score_abbaye(struct tuile_s grille[G][G], int x, int y);

#endif // SCORE
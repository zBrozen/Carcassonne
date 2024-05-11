#ifndef SCORE
#define SCORE
#include "game_structures.h"

#define G 143

void reset_traitee(struct tuile_s tuiles_placees[72]);

int poser_pion(struct joueur j, struct tuile_s grille[G][G], struct tuile_s tuile, int cotes, int res);

#endif // SCORE
#ifndef GAME_STRUCTURES
#define GAME_STRUCTURES

struct tuile_s{
    int id;
    char cotes[4]; 
    char centre;
};

void init_grille(struct tuile_s grille[72][72]);
void afficher_tuile(struct tuile_s t);

// Fonctions dans affichage.c
int recherche_tuile(struct tuile_s grille[72][72], int lig, int dx);
void affichage(struct tuile_s grille[72][72], int dx, int dy);

#endif // GAME_STRUCTURES

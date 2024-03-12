#ifndef GAME_STRUCTURES
#define GAME_STRUCTURES

struct coords{
    int x;
    int y;
};

struct tuile_s{
    int id;
    char cotes[4]; 
    char centre;
    struct coords c;
};



void afficher_tuile(struct tuile_s t);

void affichage(struct tuile_s * grille, int dx, int dy);

#endif // GAME_STRUCTURES

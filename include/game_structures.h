#ifndef GAME_STRUCTURES
#define GAME_STRUCTURES

struct joueur{
    int id; // Caractérise le joueur et les meeples
    int nbm; // Nombre de meeples en main
    int ia; // 0: joueur , 1: ia
};

struct tuile_s{
    int id;
    char cotes[4]; 
    char centre;
    int meeple;
};

struct coords{
    int x;
    int y;
};

void init_grille(struct tuile_s grille[72][72]);
void afficher_tuile(struct tuile_s t);

// Fonctions dans affichage.c
int recherche_tuile(struct tuile_s grille[72][72], int lig, int dx);
void affichage_couleurs(char c);
void affichage(struct tuile_s grille[72][72], int dx, int dy);

// Fonctions dans actions.c
struct tuile_s piocher(struct tuile_s pioche[72], int index);
struct tuile_s rotation(struct tuile_s tuile, int sens);

#endif // GAME_STRUCTURES

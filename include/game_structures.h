#ifndef GAME_STRUCTURES
#define GAME_STRUCTURES

struct coords{
    int x;
    int y;
    int rota; // Paramètres supp pour faire une rota pour placement tuile
};

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
    struct coords c;
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
struct coords * def_liste_placements(struct tuile_s grille[72][72], struct tuile_s tuiles_placees[72], struct tuile_s tuile);
void free_liste(struct coords * c);
int tour(struct joueur j, struct tuile_s pioche[72], struct tuile_s grille[72][72], struct tuile_s tuiles_placees[72], int index);

#endif // GAME_STRUCTURES

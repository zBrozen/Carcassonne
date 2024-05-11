#ifndef GAME_STRUCTURES
#define GAME_STRUCTURES

#define G 143

struct coords{
    int x;
    int y;
    int rota; // Paramètres supp pour faire une rota pour placement tuile
};

struct joueur{
    int id; // Caractérise le joueur et les meeples
    int nbm; // Nombre de meeples en main
    int score;
    int ia; // 0: joueur , 1: ia
};

struct meeple{
    int id; // Défini à quel joueur appartient le pion
    int cotes; // Défini le côté/centre sur lequel le pion est posé
};

struct tuile_s{
    int id;
    char cotes[4]; // Cotes de la tuile (ouest, nord, est, sud)
    char centre;
    struct meeple m[5]; // liste des potentiels meeples posés sur la tuile (ouest, nord, est, sud, centre)
    struct coords c;
    int traitee[5]; // Indicateur pour ne pas boucler dans les parcours récursifs (0 par défaut et 1 si partie de tuile traitee)
};

// Fonctions dans moteur_jeu.c
void init_grille(struct tuile_s grille[G][G]);
void init_tuiles_placees(struct tuile_s tuiles_placees[72]);
void init_joueur(struct joueur j, int id, int ia);

#endif // GAME_STRUCTURES

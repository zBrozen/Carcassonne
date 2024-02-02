#ifndef GAME_STRUCTURES
#define GAME_STRUCTURES

struct tuile_s{
    int identifiant;
    char cotes[4]; 
    char centre;
    // ...autres attributs...
};

void afficher_tuile(struct tuile_s t);

#endif // GAME_STRUCTURES

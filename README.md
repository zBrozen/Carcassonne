# Carcassonne Jeu
Ce projet est une implémentation en C du célèbre jeu de société Carcassonne. Il a été réalisé dans le cadre d'un premier projet de programmation universitaire.
L'objectif est de reproduire les mécaniques du jeu tout en respectant ses règles fondamentales et en explorant des concepts tels que les structures de données et l'algorithme.

---
## Table des matières
1. [Fonctionnalités](#fonctionnalités)
2. [Spécifications Techniques](#spécifications-techniques)
3. [Installation et Compilation](#installation-et-compilation)
4. [Rapport d'Analyse](#rapport-danalyse)
5. [Rapport d'Implémentation](#rapport-dimplémentation)

---

# Fonctionnalités
* Jeu jouable avec 1 à 5 joueurs, IA comprise.
* Respect des règles originales de Carcassonne.
* Gestion des tuiles, pions et points.
* Implémentation d'une IA basique (actions aléatoires).

---

# Spécifications Techniques

### Règles
Etapes définissant une partie de jeu:
	1. piocher une tuile
	2. poser la tuile:
		- Choix placement/orientation(0,90,180,270 degré)
	3. poser un pion/ou non
	4. finir le tour (joueur suivant):
		- compter points
		- changer de joueur
	5. fin de partie
		- comptage de points final
		- annonce du vainqueur
  
### Tuile: 
Liste des aspects d'une tuile:
- 4 côté
	type : pré, route, ville

- centre
	type : abbaye, fin de route, ville, route, pré

- posée ?
	oui : joueur qui pose
	non : pioche

- orientation ?

- coordonnées sur la grille
  
- pion ?
	si posé : à qui il appartient, quel emplacement sur la tuile (côtés/centre) 

- compatibilité avec les autres tuiles ?
  	cohérence avec le terrain de jeu pour poser la tuile

### Joueur:
- 1 à 5 joueurs (humains/IA)
  
- Actions (fonctions)
	piocher
	poser ma tuile (choix coord/rot)
	poser mon pion
	terminer tour

- Attributs (variables)
	id
	points
	pions (reserve et posés)
	activité (tour actif ou non)
		
### Pioche:
- Liste de tuiles non-piochées:
	Initialisation:
		tableau de tuile
		liste chainee
		liste de pointeur vers des tuiles
		pile
		file
	Melange:
		On applique une permutation sur la pioche directement (sans passer par un autre tableau) et penser à ne pas mélanger le premier élément #Revoir MelangeTabEx
- Actions:
	1 Joueur pioche: Dépiler
	2 test si vide: fin de partie

### Grille:
- Contient des tuiles
- dimensions 145x145 (statiquement)
- grille 2D grille[i][j]

### IA:
- Choisis une position aléatoire parmis les choix possibles

- Choisis de poser un pion ou non de manière aléatoire

---

# Installation et compilation
Ce projet est développé en C et est compilable sur un environnement Ubuntu.

## Etapes d'installation:
**1. Cloner le dépôt Github:**
	git clone https://github.com/zBrozen/Carcassonne.git

**2. Accéder au dossier du projet (répertoire racine, où se situe le makefile):**
	cd votre-repo

**3. Compiler le projet:**
	make

**4. Executer le programme:**
	./bin/carcassonne

---

# Rapport d'Analyse
Un rapport d'analyse accompagne le projet, expliquant:
* Les choix/idées de conception (structure de données, algorithmes).
* La structure du projet.
* Les limitation et amélioration possibles.

# Rapport d'Implémentation
Un rapport d'implémentation accompagne le projet, expliquant:
* La mise en place du rapport d'analyse.
* Des explications plus détaillées sur la structures et les algorithmes utilisés.

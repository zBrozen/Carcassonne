Carcassonne Jeu

Rendu C:
- Code C (std C99)
- Compilable sur Ubuntu (choix de bibliothèque adapaté)
- Code source sous git
- Rapport d'analyse:
	Explications des choix et de la structure du code

Spécification:
* Règles
	- faire une partie
		1 piocher une tuile
		2 poser la tuile:
			- Choix coord/orientation(0,90,180,270)
		3 poser un pion
		4 finir le tour (joueur suivant):
			- compter points
			- changer de joueur
		5 fin de partie
		6 IA fonctionnel (qui joue aléatoirement)

* Tuile: 
	- 4 côté
		type : pré, route, ville
	
	- centre
		type : abbaye, fin de route, ville, route, pré
	
	- posée ?
		oui : joueur qui pose
		non : pioche
	
	- orientation ?
	
	- pion ?
		oui : à qui il appartient
		      quel côté/centre
	
	- coordonnées
	
	- voisins
	
* Joueur:
	- 1 à 5 joueurs
	- 1 IA
	- Actions (fonctions)
		piocher -> * Pioche
		poser ma tuile (choix coord/rot) -> * Grille/* Tuile (pour rot)
		poser mon pion -> * Tuile
		terminer tour -> * Jeu(joueur pointé)
	- Attributs (variables)
		id
		points
		pions (reserve et posés)
		#actif (tour actif ou non : peut être placé dans la struct du jeu)
		
Pioche:
	- Liste de tuiles non-piochées:
		Initialisation:
			tableau de tuile
			liste chainee
			liste de pointeur vers des tuiles
			pile
			file
	- Actions:
		1 Joueur pioche: Dépiler
		2 test si vide: fin de partie

Grille:
	- Contient des tuiles
	- dimensions 145x145 (statiquement)
	- grille 2D grille[i][j]
	- grille 1D grille[i*j]

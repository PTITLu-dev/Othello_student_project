# ♟️ Othello (Reversi) - Bitboard Engine & Minimax AI

![C](https://img.shields.io/badge/Language-C-blue.svg)
![Optimization](https://img.shields.io/badge/Optimization-Bitboards-red.svg)
![AI](https://img.shields.io/badge/AI-Minimax-purple.svg)

## 📝 Description
Moteur de jeu **Othello (Reversi)** en C, développé en binôme dans le cadre d'un TP à l'Esisar (Grenoble INP). Notre IA a été confrontée à celles des autres binômes lors du tournoi de fin de TP.

L'objectif était de concevoir un moteur rapide capable de faire tourner une IA de recherche, tout en s'interfaçant avec un module de communication réseau TCP/IP (fourni par l'équipe pédagogique). Le moteur s'appuie sur la manipulation bas niveau (Bitboards) pour calculer les états de jeu instantanément.

## ✨ Fonctionnalités techniques
* **Optimisation par Bitboards :** L'état du plateau est représenté par des entiers de 64 bits (`uint64_t`), utilisant des masques (ex: `MUR_A`, `COIN_H1`) pour générer les coups possibles et les retournements de pions via des opérations binaires. Chaque génération de coups se fait en quelques opérations sur 64 bits, sans parcourir de tableau.
* **Intelligence Artificielle (Minimax) :** Le client `userSimpleIA.c` intègre un algorithme Minimax récursif (`minmax_complet`) explorant l'arbre des coups jusqu'à une profondeur de 6, sans élagage (voir les axes d'amélioration).
* **Heuristique stratégique :** La fonction `evaluer` analyse la qualité d'une position en ciblant en priorité la capture des coins et en maximisant la mobilité du bot par rapport à celle de l'adversaire.
* **Architecture Modulaire & Réseau :** Séparation stricte entre le moteur mathématique (`fonctions.c`), le client autonome (`userSimpleIA.c`), le client humain (`userSimple.c`), et le *wrapper* réseau (`userNetwork.h`) permettant des duels inter-machines.
* **Tests Unitaires :** Un pont adaptateur (`test_adaptateur.c`) permet de vérifier la fiabilité de la logique 64 bits contre un framework de test classique en tableau 2D

## ⚠️ Regard critique et Axes d'amélioration
Ce développement m'a permis d'approfondir la gestion de la mémoire et l'optimisation binaire. S'il fallait pousser ce projet au niveau supérieur, voici ce que j'implémenterais :

1. **Élagage Alpha-Beta :** Actuellement, le Minimax évalue toutes les branches de l'arbre. Ajouter un élagage Alpha-Beta permettrait de couper les branches inutiles et de doubler la profondeur de calcul de l'IA à temps d'exécution équivalent.
2. **Opening Book & Endgame Solver :** L'heuristique mathématique est solide, mais l'IA gagnerait à posséder une bibliothèque d'ouvertures pré-calculées, ainsi qu'un solveur parfait pour les 15 dernières cases.
3. **Interface Graphique :** Le jeu s'exécute aujourd'hui intégralement dans le terminal. L'ajout d'une surcouche graphique (SDL2/Raylib) rendrait le projet plus accessible.

## 🛠️ Compilation et Exécution

**Prérequis :** `gcc` et `make` sous Linux/Unix.

```bash
# Jeu local en terminal (2 joueurs humains) + programme de test du moteur
make
./othelo

# Clients réseau (IA et joueur humain) : nécessitent libothello.so,
# la librairie réseau fournie par l'Esisar, non redistribuée dans ce dépôt.
# Copiez-la à la racine du projet, puis :
make reseau
LD_LIBRARY_PATH=. ./userSimpleIA <password> <ip_serveur> <user_id>
LD_LIBRARY_PATH=. ./userSimple   <password> <ip_serveur> <user_id>

make clean
```

## 📂 Structure du code

**Moteur & IA** (développés par le binôme) :
- `fonctions.c` / `fonctions.h` : bitboards, génération des coups, retournements, Minimax et heuristique
- `main.c` : partie locale à deux joueurs dans le terminal
- `userSimpleIA.c` : client réseau piloté par l'IA
- `userSimple.c` : client réseau pour un joueur humain

**Tests** :
- `test.c` : programme de test qui rejoue des coups sur une grille 2D (`./test_othello <fichier>`)
- `test_adaptateur.c` : adaptateur entre le moteur 64 bits et ce programme de test

**Fourni par l'Esisar** :
- `userNetwork.h` (en-tête) et `libothello.so` (non incluse) : connexion au serveur de jeu

## 👥 Auteurs
PETIT Lucas
YOUSSEF Maïssa



Esisar - Fourniture de l'API réseau

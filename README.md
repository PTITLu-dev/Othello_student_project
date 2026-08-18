# ♟️ Othello (Reversi) - Bitboard Engine & Minimax AI

![C](https://img.shields.io/badge/Language-C-blue.svg)
![Optimization](https://img.shields.io/badge/Optimization-Bitboards-red.svg)
![AI](https://img.shields.io/badge/AI-Minimax-purple.svg)

## 📝 Description
Ce projet est un moteur de jeu ultra-optimisé pour **Othello (Reversi)**, développé en langage C dans le cadre de mon cursus à l'Esisar. 

L'objectif principal était de concevoir une architecture très performante capable de faire tourner une Intelligence Artificielle avancée, tout en s'interfaçant avec un module de communication réseau TCP/IP (fourni par l'équipe pédagogique). Le moteur s'appuie sur la manipulation bas niveau (Bitboards) pour calculer les états de jeu instantanément.

## ✨ Fonctionnalités techniques
* **Optimisation par Bitboards :** L'état du plateau est représenté par des entiers de 64 bits (`uint64_t`), utilisant des masques (ex: `MUR_A`, `COIN_H1`) pour générer les coups possibles et les retournements de pions via des opérations binaires. Cela réduit drastiquement la complexité algorithmique.
* **Intelligence Artificielle (Minimax) :** Le client `userSimpleIA.c` intègre un algorithme Minimax récursif (`minmax_complet`) explorant l'arbre des coups jusqu'à une profondeur de 6 (facilement extensible à 10+ grâce aux performances des bitboards).
* **Heuristique stratégique :** La fonction `evaluer` analyse la qualité d'une position en ciblant en priorité la capture des coins et en maximisant la mobilité du bot par rapport à celle de l'adversaire.
* **Architecture Modulaire & Réseau :** Séparation stricte entre le moteur mathématique (`fonctions.c`), le client autonome (`userSimpleIA.c`), le client humain (`userSimple.c`), et le *wrapper* réseau (`userNetwork.h`) permettant des duels inter-machines.
* **Tests Unitaires :** Un pont adaptateur (`test_adaptateur.c`) permet de vérifier la fiabilité de la logique 64 bits contre un framework de test classique en tableau 2D[cite: 5].

## ⚠️ Regard critique et Axes d'amélioration
Ce développement m'a permis d'approfondir la gestion de la mémoire et l'optimisation binaire. S'il fallait pousser ce projet au niveau supérieur, voici ce que j'implémenterais :

1. **Élagage Alpha-Beta :** Actuellement, le Minimax évalue toutes les branches de l'arbre. Ajouter un élagage Alpha-Beta permettrait de couper les branches inutiles et de doubler la profondeur de calcul de l'IA à temps d'exécution équivalent.
2. **Opening Book & Endgame Solver :** L'heuristique mathématique est solide, mais l'IA gagnerait à posséder une bibliothèque d'ouvertures pré-calculées, ainsi qu'un solveur parfait pour les 15 dernières cases.
3. **Interface Graphique :** Le jeu s'exécute aujourd'hui intégralement dans le terminal. L'ajout d'une surcouche graphique (SDL2/Raylib) rendrait le projet plus accessible.

## 🛠️ Compilation et Exécution

**Prérequis :** `gcc` et un environnement Linux/Unix.

```bash
# Compiler le projet complet (Moteur, IA, Humain, Tests)
make

# Lancer le client avec IA autonome
./userSimpleIA <password> <ip_serveur> <user_id>

# Lancer le client pour joueur Humain
./userSimple <password> <ip_serveur> <user_id>
```

## 📂 Structure du code
Moteur & IA (Développé par le binôme 11) :

fonctions.c / fonctions.h : Logique Bitboards, génération des coups, algorithme Minimax[cite: 5].

userSimpleIA.c : Boucle de jeu automatisée pour le bot[cite: 5].

userSimple.c : Interface CLI pour les commandes humaines[cite: 5].

test_adaptateur.c : Validations techniques[cite: 5].

Connectivité (Fourni par l'Esisar) :

userNetwork.h / libothello : Intégration réseau et gestion des sockets[cite: 5].

## 👥 Auteurs
PETIT Lucas
YOUSSEF Maïssa



Esisar - Fourniture de l'API réseau

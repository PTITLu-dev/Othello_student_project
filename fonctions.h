#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdio.h>
#include <stdlib.h> 
#include <stdint.h> 

typedef struct {
    uint64_t pions_joueur;
    uint64_t pions_adversaire;
} Plateau;


void init_plateau(uint64_t *pions_noirs, uint64_t *pions_blancs);

void afficher_plateau(uint64_t pions_noirs, uint64_t pions_blancs);

int count_bits(uint64_t calque);

uint64_t generer_coups_possibles(uint64_t mes_pions, uint64_t pions_adversaire);

Plateau jouer_coup(uint64_t mes_pions, uint64_t pions_adversaire, uint64_t coup);
int evaluer(uint64_t mes_pions, uint64_t pions_adv);
int minmax(uint64_t pion_jr, uint64_t pion_adv, int profondeur);
uint64_t minmax_complet(uint64_t pion_jr, uint64_t pion_adv, int profondeur, uint64_t coup_a_tester);

#endif

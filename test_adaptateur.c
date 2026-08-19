#include <stdint.h>
#include <stdio.h>
#include "fonctions.h"

#define N 8
#define BLACK 0
#define WHITE 1
#define EMPTY 2
#define CONVENTIONOK
typedef int8_t monType;


int faireCoupOthello(monType tableau[N][N], int8_t coup_idx, int8_t couleur) {
    
    uint64_t pions_noirs = 0;
    uint64_t pions_blancs = 0;

    for (int i = 0; i < 64; i++) {
    
        
        uint64_t masque = UINT64_C(1) << (63 - i);
        
        if (tableau[i/8][i%8] == BLACK) {
            pions_noirs |= masque;
        } else if (tableau[i/8][i%8] == WHITE) {
            pions_blancs |= masque;
        }
    }

    // 2. TRADUIRE le coup (0-63) -> masque de bit
    // La convention de test.c pour le coup (0-63) correspond à notre 'i'
    uint64_t coup_masque = UINT64_C(1) << (63 - coup_idx);

    // 3. Identifier qui joue
    uint64_t mes_pions = (couleur == BLACK) ? pions_noirs : pions_blancs;
    uint64_t pions_adv = (couleur == BLACK) ? pions_blancs : pions_noirs;

    // 4. APPELER notre moteur bitboard
    // (On vérifie d'abord si le coup est légal, car test.c peut envoyer des coups non valides)
    uint64_t coups_legaux = generer_coups_possibles(mes_pions, pions_adv);
    
    Plateau nouveau_plateau;

    if (coup_masque & coups_legaux) {
        // Le coup est légal, on le joue
        nouveau_plateau = jouer_coup(mes_pions, pions_adv, coup_masque);
    } else {
        // Le coup est illégal (ou c'est un "passe tour" 64)
        nouveau_plateau.pions_joueur = mes_pions;
        nouveau_plateau.pions_adversaire = pions_adv;
    }

    // 5. RE-TRADUIRE les bitboards -> tableau[8][8]
    // (On met à jour le tableau original que test.c nous a passé)
    
    // Récupérer les calques dans le bon ordre
    pions_noirs = (couleur == BLACK) ? nouveau_plateau.pions_joueur : nouveau_plateau.pions_adversaire;
    pions_blancs = (couleur == BLACK) ? nouveau_plateau.pions_adversaire : nouveau_plateau.pions_joueur;

    for (int i = 0; i < 64; i++) {
        uint64_t masque = UINT64_C(1) << (63 - i);

        if (pions_noirs & masque) {
            tableau[i/8][i%8] = BLACK;
        } else if (pions_blancs & masque) {
            tableau[i/8][i%8] = WHITE;
        } else {
            tableau[i/8][i%8] = EMPTY;
        }
    }

    return 0; // La fonction test.c attend un int
}


#include "fonctions.h"
#include <stdint.h> 

// A1 = bits 63 H8 = Bit 0 comme ca on peut decaler a droite.
const uint64_t MUR_A = UINT64_C(0x8080808080808080);
const uint64_t MUR_H = UINT64_C(0x0101010101010101);
const uint64_t MASQUE_GAUCHE = ~MUR_A; 
const uint64_t MASQUE_DROITE = ~MUR_H; 
const uint64_t COIN_A1 =(UINT64_C(1) << 63);
const uint64_t  COIN_H1 =(UINT64_C(1) << 56);
const uint64_t COIN_A8 =(UINT64_C(1) << 7);
const uint64_t COIN_H8= (UINT64_C(1) << 0);
const uint64_t MASQUE_COINS = (COIN_A1 | COIN_H1 | COIN_A8 | COIN_H8);

void init_plateau(uint64_t *pions_noirs, uint64_t *pions_blancs) {
    *pions_noirs = 0;
    *pions_blancs = 0;
    *pions_blancs |= (UINT64_C(1) << 36) | (UINT64_C(1) << 27);
    *pions_noirs |= (UINT64_C(1) << 35) | (UINT64_C(1) << 28);
}
void afficher_plateau(uint64_t pions_noirs, uint64_t pions_blancs) {
    printf("  A B C D E F G H\n");
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            printf("%d ", (i / 8) + 1);
        }
        uint64_t masque = UINT64_C(1) << (63 - i);

        if (pions_noirs & masque) {
            printf("N ");
        } else if (pions_blancs & masque) {
            printf("B ");
        } else {
            printf(". ");
        }
        if ((i + 1) % 8 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

int count_bits(uint64_t calque_pions) {
    int count = 0;
    while (calque_pions > 0) {
        calque_pions &= (calque_pions - 1); 
        count++;
    }
    return count;
}


uint64_t generer_coups_possibles(uint64_t mes_pions, uint64_t pions_adversaire) {
    uint64_t cases_vides = ~(mes_pions | pions_adversaire);
    uint64_t coups_totaux = 0;
    uint64_t propagation; 
    // verif droite >> 1
    propagation = ((mes_pions & MASQUE_DROITE) >> 1) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) >> 1) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) >> 1) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) >> 1) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) >> 1) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) >> 1) & pions_adversaire;
    coups_totaux |= ((propagation & MASQUE_DROITE) >> 1) & cases_vides;

    // verif gauche << 1
    propagation = ((mes_pions & MASQUE_GAUCHE) << 1) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) << 1) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) << 1) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) << 1) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) << 1) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) << 1) & pions_adversaire;
    coups_totaux |= ((propagation & MASQUE_GAUCHE) << 1) & cases_vides;

    // veris bas >> 8 
    propagation = (mes_pions >> 8) & pions_adversaire;
    propagation |= (propagation >> 8) & pions_adversaire;
    propagation |= (propagation >> 8) & pions_adversaire;
    propagation |= (propagation >> 8) & pions_adversaire;
    propagation |= (propagation >> 8) & pions_adversaire;
    propagation |= (propagation >> 8) & pions_adversaire;
    coups_totaux |= (propagation >> 8) & cases_vides;

    // verif haut << 8
    propagation = (mes_pions << 8) & pions_adversaire;
    propagation |= (propagation << 8) & pions_adversaire;
    propagation |= (propagation << 8) & pions_adversaire;
    propagation |= (propagation << 8) & pions_adversaire;
    propagation |= (propagation << 8) & pions_adversaire;
    propagation |= (propagation << 8) & pions_adversaire;
    coups_totaux |= (propagation << 8) & cases_vides;

    // diag bas droite (>> 9) 
    propagation = ((mes_pions & MASQUE_DROITE) >> 9) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) >> 9) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) >> 9) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) >> 9) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) >> 9) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) >> 9) & pions_adversaire;
    coups_totaux |= ((propagation & MASQUE_DROITE) >> 9) & cases_vides;

    // diag bas gauche >> 7 
    propagation = ((mes_pions & MASQUE_GAUCHE) >> 7) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) >> 7) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) >> 7) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) >> 7) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) >> 7) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) >> 7) & pions_adversaire;
    coups_totaux |= ((propagation & MASQUE_GAUCHE) >> 7) & cases_vides;

    // diag haut guche << 9
    propagation = ((mes_pions & MASQUE_GAUCHE) << 9) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) << 9) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) << 9) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) << 9) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) << 9) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) << 9) & pions_adversaire;
    coups_totaux |= ((propagation & MASQUE_GAUCHE) << 9) & cases_vides;

    // diag haut droite << 7
    propagation = ((mes_pions & MASQUE_DROITE) << 7) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) << 7) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) << 7) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) << 7) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) << 7) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) << 7) & pions_adversaire;
    coups_totaux |= ((propagation & MASQUE_DROITE) << 7) & cases_vides;

    return coups_totaux;
}


Plateau jouer_coup(uint64_t mes_pions, uint64_t pions_adversaire, uint64_t coup) {
    uint64_t pions_a_flipper_total = 0;
    uint64_t propagation; 

    propagation = ((coup & MASQUE_DROITE) >> 1) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) >> 1) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) >> 1) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) >> 1) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) >> 1) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) >> 1) & pions_adversaire;
    if (((propagation & MASQUE_DROITE) >> 1) & mes_pions) {
        pions_a_flipper_total |= propagation;
    }

    propagation = ((coup & MASQUE_GAUCHE) << 1) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) << 1) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) << 1) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) << 1) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) << 1) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) << 1) & pions_adversaire;
    if (((propagation & MASQUE_GAUCHE) << 1) & mes_pions) {
        pions_a_flipper_total |= propagation;
    }

    propagation = (coup >> 8) & pions_adversaire;
    propagation |= (propagation >> 8) & pions_adversaire;
    propagation |= (propagation >> 8) & pions_adversaire;
    propagation |= (propagation >> 8) & pions_adversaire;
    propagation |= (propagation >> 8) & pions_adversaire;
    propagation |= (propagation >> 8) & pions_adversaire;
    if ((propagation >> 8) & mes_pions) {
        pions_a_flipper_total |= propagation;
    }

    propagation = (coup << 8) & pions_adversaire;
    propagation |= (propagation << 8) & pions_adversaire;
    propagation |= (propagation << 8) & pions_adversaire;
    propagation |= (propagation << 8) & pions_adversaire;
    propagation |= (propagation << 8) & pions_adversaire;
    propagation |= (propagation << 8) & pions_adversaire;
    if ((propagation << 8) & mes_pions) {
        pions_a_flipper_total |= propagation;
    }

    propagation = ((coup & MASQUE_DROITE) >> 9) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) >> 9) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) >> 9) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) >> 9) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) >> 9) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) >> 9) & pions_adversaire;
    if (((propagation & MASQUE_DROITE) >> 9) & mes_pions) {
        pions_a_flipper_total |= propagation;
    }

    propagation = ((coup & MASQUE_GAUCHE) >> 7) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) >> 7) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) >> 7) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) >> 7) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) >> 7) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) >> 7) & pions_adversaire;
    if (((propagation & MASQUE_GAUCHE) >> 7) & mes_pions) {
        pions_a_flipper_total |= propagation;
    }

    propagation = ((coup & MASQUE_GAUCHE) << 9) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) << 9) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) << 9) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) << 9) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) << 9) & pions_adversaire;
    propagation |= ((propagation & MASQUE_GAUCHE) << 9) & pions_adversaire;
    if (((propagation & MASQUE_GAUCHE) << 9) & mes_pions) {
        pions_a_flipper_total |= propagation;
    }

    propagation = ((coup & MASQUE_DROITE) << 7) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) << 7) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) << 7) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) << 7) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) << 7) & pions_adversaire;
    propagation |= ((propagation & MASQUE_DROITE) << 7) & pions_adversaire;
    if (((propagation & MASQUE_DROITE) << 7) & mes_pions) {
        pions_a_flipper_total |= propagation;
    }
    Plateau nouveau_plateau;
    nouveau_plateau.pions_joueur = mes_pions | pions_a_flipper_total | coup;
    nouveau_plateau.pions_adversaire = pions_adversaire & ~pions_a_flipper_total;
    
    return nouveau_plateau;
}


int evaluer(uint64_t mes_pions, uint64_t pions_adv) {
    int score = 0;
    uint64_t mes_coups = generer_coups_possibles(mes_pions, pions_adv);
    uint64_t ses_coups = generer_coups_possibles(pions_adv, mes_pions);
      score += (count_bits(mes_coups) - count_bits(ses_coups)) * 10;
    uint64_t mes_coins = mes_pions & MASQUE_COINS;
    uint64_t ses_coins = pions_adv & MASQUE_COINS;
    score += (count_bits(mes_coins) - count_bits(ses_coins)) * 100;
    score += (count_bits(mes_pions) - count_bits(pions_adv));
    return score;
}

int minmax(uint64_t pion_jr, uint64_t pion_adv, int profondeur){
            if (profondeur == 0) {
                return evaluer(pion_jr, pion_adv);
            }
            uint64_t coups_possible = generer_coups_possibles(pion_jr, pion_adv);
            if (coups_possible == 0) {
                if(generer_coups_possibles(pion_adv,pion_jr)==0){
                    return evaluer(pion_jr, pion_adv);
                }
                return -minmax(pion_adv,pion_jr,profondeur-1);
            }
        int the_best_score=-100000;
                
        while(coups_possible !=0){
            uint64_t test_coup = coups_possible & -coups_possible;
            Plateau plateau_test = jouer_coup(pion_jr, pion_adv, test_coup);
            int score_test = -minmax(plateau_test.pions_adversaire, plateau_test.pions_joueur, profondeur - 1);
            if(score_test>the_best_score){
                the_best_score= score_test;
            }
            coups_possible ^= test_coup;
        }
        
        return the_best_score;
    }


uint64_t minmax_complet(uint64_t pion_jr, uint64_t pion_adv, int profondeur, uint64_t coup_a_tester){
    int meilleur_score=-10000;
    uint64_t meilleur_coup_bit =0;
    while (coup_a_tester != 0) {
        uint64_t coup_test = coup_a_tester & -coup_a_tester;
        Plateau suite = jouer_coup(pion_jr, pion_adv, coup_test);
        int score = -minmax(suite.pions_adversaire, suite.pions_joueur, profondeur - 1);
        if (score > meilleur_score) {
            meilleur_score = score;
            meilleur_coup_bit = coup_test;
        }
        coup_a_tester ^= coup_test;

    }
    return meilleur_coup_bit;
}






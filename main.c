#include "fonctions.h"
#include <stdint.h> 
#include <ctype.h>  
// 1 = Noir et  0 = Blanc
int main() {
    uint64_t pions_noirs;
    uint64_t pions_blancs;
    init_plateau(&pions_noirs, &pions_blancs);
    int joueur_actuel = 1; 
    int passe_tour_precedent = 0;

    while (1) {
        afficher_plateau(pions_noirs, pions_blancs);

        uint64_t mes_pions = (joueur_actuel == 1) ? pions_noirs : pions_blancs;
        uint64_t pions_adv = (joueur_actuel == 1) ? pions_blancs : pions_noirs;

        if (joueur_actuel == 1) printf(" AU noirs de jouer \n");
        else printf(" hop c'est au blanc de joue\n");

        uint64_t coups_possibles = generer_coups_possibles(mes_pions, pions_adv);
        
        if (coups_possibles == 0) {
            printf("Aucun coup possibles. dommageee\n");
            
            if (passe_tour_precedent == 1) {
                printf("Plus personne peux jouer, c'est triste\n");
                break;
            }
            passe_tour_precedent = 1;
            joueur_actuel = 1 - joueur_actuel; 
            continue; 
        }
        passe_tour_precedent = 0;

        printf("Voila ou tu peux jouer:\n");
        printf("  A B C D E F G H\n");
        for (int i = 0; i < 64; i++) {
            if (i % 8 == 0) printf("\n%d ", (i / 8) + 1);
            uint64_t masque = UINT64_C(1) << (63 - i);
            if (pions_noirs & masque) printf("N ");
            else if (pions_blancs & masque) printf("B ");
            else if (coups_possibles & masque) printf("* ");
            else printf(". ");
        }
        printf("\n\n");
        int choix_valide = 0;
        uint64_t coup_joue_calque;
        while (!choix_valide) {
            char col;
            int ligne;
            printf("Entrez votre coup (ex: C4(BOOOOOM)) : ");
            char input[10];
            if (scanf("%s", input) != 1 || !isalpha(input[0]) || !isdigit(input[1])) {
                printf("reeasye j'ai pas compris ex: C4, kaboum\n");
                while (getchar() != '\n');
                continue;
            }
            col = toupper(input[0]); 
            ligne = input[1] - '0'; 
            
            if (col < 'A' || col > 'H' || ligne < 1 || ligne > 8) {
                printf("attention tu es hors du plateau!!!!.\n");
                continue;
            }
            int index = (ligne - 1) * 8 + (col - 'A');
            coup_joue_calque = UINT64_C(1) << (63 - index);
            if (coup_joue_calque & coups_possibles) {
                choix_valide = 1;
            } else {
                printf(".... tu peux pas jouer ici .....\n");
            }
        }
        Plateau etat_apres_coup = jouer_coup(mes_pions, pions_adv, coup_joue_calque);

        if (joueur_actuel == 1) {
            pions_noirs = etat_apres_coup.pions_joueur;
            pions_blancs = etat_apres_coup.pions_adversaire;
        } else {
            pions_blancs = etat_apres_coup.pions_joueur;
            pions_noirs = etat_apres_coup.pions_adversaire;
        }
        joueur_actuel = 1 - joueur_actuel;
    }

    printf("\nETTT cest finissss\n");
    afficher_plateau(pions_noirs, pions_blancs);
    int score_noirs = count_bits(pions_noirs);
    int score_blancs = count_bits(pions_blancs);
    printf("les scoresss sont..... :\n");
    printf("Noirs : %d\n", score_noirs);
    printf("Blancs : %d\n", score_blancs);
    if (score_noirs > score_blancs) printf("les noirs ont gagne  !\n");
    else if (score_blancs > score_noirs) printf(" les blanc remporteeeeee !\n");
    else printf("Ho non zut... Égalité !\n");
    return 0;
}
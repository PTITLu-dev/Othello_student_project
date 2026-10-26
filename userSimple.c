#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include "userNetwork.h" 
#include "fonctions.h"
#include <ctype.h>  


#define BLACK 0 
uint64_t coup_adv=0;
int main(int argc,char *argv[]) 
{
	uint64_t pions_noirs;
    uint64_t pions_blancs;
    init_plateau(&pions_noirs, &pions_blancs);
    int joueur_actuel = 1; 
    int passe_tour_precedent = 0;
	game *g;
	int move; 

	if ((g=allocateGameOthello()) == NULL ) { return(EXIT_FAILURE); }

	if (argc > 3 ) { 
		g->userId=atoi(argv[3]); 
		g->address=argv[2]; 
	}
	else { fprintf(stderr,"usage : %s <userPasswd> <ip ad> <userId>\n",argv[0]); exit(-1); }

	g->port=8080; //par exemple

	if (registerGameOthello(g,argv[1]) < 0 ) { exit(-1); }	// test de l'authentification auprès du serveur 

	if (startGameOthello(g) < 0 ) { // cet appel est bloquant en attendant un adversaire 
		fprintf(stderr,"error Starting Game\n"); 
		return (EXIT_FAILURE); 
	}
	printf("I am player %s\n",(g->myColor==BLACK)?"Black":"White");
	
	// debut de partie
	while (g->state == PLAYING && !feof(stdin)) {
		uint64_t mes_pions = (g->myColor==BLACK) ? pions_noirs : pions_blancs;
    	uint64_t pions_adv = (g->myColor==BLACK) ? pions_blancs : pions_noirs;

	 	if (g->myColor != g->currentPlayer) { // attente du coup de l'adversaire 
			if ((move=waitMoveOthello(g)) == 0 ) {
				printf("Game status %d: \t",g->state); 
				if (g->state == PLAYING) { 
					printf("Received move from server %d (x=%d,y=%d)\n",g->move,g->move%8,g->move/8); 
					int index = g->move;
					uint64_t coup_adv = UINT64_C(1) << ( 63 - index);
					Plateau etat_apres_coup = jouer_coup( pions_adv , mes_pions, coup_adv);
					if (g->myColor!=BLACK) {
					  pions_noirs = etat_apres_coup.pions_joueur;
					  pions_blancs = etat_apres_coup.pions_adversaire;
					} else {
						pions_blancs  = etat_apres_coup.pions_joueur;
						pions_noirs  = etat_apres_coup.pions_adversaire;
					}
					afficher_plateau(pions_noirs, pions_blancs);
				}
			}
		}
	 	else { 		
			g->move=65; // si scanf correct cette valeur est modifiée, sinon cela terminera la partie. 
			// recuperation du coup sur stdin 
			uint64_t coups_possibles = generer_coups_possibles(mes_pions, pions_adv);
			if (coups_possibles == 0) {
				printf("Aucun coup possible : le joueur passe son tour.\n");
				g->move=64;
				if (passe_tour_precedent == 1) {
					printf("Plus aucun joueur ne peut jouer : fin de la partie.\n");
					break;
				}
				passe_tour_precedent = 1;
				joueur_actuel = 1 - joueur_actuel; 
				continue; 
			}
			passe_tour_precedent = 0;

			printf("Coups possibles (*) :\n");
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
				printf("Entrez votre coup (ex : C4) : ");
				char input[10];
				int lu = scanf("%9s", input);
				if (lu == EOF) {
					printf("\nFin de l'entrée : partie interrompue.\n");
					exit(0);
				}
				if (lu != 1 || !isalpha((unsigned char)input[0]) || !isdigit((unsigned char)input[1])) {
					printf("Saisie invalide, réessayez (ex : C4).\n");
					int c;
					while ((c = getchar()) != '\n' && c != EOF);
					continue;
				}
				col = toupper(input[0]); 
				ligne = input[1] - '0'; 
				
				if (col < 'A' || col > 'H' || ligne < 1 || ligne > 8) {
					printf("Case hors du plateau.\n");
					continue;
				}
				int index = (ligne - 1) * 8 + (col - 'A');
				coup_joue_calque = UINT64_C(1) << (63 - index);
				if (coup_joue_calque & coups_possibles) {
					g->move=index;
					choix_valide = 1;
				} else {
					printf("Coup interdit sur cette case.\n");
				}
			}
			Plateau etat_apres_coup = jouer_coup(mes_pions, pions_adv, coup_joue_calque);
			if (g->myColor!=BLACK) {
            	pions_blancs  = etat_apres_coup.pions_joueur;
            	pions_noirs = etat_apres_coup.pions_adversaire;
			} else {
				pions_noirs = etat_apres_coup.pions_joueur;
				pions_blancs = etat_apres_coup.pions_adversaire;
			}
			printf("playing move %d (x=%d,y=%d)\n",g->move,g->move%8,g->move/8);
			doMoveOthello(g);	// envoie du coup à l'adversaire 
	   	}
		g->currentPlayer=!g->currentPlayer; 
	} 
	// fin de partie 
	printf("Final game status = %d\n",g->state); 
	freeGameOthello(g);
	return 0; 
}



	

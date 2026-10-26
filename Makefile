CFLAGS = -Wall -Wextra -Werror -std=c99 -O2

# Cibles autonomes : jeu local en terminal + tests du moteur
all: othelo test_othello

othelo: main.o fonctions.o
	gcc $(CFLAGS) -o othelo main.o fonctions.o

test_othello: test.o test_adaptateur.o fonctions.o
	gcc $(CFLAGS) -o test_othello test.o test_adaptateur.o fonctions.o

# Clients réseau : nécessitent libothello.so, la librairie réseau fournie par l'Esisar
# (non redistribuée dans ce dépôt). Placer libothello.so à la racine, puis : make reseau
reseau: userSimpleIA userSimple

libothello.so:
	@echo "libothello.so manquante : c'est la librairie réseau fournie par l'Esisar (non incluse)."
	@echo "Copiez-la à la racine du projet, puis relancez : make reseau"
	@false

userSimpleIA: userSimpleIA.c fonctions.c fonctions.h libothello.so
	gcc $(CFLAGS) -L. -o userSimpleIA userSimpleIA.c fonctions.c -lothello

userSimple: userSimple.c fonctions.c fonctions.h libothello.so
	gcc $(CFLAGS) -L. -o userSimple userSimple.c fonctions.c -lothello

main.o: main.c fonctions.h
	gcc $(CFLAGS) -c main.c -o main.o

fonctions.o: fonctions.c fonctions.h
	gcc $(CFLAGS) -c fonctions.c -o fonctions.o

test.o: test.c
	gcc $(CFLAGS) -c test.c -o test.o

test_adaptateur.o: test_adaptateur.c fonctions.h
	gcc $(CFLAGS) -c test_adaptateur.c -o test_adaptateur.o

clean:
	rm -f main.o fonctions.o test.o test_adaptateur.o othelo test_othello userSimple userSimpleIA

.PHONY: all reseau clean

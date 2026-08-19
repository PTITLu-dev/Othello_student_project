CFLAGS = -Wall -Wextra -Werror -std=c99 -O2

othelo: main.o fonctions.o
	gcc $(CFLAGS) -o othelo main.o fonctions.o

userSimpleIA: userSimpleIA.c fonctions.c fonctions.h
	gcc $(CFLAGS) -L. -o userSimpleIA userSimpleIA.c fonctions.c -lothello

userSimple: userSimple.c fonctions.c fonctions.h
	gcc $(CFLAGS) -L. -o userSimple userSimple.c fonctions.c -lothello

test_othello: test.o test_adaptateur.o fonctions.o
	gcc $(CFLAGS) -o test_othello test.o test_adaptateur.o fonctions.o

main.o: main.c fonctions.h
	gcc $(CFLAGS) -c main.c -o main.o

fonctions.o: fonctions.c fonctions.h
	gcc $(CFLAGS) -c fonctions.c -o fonctions.o

test.o: test.c
	gcc $(CFLAGS) -c test.c -o test.o

test_adaptateur.o: test_adaptateur.c fonctions.h
	gcc $(CFLAGS) -c test_adaptateur.c -o test_adaptateur.o

clean:
	rm -f main.o fonctions.o test.o test_adaptateur.o othelo test_othello userSimple

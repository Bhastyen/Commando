CC=gcc
Lflags=`pkg-config --libs-only-l MLV`
Oflags=-Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV`
fichier_o=utilitaire.o joueur.o Projectile.o env.o ennemi.o Position.o Vecteur.o Hitbox.o File.o Liste.o evenement.o Trajectoire.o



all: jeu clean

jeu: main.c $(fichier_o)
	$(CC) $(Oflags) main.c $(fichier_o) $(Lflags) -o jeu -lpthread -lX11

joueur.o: joueur.c joueur.h
	$(CC) -c joueur.c -o joueur.o

utilitaire.o: utilitaire.c utilitaire.h
	$(CC) -c utilitaire.c -o utilitaire.o

Projectile.o: Projectile.c Projectile.h
	$(CC) -c Projectile.c -o Projectile.o

env.o: env.c env.h
	$(CC) -c env.c -o env.o

ennemi.o: ennemi.c ennemi.h
	$(CC) -c ennemi.c -o ennemi.o

Position.o: Position.c Position.h
	$(CC) -c Position.c -o Position.o

Hitbox.o: Hitbox.c Hitbox.h
	$(CC) -c Hitbox.c -o Hitbox.o

Vecteur.o: Vecteur.c Vecteur.h
	$(CC) -c Vecteur.c -o Vecteur.o

File.o: File.c File.h
	$(CC) -c File.c -o File.o

Liste.o: Liste.c Liste.h
	$(CC) -c Liste.c -o Liste.o

evenement.o: evenement.c evenement.h
	$(CC) -c evenement.c -o evenement.o

Trajectoire.o: Trajectoire.c Trajectoire.h
	$(CC) -c Trajectoire.c -o Trajectoire.o

clean:
	rm -f *.o *~

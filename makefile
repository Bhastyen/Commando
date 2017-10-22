CC=gcc
Lflags=`pkg-config --libs-only-l MLV`
Oflags=-Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV`
fichier_o=sources/utilitaire.o sources/joueur.o sources/Projectile.o sources/env.o sources/ennemi.o sources/Position.o sources/Vecteur.o sources/Hitbox.o sources/File.o sources/Liste.o sources/evenement.o sources/Trajectoire.o



all: jeu clean

jeu: sources/main.c $(fichier_o)
	$(CC) $(Oflags) sources/main.c $(fichier_o) $(Lflags) -o jeu -lpthread -lX11

sources/joueur.o: sources/joueur.c sources/joueur.h
	$(CC) -c sources/joueur.c -o sources/joueur.o

sources/utilitaire.o: sources/utilitaire.c sources/utilitaire.h
	$(CC) -c sources/utilitaire.c -o sources/utilitaire.o

sources/Projectile.o: sources/Projectile.c sources/Projectile.h
	$(CC) -c sources/Projectile.c -o sources/Projectile.o

sources/env.o: sources/env.c sources/env.h
	$(CC) -c sources/env.c -o sources/env.o

sources/ennemi.o: sources/ennemi.c sources/ennemi.h
	$(CC) -c sources/ennemi.c -o sources/ennemi.o

sources/Position.o: sources/Position.c sources/Position.h
	$(CC) -c sources/Position.c -o sources/Position.o

sources/Hitbox.o: sources/Hitbox.c sources/Hitbox.h
	$(CC) -c sources/Hitbox.c -o sources/Hitbox.o

sources/Vecteur.o: sources/Vecteur.c sources/Vecteur.h
	$(CC) -c sources/Vecteur.c -o sources/Vecteur.o

sources/File.o: sources/File.c sources/File.h
	$(CC) -c sources/File.c -o sources/File.o

sources/Liste.o: sources/Liste.c sources/Liste.h
	$(CC) -c sources/Liste.c -o sources/Liste.o

sources/evenement.o: sources/evenement.c sources/evenement.h
	$(CC) -c sources/evenement.c -o sources/evenement.o

sources/Trajectoire.o: sources/Trajectoire.c sources/Trajectoire.h
	$(CC) -c sources/Trajectoire.c -o sources/Trajectoire.o

clean:
	rm -f sources/*.o sources/*~

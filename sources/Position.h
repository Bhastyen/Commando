#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED


struct pos{
	double x;
	double y;
};

typedef struct pos Pos;




Pos* creer_position(double x, double y);

void modifier_position(Pos* pos, double x, double y);

void modifier_position_de_position(Pos* pos1, Pos* pos2);

void deplacement_position(Pos* pos, double x, double y);

Pos* supprimer_position(Pos* pos);




#endif
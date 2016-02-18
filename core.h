/**
 * \file core.h
 * \brief Declaration of structure for the project
 * \author Isabelle MARINO Pierrick JACQUETTE Hafca TIRICHINE
 * \version 0.1
 * \date 17 february 2016
 *
 * Declaratioin of structure for the project open stree map
 *
 */

#include <stdio.h>

typedef struct{
	float x;
	float y;
}coordonnee;


typedef struct{
	coordonnee min;
	coordonnee max;

}bound;

typedef struct{
	long id; // ou int 
	coordonnee c;
	char visible; // T = true, F= false;
}Node;

typedef struct{
	long id;
	//liste de Node à definir 
	char visible; // T = true, F= false;
	char* tag;
	char* k;
}way;


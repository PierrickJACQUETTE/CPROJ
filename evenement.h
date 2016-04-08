/**
* \file evenement.h
* \brief Declare fonctions to convert elements
* \author Isabelle MARINO Pierrick JACQUETTE Hafça TIRICHINE
* \date 8 April 2016
*
* Evenement Window
*
*/

#ifndef __EVENEMENT_H__
#define __EVENEMENT_H__

#include "point.h"
#include "line.h"

/**
* Fonction that permit the display
* While we haven't closed the window it is still on the screen
* When we do close it, it displays a message saying we closed it
* This event is handeled by a loop : while the statut is "CONTINUE" we keep the window to the screen
* Otherwise, we close it and change the statut to "QUIT"

*/
void evenement();

#endif

#ifndef NDISCOS
    #define NDISCOS

//Include de Curses
#include <ncursesw/curses.h>

//Include para dibujar los menus
#include "..\Ventanas\Ventanas.h"

//Protoripos de funciones de Discos
void Discos(DISCO **);
void LimpiarDisco(WINDOW *);
void NuevoDisco(WINDOW *, DISCO **);

#endif
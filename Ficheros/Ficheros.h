#ifndef NFICHEROS
    #define NFICHEROS

//Include de Curses
#include <ncursesw/curses.h>

//Include para dibujar los menus
#include "..\Ventanas\Ventanas.h"

//Prototipos de funciones de Ficheros
void Fichero(DISCO **, int);
void ImportarFichero(DISCO **,WINDOW *,bool);
void ExportarFichero(DISCO **,WINDOW *);
void DescartarFichero(DISCO **,WINDOW *);
char *strsep(char **, char *);

#endif
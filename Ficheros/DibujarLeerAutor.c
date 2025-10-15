/*****************************************
 * Nombre: DibujarLeerAutor
 * Argumentos: Window *Wautor:   Ventana donde se va a dibujar el patrón
 * Descripción: Dibuja el patrón para leer el comienzo del apellido del autor(es) de los que se desean
 *              buscar y listar sus libros.
 * Reglas de uso: 
 * Código de Retorno: N/A
 * Programador: 
 *****************************************/

//Include del módulo funcional
#include "Ventanas.h"

void DibujarLeerAutor(WINDOW *Wautor)
{
    
    //Código del alumno

    /*Utilizare este init_pair(9,COLOR_YELLOW,COLOR_BLUE) y este init_pair(8,COLOR_CYAN,COLOR_BLUE) de Discoteca0.c 
    para el color de texto y de fondo*/

    //Lineas y columnas sacadas de los parámetros de la creación de la ventana en Discoteca0.c. newwin(4,76,5,2)
    int Lineas = 4;
    int Columnas = 76;
    
    //Inicializo i
    int i = 0;

    //Pongo toda la ventana con los colores que he dicho que utilizare
    wcolor_set(Wautor, 9, NULL);

    i=(Columnas-strlen("Busqueda por Autor"))/2; //Encuentro el punto medio de la pantalla 
    mvwprintw(Wautor,0,i,"Busqueda por Autor"); // Escribo el título
    

    //Creo el cuadrado con solo 3 lineas para que haya espacio solo para el único texto que quiero escribir
    wattron(Wautor, COLOR_PAIR(8));
    Cuadrado(Wautor,1,1,Lineas - 1,Columnas - 1,SOLIDO);
    wattroff(Wautor, COLOR_PAIR(8));

    //Vuelvo a poner texto amarillo y fondo azul
    wcolor_set(Wautor, 9, NULL);
  
    
    //Escribo los apellidos del autor que empezarán en la misma columna pero distinta fila
    mvwprintw(Wautor,2,2,"Apellidos del Autor:                                                     ");

    return;
}
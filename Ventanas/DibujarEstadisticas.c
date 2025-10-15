/*****************************************
 * Nombre: DibujarEstadisticas
 * Argumentos: Window *Westad :   Ventana donde se va a dibujar el patrón
 * Descripción: Dibuja el patrón para ver las estadísticas del programa
 * Reglas de uso: 
 * Código de Retorno: N/A
 * Programador: 
 *****************************************/

//Include del módulo funcional
#include "Ventanas.h"

void DibujarEstadisticas(WINDOW *Westad)
{   
    //Código del alumno
    /*Utilizare este init_pair(9,COLOR_YELLOW,COLOR_BLUE) y este init_pair(8,COLOR_CYAN,COLOR_BLUE)
     de Discoteca0.c para el color de texto y de fondo*/

    //Lineas y columnas sacadas de los parámetros de la creación de la ventana en Discoteca0.c. newwin(14,76,3,2)
    int Lineas = 14;
    int Columnas = 76;
    
    //Inicializo i
    int i = 0;

    //Pongo toda la ventana con los colores que he dicho que utilizare
    wcolor_set(Westad, 9, NULL);

    i=(Columnas-strlen("   Estadisticas   "))/2; //Encuentro el punto medio de la pantalla 
    mvwprintw(Westad,0,i,"   Estadisticas   "); // Escribo el título

    //Creo el cuadrado con color Cian y fondo azul
    wattron(Westad, COLOR_PAIR(8));
    Cuadrado(Westad,1,1,Lineas-1,Columnas-1,SOLIDO);    
    wattroff(Westad, COLOR_PAIR(8));

    //Vuelvo a poner texto amarillo y fondo azul
    wcolor_set(Westad, 9, NULL);
    
    //Escribo todas las estadísticas que empezarán en la misma columna pero distinta fila
    mvwprintw(Westad,2,2,"Nombre del fichero:                                                      ");
    mvwprintw(Westad,3,2,"Fichas de los discos:                                                    ");
    mvwprintw(Westad,4,2,"Numero de Discos con memoria reservada:                                  ");
    mvwprintw(Westad,5,2,"Microsegundos en Importar:                                               ");
    mvwprintw(Westad,6,2,"Microsegundos en ordenar por Seleccion:                                  ");
    mvwprintw(Westad,7,2,"Microsegundos en ordenar por Burbuja:                                    ");
    mvwprintw(Westad,8,2,"Microsegundos en ordenar por Insercion:                                  ");
    mvwprintw(Westad,9,2,"Microsegundos en ordenar por Quicksort:                                  ");
    mvwprintw(Westad,10,2,"Microsegundos en crear el arbol binario:                                 ");
    mvwprintw(Westad,11,2,"Microsegundos en buscar por Obra:                                        ");
    mvwprintw(Westad,12,2,"Microsegundos en buscar por Autor:                                       ");

    return;
}
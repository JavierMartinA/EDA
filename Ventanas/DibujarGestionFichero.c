/*****************************************
 * Nombre: DibujarGestionFichero
 * Argumentos: Window *Wfichero :   Ventana donde se va a dibujar el patrón
 * Descripción: Dibuja el patrón para leer el nombre del fichero y después de tratarlo mostrar
 *              el número de fichas de libros leídas y descartadas.
 * Reglas de uso: 
 * Código de Retorno: N/A
 * Programador: 
 *****************************************/

//Include del módulo funcional
#include "Ventanas.h"

void DibujarGestionFichero(WINDOW *Wfichero)
{
    
    //Código del alumno  

    /*Utilizare este init_pair(9,COLOR_YELLOW,COLOR_BLUE) y este init_pair(8,COLOR_CYAN,COLOR_BLUE) de Discoteca0.c 
    para el color de texto y de fondo*/

    //Lineas y columnas sacadas de los parámetros de la creación de la ventana en Discoteca0.c. newwin(5,76,5,2)
    int Lineas = 5;
    int Columnas = 76;
    
    //Inicializo i
    int i = 0;

    //Pongo toda la ventana con los colores que he dicho que utilizare
    wcolor_set(Wfichero, 9, NULL);
    //Creo el titulo con fondo azul pintado en el centro arriba
    i=(Columnas-strlen("   Importar fichero de discos   "))/2; //Encuentro el punto medio de la pantalla 
    mvwprintw(Wfichero,0,i,"   Importar fichero de discos   "); // Escribo el título

    
    //Pinto el cuadrado
    //Creo el cuadrado con color Cian y fondo azul
    wattron(Wfichero, COLOR_PAIR(8));
    Cuadrado(Wfichero,1,1,Lineas - 1,Columnas - 1,SOLIDO);    
    wattroff(Wfichero, COLOR_PAIR(8));

    //Vuelvo a poner texto amarillo y fondo azul
    wcolor_set(Wfichero, 9, NULL);

    //Escribo las opciones
    mvwprintw(Wfichero,2,2," Nombre del fichero:                                                     ");
    mvwprintw(Wfichero,3,2," Fichas tratadas:                          ");
    mvwprintw(Wfichero,3,35,"Fichas descartadas:                ");

    return;
}
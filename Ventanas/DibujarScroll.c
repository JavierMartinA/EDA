/*****************************************
 * Nombre: DibujarScroll
 * Argumentos: Window *Wlistado:   Ventana donde se va a dibujar el patrón
 * Descripción: Dibuja el patrón para los listados de libros, con 10 fichas por pantalla.
 * Reglas de uso: 
 * Código de Retorno: N/A
 * Programador: 
 *****************************************/

////Include del módulo funcional
#include "Ventanas.h"

void DibujarScroll(WINDOW *Wlistado)
{
        
    //Código del alumno
    /*Utilizare este init_pair(9,COLOR_YELLOW,COLOR_BLUE), este init_pair(1,COLOR_BLUE,COLOR_BLACK) y este
    init_pair(2,COLOR_CYAN,COLOR_BLACK) de Discoteca0.c para el color de texto y de fondo*/

    //Lineas y columnas sacadas de los parámetros de la creación de la ventana en Discoteca0.c. newwin(16,76,2,2)
    int Lineas = 16;
    int Columnas = 76;
    
    //Inicializo i
    int i = 0;

    //Pongo toda la ventana con los colores que he dicho que utilizare
    wcolor_set(Wlistado, 9, NULL);

    i=(Columnas-strlen("          Listado de Discos          "))/2; //Encuentro el punto medio de la pantalla 
    mvwprintw(Wlistado,0,i,"          Listado de Discos          "); // Escribo el título
    

    /*Creo el primer cuadrado con pocas líneas(3) (justo para dentro solo pueda haber una línea de texto)
     que solo contendrá qué representa cada fila (Nombre, obra, autor)*/
    wattron(Wlistado, COLOR_PAIR(8));
    Cuadrado(Wlistado,1,1,3,Columnas-1,SOLIDO);  
    wattroff(Wlistado, COLOR_PAIR(8));  

    //Vuelvo a poner texto amarillo y fondo azul
    wcolor_set(Wlistado, 9, NULL);

    
    //Escribo todas las cabeceras que empezarán en la misma fila pero distinta columna
    mvwprintw(Wlistado,2,2,"Numero                 ");
    mvwprintw(Wlistado,2,25,"Obra                                ");
    mvwprintw(Wlistado,2,60,"Autor          ");
    
    //Creo el cuadrado donde estarán todos los discos, el cuadrado llegará hasta la penúltima línea de la ventana
    wattron(Wlistado, COLOR_PAIR(8));
    Cuadrado(Wlistado, 3, 1, Lineas - 4, Columnas - 1, SOLIDO);
    wattroff(Wlistado, COLOR_PAIR(8));

    wcolor_set(Wlistado, 9, NULL);

    //Escribo las lineas con espacios en blanco para poner el fondo azul
    //Creo un array donde meter los espacios que imprimiré
    char mensaje[80] = "";
    
    //Creo un bucle que insertará en el array la cantidad de espacios en blanco
    for (int k = 0; k < (Columnas - 2 - 1); k++)
    {
        strcat(mensaje, " ");
    }

    //Creo un bucle para escribir los espacios con mvwprintw
    for (int j = 4; j < Lineas - 2; j++)
    {
        mvwprintw(Wlistado, j, 2, "%s", mensaje);
    }

    //Aplico el atributo de texto azul y fondo negro a lo siguiente que voy a escribir
    wattron(Wlistado, COLOR_PAIR(2));
    mvwprintw(Wlistado,Lineas - 1, 10, "ESC=Salir Flechas=Subir/Bajar AvPag/RePag=Pag siguiente/anterior");
    wattroff(Wlistado, COLOR_PAIR(2));

    return;
}
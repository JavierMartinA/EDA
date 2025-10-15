/*****************************************
 * Nombre: DibujarDisco
 * Argumentos: Window *Wdisco:   Ventana donde se va a dibujar el patrón
 * Descripción: Dibuja el patrón para mostrar o capturar los datos de las fichas de un disco.
 * Reglas de uso: 
 * Código de Retorno: N/A
 * Programador: 
 *****************************************/

//Include del módulo funcional
#include "Ventanas.h"

void DibujarDisco(WINDOW *Wdisco)
{
        
    //Código del alumno
    
    /*Utilizare este init_pair(9,COLOR_YELLOW,COLOR_BLUE), este init_pair(8,COLOR_CYAN,COLOR_BLUE) y este
    init_pair(1,COLOR_BLUE,COLOR_BLACK) de Discoteca0.c para el color de texto y de fondo*/

    //Lineas y columnas sacadas de los parámetros de la creación de la ventana en Discoteca0.c. newwin(12,76,5,2)
    int Lineas = 12;
    int Columnas = 76;
    
    //Inicializo i
    int i = 0;

    //Pongo toda la ventana con los colores que he dicho que utilizare
    wcolor_set(Wdisco, 9, NULL);

    i=(Columnas-strlen("Gestion de Discos"))/2; //Encuentro el punto medio de la pantalla 
    mvwprintw(Wdisco,0,i,"Gestion de Discos"); // Escribo el título
    
    //Creo el cuadrado con color Cian y fondo azul
    wattron(Wdisco, COLOR_PAIR(8));
    Cuadrado(Wdisco,1,1,Lineas-1,Columnas-1,SOLIDO);    
    wattroff(Wdisco, COLOR_PAIR(8));

    //Vuelvo a poner texto amarillo y fondo azul
    wcolor_set(Wdisco, 9, NULL);   
    
    //Escribo todas las estadísticas que empezarán en la misma columna pero distinta fila
    mvwprintw(Wdisco,2,2,"Numero de Disco:                                                         ");
    mvwprintw(Wdisco,3,2,"Obra:                                                                    ");
    mvwprintw(Wdisco,4,2,"Apellidos del Autor:                                                     ");
    mvwprintw(Wdisco,5,2,"Nommbre del Autor:                                                       ");
    mvwprintw(Wdisco,6,2,"Tonalidad:                                                               ");
    mvwprintw(Wdisco,7,2,"Opus:                                                                    ");
    mvwprintw(Wdisco,8,2,"Duracion:                                                                ");
    
    //Escribo las lineas con espacios en blanco, lo haré a través de una idea sacada del código ya escrito en VentanaError.c
    //Creo un array donde meter los espacios que imprimiré
    char mensaje[80] = "";
    
    //Creo un bucle que insertará en el array mensaje la cantidad de espacios en blanco necesarias para rellenar de lado a lado del cuadrado
    //Es k < Columnas -2 -1, porque el cuadrado empieza en columna 1, y dejo 1 de margen por cada lado
    for (int k = 0; k < (Columnas - 2 - 1); k++)
    {
        strcat(mensaje, " ");
    }

    /*Creo un bucle para escribir los espacios con mvwprintw, la última línea escrita será la anterior fila a 
    donde está la línea horizontal que cierra el cuadrado, es decir, si la ventana es de 12 líneas, y por ello, un cuadrado que empieza
    en 0, 0. Cuyo final del cuadrado se sitúa en la línea 11 (ya que la línea 0 existe), entonces la última línea de espacios 
    en blanco será la 10*/
    for (int j = 9; j < Lineas - 1; j++)
    {
        mvwprintw(Wdisco, j, 2, "%s", mensaje);
    }

    //Escribo las instrucciones que aparecen en el borde inferior del cuadrado
    i=(Columnas-strlen("Enter=Nuevo/Salir       #-Visualizar Disco"))/2; //Encuentro el punto medio de la pantalla para mi texto
    //Pongo el atributo de fondo negro y color azul para las instrucciones
    wattron(Wdisco, COLOR_PAIR(1));
    mvwprintw(Wdisco, Lineas - 1, i, "Enter=Nuevo/Salir       #-Visualizar Disco");
    wattroff(Wdisco, COLOR_PAIR(1));

    return;

}
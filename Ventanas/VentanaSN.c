/*****************************************
 * Nombre: VentanaSN
 * Argumentos: char *mensaje    : Mensaje de la pregunta 'S' o 'N'
 * Descripción: Presenta el mensaje en la penúltima línea de la pantalla stdscr en un color diferente y lee del teclado
 *              la respuesta del usuario que solo puede ser 'S' o 'N'. La respuesta no debe ser sensible
 *              mayúsculas o minúsculas. Cualquier carácter que no sea válido se ignorará y se emitirá un
 *              beep.
 * Reglas de uso: 
 * Código de Retorno: char Tecla: Solo puede ser 'S' o 'N' (en mayúsculas)
 * Programador: 
 *****************************************/

//Include del módulo funcional
#include "Ventanas.h"

char VentanaSN(char *mensaje)
{
    WINDOW *Wsn;
    char Tecla;
    int j,k;

    //Calculamos la posición de la ventana
    k=strlen(mensaje)+3;
    j=(80-k)/2;
    Wsn=newwin(1,k,18,j);
    wcolor_set(Wsn,5,NULL);
    mvwprintw(Wsn,0,0," %s  ",mensaje);
    curs_set(1);
    while(true) {
        mvwaddch(Wsn,0,k-1,' ');
        wrefresh(Wsn);
        Tecla=mvwgetch(Wsn,0,k-1);
        if (Tecla > 'Z')
            Tecla -= 32;
        mvwaddch(Wsn,0,k-1,Tecla);
        wrefresh(Wsn);
        if ((Tecla == 'S') || (Tecla == 'N'))
            break;
        beep();
        sleep(1);
    }
    curs_set(0);
    usleep(1000);
    delwin(Wsn);
    touchwin(stdscr);
    wrefresh(stdscr);
    return (Tecla);
}

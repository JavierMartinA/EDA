/*****************************************
 * Nombre: VentanaError
 * Argumentos: char *mensaje    : Mensaje de error
 * Descripción: Presenta el mensaje en la penúltima línea de la pantalla stdscr en unc olor llamativo y en la última línea
 *              escribe el mensaje "Pulse una tecla para continuar" y espera hasta que el usuario pulsa una tecla. A continuación
 *              borra la ventana de error y restaura la pantalla stdscr.
 * Reglas de uso: 
 * Código de Retorno: N/A
 * Programador: 
 *****************************************/

//Include del módulo funcional
#include "Ventanas.h"

void VentanaError(char *mensaje)
{
    WINDOW *Werr;
    char err_mensaje[80];
    int i,j,k,l;

    //Calculamos la posición de la ventana
    if ((i=strlen(mensaje)) < 30)
        k=30;
    else
        k=i;
    j=(80-k)/2-1;
    Werr=newwin(2,k+2,18,j);
    wcolor_set(Werr,4,NULL);
    j=(k+2-i)/2;
    err_mensaje[0]=0;
    for(l=0;l<j;l++)
        strcat(err_mensaje," ");
    strcat(err_mensaje,mensaje);
    for(l=0;l<j;l++)
        strcat(err_mensaje," ");
    if (strlen(err_mensaje) < k+2)
        strcat(err_mensaje," ");
    mvwprintw(Werr,0,0,"%s",err_mensaje);
    j=(k+2-30)/2;
    err_mensaje[0]=0;
    for(l=0;l<j;l++)
        strcat(err_mensaje," ");
    strcat(err_mensaje,"Pulse una tecla para continuar");
    for(l=0;l<j;l++)
        strcat(err_mensaje," ");
    if (strlen(err_mensaje) < k+2)
        strcat(err_mensaje," ");
    mvwprintw(Werr,1,0,"%s",err_mensaje);
    wrefresh(Werr);
    wgetch(Werr);
    delwin(Werr);
    touchwin(stdscr);
    wrefresh(stdscr);
    return;
}

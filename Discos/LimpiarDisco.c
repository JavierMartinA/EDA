/*****************************************
 * Nombre: LimpiarDisco
 * Argumentos: Window *Wdisco :   Ventana a limpiar
 * Descripción: Limpia los datos de la ventan de gestión de discos
 * Reglas de uso: 
 * Código de Retorno: N/A
 * Programador: (JMSM sept-24)
 *****************************************/

// Include de la unidad funcional
#include "Discos.h"

void LimpiarDisco(WINDOW *Wdisco)
{
    // Limpiar los datos de la ventana
    wcolor_set(Wdisco,9,NULL);
    mvwprintw(Wdisco,2,23,"                                                   ");
    mvwprintw(Wdisco,3,23,"                                                   ");
    mvwprintw(Wdisco,4,23,"                                                   ");
    mvwprintw(Wdisco,5,23,"                                                   ");
    mvwprintw(Wdisco,6,23,"                                                   ");
    mvwprintw(Wdisco,7,23,"                                                   ");
    mvwprintw(Wdisco,8,23,"                                                   ");
    mvwprintw(Wdisco,9,1,"                                                                          ");
    mvwprintw(Wdisco,10,1,"                                                                          ");
    return;
}
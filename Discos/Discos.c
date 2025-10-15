/*****************************************
 * Nombre: Discos
 * Argumentos: DISCO **Fichas:   Puntero al array de discos
 * Descripción: Pantalla de gestión de fichas de discos completos.
 *              Si se introduce un número, se muestra ese número de disco o error
 *              Si se pulsa ENTER se pregunta si se quiere añadir un disco
 *              Si se responde 'S' se introduce un disco nuevo
 *              Si se responde 'N', la función retorna.
 * Reglas de uso: 
 * Código de Retorno:
 * Programador: JMSM (Sept-24)
 *****************************************/

#include "Discos.h"

void Discos(DISCO **Fichas)
{
    static WINDOW *Wdisco=NULL;
    char linea[52];
    int NumeroDisco;
    char Tecla;
    int TeclaFuncion;

    // Creación y dibujo de la ventana de gestión de discos
    if (Wdisco == NULL) {
        Wdisco=newwin(12,76,5,2);
        DibujarDisco(Wdisco);
    }

    // Bucle hasta que se desee salir
    while(true) {
        // Limpiar los datos de la ventana de gestión de discos y mensajes de ayuda
        LimpiarDisco(Wdisco);
        wcolor_set(Wdisco,2,NULL);
        mvwprintw(Wdisco,11,17,"Enter=Nuevo/Salir      #-Visualizar Disco");
        wcolor_set(Wdisco,9,NULL);
        touchwin(Wdisco);
        wrefresh(Wdisco);
        curs_set(1);
        echo();

        // Captura del número de disco a visualizar
        NumeroDisco=0;
        mvwgetnstr(Wdisco,2,23,linea,50);
        NumeroDisco=atoi(linea);
        noecho();
        curs_set(0);

        // Si no es un número válido se pregunta si se desea salir
        if (NumeroDisco <=0 ) {
            Tecla=VentanaSN("Desea dar de alta un nuevo disco (S/N)?");
            touchwin(Wdisco);
            wrefresh(Wdisco);
            // Se quiere introducir un disco nuevo
            if (Tecla == 'S')
                NuevoDisco(Wdisco,Fichas);
            else
                // Se desea salir
                return;
        }
        else {
            // Es un número mayor que los discos que hay
            if (NumeroDisco > Estadisticas.NumeroFichas) {
                VentanaError("No existe esa ficha de disco");
                continue;
            }
            // Leer anterior/siguiente o ESC=salir
            keypad(Wdisco,true);
            while(true) {
                // Visualizar el disco actual
                LimpiarDisco(Wdisco);
                wcolor_set(Wdisco,9,NULL);
                mvwprintw(Wdisco,2,23,"%d",NumeroDisco);
                mvwprintw(Wdisco,3,23,"%.51s",(*Fichas)[NumeroDisco-1].Obra);
                mvwprintw(Wdisco,4,23,"%.51s",(*Fichas)[NumeroDisco-1].ApellAutor);
                mvwprintw(Wdisco,5,23,"%.51s",(*Fichas)[NumeroDisco-1].NomAutor);
                mvwprintw(Wdisco,6,23,"%.51s",(*Fichas)[NumeroDisco-1].Tonalidad);
                mvwprintw(Wdisco,7,23,"%.51s",(*Fichas)[NumeroDisco-1].Opus);
                mvwprintw(Wdisco,8,23,"%.51s",(*Fichas)[NumeroDisco-1].Duracion);
                wrefresh(Wdisco);
                while(true) {
                    // Si ESC salir del bucle
                    if ((TeclaFuncion=wgetch(Wdisco)) == KEY_ESC)
                        break;
                    else {
                        // Si LEFT, disco anterior
                        if (TeclaFuncion == KEY_LEFT) {
                            if (NumeroDisco > 1) {
                                NumeroDisco--;
                                break;
                            }
                            else
                                beep();
                        }
                        else {
                            // SI RIGHT, disco siguiente
                            if ((TeclaFuncion == KEY_RIGHT) && (NumeroDisco < Estadisticas.NumeroFichas)) {
                                NumeroDisco++;
                                break;
                            }
                            else
                                beep();
                        }
                    }
                }
                // Si ESC se vuelve a pedir el número de disco
                if (TeclaFuncion == KEY_ESC)
                    break;
            }
            keypad(Wdisco,false);
        }
    }
    return;
}
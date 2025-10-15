/*****************************************
 * Nombre: NuevoDisco
 * Argumentos: Window *Wdisco :   Ventana para la captura de los datos del disco nuevo
 *             DISCO **Fichas:    Puntero al array de discos
 * Descripción: Captura los datos de un nuevo disco y lo añade al final del array de discos
 * Reglas de uso: 
 * Código de Retorno: N/A
 * Programador: (JMSM sept-24)
 *****************************************/

#include "Discos.h"

void NuevoDisco(WINDOW *Wdisco,DISCO **Fichas)
{
    char linea[52];
    char linea1[52];
    char Tecla;

    // Si no hay espacio para un nuevo disco se reasigna más espacio al array de discos
    if (Estadisticas.NumeroFichas == Estadisticas.MaxFichas) {
        if ((*Fichas=realloc(*Fichas,sizeof(DISCO)*(Estadisticas.MaxFichas+100))) == NULL) {
            sprintf(linea,"Error %d al alocar %d bytes",errno,sizeof(DISCO)*(Estadisticas.MaxFichas+100));
            VentanaError(linea);
            return;
        }
        Estadisticas.MaxFichas+=100;
    }
    
    curs_set(1);
    echo();

    // Se imprime el número que tendrá el nuevo disco
    mvwprintw(Wdisco,2,23,"%d",Estadisticas.NumeroFichas+1);

    // Se captura la obra del disco. No puede estar en blanco
    while(true) {
        linea[0]=0;
        mvwgetnstr(Wdisco,3,23,linea,50);
        if (strlen(linea) == 0) {
            Tecla=VentanaSN("La obra no puede estar vacia. Desea continuar (S/N)?");
            if (Tecla == 'N')
                return;
            touchwin(Wdisco);
            wrefresh(Wdisco);
        }
        else
            break;
    }

    // Se captura el autor. No puede estar en blanco
    while(true) {
        linea1[0]=0;
        mvwgetnstr(Wdisco,4,23,linea1,50);
        if (strlen(linea1) == 0) {
            Tecla=VentanaSN("El autor no puede estar vacio. Desea continuar (S/N)?");
            if (Tecla == 'N')
                return;
            touchwin(Wdisco);
            wrefresh(Wdisco);
        }
        else
            break;
    }
    // Se guarda el apellido y el nombre
    (*Fichas)[Estadisticas.NumeroFichas].Obra=malloc(strlen(linea)+1);
    strcpy((*Fichas)[Estadisticas.NumeroFichas].Obra,linea);
    (*Fichas)[Estadisticas.NumeroFichas].ApellAutor=malloc(strlen(linea1)+1);
    strcpy((*Fichas)[Estadisticas.NumeroFichas].ApellAutor,linea1);
    // Se captura el nombre del autor. Si es blanco, se guarda NULL
    linea[0]=0;
    mvwgetnstr(Wdisco,5,23,linea,50);
    if (strlen(linea) == 0)
        (*Fichas)[Estadisticas.NumeroFichas].NomAutor=NULL;
    else {
        (*Fichas)[Estadisticas.NumeroFichas].NomAutor=malloc(strlen(linea)+1);
        strcpy((*Fichas)[Estadisticas.NumeroFichas].NomAutor,linea);
    }
    // Se captura la Tonalidad del disco. Si es blanco, se guarda NULL
    linea[0]=0;
    mvwgetnstr(Wdisco,6,23,linea,50);
    if (strlen(linea) == 0)
        (*Fichas)[Estadisticas.NumeroFichas].Tonalidad=NULL;
    else {
        (*Fichas)[Estadisticas.NumeroFichas].Tonalidad=malloc(strlen(linea)+1);
        strcpy((*Fichas)[Estadisticas.NumeroFichas].Tonalidad,linea);
    }
    // Se captura la Editorial. Si es blanco, se guarda NULL
    linea[0]=0;
    mvwgetnstr(Wdisco,7,23,linea,50);
    if (strlen(linea) == 0)
        (*Fichas)[Estadisticas.NumeroFichas].Opus=NULL;
    else {
        (*Fichas)[Estadisticas.NumeroFichas].Opus=malloc(strlen(linea)+1);
        strcpy((*Fichas)[Estadisticas.NumeroFichas].Opus,linea);
    }
    // Se captura la Colección del disco. Si es blanco, se guarda NULL
    linea[0]=0;
    mvwgetnstr(Wdisco,8,23,linea,50);
    if (strlen(linea) == 0)
        (*Fichas)[Estadisticas.NumeroFichas].Duracion=NULL;
    else {
        (*Fichas)[Estadisticas.NumeroFichas].Duracion=malloc(strlen(linea)+1);
        strcpy((*Fichas)[Estadisticas.NumeroFichas].Duracion,linea);
    }

    // Se aumenta el número de discos
    Estadisticas.NumeroFichas++;
    noecho();    
    curs_set(0);

    // Mensaje de que se ha hecho bien
    VentanaError("El Disco se ha dado de alta correctamente");
    return;
}
/*****************************************
 * Nombre: DescartarFichero
 * Argumentos: DISCO **Fichas:   Puntero al array de discos
 *             WINDOW *Wfichero: Ventana para mostrar el nombre del fichero
 * Descripción: Muestra los datos del fichero y los discos almacenados y descarta todos
 *              los discos en memoria y libera la memoria asignada.
 * Reglas de uso: 
 * Código de Retorno:
 * Programador: JMSM (Sept-24)
 *****************************************/

#include "Ficheros.h"

void DescartarFichero(DISCO **Fichas,WINDOW *Wfichero)
{
    
    // Código del alumno
    char Tecla;

    if(*Fichas == NULL)
    {
        VentanaError("No hay fichas de disco para descartar");
    }else
    {
        Tecla=VentanaSN("Esta seguro de querer eliminar los discos? (S/N)?");
        if (Tecla == 'S' || Tecla == 's') 
        {
            for (int j = 0; j < Estadisticas.NumeroFichas; j++)
            {
                free((*Fichas)[j].Obra);
                free((*Fichas)[j].ApellAutor);
                free((*Fichas)[j].NomAutor);
                free((*Fichas)[j].Tonalidad);
                free((*Fichas)[j].Opus);
                free((*Fichas)[j].Duracion);
            }
            Estadisticas.NumeroFichas = 0;    
            free(*Fichas);
            *Fichas = NULL;
            touchwin(Wfichero);
            wrefresh(Wfichero);
            VentanaError("La eliminacion se llevo acabo correctamente");
        }
    }
    
}
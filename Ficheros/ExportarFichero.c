/*****************************************
 * Nombre: ExportarFichero
 * Argumentos: DISCO **Fichas:   Puntero al array de discos
 *             WINDOW *Wfichero: Ventana para capturar el nombre del fichero
 * Descripción: Lee el nombre del fichero que contendrá los datos a exportar. Exporta los datos de la estructura
 *              de todos los discos en el fichero.
 * Reglas de uso: 
 * Código de Retorno:
 * Programador: JMSM (Sept-24)
 *****************************************/

#include "Ficheros.h"

void ExportarFichero(DISCO **Fichas,WINDOW *Wfichero)
{
    // Código del alumno
    //Variables locales
    char nombreFicheros[50];//cadena de caracteres para el nombre del fichero
    FILE *punteroFichero = NULL; 

    //Variables donde guardaré los valores de cada disco
    char obra[50];
    char apellidos[50];
    char nombre[50];
    char tonalidad[50];
    char opus[50];
    char duracion[50];

    int contador = 0; // contador para las fichas exportadas

    //condicional para mostrar error en caso que no haya ficheros por exportar
    if (Fichas == NULL || *Fichas == NULL) { 
        VentanaError("No hay fichas de discos que exportar.");
        return;
    }
        

    touchwin(Wfichero);
    wrefresh(Wfichero);

    // Mover cursor a la posición de entrada, y capturar entrada
    echo(); //Dejo que el usuario vea lo que escribe
    curs_set(1); //Enseño donde está el cursor
    mvwgetnstr(Wfichero, 2,25, nombreFicheros, 50);
    curs_set(0); //Ya no se ve el cursor
    noecho();  //Ya no se enseña lo que se escribe 
    wrefresh(Wfichero);

    
    
    
    // Controlar si se introdujo un nombre válido
    if (nombreFicheros[0] == '\0') {
        VentanaError("Exportación cancelada: Nombre de fichero no válido.");
        return;
    }

    //Abro el fichero en escritura
    punteroFichero = fopen(nombreFicheros, "w");
    
    //Controlo si ha habido algún error
    if (punteroFichero == NULL) {
        VentanaError("ERROR: No se pudo abrir el fichero para escritura.");
        return;
    }
    

    // Escribo la cabecera en el fichero.
    fprintf(punteroFichero, "Obra;Apellidos;Nombre;Tonalidad;Opus;Duracion\n");
    
    // Inicio el loop que escribirá cada disco en el fichero
    int i = 0;
    while (i < Estadisticas.NumeroFichas) //Se reproducirá hasta que haya escrito todas las fichas
    { 

        //Copio los valores a un string para evitar excepciones a la hora de escribir en  la exportación
        //Como Obra y apellidos no pueden ser nulos, no hago la comprobación
        strcpy(obra, (*Fichas)[i].Obra);
        strcpy(apellidos, (*Fichas)[i].ApellAutor);
        
        //Si el campo del nombre del autor es nulo, le copio al string un texto sin nada para evitar excepciones
        //Nombre del autor
        if ((*Fichas)[i].NomAutor == NULL)
        {
            strcpy(nombre, "");
        }

        else
        {
            strcpy(nombre, (*Fichas)[i].NomAutor);
        }

        //Tonalidad
        if ((*Fichas)[i].Tonalidad == NULL)
        {
            strcpy(tonalidad, "");
        }

        else
        {
            strcpy(tonalidad, (*Fichas)[i].Tonalidad);
        }

        //Opus
        if ((*Fichas)[i].Opus == NULL)
        {
            strcpy(opus, "");
        }

        else
        {
            strcpy(opus, (*Fichas)[i].Opus);
        }

        //Duración
        if ((*Fichas)[i].Duracion == NULL)
        {
            strcpy(duracion, "");
        }

        else
        {
            strcpy(duracion, (*Fichas)[i].Duracion);
        }

        // Escribo una línea con los datos del disco separados por ';'.
        fprintf(punteroFichero, "%s;%s;%s;%s;%s;%s\n",
                obra,
                apellidos,
                nombre,
                tonalidad,
                opus,
                duracion);

        contador++; // Contar discos exportados
        i++;
    }

    // Cierro el fichero
    fclose(punteroFichero);


    // Muestro el número de discos exportados.
    mvwprintw(Wfichero, 3, 20, "%d", contador);
    touchwin(Wfichero);
    wrefresh(Wfichero);
    // Informo que los discos se han exportado correctamente.
    VentanaError("Datos guardados correctamente"); 
}
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
    char nombreFicheros[50];//cadena de caracteres para los diferentes campos de cada disco
    FILE *punteroFichero = NULL; 

    int contador = 0; // contador para las fichas exportadas

    //condicional para mostrar error en caso que no haya ficheros por exportar
    if (Fichas == NULL || *Fichas == NULL) { 
        VentanaError("No hay fichas de discos que exportar.");
        return;
    }
        

    touchwin(Wfichero);
    wrefresh(Wfichero);

    // Mover cursor a la posición de entrada, y capturar entrada
    echo(); // Habilita el eco
    curs_set(1);
    mvwgetnstr(Wfichero, 2,25, nombreFicheros, 250);
    curs_set(0);
    noecho(); // Deshabilita el eco
    wrefresh(Wfichero);

    
    
    
    // Controlar si se introdujo un nombre válido
    if (nombreFicheros[0] == '\0') {
        VentanaError("Exportación cancelada: Nombre de fichero no válido.");
        return;
    }

    // 3. Abrir el fichero en escritura y controlar si ha habido error.
    punteroFichero = fopen(nombreFicheros, "w");
    
    if (punteroFichero == NULL) {
        VentanaError("ERROR: No se pudo abrir el fichero para escritura.");
        return;
    }
    

    // 4. Escribir la cabecera en el fichero.
    // La cabecera coincide con el formato de campos de su importación.
    fprintf(punteroFichero, "Obra;Apellidos;Nombre;Tonalidad;Opus;Duracion\n");
    
    // 5. Para cada disco en la estructura de discos:
    int i = 0;
    while (Fichas[i] != NULL) 
    {
        
        DISCO *disco_actual = malloc(sizeof(DISCO));
        *disco_actual = (*Fichas)[i];

        // Escribir una línea con los datos del disco separados por ';'.
        fprintf(punteroFichero, "%s;%s;%s;%s;%s;%s\n",
                disco_actual->Obra,
                disco_actual->ApellAutor,
                disco_actual->NomAutor,
                disco_actual->Tonalidad,
                disco_actual->Opus,
                disco_actual->Duracion);

        contador++; // Contar discos exportados
        i++;
    }

    // 6. Cerrar el fichero
    fclose(punteroFichero);


    // 7. Mostrar el número de discos exportados.
    mvwprintw(Wfichero, 3, 20, "%d", contador);
    touchwin(Wfichero);
    wrefresh(Wfichero);
    // 8. Informar que los discos se han exportado correctamente.
    VentanaError("Datos guardados correctamente"); 
}
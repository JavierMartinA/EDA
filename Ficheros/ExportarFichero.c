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
    
    //variables de tiempo
    long inicio;
    long final;
    int tim;

    int contador = 0; // contador para las fichas exportadas

    //condicional para mostrar error en caso que no haya ficheros por exportar
    if (Fichas == NULL || *Fichas == NULL) { 
        VentanaError("No hay fichas de discos que exportar.");
        return;
    }
        

    touchwin(Wfichero);
    wrefresh(Wfichero);

    // Prompt en la ventana preguntando el nombre del fichero
    mvwprintw(Wfichero, 3, 2, "Fichero a exportar (ej: export.csv): ");
    
    // Mover cursor a la posición de entrada, limpiar línea y capturar entrada
    int x_entrada = 37; // Ajuste de columna
    wmove(Wfichero, 3, x_entrada); 
    wclrtoeol(Wfichero); 
    echo(); // Habilita el eco
    wgetnstr(Wfichero, nombreFicheros, sizeof(nombreFicheros) - 1);
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
    
    inicio = clock(); // Iniciar medición de tiempo

    // 4. Escribir la cabecera en el fichero.
    // La cabecera coincide con el formato de campos de su importación.
    fprintf(punteroFichero, "Obra;Apellidos;Nombre;Tonalidad;Opus;Duracion\n");
    
    // 5. Para cada disco en la estructura de discos:
    int i = 0;
    while (Fichas[i] != NULL) 
    {
        DISCO *disco_actual = Fichas[i];

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

    final = clock(); // Finalizar medición de tiempo
    tim = (int)(final - inicio) * 1000 / CLOCKS_PER_SEC; // Cálculo del tiempo (ms)

    // 7. Mostrar el número de discos exportados.
    char msg[100];
    snprintf(msg, sizeof(msg), "Exportación finalizada. Se exportaron %d fichas en %d ms.", contador, tim);
    VentanaError(msg); 

    // 8. Informar que los discos se han exportado correctamente.
    snprintf(msg, sizeof(msg), "Datos guardados correctamente en: %s", nombreFicheros);
    VentanaError(msg); 
}
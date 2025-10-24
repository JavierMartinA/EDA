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
    
    char Tecla; //Variable para la confirmación del ususarios

    //Comprobamos si existen discos cargados
    if(*Fichas == NULL)
    {
        VentanaError("No hay fichas de disco para descartar"); //Error si no hay discos
    }
    else
    {
        Tecla=VentanaSN("Esta seguro de querer eliminar los discos? (S/N)?"); //Mensaje de confirmación de eliminación
        if (Tecla == 'S' || Tecla == 's') 
        {
            for (int j = 0; j < Estadisticas.NumeroFichas; j++) //Bucle for para liberar el espacio asignado a cada campo de la estructura de DISCOS
            {
                free((*Fichas)[j].Obra);
                free((*Fichas)[j].ApellAutor);
                free((*Fichas)[j].NomAutor);
                free((*Fichas)[j].Tonalidad);
                free((*Fichas)[j].Opus);
                free((*Fichas)[j].Duracion);
            }
            free(*Fichas); // Liberamos el array completo de estructuras DISCO
            *Fichas = NULL; //Inicializamos el array de estructuras de DISCOS a NULL 
             Estadisticas.NumeroFichas = 0; //Reseteamos las estadísticas
            Estadisticas.MaxFichas = 0;
            Estadisticas.TiempoCarga = 0;
            Estadisticas.TiempoSeleccion = 0;
            Estadisticas.TiempoBurbuja = 0;
            Estadisticas.TiempoInsercion = 0;
            Estadisticas.TiempoQuicksort = 0;
            Estadisticas.TiempoBusquedaSecuencial = 0;
            Estadisticas.TiempoBusquedaBinaria = 0;
            Estadisticas.TiempoBusquedaArbol = 0;
            VentanaError("La eliminacion se llevo acabo correctamente"); //Confirmación de eliminación
        }
    }
    
}
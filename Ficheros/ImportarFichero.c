/*****************************************
 * Nombre: ImortarFichero
 * Argumentos: DISCO **Fichas:   Puntero al array de discos
 *             WINDOW *Wfichero: Ventana para capturar el nombre del fichero
 *             bool sumar:       Si es true las fichas de discos se añaden a las existentes,
 *                               si es false la lista de discos tiene que estar vacía.
 * Descripción: Lee el nombre del fichero que contendrá los datos a importar. Carga los discos del fichero
 *              en el array de discos, dimensionándolo si es necesario y descartando los que no tengan título o autor.
 * Reglas de uso: 
 * Código de Retorno:
 * Programador: JMSM (Sept-24)
 *****************************************/

#include "Ficheros.h"

void ImportarFichero(DISCO **Fichas,WINDOW *Wfichero,bool sumar)
{
   
    #include "Ficheros.h"

    char nombreFicheros[50];

    FILE *punteroFichero;

    long inicio;
    long final;
    int tim;

    char obra[50];
    char apellidos[50];
    char nombre[50];
    char tonalidad[50];
    char opus[50];
    char duracion[50];

    int contador;


    // Código del alumno
    if (!sumar) //No debería haber discos
    {
        if (Estadisticas.NumeroFichas == '0') //Comprobación de 0 discos
        {
            touchwin(Wfichero);
            wrefresh(Wfichero);

            wscanw(Wfichero,"%s",&nombreFicheros);

            fopen(nombreFicheros, "r"); //Cabecera en línea 0

            if (punteroFichero == NULL)
            {
                VentanaError("No se ha encontrado el fichero");
                return;
            }

            
            inicio = clock();
            fscanf(punteroFichero, "%s; %s; %s;%s;%s;%s"); //Para quitar header

            while (fscanf(punteroFichero, "%s; %s; %s;%s;%s;%s"), &obra, &apellidos, &nombre, &tonalidad, &opus, &duracion)
            {
                contador++;

            }
            


            


        }

        else
        {
            VentanaError("Hay fichas de discos");
            return;
        }
        
        
    }

    else
    {
        if(Estadisticas.NumeroFichas > 0 || Estadisticas.NumeroFichas < 0) //Comprobación de que hay discos
        {

        }

        else
        {
            VentanaError("No hay fichas de discos");
        }
    }

}
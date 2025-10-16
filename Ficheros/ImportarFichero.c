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

    char scan[200];
    char obra[50];
    char apellidos[50];
    char nombre[50];
    char tonalidad[50];
    char opus[50];
    char duracion[50];

    int contador = 0;
    int numValor;
    int descartes = 0;
    int tratados = 0;


    // Código del alumno
    if (!sumar) //No debería haber discos
    {
        if (Estadisticas.NumeroFichas == 0) //Comprobación de 0 discos
        {
            touchwin(Wfichero);
            wrefresh(Wfichero);

            wscanw(Wfichero,"%s",&nombreFicheros);
            mvwscanw(Wfichero, 3, 20,"%s",&nombreFicheros);

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
            Fichas = realloc(Fichas, (contador + 1) * sizeof(DISCO *));
            fscanf(punteroFichero, "%s"); //Para quitar header

            while (fscanf(punteroFichero, "%s", &scan) != NULL) //Para leer todas las líneas
            {
                Fichas[contador] = malloc(sizeof(DISCO));
                contador++;

                while(scan != NULL) //Para leer cada valor de cada línea
                {
                    char * punteroScan = scan;
                    char * valor;
                    char *valores[6];

                    while ((valor = strsep(punteroScan, ";")) != NULL) //Guardar todos los valores
                    {
                        valores[numValor] = valor; //Guardar valor en el array
                        numValor++; //Siguiente espacio en el array
                    }

                    if (valores[0] == NULL || valores[1] == NULL) //Si obra o apellidos no están descarto la ficha
                    {
                        descartes++;
                        return;
                    }

                    Fichas[contador]->Obra = valores[0];
                    Fichas[contador]->ApellAutor = valores[1];
                    Fichas[contador]->NomAutor = valores[2];
                    Fichas[contador]->Tonalidad = valores[3];
                    Fichas[contador]->Opus = valores[4];
                    Fichas[contador]->Duracion = valores[5];

                    
                    


                    
                }



                
            }

            if (contador == 0)
            {
                VentanaError("No contiene discos");
                return;
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
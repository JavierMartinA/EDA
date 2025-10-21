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
    // Código del alumno

    char nombreFicheros[250];

    FILE *punteroFichero; //Declaro puntero tipo FILE para cuando abra el fichero

    long inicio;
    long final;
    long tim;

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

    if (!sumar) //No debería haber discos
    {
        if (Estadisticas.NumeroFichas == 0) //Comprobación de 0 discos
        {
            touchwin(Wfichero);
            wrefresh(Wfichero);

            wscanw(Wfichero,"%s",nombreFicheros);
            mvwscanw(Wfichero, 3, 20,"%s",nombreFicheros);

            punteroFichero = fopen(nombreFicheros, "r"); //Abro el fichero

            if (punteroFichero == NULL)
            {
                VentanaError("No se ha encontrado el fichero");
                return;
            }

            
            inicio = clock();

            fscanf(punteroFichero, "%s"); //Para quitar header

            while (fscanf(punteroFichero, "%s", &scan) != NULL) //Para leer todas las líneas
            {
                //Pongo la suma del contador al final para facilitar el número de discos tratados y el acceso al array
                *Fichas = realloc(*Fichas, (contador+1) * sizeof(DISCO *)); //Pido memoria para el array de discos
                if (*Fichas == NULL)
                {
                    VentanaError("No se ha encontrado espacio para el bloque de discos"); //Compruebo que se me haya dado espacio
                    return;
                }
                Fichas[contador] = malloc(sizeof(DISCO)); //Pido memoria en cada una de las celdas del (array) Fichas para contener los valores de la estructura disco
                if (Fichas[contador] == NULL)
                {
                    VentanaError("No hay espacio para guardar el disco");
                    return;
                }

                //Leo cada valor de cada línea
                char *punteroScan = scan;
                char *valor;
                char **valores;

                while ((valor = strsep(punteroScan, ";")) != NULL) //Guardar todos los valores
                {
                    valores[numValor] = *valor; //Guardar valor en el array
                    numValor++; //Siguiente espacio en el array
                }

                if (valores[0] == NULL || valores[1] == NULL) //Si obra o apellidos no están, descarto la ficha
                {
                    descartes++;
                    break; //No dejo que guarde los valores en la estructura
                }

                Fichas[contador]->Obra = valores[0];
                Fichas[contador]->ApellAutor = valores[1];
                Fichas[contador]->NomAutor = valores[2];
                Fichas[contador]->Tonalidad = valores[3];
                Fichas[contador]->Opus = valores[4];
                Fichas[contador]->Duracion = valores[5];

                tratados++;
                contador++; //Contador de discos en el fichero

            }

            //mvwprint(Wfichero, x, y, "Ficheros tratados: %d", tratados);
            //mvwprint(Wfichero, x, y, "Ficheros descartados: %d", descartes);


            fclose (punteroFichero); //Cierro el fichero
            final = clock();
            tim = gettimeofday(inicio, final);


            if (contador == 0)
            {
                VentanaError("El fichero solo tiene cabecera");
                return;
            }
        }

        else
        {
            VentanaError("Hay fichas de discos");
            return;
        }
        
        
    }

    else //Para añadir las fichas de un fichero a la lista de discos existentes
    {
        if(Estadisticas.NumeroFichas > 0 || Estadisticas.NumeroFichas < 0) //Comprobación de que hay discos
        {
        
            touchwin(Wfichero);
            wrefresh(Wfichero);

            wscanw(Wfichero,"%s",&nombreFicheros);
            mvwscanw(Wfichero, 3, 20,"%s",&nombreFicheros);

            punteroFichero = fopen(nombreFicheros, "r"); //Abro el fichero

            if (punteroFichero == NULL)
            {
                VentanaError("No se ha encontrado el fichero");
                return;
            }

            
            inicio = clock();

            fscanf(punteroFichero, "%s"); //Para quitar header

            while (fscanf(punteroFichero, "%s", &scan) != NULL) //Para leer todas las líneas
            {
                //Pongo la suma del contador al final para facilitar el número de discos tratados y el acceso al array
                *Fichas = realloc(*Fichas, ((contador+1)+Estadisticas.NumeroFichas) * sizeof(DISCO *)); //Pido memoria para el array de discos
                if (*Fichas == NULL)
                {
                    VentanaError("No se ha encontrado espacio para el bloque de discos"); //Compruebo que se me haya dado espacio
                    return;
                }
                Fichas[contador + Estadisticas.NumeroFichas] = malloc(sizeof(DISCO)); //Pido memoria en cada una de las celdas del (array) Fichas para contener los valores de la estructura disco
                if (Fichas[contador + Estadisticas.NumeroFichas] == NULL)
                {
                    VentanaError("No hay espacio para guardar el disco");
                    return;
                }

            
                char * punteroScan = scan;
                char * valor;
                char **valores;

                while ((valor = strsep(punteroScan, ";")) != NULL) //Guardar todos los valores
                {
                    valores[numValor] = valor; //Guardar valor en el array
                    numValor++; //Siguiente espacio en el array
                }

                if (valores[0] == NULL || valores[1] == NULL) //Si obra o apellidos no están, descarto la ficha
                {
                    descartes++;
                    break; //No dejo que guarde los valores en la estructura
                }

                *Fichas[contador + Estadisticas.NumeroFichas]->Obra = valores[0];
                *Fichas[contador + Estadisticas.NumeroFichas]->ApellAutor = valores[1];
                *Fichas[contador + Estadisticas.NumeroFichas]->NomAutor = valores[2];
                *Fichas[contador + Estadisticas.NumeroFichas]->Tonalidad = valores[3];
                *Fichas[contador + Estadisticas.NumeroFichas]->Opus = valores[4];
                *Fichas[contador + Estadisticas.NumeroFichas]->Duracion = valores[5];

                tratados++;
                contador++; //Contador de discos en el fichero

            

                //mvwprint(Wfichero, x, y, "Ficheros tratados: %d", tratados);
                //mvwprint(Wfichero, x, y, "Ficheros descartados: %d", descartes);


                fclose (punteroFichero); //Cierro el fichero
                final = clock();
                tim = gettimeofday(inicio, final);


                if (contador == 0)
                {
                    VentanaError("El fichero solo tiene cabecera");
                    return;
                }
            }
        }

        else
        {
            VentanaError("No hay fichas de discos");
            return;
        }
    }

    
    //Actualizar datos de Estadísticas
    Estadisticas.Fichero = nombreFicheros;
    Estadisticas.MaxFichas = Estadisticas.MaxFichas + tratados + descartes;
    Estadisticas.NumeroFichas = Estadisticas.NumeroFichas + tratados;
    Estadisticas.TiempoCarga = tim;

    return;

}
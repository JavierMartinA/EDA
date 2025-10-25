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
    #define TAM_LINEA 100

    // Código del alumno
    char nombreFicheros[250];

    FILE *punteroFichero; //Declaro puntero tipo FILE para cuando abra el fichero

    struct timeval inicio;
    struct timeval final;
    int lineas = 0;
    

    char scan[256];

    int contador = 0;
    int descartes = 0;
    int tratados = 0;

    if (!sumar) //No debería haber discos
    {
        if (Estadisticas.NumeroFichas == 0) //Comprobación de 0 discos
        {
            touchwin(Wfichero);
            wrefresh(Wfichero);

            //La mayoría de este código ha sido basado en el código de NuevoDisco.c

            //Guardo memoria para la primera tanda de discos
            if ((*Fichas=realloc(*Fichas,sizeof(DISCO)*(Estadisticas.MaxFichas+100))) == NULL)
            {
                VentanaError("No hay suficiente espacio");
                return;
            }

            Estadisticas.MaxFichas +=100;

            //Permito al usuario escribir el nombre del csv
            wattroff(Wfichero, A_ALTCHARSET);
            echo();
            curs_set(1);
            mvwgetnstr(Wfichero,2,25,nombreFicheros, 250); //Recojo el nombre
            curs_set(0);
            noecho();


            punteroFichero = fopen(nombreFicheros, "r"); //Abro el fichero

            if (punteroFichero == NULL) //Compruebo que el nombre del fichero sea correcto
            {
                VentanaError("No se ha encontrado el fichero");
                return; //Si no es correcto, cierro la función de ImportarFichero.c y vuelvo al menú principal
            }
            
            Estadisticas.Fichero = malloc(strlen(nombreFicheros) + 1); //Reservo memoria para guardar el valor de nombre del fichero en la variable global correspondiente
            strcpy(Estadisticas.Fichero, nombreFicheros);//Copio el nombre del fichero en la variables global
            
            gettimeofday(&inicio, NULL); //Get time of day contiene 2 parámetros, un parámetro es un puntero tipo estructura donde guarda la hora actual y el otro parámetro es la zona horaria
            //Guarda la hora actual en medida en segundos y microsegundos

                   
            fgets(scan, 256, punteroFichero); //Para quitar header          

            
            //Empiezo a leer las líneas que contienen los discos 
            while (fgets(scan, TAM_LINEA, punteroFichero) != NULL)
            { 
                // Si no hay espacio para un nuevo disco se reasigna más espacio al array de discos
                if (Estadisticas.NumeroFichas == Estadisticas.MaxFichas) {
                    if ((*Fichas=realloc(*Fichas,sizeof(DISCO)*(Estadisticas.MaxFichas+100))) == NULL) {

                        VentanaError("No hay suficiente espacio");
                        return; //Si no hay espacio cierro la función y vuelvo al menú
                    }
                    Estadisticas.MaxFichas+=100; //Aumento el número máximo de fichas que tengo + 100
                }


                //El fgets lee 100 bits que es la constante que le hemos puesto, por eso luego crea espacios en negro cuando lo escribo en gestión de discos
                //Para resolverlo, voy a eliminar desde el final los bits que no contengan ninguna letra
                // Para ello recorro la cadena desde el final hasta el inicio
                for (int i = strlen(scan) - 1; i >= 0; i--) {
                    if (scan[i] == '\n' || scan[i] == '\r') { //Remplazo los carácteres especiales que no son letras por final de línea
                        scan[i] = '\0';  
                    } else {
                        break;  // En cuanto detecto una letra, paro de sobreescribir los bits como final de línea
                    }
                }
            
                

                //El elemento fgets lee hasta el \0, el problema es que detecta algunos \0 antes de leerse todo el texto de la línea y por ello aumenta el número de líneas leídas y descartadas
                //Por ello leo cuantos separadores hay en la línea leída y si hay menos de los 5 que debe, lo paso
                int numeroSeparadores = 0;
                for (int i = 0; scan[i] != '\0'; i++) //Voy recorriendo la línea de inicio a fin
                {
                    if (scan[i] == ';') //Aumento el número de separadores leídos cada vez que me encuentro uno
                    {
                        numeroSeparadores++;
                    }
                }
                if (numeroSeparadores < 5) //Entra si hay un salto de línea antes de que se me den los 6 valores
                {
                    continue;
                }

                char *punteroScan = scan; //Creo puntero que apunte a la línea leída por fgets
                char *valor; //Puntero para recibir cada string de la función strsep
                char palabra[100]; //String para guardar lo que tenga valor y pasarselo a parte de la estructura de disco correspondiente

                valor = strsep(&punteroScan, ";"); //Coger el valor de obra de cada línea

                // Si no hay valor o está vacío
                if (valor == NULL || valor[0] == '\0') //Elimino el disco y voy a la siguiente iteración
                {
                    //VentanaError("Nombre de la obra en blanco, se eliminara este disco");
                    descartes++;
                    continue;
                }

                strcpy(palabra, valor); //Paso a palabra el valor al que apunta valor, en este caso el nombre de la obra

                (*Fichas)[Estadisticas.NumeroFichas].Obra = malloc(strlen(palabra) + 1); //Reservo espacio para el nombre de la obra en el puntero de disco .Obra
                strcpy((*Fichas)[Estadisticas.NumeroFichas].Obra, palabra); //Paso el valor de palabra a obra
                palabra[0] = 0; //Limpiar palabra

            

                valor = strsep(&punteroScan, ";"); //Coger el valor de apellidos del autor de cada línea
                
                if (valor == NULL || valor[0] == '\0')
                {
                    //VentanaError("Apellidos del autor en blanco, se eliminara este disco");
                    free((*Fichas)[Estadisticas.NumeroFichas].Obra);
                    descartes ++;
                    continue;
                }

                strcpy(palabra, valor);       
                (*Fichas)[Estadisticas.NumeroFichas].ApellAutor=malloc(strlen(palabra)+1);
                strcpy((*Fichas)[Estadisticas.NumeroFichas].ApellAutor,palabra);
                palabra[0]=0;

                valor = strsep(&punteroScan, ";"); //Coger el valor de nombre del autor para cada línea
                strcpy(palabra, valor);
                if (strlen(palabra) == 0) //Si valor apunta a un valor vacío, palabra también estará vacío y pondrá el nombre de autor como nulo
                    (*Fichas)[Estadisticas.NumeroFichas].NomAutor=NULL;
                else { //Si valor no está vacío, reservo espacio para el puntero de nombre autor del disco y le copio el contenido de palabra
                    (*Fichas)[Estadisticas.NumeroFichas].NomAutor=malloc(strlen(palabra)+1);
                    strcpy((*Fichas)[Estadisticas.NumeroFichas].NomAutor,palabra);
                }
                palabra[0]=0;

                valor = strsep(&punteroScan, ";"); //Coger el valor de tonalidad de la obra para cada línea
                strcpy(palabra, valor);
                if (strlen(palabra) == 0)
                    (*Fichas)[Estadisticas.NumeroFichas].Tonalidad=NULL;
                else {
                    (*Fichas)[Estadisticas.NumeroFichas].Tonalidad=malloc(strlen(palabra)+1);
                    strcpy((*Fichas)[Estadisticas.NumeroFichas].Tonalidad,palabra);
                }
                palabra[0]=0;

                valor = strsep(&punteroScan, ";");//Coger el valor de opus de la obra para cada línea
                strcpy(palabra, valor);
                if (strlen(palabra) == 0)
                    (*Fichas)[Estadisticas.NumeroFichas].Opus=NULL;
                else {
                    (*Fichas)[Estadisticas.NumeroFichas].Opus=malloc(strlen(palabra)+1);
                    strcpy((*Fichas)[Estadisticas.NumeroFichas].Opus,palabra);
                }
                palabra[0]=0;

                valor = strsep(&punteroScan, ";"); //Coger el valor de duración de la obra para cada línea
                strcpy(palabra, valor);
                if (strlen(palabra) == 0)
                    (*Fichas)[Estadisticas.NumeroFichas].Duracion=NULL;
                else {
                    (*Fichas)[Estadisticas.NumeroFichas].Duracion=malloc(strlen(palabra)+1);
                    strcpy((*Fichas)[Estadisticas.NumeroFichas].Duracion,palabra);
                }

                contador++; //Aumento contador solo para comprobar que el file tenga más que solo cabecera
                Estadisticas.NumeroFichas++; //Aumento el número de fichas que tengo, para que en la siguiente iteración se utilice la siguiente estructura de disco en la superestructura (array de discos)
            }    

            mvwprintw(Wfichero, 3, 20, "%d", contador);
            mvwprintw(Wfichero, 3, 55, "%d", descartes);

            touchwin(Wfichero);
            wrefresh(Wfichero);

            if (contador == 0)
            {
                VentanaError("El fichero solo tiene cabecera");
                return;
            }

            fclose (punteroFichero); //Cierro el fichero
            gettimeofday(&final, NULL);
            //tim = gettimeofday(inicio, final);
            //Estadisticas.TiempoCarga = tim;
            VentanaError("Documento leido");    
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

            //La mayoría de este código ha sido basado en el código de NuevoDisco.c

            //Esta vez no pido memoria de inicio para la tanda de discos, ya que ya debería de haber declarado otros discos antes
            //Aunque no hubiera suficiente, la pediré cuando entre al while

            //Permito al usuario escribir el nombre del csv
            wattroff(Wfichero, A_ALTCHARSET);
            echo();
            curs_set(1);
            mvwgetnstr(Wfichero,2,25,nombreFicheros, 250); //Recojo el nombre
            curs_set(0);
            noecho();


            punteroFichero = fopen(nombreFicheros, "r"); //Abro el fichero

            if (punteroFichero == NULL) //Compruebo que el nombre del fichero sea correcto
            {
                VentanaError("No se ha encontrado el fichero");
                return; //Si no es correcto, cierro la función de ImportarFichero.c y vuelvo al menú principal
            }

            Estadisticas.Fichero = malloc(strlen(nombreFicheros) + 1); //Reservo memoria para guardar el valor de nombre del fichero en la variable global correspondiente
            strcpy(Estadisticas.Fichero, nombreFicheros);//Copio el nombre del fichero en la variables global
            
            gettimeofday(&inicio, NULL);

                   
            fgets(scan, 256, punteroFichero); //Para quitar header          

            //Empiezo a leer las líneas que contienen los discos 
            while (fgets(scan, TAM_LINEA, punteroFichero) != NULL)
            {
                // Si no hay espacio para un nuevo disco se reasigna más espacio al array de discos
                if (Estadisticas.NumeroFichas == Estadisticas.MaxFichas) 
                {
                        if ((*Fichas=realloc(*Fichas,sizeof(DISCO)*(Estadisticas.MaxFichas+100))) == NULL) 
                    {
                        VentanaError("No hay suficiente espacio");
                        return; //Si no hay espacio cierro la función y vuelvo al menú
                    }
                    Estadisticas.MaxFichas+=100; //Aumento el número máximo de fichas que tengo + 100
                }

                //El fgets lee 100 bits que es la constante que le hemos puesto, por eso luego crea espacios en negro cuando lo escribo en gestión de discos
                //Para resolverlo, voy a eliminar desde el final los bits que no contengan ninguna letra
                // Para ello recorro la cadena desde el final hasta el inicio
                for (int i = strlen(scan) - 1; i >= 0; i--) {
                    if (scan[i] == '\n' || scan[i] == '\r') { //Remplazo los carácteres especiales que no son letras por final de línea
                        scan[i] = '\0';  
                    } else {
                        break;  // En cuanto detecto una letra, paro de sobreescribir los bits como final de línea
                    }
                }
            
                

                //El elemento fgets lee hasta el \0, el problema es que detecta algunos \0 antes de leerse todo el texto de la línea y por ello aumenta el número de líneas leídas y descartadas
                //Por ello leo cuantos separadores hay en la línea leída y si hay menos de los 5 que debe, lo paso
                int numeroSeparadores = 0;
                for (int i = 0; scan[i] != '\0'; i++) //Voy recorriendo la línea de inicio a fin
                {
                    if (scan[i] == ';') //Aumento el número de separadores leídos cada vez que me encuentro uno
                    {
                        numeroSeparadores++;
                    }
                }
                if (numeroSeparadores < 5) //Entra si hay un salto de línea antes de que se me den los 6 valores
                {
                    continue;
                }
                

                char *punteroScan = scan; //Creo puntero que apunte a la línea leída por fgets
                char *valor; //Puntero para recibir cada string de la función strsep
                char palabra[100]; //String para guardar lo que tenga valor y pasarselo a parte de la estructura de disco correspondiente

                valor = strsep(&punteroScan, ";"); //Coger el valor de obra de cada línea

                // Si no hay valor o está vacío
                if (valor == NULL || valor[0] == '\0') //Elimino el disco y voy a la siguiente iteración
                {
                    //VentanaError("Nombre de la obra en blanco, se eliminara este disco");
                    descartes++;
                    continue;
                }

                strcpy(palabra, valor); //Paso a palabra el valor al que apunta valor, en este caso el nombre de la obra

                (*Fichas)[Estadisticas.NumeroFichas].Obra = malloc(strlen(palabra) + 1); //Reservo espacio para el nombre de la obra en el puntero de disco .Obra
                strcpy((*Fichas)[Estadisticas.NumeroFichas].Obra, palabra); //Paso el valor de palabra a obra
                palabra[0] = 0; //Limpiar palabra

            

                valor = strsep(&punteroScan, ";"); //Coger el valor de apellidos del autor de cada línea
                
                if (valor == NULL || valor[0] == '\0')
                {
                    //VentanaError("Apellidos del autor en blanco, se eliminara este disco");
                    free((*Fichas)[Estadisticas.NumeroFichas].Obra);
                    descartes ++;
                    continue;
                }

                strcpy(palabra, valor);       
                (*Fichas)[Estadisticas.NumeroFichas].ApellAutor=malloc(strlen(palabra)+1);
                strcpy((*Fichas)[Estadisticas.NumeroFichas].ApellAutor,palabra);
                palabra[0]=0;

                valor = strsep(&punteroScan, ";"); //Coger el valor de nombre del autor para cada línea
                strcpy(palabra, valor);
                if (strlen(palabra) == 0) //Si valor apunta a un valor vacío, palabra también estará vacío y pondrá el nombre de autor como nulo
                    (*Fichas)[Estadisticas.NumeroFichas].NomAutor=NULL;
                else { //Si valor no está vacío, reservo espacio para el puntero de nombre autor del disco y le copio el contenido de palabra
                    (*Fichas)[Estadisticas.NumeroFichas].NomAutor=malloc(strlen(palabra)+1);
                    strcpy((*Fichas)[Estadisticas.NumeroFichas].NomAutor,palabra);
                }
                palabra[0]=0;

                valor = strsep(&punteroScan, ";"); //Coger el valor de tonalidad de la obra para cada línea
                strcpy(palabra, valor);
                if (strlen(palabra) == 0)
                    (*Fichas)[Estadisticas.NumeroFichas].Tonalidad=NULL;
                else {
                    (*Fichas)[Estadisticas.NumeroFichas].Tonalidad=malloc(strlen(palabra)+1);
                    strcpy((*Fichas)[Estadisticas.NumeroFichas].Tonalidad,palabra);
                }
                palabra[0]=0;

                valor = strsep(&punteroScan, ";");//Coger el valor de opus de la obra para cada línea
                strcpy(palabra, valor);
                if (strlen(palabra) == 0)
                    (*Fichas)[Estadisticas.NumeroFichas].Opus=NULL;
                else {
                    (*Fichas)[Estadisticas.NumeroFichas].Opus=malloc(strlen(palabra)+1);
                    strcpy((*Fichas)[Estadisticas.NumeroFichas].Opus,palabra);
                }
                palabra[0]=0;

                valor = strsep(&punteroScan, ";"); //Coger el valor de duración de la obra para cada línea
                strcpy(palabra, valor);
                if (strlen(palabra) == 0)
                    (*Fichas)[Estadisticas.NumeroFichas].Duracion=NULL;
                else {
                    (*Fichas)[Estadisticas.NumeroFichas].Duracion=malloc(strlen(palabra)+1);
                    strcpy((*Fichas)[Estadisticas.NumeroFichas].Duracion,palabra);
                }

                contador++; //Aumento contador solo para comprobar que el file tenga más que solo cabecera
                Estadisticas.NumeroFichas++; //Aumento el número de fichas que tengo, para que en la siguiente iteración se utilice la siguiente estructura de disco en la superestructura (array de discos)
            }    

            mvwprintw(Wfichero, 3, 20, "%d", contador);
            mvwprintw(Wfichero, 3, 55, "%d", descartes);

            touchwin(Wfichero);
            wrefresh(Wfichero);

            if (contador == 0)
            {
                VentanaError("El fichero solo tiene cabecera");
                return;
            }

            fclose (punteroFichero); //Cierro el fichero
            gettimeofday(&final, NULL);
            //tim = gettimeofday(inicio, final);
            //Estadisticas.TiempoCarga = tim;
            VentanaError("Documento leido en sumar fichero");
        }

        else
        {
            VentanaError("No hay fichas de discos");
            return;
        }
    }

    
    //Actualizar datos de Estadísticas
    Estadisticas.NumeroFichas = Estadisticas.NumeroFichas + tratados;
    Estadisticas.TiempoCarga = DifTiempo(inicio, final);

    return;

}
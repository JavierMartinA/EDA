/*****************************************
 * Nombre: DifTiempo
 * Argumentos: struct timeval inicio:   Tiempo de inicio
 *             struct timeval fin:      Tiempo de fin
 * Descripción: Calcula los microsegundos de diferencia entre ambos tiempos
 * Reglas de uso: 
 * Código de Retorno: Microsegundos de diferencia
 * Programador: JMSM (Sept-24)
 *****************************************/

// Include del módulo funcional
#include "Comun.h"

int DifTiempo(struct timeval inicio,struct timeval fin) //timeval es una estructura con 2 elementos: long tv_sec; long tv_usec;
//tv_sec = tiempo en segundos
//tv_usec = tiempo sobrante que está en microsegundos
{
    int diferencia;         // Microsegundos de diferencia

    // Se restan los microsegundos
    diferencia=fin.tv_usec-inicio.tv_usec; //Diferencia entre los microsegundos tomados en inicio y en el final

    // Si es menor que 0 hay que añadir un segundo y quitarselo a inicio
    if (diferencia < 0) { //La diferencia puede ser negativa ya que por ejemplo inicio puede tener 14 segundos y 54 microsegundos, mientras que final tener 17 segundos y 32 microsegundos
        diferencia += 1000000; //Para resolver esto, simplemente sumas un segundo a los microsegundos y se lo restas a los segundos del final para no equivocarte al sumar luego los segundos de diferencia entre fin e inicio
        fin.tv_sec--;
    }

    // Se añaden los segundos de diferencia
    diferencia=diferencia+(fin.tv_sec-inicio.tv_sec)*1000000; //Diferencia entre los segundos de inicio y final multiplicado por 10^6 ya que son segundos, más(+) los microsegundos calculados antes

    // Se devuelve el número de microsegundos de diferencia
    return(diferencia);
}
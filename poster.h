#ifndef POSTER_H_INCLUDED
#define POSTER_H_INCLUDED

#include "utn.h"
#define POSTER_NAME_MAX 64 /**< Longitud maxima de nombre de imagen de Afiche. */
#define POSTER_INIT 1 /**< Numero entero inicial del Id de Afiche. */
#define POSTER_MAX 1000 /**< Cantidad maxima de Afiches. */

/*! \struct Poster
    \brief
    Tipo de dato de Afiche.
    Afiche a vender a Cliente.
*/
typedef struct
{
    int posterId; /**< Identificador numerico autoincremental de Afiche. */
    char imageName[POSTER_NAME_MAX]; /**< Nombre de la imagen del Afiche. */
    int isEmpty; /**< Indicador de elemento vacio o lleno. */
}Poster;

/** \brief
 *  Funcion que inicializa un array de Aiches con estado vacio.
 *  \param list Poster* Direccion de memoria del array de Afiches.
 *  \param len int Longitud del array de Afiches.
 *  \return 0 si se inicializo correctamente, -1 si hubo un error.
 *
 */
int poster_init(Poster* list, int len);

/** \brief
 *  Funcion que busca el primer Afiche libre a cargar en el array.
 *  \param list Poster* Direccion de memoria del array de Afiches.
 *  \param len int Longitud del array de Afiches.
 *  \return El indice del elemento libre, -1 si no encontro elemento libre.
 *
 */
int poster_getFirstEmpty(Poster* list, int len);

#endif //POSTER_H_INCLUDED
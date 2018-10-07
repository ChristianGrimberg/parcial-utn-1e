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

/** \brief
 *  Funcion que busca si existe el ID del Afiche en el array
 *      y devuelve el indice del elemento.
 *  \param list Poster* Direccion de memoria del array de Afiches.
 *  \param len int Longitud del array de Afiches.
 *  \param id int Numero del ID del Afiche a buscar.
 *  \return El indice del elemento del array, -1 si no lo encontro.
 * 
 */
int poster_findId(Poster* list, int len, int id);

/** \brief
 *  Funcion que busca el ID del Afiche del nombre de la imagen.
 *  \param list Poster* Direccion de memoria del array de Afiches.
 *  \param len int Longitud del array de Afiches.
 *  \param imageName char* Direccion de memoria del nombre de la imagen
 *      del Afiche.
 *  \return El ID del Afiche buscado, -1 si no lo encontro.
 */
int poster_findImage(Poster* list, int len, char* imageName);

/** \brief
 *  Funcion que agrega un Afiche al array.
 *  \param list Poster* Direccion de memoria del array de Afiches.
 *  \param len int Longitud del array de Afiches.
 *  \param imageName char* Direccion de memoria del nombre de la imagen
 *      del Afiche.
 *  \return 0 si pudo agregar el Afiche correctamente, -1 si hubo un error.
 * 
 */
int poster_add(Poster* list, int len, char* imageName);

/** \brief
 *  Funcion que cambia el estado a vacio al indice del Afiche ingresado.
 *  \param list Poster* Direccion de memoria del array de Afiches.
 *  \param len int Longitud del array de Afiches.
 *  \param index int Indice del array de Afiches.
 *  \return 0 si pudo eliminar el Afiche correctamente, -1 si hubo un error.
 * 
 */
int poster_remove(Poster* list, int len, int index);

/** \brief
 *  Funcion que imprime un indice de Afiche del array.
 *  \param list Poster* Direccion de memoria del array de Afiches.
 *  \param index int Indice del array de Afiches.
 *  \return No retona valores.
 * 
 */
void poster_print(Poster* list, int index);

#endif //POSTER_H_INCLUDED
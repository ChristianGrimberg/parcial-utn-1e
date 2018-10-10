#ifndef UTN_H_INCLUDED
#define UTN_H_INCLUDED

#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>
#define CHARACTERS_NUMBERS 64 /**< Valor maximo de caracteres numericos. */
#define STRING_MAX 4096 /**< Valor maximo en cadena de caracteres. */
#define EXIT_BUFFER '\0' /**< Valor de terminacion de cadena de caracteres. */
#define CURRENT_LEN 2 /**< Longitud de valor actual. */
#define DNI_MAX 16 /**< Valor maximo de caracteres de un DNI formateado. */
#define CUIT_HEADER 3 /**< Longitud del encabezado de un CUIT. */
#define CUIT_FOOTER 2 /**< Longitud del pie del CUIT. */
#define EMAIL_MAX 64 /**< Longitud maxima de un Email. */
#define EMAIL_NICK 32 /**< Longitud del nick de una direccion de Email. */
#define EMAIL_DOMAIN 32 /**< Longitud del dominio de una direccion de Email. */
#define RETRY 3 /**< Valor por defecto para reintentos. */
#define ONLY_LETTERS 1 /**< Indicador que es solo letras la cadena. */
#define ALL_CHARACTERES 0 /**< Indicador de cadena que tiene caracteres de todo tipo. */
#define TRUE 1 /**< Estado lleno del elemento del array. */
#define FALSE 0 /**< Estado vacio del elemento del array. */
#define FORMAT_LEN_ID 5 /**< Longitud de formato a cadena del campo id. */
#define HEADER 1 /**< Encabezado de tabla de una lista. */
#define BODY 2 /**< Cuerpo de tabla de una lista. */
#define FOOTER 3 /**< Pie de tabla de una lista. */
#define ERROR_MESSAGE "Valor incorrecto. " /**< Mensaje de falla ante reintentos. */
#define ERROR_EMPTY_LIST "No hay elementos en la lista.\n" /**< Mensaje de lista vacia. */
#define ERROR_FULL_LIST "No hay elementos libres en la lista.\n" /**< Mensaje de lista llena. */
#define ERROR_EXIST_EMPTY "El elemento ya esta dado de baja.\n" /**< Mensaje de elemento ya dado de baja. */
#define ERROR_EXIST_FULL "El elemento ya existe.\n" /**< Mensaje de elemento pre-existente. */
#define ERROR_NOT_EXIST "El elemento no existe.\n" /**< Mensaje de elemento que no existe. */
#define ERROR_EDITION "Error de edicion del elemento.\n" /**< Mensaje de error de edicion. */

/** \brief
 *  Funcion para obtener un entero por teclado en un rango, con mensajes
 *      al usuario.
 *  \param pNumber int* Direccion en memoria del numero a almacenar.
 *  \param retry int Cantidad de reintentos al usuario.
 *  \param min int Valor minimo a ingresar.
 *  \param max int Valor maximo a ingresar.
 *  \param message char* Mensaje personalizado que solicita el dato al usuario.
 *  \param error char* Mensaje personalizado en caso de error.
 *  \return Retorna 0 si obtuvo un entero dentro del rango,
 *      -1 si no es un valor valido.
 *
 */
int utn_getInt(int* pNumber, int retry, int min, int max,
    char* message, char* error);

/** \brief
 *  Funcion para obtener un flotante por teclado en un rango, con mensajes
 *      al usuario.
 *  \param pNumber float* Direccion en memoria del numero a almacenar.
 *  \param retry int Cantidad de reintentos al usuario.
 *  \param min float Valor minimo a ingresar.
 *  \param max float Valor maximo a ingresar.
 *  \param message char* Mensaje personalizado que solicita el dato al usuario.
 *  \param error char* Mensaje personalizado en caso de error.
 *  \return Retorna 0 si obtuvo un flotante dentro del rango,
 *      -1 si no es un valor valido.
 *
 */
int utn_getFloat(float* pNumber, int retry, float min, float max,
    char* message, char* error);

/** \brief
 *  Funcion que obtiene un caracter por teclado y lo valida.
 *  \param pCharacter char* Direccion de memoria del caracter a almacenar.
 *  \param retry int Cantidad de reintentos al usuario.
 *  \param message char* Mensaje personalizado que solicita el dato al usuario.
 *  \param error char* Mensaje personalizado en caso de error.
 *  \return Retorna 0 si obtuvo un caracter, -1 si hubo un error.
 *
 */
int utn_getChar(char* pCharacter, int retry, char* message, char* error);

/** \brief
 *  Funcion para obtener una cadena de caracteres por teclado con mensajes
 *      al usuario.
 *  \param pString char* Direccion de memoria a almacenar la cadena
 *      ingresada por teclado.
 *  \param len int Longitud del array de caracteres a ingresar por teclado.
 *  \param retry int Cantidad de reintentos al usuario.
 *  \param message char* Mensaje personalizado que solicita el dato al usuario.
 *  \param error char* Mensaje personalizado en caso de error.
 *  \param isOnlyLetters int Indicador si acepta solo letras (ONLY_LETTERS:1)
 *      o letras, numeros y caracteres especiales (ALL_CHARACTERES: 0).
 *  \return Retorna 0 si obtuvo la cadena correctamente, -1 si hubo un error.
 *
 */
int utn_getString(char* pString, int len, int retry,
    char* message, char* error, int isOnlyLetters);

/** \brief
 *  Funcion que solicita el ingreso por teclado de un numero telefonico
 *      con codigo de area separado por un guion.
 *  \param pPhone char* Direccion de memoria a almacenar
 *      el numero de telefono.
 *  \param len int Cantidad maxima de numeros que debera tener
 *      el numero telefonico.
 *  \param retry int Cantidad de reintentos al usuario.
 *  \param message char* Mensaje personalizado que solicita el dato al usuario.
 *  \param error char* Mensaje personalizado en caso de error.
 *  \return Retorna 0 si obtuvo un telefono correcto,
 *      -1 si no es un valor valido.
 *
 */
int utn_getPhone(char* pPhone, int len, int retry,
    char* message, char* error);

/** \brief
 *  Funcion que solicita y valida el ingreso de DNI Argentino formateado,
 *      por ejemplo "99.999.999".
 *  \param pDNI char* Direccion de memoria a almacenar
 *      el DNI ingresado formateado.
 *  \param len int Cantidad maxima de numeros que debera
 *      tener el numero telefonico.
 *  \param retry int Cantidad de reintentos al usuario.
 *  \param message char* Mensaje personalizado que solicita el dato al usuario.
 *  \param error char* Mensaje personalizado en caso de error.
 *  \return Retorna 0 si obtuvo un DNI dentro del rango,
 *      -1 si no es un valor valido.
 *
 */
int utn_getDNI(char* pDNI, int len, int retry,
    char* message, char* error);

/** \brief
 *  Funcion que solicita y valida el ingreso de CUIT Argentino formateado,
 *      ejemplo "99/99.999.999-9".
 *  \param pCuit char* Direccion de memoria al almacenar el CUIT validado.
 *  \param len int Cantidad maxima de numeros que debera tener el numero telefonico.
 *  \param message char* Mensaje personalizado que solicita el dato al usuario.
 *  \param error char* Mensaje personalizado en caso de error.
 *  \return Retorna 0 si obtuvo un CUIT valido, -1 si hubo un error.
 *
 */
int utn_getCUIT(char* pCUIT, int len, int retry,
    char* message, char* error);

/** \brief
 *  Funcion que solicita el ingreso por teclado de una direccion email y la valida.
 *  \param pEmail char* Direccion de memoria a almacenar el email validado.
 *  \param len int Longitud del array de caracteres a ingresar por teclado.
 *  \param retry int Cantidad de reintentos al usuario.
 *  \param message char* Mensaje personalizado que solicita el dato al usuario.
 *  \param error char* Mensaje personalizado en caso de error.
 *  \return Retorna 0 si obtuvo el email correctamente, -1 si hubo un error.
 *
 */
int utn_getEmail(char* pEmail, int len, int retry,
    char* message, char* error);

#endif //UTN_H_INCLUDED

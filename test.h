#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include "sale.h"
#define WITH_HARDCODE 1 /**< Carga HardCode de Clientes, 1 (SI) 0 (NO). */
#define ERROR_HARDCODE "Error en HardCode.\n" /**< Mensaje de falla de alta HardCode. */

/** \brief
 *  Funcion que realiza carga de Clientes de ejemplo.
 *  \param list Client* Direccion de memoria del array de Clientes.
 *  \param len int Longitud del array de Clientes.
 *  \return 0 si la carga de ejemplo fue exitosa, -1 si hubo un error.
 */
int test_clientHardCode(Client* list, int len);

#endif //TEST_H_INCLUDED

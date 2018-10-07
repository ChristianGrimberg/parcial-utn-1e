#ifndef INFORM_H_INCLUDED
#define INFORM_H_INCLUDED

#include "sale.h"

/** \brief
 *  Imprime la lista ingresada de Clientes en una tabla.
 *  \param list Employee* Direccion de memoria del array de Clientes.
 *  \param len int Longitud del array de Clientes.
 *  \return La funcion no retorna valores.
 *
 */
void inform_printClientList(Client* list, int len);

#endif //INFORM_H_INCLUDED
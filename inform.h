#ifndef INFORM_H_INCLUDED
#define INFORM_H_INCLUDED

#include "sale.h"

/** \brief
 *  Imprime la lista ingresada de Clientes en una tabla.
 *  \param list Client* Direccion de memoria del array de Clientes.
 *  \param len int Longitud del array de Clientes.
 *  \return La funcion no retorna valores.
 *
 */
void inform_printClientList(Client* list, int len);

/** \brief
 *  Imprime la lista ingresada de Afiches en una tabla.
 *  \param list Poster* Direccion de memoria del array de Afiches.
 *  \param len int Longitud del array de Afiches.
 *  \return La funcion no retorna valores.
 *
 */
void inform_printPosterList(Poster* list, int len);

void inform_printSaleList(Sale* saleList, int saleLen, Client* clientList,
    int clientLen, Poster* posterList, int posterLen);

#endif //INFORM_H_INCLUDED
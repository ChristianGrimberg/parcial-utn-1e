#ifndef SALE_H_INCLUDED
#define SALE_H_INCLUDED

#include "client.h"
#include "poster.h"
#define SALE_MAX 1000
#define ZONA_MAX 16
#define CABA 1
#define ZONA_SUR 2
#define ZONA_OESTE 3
#define SALE_INIT 1
#define A_COBRAR 1
#define COBRADA 2
#define FIELD_CLIENT_ID 1
#define FIELD_AFICHES 2
#define FIELD_ARCHIVO 3
#define FIELD_ZONA 4

typedef struct
{
    int saleId;
    int clientId;
    int posterId;
    int posterQty;
    int zone;
    int state;
    int isEmpty;
}Sale;

/** \brief
 *  Funcion que inicializa un array de Ventas con estado vacio FALSE.
 *  \param list Venta* Direccion de memoria del array de Ventas.
 *  \param len int Longitud del array de Ventas.
 *  \return 0 si se inicializo correctamente, -1 si hubo un error.
 *
 */
int sale_init(Sale*, int len);

/** \brief
 *  Funcion que busca la primer Venta libre a cargar en el array.
 *  \param list Venta* Direccion de memoria del array de Ventas.
 *  \param len int Longitud del array de Ventas.
 *  \return El indice del elemento libre, -1 si no encontro elemento libre.
 *
 */
int sale_getFirstEmpty(Sale* list, int len);

int sale_selectionZone(int* zone);

int sale_findId(Sale*, int len, int id);

/** \brief
 *  La funcion agrega una nueva Venta de acuerdo a los parametros ingresados
 *      en un array existente.
 *  \param list Venta* Direccion de memoria del array de Ventas.
 *  \param len int Longitud del array de Ventas.
 *  \param clientId int Id de Cliente.
 *  \param posterId int
 *  \param posterQty int
 *  \param zona int
 *  \return 0 si se pudo agregar la Venta, -1 si hubo un error.
 *
 */
int sale_add(Sale* list, int len, int clientId, int posterId,
    int posterQty, int zone);

int sale_edit(Sale* saleList, int lenVenta,
    Client* clientList, int lenClient, int index, int field);

void sale_printTableOptions(Sale* saleList, int saleLen, Client* clientList,
    int clientLen, Poster* posterList, int posterLen, int index, int table);

void sale_print(Sale* saleList, int saleLen, Client* clientList,
    int clientLen, Poster* posterList, int posterLen, int index);

#endif // SALE_H_INCLUDED

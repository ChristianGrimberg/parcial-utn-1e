#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include "utn.h"
#define CLIENT_NAMES_MAX 32
#define CUIT_MAX 32
#define CLIENT_INIT 1
#define CLIENT_MAX 100
#define FIELD_NAME 1 /**< Campo Nombre del Cliente. */
#define FIELD_LASTNAME 2 /**< Campo Apellido del Cliente. */
#define FIELD_CUIT 3 /**< Campo CUIT del Cliente. */
#define FORMAT_LEN_ID 5


/*! \struct Client
    \brief
    Tipo de dato de Cliente.
    Cliente que adquiere afiches.
*/
typedef struct
{
    int clientId;
    char name[CLIENT_NAMES_MAX];
    char lastName[CLIENT_NAMES_MAX];
    char cuit[CUIT_MAX];
    int isEmpty;
}Client;

/** \brief
 *  Funcion que inicializa un array de Clientes con estado vacio FALSE.
 *  \param list Client* Direccion de memoria del array de Clientes.
 *  \param len int Longitud del array de Clientes.
 *  \return 0 si se inicializo correctamente, -1 si hubo un error.
 *
 */
int client_init(Client* list, int len);

/** \brief
 *  Funcion que busca el primer Cliente libre a cargar en el array.
 *  \param list Client* Direccion de memoria del array de Clientes.
 *  \param len int Longitud del array de Clientes.
 *  \return El indice del elemento libre, -1 si no encontro elemento libre.
 *
 */
int client_getFirstEmpty(Client* list, int len);

/** \brief
 *  La funcion busca un Cliente en un array por el campo Id.
 *  \param list Client* Direccion de memoria del array de Clientes.
 *  \param len int Longitud del array de Clientes.
 *  \param id int Campo Id del Cliente.
 *  \return El indice del elemento en el array, de lo contrario devuelve -1.
 *
 */
int client_findId(Client* list, int len, int id);

/** \brief
 *  Funcion que busca el ID del Cliente con el mismo CUIT.
 *  \param list Client* Direccion de memoria del array de Clientes.
 *  \param len int Longitud del array de Clientes.
 *  \param cuit char* Campo CUIT del Cliente.
 *  \return El ID del Cliente buscado, -1 si no lo encontro.
 * 
 */
int client_findCUIT(Client* list, int len, char* cuit);

/** \brief
 *  La funcion agrega un nuevo Cliente de acuerdo a los parametros ingresados
 *      en un array existente.
 *  \param list Client* Direccion de memoria del array de Clientes.
 *  \param len int Longitud del array de Clientes.
 *  \param name char* Campo Nombre del Cliente.
 *  \param lastName char* Campo Apellido del Cliente.
 *  \param cuit char* Campo CUIT del Cliente.
 *  \return 0 si se pudo agregar el Cliente, -1 si hubo un error.
 *
 */
int client_add(Client* list, int len, char* name, char* lastName,
    char* cuit);

/** \brief
 *  La funcion obtiene la cantidad de Cliente Activos de la nomina.
 *  \param list Client* Direccion de memoria del array de Cliente.
 *  \param len int Longitud del array de Cliente.
 *  \return La cantidad de Cliente Activos, si no hay ninguno devuelve -1.
 *
 */
int client_getQuantity(Client* list, int len);

/** \brief
 *  La funcion edita un Cliente del array mediante el ingreso del indice del Array.
 *  \param list Client* Direccion de memoria del array de Clientes.
 *  \param len int Longitud del array de Clientes.
 *  \param index int Direccion de memoria del Indice del Array del Cliente.
 *  \param field int Campo del Cliente a modificar.
 *  \return 0 si la edicion fue correcta, -1 si hubo un error.
 *
 */
int client_editClientByIndex(Client* list, int len, int index, int field);

/** \brief
 *  La funcion da de baja un Cliente del array indicando si estado en FALSE
 *      como vacio.
 *  \param list Client* Direccion de memoria del array de Clientes.
 *  \param len int Longitud del array de Clientes.
 *  \param index int Indice del Array del Cliente.
 *  \return 0 si la baja fue correcta, -1 si hubo un error.
 *
 */
int client_removeClientByIndex(Client* list, int len, int index);

/** \brief
 *  Imprime un elemento de un array de Clientes.
 *  \param list Employee* Direccion de memoria del array de Clientes.
 *  \param index int Indice del array de Clientes.
 *  \param table int Indicador de seccion de impresion de lista en una tabla.
 *  \return No retorna valores.
 *
 */
void client_printFormatedClient(Client* list, int index, int table);

/** \brief
 *  Imprime un elemento de un array de Clientes.
 *  \param list Employee* Direccion de memoria del array de Clientes.
 *  \param index int Indice del Array del Cliente.
 *  \return La funcion no retorna valores.
 *
 */
void client_print(Client* list, int index);

#endif // CLIENT_H_INCLUDED

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "sale.h"
#include "inform.h"
#define PURGE_LEN 2 /**< Longitud del buffer de entrada para pausar la pantalla. */
#define MENU_PRINCIPAL_MIN 1 /**< Minima opcion del menu principal. */
#define MENU_PRINCIPAL_MAX 9 /**< Maxima opcion del menu principal. */
#define CLIENT_EDIT_MIN 1 /**< Minima opcion de edicion de Clientes. */
#define CLIENT_EDIT_MAX 4 /**< Maxima opcion de edicion de Clientes. */
#define SALE_EDIT_MIN 1
#define SALE_EDIT_MAX 4
#define INFORM_MENU_MIN 1
#define INFORM_MENU_MAX 11

/** \brief
 *  Funcion que pausa la ejecucion del programa hasta presionar Enter con un mensaje.
 *  \param message char* Mensaje a mostrar en pantalla.
 *  \return No retorna valores.
 *
 */
void menu_pauseScreen(char* message);

/** \brief
 *  Funcion que limpia la pantalla de la consola del programa.
 *  \return No retorna valores.
 *
 */
void menu_clearScreen(void);

/** \brief
 *  Funcion que imprime el menu principal en pantalla y consulta la opcion
 *      la elegir.
 *  \param selectionMenu int* Direccion de memoria donde se almacena la opcion
 *      de menu elegida por el usuario.
 *  \return Retorna la opcion elegida con un numero entero.
 *
 */
int menu_showPrincipalMenu(int* selectionMenu);

/** \brief
 *  Funcion que valida la carga de valores de los campos de un Cliente.
 *  \param client Client* Direccion de memoria donde se almacena el
 *      Cliente validado.
 *  \return 0 si los valores son correctos, -1 si hubo un error.
 *
 */
int menu_loadClientAux(Client* client);

/** \brief
 *  Funcion que brinda opciones para la modificacion de un Cliente.
 *  \param list Client* Direccion de memoria del array de Clientes.
 *  \param len int Longitud del array de Clientes.
 *  \param index int* Direccion de memoria del Indice del Array del Cliente.
 *  \param selectionMenu int* Direccion de memoria donde se almacena la
 *      opcion de menu elegida por el usuario.
 *  \return 0 si las opciones elegidas son validas, -1 si hubo un error.
 *
 */
int menu_editClientOptions(Client* list, int len, int* index, int* selectionMenu);

/** \brief
 *  Funcion asiste al usuario para borrar a un Cliente.
 *  \param list Client* Direccion de memoria del array de Clientes.
 *  \param len int Longitud del array de Clientes.
 *  \param index int Direccion de memoria del Indice del Array del Cliente.
 *  \return 1 si encontro y acepta borrar el usuario, 0 si cancela el borrado.
 *
 */
int menu_removeClientOptions(Client* list, int len, int* index);

int menu_loadSaleAux(Sale* sale, Client* clientList, int clientLen,
    Poster* posterList, int posterLen);

int menu_editSaleOptions(Sale* saleList, int saleLen, Client* clientList, int clientLen,
    Poster* posterList, int posterLen, int* index, int* selectionMenu);

int menu_editSaleState(Sale* saleList, int saleLen, Client* clientList, int clientLen,
    Poster* posterList, int posterLen, int* index);

int menu_showInformMenu(int* selectionMenu);

#endif //MENU_H_INCLUDED

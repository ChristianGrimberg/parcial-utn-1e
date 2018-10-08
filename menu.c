#include "menu.h"

void menu_pauseScreen(char* mensaje)
{
    char flush[PURGE_LEN] = " \n";
    printf("%s\n", mensaje);
    __fpurge(stdin);
    fgets(flush, PURGE_LEN, stdin);
}

void menu_clearScreen(void)
{
    #ifdef __unix__
        system("clear");
    #else
        system("cls");
    #endif //__unix__
}

int menu_showPrincipalMenu(int* selectionMenu)
{
    int returnValue = -1;
    int optionAux;

    printf("===========VENTA DE AFICHES===========\n");
    printf("1. Alta de Cliente.\n");
    printf("2. Modificar Cliente por ID.\n");
    printf("3. Baja de Cliente del Sistema.\n");
    printf("4. Vender Afiches.\n");
    printf("5. Editar Venta.\n");
    printf("6. Cobrar Venta.\n");
    printf("7. Imprimir Clientes.\n");
    printf("8. Salir del programa.\n");
    printf("=======================================\n");
    if(utn_getInt(&optionAux, RETRY, MENU_PRINCIPAL_MIN, MENU_PRINCIPAL_MAX,
        "Indique la opcion deseada: ", "Seleccion no valida. ") == 0)
    {
        *selectionMenu = optionAux;
        returnValue = 0;
    }

    return returnValue;
}

int menu_loadClientAux(Client* client)
{
    int returnValue = -1;
    Client clientAux;

    if(!utn_getString(clientAux.name, CLIENT_NAMES_MAX, RETRY,
        "Ingrese el Nombre: ", ERROR_MESSAGE, ONLY_LETTERS)
    && !utn_getString(clientAux.lastName, CLIENT_NAMES_MAX, RETRY,
        "Ingrese el Apellido: ", ERROR_MESSAGE, ONLY_LETTERS)
    && !utn_getCUIT(clientAux.cuit, CUIT_MAX, RETRY,
        "Ingrese el CUIT: ", ERROR_MESSAGE))
    {
        *client = clientAux;
        returnValue = 0;
    }

    return returnValue;
}

int menu_editClientOptions(Client* list, int len, int* index, int* selectionMenu)
{
    int returnValue = -1;
    int optionAux;
    int idAux;
    int indexAux;
    int clientQty;

    clientQty = client_getQuantity(list, len);
    if(clientQty != -1)
    {
        if(utn_getInt(&idAux, RETRY, CLIENT_INIT, CLIENT_MAX,
            "Ingrese el numero ID a modificar: ", ERROR_MESSAGE) == 0)
        {
            indexAux = client_findId(list, len, idAux);
            if(indexAux != -1)
            {
                menu_clearScreen();
                client_print(list, indexAux);
                printf("=========MODIFICAR EMPLEADO/A==========\n");
                printf("1. Modificar el Nombre.\n");
                printf("2. Modificar el Apellido.\n");
                printf("3. Modificar el CUIT.\n");
                printf("4. Salir de la edicion.\n");
                printf("=======================================\n");
                if(utn_getInt(&optionAux, RETRY, CLIENT_EDIT_MIN, CLIENT_EDIT_MAX,
                    "Indique la opcion deseada: ", "Seleccion no valida. ") == 0)
                {
                    *selectionMenu = optionAux;
                    *index = indexAux;
                    returnValue = 0;
                }
            }
        }
        else
        {
            printf("Edicion cancelada por error de valores ingresados.\n");
        }
    }
    else
    {
        printf(ERROR_EMPTY_LIST);
    }

    return returnValue;
}

int menu_removeClientOptions(Client* list, int len, int* index)
{
    int returnValue = 0;
    int idAux;
    int indexAux;
    char deleteClient;
    int clientQty;

    clientQty = client_getQuantity(list, len);
    if(clientQty != -1)
    {
        if(utn_getInt(&idAux, RETRY, CLIENT_INIT, CLIENT_MAX,
            "Ingrese el ID del/la Cliente/a a eliminar: ", ERROR_MESSAGE) == 0)
        {
            indexAux = client_findId(list, len, idAux);
            if(indexAux != -1)
            {
                menu_clearScreen();
                client_print(list, indexAux);
                do
                {
                    if(utn_getChar(&deleteClient, RETRY,
                        "Desea eliminar el Cliente/a? (S/N): ", ERROR_MESSAGE) == 0
                    && (char)(toupper(deleteClient)) == 'S')
                    {
                        *index = indexAux;
                        returnValue = 1;
                        break;
                    }
                    if((char)(toupper(deleteClient)) == 'N')
                    {
                        break;
                    }
                }while(TRUE);
            }
        }
        else
        {
            printf("Baja cancelada por error de valores ingresados.\n");
        }
    }
    else
    {
        printf(ERROR_EMPTY_LIST);
    }

    return returnValue;
}

int menu_loadSaleAux(Sale* sale, Client* clientList, int clientLen,
    Poster* posterList, int posterLen)
{
    int returnValue = -1;
    Sale saleAux;
    Poster posterAux;
    int clientId;
    int posterId;
    int clientIndex;
    int posterIndex;
    char accept;
    
    inform_printClientList(clientList, clientLen);
    if(!utn_getInt(&clientId, RETRY, CLIENT_INIT, CLIENT_MAX,
        "Ingrese el ID del Cliente: ", ERROR_MESSAGE))
    {
        clientIndex = client_findId(clientList, clientLen, clientId);
        if(clientIndex != -1)
        {
            client_print(clientList, clientIndex);
            if(!utn_getChar(&accept, 0,
                "Esta de acuerdo con el Cliente? (S/N): ", ERROR_MESSAGE)
            && (char)(toupper(accept)) == 'S')
            {
                saleAux.clientId = clientId;
                posterIndex = poster_getFirstEmpty(posterList, posterLen);
                if(posterIndex != -1
                && !utn_getString(posterAux.imageName, POSTER_NAME_MAX, RETRY,
                    "Ingrese la imagen del Afiche: ", ERROR_MESSAGE, ALL_CHARACTERES)
                && !utn_getInt(&saleAux.posterQty, RETRY, 0, INT_MAX,
                    "Ingrese la cantidad de Afiches: ", ERROR_MESSAGE))
                {
                    printf("Elija la zona:\n");
                    if(!sale_selectionZone(&saleAux.zone)
                    && !poster_add(posterList, posterLen, posterAux.imageName))
                    {                        
                        posterId = poster_findImage(posterList, posterLen,
                            posterAux.imageName);
                        if(posterId != -1)
                        {
                            saleAux.posterId = posterId;
                            *sale = saleAux;
                            returnValue = 0;
                        }
                    }
                }
            }
        }
    }

    return returnValue;
}

int menu_editSaleOptions(Sale* list, int len, int* index, int* selectionMenu)
{
    int returnValue = -1;
    int optionAux;
    int idAux;
    int indexAux;

    if(utn_getInt(&idAux, RETRY, CLIENT_INIT, CLIENT_MAX,
        "Ingrese el ID de venta a modificar: ", ERROR_MESSAGE) == 0)
    {
        indexAux = sale_findId(list, len, idAux);
        if(indexAux != -1)
        {
            menu_clearScreen();
            printf("===========MODIFICAR VENTA=============\n");
            printf("1. Modificar el Cliente.\n");
            printf("2. Modificar la cantidad de Afiches.\n");
            printf("3. Modificar la Zona.\n");
            printf("4. Salir de la edicion.\n");
            printf("=======================================\n");
            if(utn_getInt(&optionAux, RETRY, SALE_EDIT_MIN, SALE_EDIT_MAX,
                "Indique la opcion deseada: ", "Seleccion no valida. ") == 0)
            {
                *selectionMenu = optionAux;
                *index = indexAux;
                returnValue = 0;
            }
        }
    }
    else
    {
        printf("Edicion cancelada por error de valores ingresados.\n");
    }

    return returnValue;
}

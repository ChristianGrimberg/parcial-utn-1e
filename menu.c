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

int menu_loadNewClientByUser(Client* client)
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

int menu_editClientByUser(Client* list, int len, int* index, int* selectionMenu)
{
    int returnValue = -1;
    int optionAux;
    int idAux;
    int indexAux;
    int clientQty;

    clientQty = cliente_getNumberOfClients(list, len);
    if(clientQty != -1)
    {
        if(utn_getInt(&idAux, RETRY, CLIENT_INIT, CLIENT_MAX,
            "Ingrese el numero ID a modificar: ", ERROR_MESSAGE) == 0)
        {
            indexAux = cliente_findClientById(list, len, idAux);
            if(indexAux != -1)
            {
                menu_clearScreen();
                cliente_printClientByIndex(list, len, indexAux);
                printf("=========MODIFICAR EMPLEADO/A==========\n");
                printf("1. Modificar el Nombre.\n");
                printf("2. Modificar el Apellido.\n");
                printf("3. Modificar el CUIT.\n");
                printf("4. Salir de la edicion.\n");
                printf("=======================================\n");
                if(utn_getInt(&optionAux, RETRY, MENU_EDIT_MIN, MENU_EDIT_MAX,
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

int menu_removeClientByUser(Client* list, int len, int* index)
{
    int returnValue = 0;
    int idAux;
    int indexAux;
    char deleteClient;
    int clientQty;

    clientQty = cliente_getNumberOfClients(list, len);
    if(clientQty != -1)
    {
        if(utn_getInt(&idAux, RETRY, CLIENT_INIT, CLIENT_MAX,
            "Ingrese el ID del/la Cliente/a a eliminar: ", ERROR_MESSAGE) == 0)
        {
            indexAux = cliente_findClientById(list, len, idAux);
            if(indexAux != -1)
            {
                menu_clearScreen();
                cliente_printClientByIndex(list, len, indexAux);
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

int menu_loadNewVentaByUser(Sale* sale, Client* list, int len)
{
    int returnValue = -1;
    Sale saleAux;
    int clientId;
    int clientIndex;
    char acceptClient;

    if(utn_getInt(&clientId, RETRY, CLIENT_INIT, CLIENT_MAX,
        "Ingrese el ID del/la Cliente/a a vender: ", ERROR_MESSAGE) == 0)
    {
        clientIndex = cliente_findClientById(list, len, clientId);
        if(clientIndex != -1)
        {
            menu_clearScreen();
            cliente_printClientByIndex(list, len, clientIndex);
            if(utn_getChar(&acceptClient, 0,
                "Esta de acuerdo con el/la Cliente/a? (S/N): ", ERROR_MESSAGE) == 0
            && (char)(toupper(acceptClient)) == 'S')
            {
                saleAux.clientId = clientId;
                if(utn_getInt(&saleAux.cantidadAfiches, RETRY, 0, INT_MAX,
                    "Ingrese la cantidad de afiches: ", ERROR_MESSAGE) == 0
                && utn_getString(saleAux.nombreAfiche, POSTER_NAME_MAX, RETRY,
                    "Ingrese el archivo del afiche: ", ERROR_MESSAGE, ALL_CHARACTERES) == 0)
                {
                    menu_clearScreen();
                    printf("Elija la zona:\n");
                    if(sale_selectionZone(&saleAux.zona) == 0)
                    {
                        *sale = saleAux;
                        returnValue = 0;
                    }
                }
            }
        }
    }

    return returnValue;
}

int menu_editVentaByUser(Sale* list, int len, int* index, int* selectionMenu)
{
    int returnValue = -1;
    int optionAux;
    int idAux;
    int indexAux;

    if(utn_getInt(&idAux, RETRY, CLIENT_INIT, CLIENT_MAX,
        "Ingrese el ID de venta a modificar: ", ERROR_MESSAGE) == 0)
    {
        indexAux = venta_findVentaById(list, len, idAux);
        if(indexAux != -1)
        {
            menu_clearScreen();
            printf("===========MODIFICAR VENTA=============\n");
            printf("1. Modificar el Cliente.\n");
            printf("2. Modificar la cantidad de Afiches.\n");
            printf("3. Modificar el Archivo.\n");
            printf("4. Modificar la Zona.\n");
            printf("5. Salir de la edicion.\n");
            printf("=======================================\n");
            if(utn_getInt(&optionAux, RETRY, VENTA_EDIT_MIN, VENTA_EDIT_MAX,
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

int venta_editVentaByIndex(Sale* saleList, int lenVenta, Client* clientList, int lenClient, int index, int field)
{
    int returnValue = -1;
    Sale saleAux;
    int clientId;
    int clientIndex;
    char acceptClient;

    if(index >= 0 && index < SALES_MAX
    && field >= FIELD_CLIENT_ID && field <= FIELD_ZONA)
    {
        saleAux = saleList[index];
        switch(field)
        {
            case 1:
                if(utn_getInt(&clientId, RETRY, CLIENT_INIT, CLIENT_MAX,
                    "Ingrese el ID del/la Cliente/a: ", ERROR_MESSAGE) == 0)
                {
                    clientIndex = cliente_findClientById(clientList, lenClient, clientId);
                    if(clientIndex != -1)
                    {
                        cliente_printClientByIndex(clientList, lenClient, clientIndex);
                        if(utn_getChar(&acceptClient, 0,
                            "Esta de acuerdo con el/la Cliente/a? (S/N): ", ERROR_MESSAGE) == 0
                        && (char)(toupper(acceptClient)) == 'S')
                        {
                            saleAux.clientId = clientId;
                        }
                        else
                        {
                            printf("Error de edicion del Cliente.\n");
                        }
                    }
                }
                break;
            case 2:
                if(utn_getInt(&saleAux.cantidadAfiches, RETRY, 0, INT_MAX,
                    "Ingrese la nueva cantidad de Afiches: ", ERROR_MESSAGE) == -1)
                {
                    printf("Error de edicion de cantidad de Afiches.\n");
                }
                break;
            case 3:
                if(utn_getString(saleAux.nombreAfiche, POSTER_NAME_MAX, RETRY,
                    "Ingrese el nuevo Archivo: ", ERROR_MESSAGE, ONLY_LETTERS) == -1)
                {
                    printf("Error de edicion del Archivo.\n");
                }
                break;
            case 4:
                printf("Elija la zona:\n");
                if(sale_selectionZone(&saleAux.zona) == -1)
                {
                    printf("Error de edicion de la zona.\n");
                }
                break;
        }
        saleList[index] = saleAux;
        returnValue = 0;
    }

    return returnValue;
}

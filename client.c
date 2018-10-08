#include "client.h"

/** \brief
 *  Funcion que obtiene un Id de Cliente autonumerico incremental en 1.
 *  \return Numero entero incremental en 1 irrepetible.
 *
 */
static int getNewClientId(void);

int client_init(Client* list, int len)
{
    int returnValue = -1;
    int i;

    if(list != NULL && len > 0 && len <= CLIENT_MAX)
    {
        for(i = 0; i < len; i++)
        {
            (list+i)->isEmpty = TRUE;
        }
        if(i == len)
        {
            returnValue = 0;
        }
    }

    return returnValue;
}

int client_getFirstEmpty(Client* list, int len)
{
    int returnValue = -1;
    int i;

    if(list != NULL && len > 0 && len <= CLIENT_MAX)
    {
        for(i = 0; i < len; i++)
        {
            if((list+i)->isEmpty)
            {
                returnValue = i;
                break;
            }
        }
    }

    return returnValue;
}

int client_findId(Client* list, int len, int id)
{
    int returnValue = -1;
    int i;

    if(list != NULL && len > 0 && len <= CLIENT_MAX
        && id >= CLIENT_INIT && id <= CLIENT_MAX)
    {
        for(i = 0; i < len; i++)
        {
            if(!(list+i)->isEmpty && (list+i)->clientId == id)
            {
                returnValue = i;
                break;
            }
        }
    }

    return returnValue;
}

int client_findCUIT(Client* list, int len, char* cuit)
{
    int returnValue = -1;
    int i;

    if(list != NULL && len >= CLIENT_INIT && len <= CLIENT_MAX
        && cuit != NULL)
    {
        for(i = 0; i < len; i++)
        {
            if(strncmp((list+i)->cuit, cuit, CUIT_MAX) == 0
                && !(list+i)->isEmpty)
            {
                returnValue = (list+i)->clientId;
                break;
            }
        }
    }

    return returnValue;
}

int client_add(Client* list, int len, char* name, char* lastName,
    char* cuit)
{
    int returnValue = -1;
    int idAux;
    int indexAux;

    if(list != NULL && len > 0 && len <= CLIENT_MAX
        && name != NULL && lastName != NULL && cuit != NULL)
    {
        idAux = getNewClientId();
        if(idAux >= CLIENT_INIT && idAux <= CLIENT_MAX)
        {
            indexAux = client_getFirstEmpty(list, len);
            if(indexAux != -1 && client_findCUIT(list, len, cuit) == -1)
            {
                (list+indexAux)->clientId = idAux;
                strncpy((list+indexAux)->name, name, CLIENT_NAMES_MAX);
                strncpy((list+indexAux)->lastName, lastName, CLIENT_NAMES_MAX);
                strncpy((list+indexAux)->cuit, cuit, CUIT_MAX);
                (list+indexAux)->isEmpty = FALSE;
                returnValue = 0;
            }
            else
            {
                printf(ERROR_EXIST_FULL);
            }
        }
        else
        {
            printf("El sistema no soporta la carga del id: %d,\n", idAux);
        }
    }

    return returnValue;
}

int client_getQuantity(Client* list, int len)
{
    int returnValue = -1;
    int clientCounter = 0;
    int i;

    if(list != NULL && len > 0 && len <= CLIENT_MAX)
    {
        for(i = 0; i < len; i++)
        {
            if(!(list+i)->isEmpty)
            {
                clientCounter++;
            }
        }
        if(clientCounter > 0)
        {
            returnValue = clientCounter;
        }
    }

    return returnValue;
}

int client_edit(Client* list, int len, int index, int field)
{
    int returnValue = -1;
    Client clientAux;

    if(index >= 0 && index < CLIENT_MAX
    && field >= FIELD_NAME && field <= FIELD_CUIT)
    {
        clientAux = list[index];
        switch(field)
        {
            case 1:
                if(utn_getString(clientAux.name, CLIENT_NAMES_MAX, RETRY,
                    "Ingrese el nuevo Nombre: ", ERROR_MESSAGE, ONLY_LETTERS) == -1)
                {
                    printf(ERROR_EDITION);
                }
                break;
            case 2:
                if(utn_getString(clientAux.lastName, CLIENT_NAMES_MAX, RETRY,
                    "Ingrese el nuevo Apellido: ", ERROR_MESSAGE, ONLY_LETTERS) == -1)
                {
                    printf(ERROR_EDITION);
                }
                break;
            case 3:
                if(utn_getCUIT(clientAux.cuit, CUIT_MAX, RETRY,
                    "Ingrese el nuevo CUIT: ", ERROR_MESSAGE) == -1)
                {
                    printf(ERROR_EDITION);
                }
                break;
        }
        list[index] = clientAux;
        returnValue = 0;
    }

    return returnValue;
}

int client_remove(Client* list, int len, int index)
{
    int returnValue = -1;

    if(list != NULL && index >= 0 && index < len
    && len >= CLIENT_INIT && len <= CLIENT_MAX)
    {
        if(!(list+index)->isEmpty)
        {
            (list+index)->isEmpty = TRUE;
            returnValue = 0;
        }
        else
        {
            printf(ERROR_EXIST_EMPTY);
        }
    }

    return returnValue;
}

void client_printTableOptions(Client* list, int index, int table)
{
    char idAux[FORMAT_LEN_ID];

    if(list != NULL && index >= 0 && index < CLIENT_MAX)
    {
        sprintf(idAux, "%d", list[index].clientId);
        if(table == HEADER)
        {
            printf("+=====+====================+===================="
                "+====================+\n");
            printf("|%4s%1s|%10s%10s|%10s%10s|%10s%10s|\n",
                "ID", "", "Nombre", "", "Apellido", "", "CUIT", "");
            printf("+=====+====================+===================="
                "+====================+\n");
        }
        else if(table == BODY)
            printf("|%4s |%19s |%19s |%19s |\n",
                idAux, list[index].name, list[index].lastName, list[index].cuit);
        else if(table == FOOTER)
            printf("+-----+--------------------+--------------------"
                "+--------------------+\n");
    }
    else
        printf("El Cliente/a no existe.\n");
}

void client_print(Client* list, int index)
{
    if(list != NULL && !(list+index)->isEmpty)
    {
        client_printTableOptions(list, 0, HEADER);
        client_printTableOptions(list, index, BODY);
        client_printTableOptions(list, 0, FOOTER);
    }
}

static int getNewClientId(void)
{
    static int clientIdCounter = CLIENT_INIT - 1;
    clientIdCounter++;
    return clientIdCounter;
}

#include "sale.h"

/** \brief
 *  Funcion que obtiene un Id de Venta autonumerico incremental en 1.
 *  \return Numero entero incremental en 1 irrepetible.
 *
 */
static int getNewSaleId(void);

int sale_init(Sale* list, int len)
{
    int returnValue = -1;
    int i;

    if(list != NULL && len > 0 && len <= SALE_MAX)
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

int sale_getFirstEmpty(Sale* list, int len)
{
    int returnValue = -1;
    int i;

    if(list != NULL && len > 0 && len <= SALE_MAX)
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

int sale_selectionZone(int* zone)
{
    int returnValue = -1;
    int optionAux;

    if(zone != NULL)
    {
        printf("+======================+\n");
        printf("|   Zonas de Afiches   |\n");
        printf("+======================+\n");
        printf("|%d. CABA.              |\n", CABA);
        printf("|%d. Zona Sur.          |\n", ZONA_SUR);
        printf("|%d. Zona Oeste.        |\n", ZONA_OESTE);
        printf("+----------------------+\n");
        if(!utn_getInt(&optionAux, RETRY, CABA, ZONA_OESTE,
            "Indique la opcion deseada: ", "Seleccion no valida. "))
        {
            *zone = optionAux;
            returnValue = 0;
        }
    }

    return returnValue;
}

int sale_findId(Sale* list, int len, int id)
{
    int returnValue = -1;
    int i;

    if(list != NULL && len > 0
    && len <= SALE_MAX && id >= SALE_INIT && id < SALE_MAX)
    {
        for(i = 0; i < len; i++)
        {
            if(!(list+i)->isEmpty && (list+i)->saleId == id)
            {
                returnValue = i;
                break;
            }
        }
    }

    return returnValue;
}

int sale_add(Sale* list, int len, int clientId, int posterId,
    int posterQty, int zone)
{
    int returnValue = -1;
    int idAux;
    int indexAux;

    if(list != NULL && len > 0 && len <= SALE_MAX
        && clientId >= CLIENT_INIT && clientId <= CLIENT_MAX
        && posterId >= POSTER_INIT && posterId <= POSTER_MAX
        && posterQty >= 0)
    {
        idAux = getNewSaleId();
        if(idAux >= SALE_INIT && idAux <= SALE_MAX)
        {
            indexAux = sale_getFirstEmpty(list, len);
            if(indexAux != -1)
            {
                (list+indexAux)->saleId = idAux;
                (list+indexAux)->clientId = clientId;
                (list+indexAux)->posterId = posterId;
                (list+indexAux)->posterQty = posterQty;
                (list+indexAux)->zone = zone;
                (list+indexAux)->state = A_COBRAR;
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

int sale_getQuantity(Sale* list, int len)
{
    int returnValue = -1;
    int saleCounter = 0;
    int i;

    if(list != NULL && len > 0 && len <= SALE_MAX)
    {
        for(i = 0; i < len; i++)
        {
            if(!(list+i)->isEmpty)
            {
                saleCounter++;
            }
        }
        if(saleCounter > 0)
        {
            returnValue = saleCounter;
        }
    }

    return returnValue;
}

int sale_edit(Sale* saleList, int saleLen, Client* clientList, int clientLen,
    int index, int field)
{
    int returnValue = -1;
    Sale saleAux;
    int clientId;
    int clientIndex;
    char accept;

    if(index >= 0 && index < SALE_MAX
    && field >= FIELD_CLIENT_ID && field <= FIELD_ZONE)
    {
        saleAux = saleList[index];
        switch(field)
        {
            case 1:
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
                        }
                        else
                        {
                            printf("Error de edicion del Cliente.\n");
                        }
                    }
                }
                break;
            case 2:
                if(utn_getInt(&saleAux.posterQty, RETRY, 0, INT_MAX,
                    "Ingrese la nueva cantidad de Afiches: ", ERROR_MESSAGE) == -1)
                {
                    printf("Error de edicion de cantidad de Afiches.\n");
                }
                break;
            case 3:
                printf("Elija la zona:\n");
                if(sale_selectionZone(&saleAux.zone) == -1)
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

int sale_removeByClient(Sale* saleList, int saleLen, Client* clientList,
    int clientLen, int clientId)
{
    int returnValue = -1;
    int i;

    if(saleList != NULL && saleLen > 0 && saleLen <= SALE_MAX
        && clientList != NULL && clientLen > 0 && clientLen <= CLIENT_MAX)
    {
        returnValue = 0;
        if(client_findId(clientList, clientLen, clientId) != -1)
        {
            for(i = 0; i < saleLen; i++)
            {
                if((saleList+i)->clientId == clientId)
                {
                    (saleList+i)->isEmpty = TRUE;                    
                }
            }
        }
    }

    return returnValue;
}

void sale_printTableOptions(Sale* saleList, int saleLen, Client* clientList,
    int clientLen, Poster* posterList, int posterLen, int index, int table)
{
    char saleIdAux[FORMAT_LEN_ID];
    char clientIdAux[FORMAT_LEN_ID];
    char posterQtyAux[FORMAT_LEN_ID];
    char zoneAux[ZONE_MAX];
    char statusAux[STATUS_MAX];
    int clientIndex;
    int posterIndex;

    if(saleList != NULL && saleLen >= SALE_INIT && saleLen <= SALE_MAX
        && clientList != NULL && clientLen >= CLIENT_INIT && clientLen <= CLIENT_MAX
        && posterList != NULL && posterLen >= POSTER_INIT && posterLen <= POSTER_MAX
        && index >= 0 && index < SALE_MAX)
    {
        clientIndex = client_findId(clientList, clientLen, saleList[index].clientId);
        posterIndex = poster_findId(posterList, posterLen, saleList[index].posterId);
        if(clientIndex != -1)
        {
            sprintf(saleIdAux, "%d", saleList[index].saleId);
            sprintf(clientIdAux, "%d", saleList[index].clientId);
            sprintf(posterQtyAux, "%d", saleList[index].posterQty);
            switch(saleList[index].zone)
            {
                case CABA:
                    strncpy(zoneAux, "CABA", ZONE_MAX);
                    break;
                case ZONA_SUR:
                    strncpy(zoneAux, "Zona Sur", ZONE_MAX);
                    break;
                case ZONA_OESTE:
                    strncpy(zoneAux, "Zona Oeste", ZONE_MAX);
                    break;
            }
            switch((saleList+index)->state)
            {
                case A_COBRAR:
                    strncpy(statusAux, "A cobrar", STATUS_MAX);
                    break;
                case COBRADA:
                    strncpy(statusAux, "Cobrada", STATUS_MAX);
                    break;
            }
        }
        if(table == HEADER)
        {
            printf("+============+============+==============================+"
                "====================+============+================+==========+\n");
            printf("|%10s%2s|%11s%1s|%15s%15s|%10s%10s|%10s%2s|%8s%8s|%8s%2s|\n",
                "ID Venta", "", "ID Cliente", "", "Cliente", "", 
                "Imagen", "", "Cant.", "", "Zona", "", "Estado", "");
            printf("+============+============+==============================+"
                "====================+============+================+==========+\n");
        }
        else if(table == BODY)
        {
            printf("|%11s |%11s |%14s %14s |%19s |%11s |%15s |%9s |\n", saleIdAux,
                clientIdAux, clientList[clientIndex].name, clientList[clientIndex].lastName,
                posterList[posterIndex].imageName, posterQtyAux, zoneAux, statusAux);
        }
        else if(table == FOOTER)
        {
            printf("+------------+------------+------------------------------+"
                "--------------------+------------+----------------+----------+\n");
        }
    }
    else
    {
        printf(ERROR_NOT_EXIST);
    }
}

void sale_print(Sale* saleList, int saleLen, Client* clientList,
    int clientLen, Poster* posterList, int posterLen, int index)
{
    if(!(saleList+index)->isEmpty)
    {
        sale_printTableOptions(saleList, saleLen, clientList, clientLen,
            posterList, posterLen, 0, HEADER);
        sale_printTableOptions(saleList, saleLen, clientList, clientLen,
            posterList, posterLen, index, BODY);
        sale_printTableOptions(saleList, saleLen, clientList, clientLen,
            posterList, posterLen, 0, FOOTER);
    }
}

static int getNewSaleId(void)
{
    static int saleIdCounter = SALE_INIT - 1;
    saleIdCounter++;
    return saleIdCounter;
}

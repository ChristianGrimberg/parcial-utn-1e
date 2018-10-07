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

    if(list != NULL && len > 0 && len <= SALES_MAX)
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

int sale_getFirstEmptySale(Sale* list, int len)
{
    int returnValue = -1;
    int i;

    if(list != NULL && len > 0 && len <= SALES_MAX)
    {
        for(i = 0; i < len; i++)
        {
            if(list[i].isEmpty == TRUE)
            {
                returnValue = i;
                break;
            }
        }
    }

    return returnValue;
}

int sale_selectionZone(int* zona)
{
    int returnValue = -1;
    int optionAux;

    if(zona != NULL)
    {
        printf("+======================+\n");
        printf("|   Zonas de Afiches   |\n");
        printf("+======================+\n");
        printf("|%d. CABA.              |\n", CABA);
        printf("|%d. Zona Sur         . |\n", ZONA_SUR);
        printf("|%d. Zona Oeste.        |\n", ZONA_OESTE);
        printf("+----------------------+\n");
        if(utn_getInt(&optionAux, RETRY, CABA, ZONA_OESTE,
            "Indique la opcion deseada: ", "Seleccion no valida. ") == 0)
        {
            *zona = optionAux;
            returnValue = 0;
        }
    }

    return returnValue;
}

int sale_findVentaById(Sale* list, int len, int id)
{
    int returnValue = -1;
    int i;

    if(list != NULL && len > 0
    && len <= SALES_MAX && id >= SALE_INIT && id < SALES_MAX)
    {
        for(i = 0; i < len; i++)
        {
            if(list[i].isEmpty == FALSE && list[i].ventaId == id)
            {
                returnValue = i;
                break;
            }
        }
    }

    return returnValue;
}

int sale_addVenta(Sale* list, int len, int clientId,
    int cantidadAfiches, char* nombreAfiche, int zona)
{
    int returnValue = -1;
    int idAux;
    int indexAux;

    if(list != NULL && len > 0 && len <= SALES_MAX
        && clientId > 0 && cantidadAfiches >= 0 && nombreAfiche != NULL)
    {
        idAux = getNewSaleId();
        if(idAux >= SALE_INIT && idAux <= SALES_MAX)
        {
            indexAux = sale_getFirstEmptySale(list, len);
            if(indexAux != -1)
            {
                (list+indexAux)->ventaId = idAux;
                (list+indexAux)->clientId = clientId;
                (list+indexAux)->cantidadAfiches = cantidadAfiches;
                (list+indexAux)->zona = zona;
                strncpy((list+indexAux)->nombreAfiche, nombreAfiche, POSTER_NAME_MAX);
                (list+indexAux)->estado = A_COBRAR;
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

static int getNewSaleId(void)
{
    static int ventaIdCounter = SALE_INIT - 1;
    ventaIdCounter++;
    return ventaIdCounter;
}

static void printFormatVentaByIndex(Sale* list, int index, int table)
{
    char ventaIdAux[FORMAT_LEN_ID];
    char clienteIdAux[FORMAT_LEN_ID];
    char afichesAux[FORMAT_LEN_ID];
    char zonaAux[ZONA_MAX];

    if(list != NULL && index >= 0 && index < SALES_MAX)
    {
        sprintf(ventaIdAux, "%d", list[index].ventaId);
        sprintf(clienteIdAux, "%d", list[index].clientId);
        sprintf(afichesAux, "%d", list[index].cantidadAfiches);
        switch(list[index].zona)
        {
            case 1:
                strncpy(zonaAux, "CABA", ZONA_MAX);
                break;
            case 2:
                strncpy(zonaAux, "Zona Sur", ZONA_MAX);
                break;
            case 3:
                strncpy(zonaAux, "Zona Oeste", ZONA_MAX);
                break;
        }
        if(table == HEADER)
        {
            printf("+============+============+====================+"
                "====================+====================+\n");
            printf("|%5s%7s|%5s%7s|%10s%10s|%10s%10s|%10s%10s|\n",
                "ID Venta", "", "ID Cliente", "", "Afiches", "", "Archivo", "", "Zona", "");
            printf("+============+============+====================+"
                "====================+====================+\n");
        }
        else if(table == BODY)
            printf("|%11s |%11s |%19s |%19s |%19s |\n",
                ventaIdAux, clienteIdAux, afichesAux, list[index].nombreAfiche, zonaAux);
        else if(table == FOOTER)
            printf("+------------+------------+--------------------+"
                "--------------------+--------------------+\n");
    }
    else
        printf("El Cliente/a no existe.\n");
}

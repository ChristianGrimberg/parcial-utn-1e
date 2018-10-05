#include "venta.h"

/** \brief
 *  Funcion que obtiene un Id de Venta autonumerico incremental en 1.
 *  \return Numero entero incremental en 1 irrepetible.
 *
 */
static int getNewVentaId(void);

int venta_init(Venta* list, int len)
{
    int returnValue = -1;
    int i;

    if(list != NULL && len > 0 && len <= VENTAS_MAX)
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

int venta_getFirstEmptyVenta(Venta* list, int len)
{
    int returnValue = -1;
    int i;

    if(list != NULL && len > 0 && len <= VENTAS_MAX)
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

int venta_zonaSelection(int* zona)
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

int venta_findVentaById(Venta* list, int len, int id)
{
    int returnValue = -1;
    int i;

    if(list != NULL && len > 0
    && len <= VENTAS_MAX && id >= VENTA_INIT && id < VENTAS_MAX)
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

int venta_addVenta(Venta* list, int len, int clientId,
    int cantidadAfiches, char* nombreAfiche, int zona)
{
    int returnValue = -1;
    int idAux;
    int indexAux;

    if(list != NULL && len > 0 && len <= VENTAS_MAX
        && clientId > 0 && cantidadAfiches >= 0 && nombreAfiche != NULL)
    {
        idAux = getNewVentaId();
        if(idAux >= VENTA_INIT && idAux <= VENTAS_MAX)
        {
            indexAux = venta_getFirstEmptyVenta(list, len);
            if(indexAux != -1)
            {
                (list+indexAux)->ventaId = idAux;
                (list+indexAux)->clientId = clientId;
                (list+indexAux)->cantidadAfiches = cantidadAfiches;
                (list+indexAux)->zona = zona;
                strncpy((list+indexAux)->nombreAfiche, nombreAfiche, AFICHE_NOMBRE_MAX);
                (list+indexAux)->estado = A_COBRAR;
                (list+indexAux)->isEmpty = FALSE;
                returnValue = 0;
            }
            else
            {
                printf("No hay elementos libres a cargar.\n");
            }
        }
        else
        {
            printf("El sistema no soporta la carga del id: %d,\n", idAux);
        }
    }

    return returnValue;
}

static int getNewVentaId(void)
{
    static int ventaIdCounter = VENTA_INIT - 1;
    ventaIdCounter++;
    return ventaIdCounter;
}

static void printFormatVentaByIndex(Venta* list, int index, int table)
{
    char ventaIdAux[FORMAT_ID_LEN];
    char clienteIdAux[FORMAT_ID_LEN];
    char afichesAux[FORMAT_ID_LEN];
    char zonaAux[ZONA_MAX];

    if(list != NULL && index >= 0 && index < VENTAS_MAX)
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

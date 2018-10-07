#include "poster.h"

/** \brief
 *  Funcion que obtiene un Id de Afiche autonumerico incremental en 1.
 *  \return Numero entero incremental en 1 irrepetible.
 *
 */
static int getNewPosterId(void);

/** \brief
 *  Funcion que imprime el indice del Afiche.
 *  \param list Poster* Direccion de memoria del array de Afiches.
 *  \param len int Longitud del array de Afiches.
 *  \param index int Indice del array de Afiches.
 *  \return No retorna valores.
 */
static void printFormatedPoster(Poster* list, int index, int table);

int poster_init(Poster* list, int len)
{
    int returnValue = -1;
    int i;

    if(list != NULL && len > 0 && len <= POSTER_MAX)
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

int poster_getFirstEmpty(Poster* list, int len)
{
    int returnValue = -1;
    int i;

    if(list != NULL && len > 0 && len <= POSTER_MAX)
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

int poster_findId(Poster* list, int len, int id)
{
    int returnValue = -1;
    int i;

    if(list != NULL && len > 0 && len <= POSTER_MAX
        && id >= POSTER_INIT && id <= POSTER_MAX)
    {
        for(i = 0; i < len; i++)
        {
            if((list+i)->isEmpty && (list+i)->posterId == id)
            {
                returnValue = i;
                break;
            }
        }
    }

    return returnValue;
}

int poster_findImage(Poster* list, int len, char* imageName)
{
    int returnValue = -1;
    int i;
    int idAux;

    if(list != NULL && len >= POSTER_INIT && len < POSTER_MAX
        && imageName != NULL)
    {
        for(i = 0; i < len; i++)
        {
            if(strncmp((list+i)->imageName, imageName, POSTER_NAME_MAX) == 0
                && !(list+i)->isEmpty)
            {
                returnValue = (list+i)->posterId;
                break;
            }
        }
    }

    return returnValue;
}

int poster_add(Poster* list, int len, char* imageName)
{
    int returnValue = -1;
    int idAux;
    int indexAux;

    if(list != NULL && len > 0 && len <= POSTER_MAX && imageName != NULL)
    {
        idAux = getNewPosterId();
        if(idAux >= POSTER_INIT && idAux <= POSTER_MAX)
        {
            indexAux = poster_getFirstEmpty(list, len);
            if(indexAux != -1)
            {
                (list+indexAux)->posterId = idAux;
                strncpy((list+indexAux)->imageName, imageName, POSTER_NAME_MAX);
                (list+indexAux)->isEmpty = FALSE;
                returnValue = 0;
            }
            else
            {
                printf(ERROR_FULL_LIST);
            }
        }
        else
        {
            printf("El sistema no soporta la carga del id: %d,\n", idAux);
        }
    }

    return returnValue;
}

int poster_remove(Poster* list, int len, int index)
{
    int returnValue = -1;

    if(list != NULL && len >= POSTER_INIT && len <= POSTER_MAX
        && index >= 0 && index < len)
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

void poster_print(Poster* list, int index)
{
    if(list != NULL && !(list+index)->isEmpty)
    {
        printFormatedPoster(list, 0, HEADER);
        printFormatedPoster(list, index, BODY);
        printFormatedPoster(list, 0, FOOTER);
    }
}

static int getNewPosterId(void)
{
    static int posterIdCounter = POSTER_INIT - 1;
    posterIdCounter++;
    return posterIdCounter;
}

static void printFormatedPoster(Poster* list, int index, int table)
{
    char idAux[FORMAT_LEN_ID];

    if(list != NULL && index >= 0 && index < POSTER_MAX)
    {
        if(!(list+index)->isEmpty)
        {
            sprintf(idAux, "%d", (list+index)->posterId);
            if(table == HEADER)
            {
                printf("+=====+====================+\n");
                printf("|%4s%1s|%10s%10s|\n",
                    "ID", "", "Imagen", "");
                printf("+=====+====================+\n");
            }
            else if(table == BODY)
                printf("|%4s |%19s |\n", idAux, (list+index)->imageName);
            else if(table == FOOTER)
                printf("+-----+--------------------+\n");
        }
        else
        {
            printf(ERROR_EXIST_EMPTY);
        }
    }
}

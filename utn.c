#include "utn.h"

/** \brief
 *  Funcion que obtiene y valida un valor entero por ingreso de teclado.
 *  \param number int* Posicion de memoria a almacenar el entero validado.
 *  \return Retorna 0 si obtuvo un numero entero, -1 si no es un valor valido.
 *
 */
static int getInt(int* number);

/** \brief
 *  Funcion que obtiene y valida un valor flotante por ingreso de teclado.
 *  \param decimal float* Posicion de memoria a almacenar el decimal validado.
 *  \return Retorna 0 si obtuvo un numero flotante, -1 si no es un valor valido.
 *
 */
static int getFloat(float* decimal);

/** \brief
 *  Funcion que obtiene un puntero a un array de caracteres y valida
 *      su ingreso por teclado.
 *  \param pString char* Array de caracteres para almacenar el
 *      valor ingreso por teclado.
 *  \param len int Longitud del array de caracteres.
 *  \return 0 si pudo obtener el valor de manera correcta, -1 si hubo un error.
 *
 */
static int getString(char* pString, int len);

/** \brief
 *  Funcion que valida si la cadena ingresada es numerica entera o no.
 *  \param stringValue char* Cadena de caracteres a validar.
 *  \return 0 si es un entero, -1 si no lo es.
 *
 */
static int isNumber(char* stringValue);

/** \brief
 *  Funcion que valida si una cadena ingresada no es un numero.
 *  \param stringValue char* Cadena de caracteres a validar.
 *  \return 0 si no es numerico, -1 si lo es.
 *
 */
static int isNotNumber(char* stringValue);

/** \brief
 *  Funcion que valida si la cadena ingresada es numerica flotante o no.
 *  \param stringValue char* Cadena de caracteres a validar.
 *  \return 0 si es un flotante, -1 si no lo es.
 *
 */
static int isFloat(char* stringValue);

/**  \brief
 *  Funcion que valida si la cadena ingresa tiene el formato de DNI
 *      con separador de miles.
 *  \param stringValue char* Cadena de caracteres a validar.
 *  \return 0 si el formato DNI es correcto, -1 si no lo es.
 */
static int isFormatDNI(char* stringValue);

/** \brief
 *  La funcion obtiene un cadena por teclado y si es solo letras,
 *      la referencia al parametro ingresado.
 *  \param pString char* Array de caracteres para almacenar
 *      el valor ingreso por teclado.
 *  \param len int Longitud del array de caracteres.
 *  \return 0 si pudo obtener el valor de manera correcta,
 *      -1 si hubo un error.
 *
 */
static int getStringOnlyLetters(char* pString, int len);

/** \brief
 *  La funcion obtiene un cadena por teclado y si es numerica,
 *      la referencia al parametro ingresado.
 *  \param pString char* Array de caracteres para almacenar
 *      el valor ingreso por teclado.
 *  \param len int Longitud del array de caracteres.
 *  \return 0 si pudo obtener el valor de manera correcta,
 *      -1 si hubo un error.
 *
 */
static int getStringOnlyNumbers(char* pString, int len);

int utn_getInt(int* pNumber, int retry, int min, int max,
    char* message, char* error)
{
    int returnValue = -1;
    int numeroAux;

    if(max >= min && retry >= 0 && pNumber != NULL
    && message != NULL && error != NULL)
    {
        do
        {
            retry--;
            printf(message);
            if(getInt(&numeroAux) == 0
            && numeroAux >= min && numeroAux <= max)
            {
                *pNumber = numeroAux;
                returnValue = 0;
                break;
            }
            else
            {
                printf(error);
            }
        }while(retry >= 0);
    }

    return returnValue;
}

int utn_getFloat(float* pNumber, int retry, float min, float max,
    char* message, char* error)
{
    int returnValue = -1;
    float floatAux;

    if(max >= min && retry >= 0 && pNumber != NULL
    && message != NULL && error != NULL)
    {
        do
        {
            retry--;
            printf(message);
            if(getFloat(&floatAux) == 0
            && floatAux >= min && floatAux <= max)
            {
                *pNumber = floatAux;
                returnValue = 0;
                break;
            }
            else
            {
                printf(error);
            }
        }while(retry >= 0);
    }

    return returnValue;
}

int utn_getChar(char* pCharacter, int retry, char* message, char* error)
{
    int returnValue = -1;
    char charAux;

    if(pCharacter != NULL && retry >= 0
    && message != NULL && error != NULL)
    {
        printf(message);
        __fpurge(stdin);
        fgets(&charAux, 2, stdin); /**< Por si esta el caracter \n en el buffer. */
        if(sizeof(charAux) == 1)
        {
            strncpy(pCharacter, &charAux, 1);
            returnValue = 0;
        }
        else
        {
            printf(error);
        }
    }

    return returnValue;
}

int utn_getString(char* pString, int len, int retry,
    char* message, char* error, int isOnlyLetters)
{
    int returnValue = -1;
    char stringAux[STRING_MAX];

    if(pString != NULL && len > 0 && retry >= 0
    && message != NULL && error != NULL)
    {
        do
        {
            retry--;
            printf(message);
            if((isOnlyLetters == ALL_CHARACTERES
                && getString(stringAux, len) == 0)
            || (isOnlyLetters = ONLY_LETTERS
                && getStringOnlyLetters(stringAux, len) == 0))
            {
                strncpy(pString, stringAux, len);
                returnValue = 0;
                break;
            }
            else
            {
                printf(error);
            }
        }while(retry >= 0);
    }

    return returnValue;
}

int utn_getPhone(char* pPhone, int len, int retry,
    char* message, char* error)
{
    int returnValue = -1;
    char stringAux[len];
    char currentValue[CURRENT_LEN];
    int scriptQty;
    int i;

    if(pPhone != NULL && len > 0 && retry >= 0
    && message != NULL && error != NULL)
    {
        do
        {
            retry--;
            printf(message);
            if(getString(stringAux, len) == 0)
            {
                i = 0;
                scriptQty = 0;
                currentValue[1] = EXIT_BUFFER;
                while(stringAux[i] != EXIT_BUFFER)
                {
                    currentValue[0] = stringAux[i];
                    if(i > 0 && stringAux[i-1] == stringAux[i]
                    && (stringAux[i] == '-' || stringAux[i] == '+'))
                    {
                        returnValue = -1;
                        break;
                    }
                    else if(stringAux[i] == '-')
                    {
                        scriptQty++;
                        i++;
                        continue;
                    }
                    else if(i == 0 && stringAux[i] == '+')
                    {
                        i++;
                        continue;
                    }
                    if((isNotNumber(currentValue) == 0
                    && stringAux[i] != '-') || scriptQty > 2)
                    {
                        returnValue = -1;
                        break;
                    }
                    else if(isNumber(currentValue) == 0)
                    {
                        returnValue = 0;
                    }
                    i++;
                }
                if(currentValue[0] == '-')
                {
                    returnValue = -1;
                }
            }
            if(returnValue == 0)
            {
                strncpy(pPhone, stringAux, len);
                retry = -1;
            }
            else
            {
                printf(error);
            }
        }while(retry >= 0);
    }

    return returnValue;
}

int utn_getDNI(char* pDNI, int len, int retry,
    char* message, char* error)
{
    int returnValue = -1;
    char dniAux[DNI_MAX];

    if(pDNI != NULL && retry >= 0 && len > 0
    && message != NULL && error != NULL)
    {
        do
        {
            retry--;
            printf(message);
            if(getString(dniAux, DNI_MAX) == 0 && isFormatDNI(dniAux) == 0)
            {
                strncpy(pDNI, dniAux, len);
                returnValue = 0;
                break;
            }
            else
            {
                printf(error);
            }
        }while(retry >= 0);
    }

    return returnValue;
}

int utn_getCUIT(char* pCUIT, int len, int retry,
    char* message, char* error)
{
    int returnValue = -1;
    char cuitAux[len];
    char cuitHeader[CUIT_HEADER];
    char cuitDNI[DNI_MAX];
    char cuitFooter[CUIT_FOOTER];
    int i;
    int j;
    int k;

    if(pCUIT != NULL && len > 0 && retry >= 0
    && message != NULL && error != NULL)
    {
         do
         {
             retry--;
             printf(message);
             if(getString(cuitAux, len) == 0)
             {
                 for(i = 0; i < 2; i++)
                {
                    cuitHeader[i] = cuitAux[i];
                }
                cuitHeader[2] = '\0';
                if(isNumber(cuitHeader) == 0 && cuitAux[2] == '/')
                {
                    for(j = 3; cuitAux[j] != '-'; j++)
                    {
                        cuitDNI[j-3] = cuitAux[j];
                    }
                    k = j-3;
                    cuitDNI[k] = '\0';
                    cuitFooter[0] = cuitAux[k+4];
                    cuitFooter[1] = '\0';
                    if(isFormatDNI(cuitDNI) == 0 && cuitAux[k+3] == '-'
                    && isNumber(cuitFooter) == 0)
                    {
                        returnValue = 0;
                        strncpy(pCUIT, cuitAux, len);
                        break;
                    }
                }
             }
         }while(retry >= 0);
    }

    return returnValue;
}

int utn_getEmail(char* pEmail, int len, int retry,
    char* message, char* error)
{
    int returnValue = -1;
    char emailAux[EMAIL_MAX];
    char emailNickName[EMAIL_NICK];
    char emailAt;
    char emailDomain[EMAIL_DOMAIN];
    char dotCounter;
    int i;
    int j;

    if(pEmail != NULL && len > 0 && retry >= 0
    && message != NULL && error != NULL)
    {
        do
        {
            i = 0;
            j = 0;
            dotCounter = 0;
            retry--;
            printf(message);
            if(getString(emailAux, len) == 0)
            {
                while(emailAux[i] != '@' && emailAux[i] != EXIT_BUFFER)
                {
                    emailNickName[i] = emailAux[i];
                    i++;
                }
                emailNickName[i] = EXIT_BUFFER;
                if(emailAux[i] == '@' && i > 0)
                {
                    emailAt = emailAux[i];
                    i++;
                    j = i;
                    if(emailAux[i] != '.')
                    {
                        while(emailAux[i] != EXIT_BUFFER)
                        {
                            if(dotCounter > 2
                            || (emailAux[i] == '.' && emailAux[i-1] == '.')
                            || emailAux[i] == '@')
                            {
                                break;
                            }
                            else
                            {
                                emailDomain[i-j] = emailAux[i];
                                if(emailAux[i] == '.')
                                {
                                    dotCounter++;
                                }
                                i++;
                            }
                        }
                        emailDomain[i-j] = EXIT_BUFFER;
                        if(dotCounter > 0 && dotCounter <= 2
                        && emailAux[i-1] != '.' && emailAux[i] != '@')
                        {
                            sprintf(emailAux, "%s%c%s",
                                    emailNickName, emailAt, emailDomain);
                            strncpy(pEmail, emailAux, EMAIL_MAX);
                            returnValue = 0;
                            retry = -1;
                        }
                    }
                }
            }
        }while(retry >= 0);
    }

    return returnValue;
}

static int getInt(int* number)
{
    int returnValue = -1;
    char stringAux[CHARACTERS_NUMBERS];
    char stringAtoi[CHARACTERS_NUMBERS];
    int numberAux;

    if(getStringOnlyNumbers(stringAux, CHARACTERS_NUMBERS) == 0
    && isNumber(stringAux) == 0)
    {
        numberAux = atoi(stringAux);
        /**< Validating conversion functions in interger limits. */
        sprintf(stringAtoi, "%d", numberAux);
        if(strncmp(stringAux, stringAtoi, sizeof(stringAux)) == 0)
        {
            *number = numberAux;
            returnValue = 0;
        }
    }

    return returnValue;
}

static int getFloat(float* decimal)
{
    int returnValue = -1;
    char stringAux[CHARACTERS_NUMBERS];
    float numberAux;
    int numberInt;

    if(getStringOnlyNumbers(stringAux, CHARACTERS_NUMBERS) == 0)
    {
        numberAux = atof(stringAux);
        /**< Validating conversion functions in float limits. */
        numberInt = atoi(stringAux);
        if((int)numberAux == numberInt)
        {
            *decimal = numberAux;
            returnValue = 0;
        }
    }

    return returnValue;
}

static int getString(char* pString, int len)
{
    int returnValue = -1;
    char stringAux[STRING_MAX];

    if(pString != NULL && len > 0)
    {
        __fpurge(stdin);
        fgets(stringAux, sizeof(stringAux), stdin);
        if(stringAux[(strlen(stringAux))-1] == '\n')
        {
            stringAux[(strlen(stringAux))-1] = '\0';
        }
        if(strlen(stringAux) <= len)
        {
            sprintf(pString, "%s", stringAux);
            returnValue = 0;
        }

    }

    return returnValue;
}

static int isNumber(char* stringValue)
{
    int returnValue = -1;
    char charAux;
    int i = 0;

    while(stringValue[i] != (int)EXIT_BUFFER)
    {
        charAux = stringValue[i];
        if(i == 0 && (charAux == '-' || charAux == '+'))
        {
            i = 1;
        }
        if((int)charAux >= (int)'0' && (int)charAux <= (int)'9')
        {
            returnValue = 0;
        }
        else
        {
            returnValue = -1;
            break;
        }
        i++;
    }

    return returnValue;
}

static int isNotNumber(char* stringValue)
{
    int returnValue = -1;
    char charAux;
    int i = 0;

    while(stringValue[i] != (int)EXIT_BUFFER)
    {
        charAux = stringValue[i];
        if((int)charAux < (int)'0' || (int)charAux > (int)'9')
        {
            returnValue = 0;
        }
        else
        {
            returnValue = -1;
            break;
        }
        i++;
    }

    return returnValue;
}

static int isFloat(char* stringValue)
{
    int returnValue = -1;
    int pointerCounter = 0;
    int i = 0;

    while(stringValue[i] != (int)EXIT_BUFFER)
    {
        if(i == 0 && ((int)stringValue[0] == (int)'-'
        || (int)stringValue[0] == (int)'+'))
        {
            i = 1;
        }
        if(stringValue[i] == '.')
        {
            pointerCounter++;
        }
        else if((int)stringValue[i] >= (int)'0'
        && (int)stringValue[i] <= (int)'9' && pointerCounter <= 1)
        {
            returnValue = 0;
        }
        else
        {
            returnValue = -1;
            break;
        }
        i++;
    }

    return returnValue;
}

static int isFormatDNI(char* stringValue)
{
    int returnValue = -1;
    char dniAux[DNI_MAX];
    int pointCounter = 0;
    int pointSeparation = 0;
    char currentValue[2];
    int i =0;

    strncpy(dniAux, stringValue, DNI_MAX);
    currentValue[1] = EXIT_BUFFER;
    while(dniAux[i] != EXIT_BUFFER)
    {
        currentValue[0] = dniAux[i];
        if((i == 0 && isNotNumber(currentValue) == 0)
        || (i == 0 && isNumber(currentValue) == 0 && dniAux[i] == '0'))
        {
            returnValue = -1;
            break;
        }
        else if((dniAux[i] == '.' && pointSeparation%3 == 0)
        || (dniAux[i] == '.' && (pointSeparation > 0 && pointSeparation < 3)
            && pointCounter == 0))
        {
            pointCounter++;
            pointSeparation = 0;
            returnValue = 0;
        }
        else if(dniAux[i] == '.' && pointSeparation >= 3 && pointSeparation%3 != 0)
        {
            returnValue = -1;
            break;
        }
        else if(isNumber(currentValue) == 0)
        {
            pointSeparation++;
            returnValue = 0;
        }
        if(pointSeparation != 3)
        {
            returnValue = -1;
        }
        i++;
    }
    if(returnValue == 0)
    {
        strncpy(stringValue, dniAux, DNI_MAX);
    }

    return returnValue;
}

static int getStringOnlyLetters(char* pString, int len)
{
    int returnValue = -1;
    char stringAux[len];

    if(pString != NULL && len > 0)
    {
        if(getString(stringAux, len) == 0 && isNumber(stringAux) == -1)
        {
            strncpy(pString, stringAux, len);
            returnValue = 0;
        }
    }

    return returnValue;
}

static int getStringOnlyNumbers(char* pString, int len)
{
    int returnValue = -1;
    char stringAux[len];

    if(pString != NULL && len > 0)
    {
        if(getString(stringAux, len) == 0 && isFloat(stringAux) == 0)
        {
            strncpy(pString, stringAux, len);
            returnValue = 0;
        }
    }

    return returnValue;
}

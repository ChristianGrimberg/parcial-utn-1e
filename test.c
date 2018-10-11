#include "test.h"

int test_clientHardCode(Client* list, int len)
{
    int returnValue = -1;

    if(WITH_HARDCODE
    && (!client_add(list, len, "Homero", "Simpson", "11/2.222.222-3")
    && !client_add(list, len, "Barney", "Gomez", "12/3.456.789-0")
    && !client_add(list, len, "Marge", "Simpson", "22/3.333.333-4")
    && !client_add(list, len, "Ned", "Flanders", "56/7.890.123-4")
    && !client_add(list, len, "Montgomery", "Burns", "44/5.555.555-6")
    && !client_add(list, len, "Edna", "Krabappel", "98/7.654.321-0")))
    {
        returnValue = 0;
    }

    return returnValue;
}

int test_posterHardCode(Poster* list, int len)
{
    int returnValue = -1;

    if(WITH_HARDCODE
    && (!poster_add(list, len, "imagen1.jpg")
    && !poster_add(list, len, "imagen2.jpg")
    && !poster_add(list, len, "imagen3.jpg")
    && !poster_add(list, len, "imagen4.jpg")))
    {
        returnValue = 0;
    }

    return returnValue;
}

int test_saleHardCode(Sale* list, int len)
{
    int returnValue = -1;

    if(WITH_HARDCODE
    && (!sale_add(list, len, 1, 1, 20, CABA)
    && !sale_add(list, len, 1, 2, 30, ZONA_SUR)
    && !sale_add(list, len, 2, 2, 55, ZONA_OESTE)
    && !sale_add(list, len, 3, 4, 10, ZONA_SUR)
    && !sale_add(list, len, 3, 3, 60, CABA)
    && !sale_add(list, len, 3, 1, 40, ZONA_OESTE)
    && !sale_add(list, len, 4, 1, 45, ZONA_OESTE)
    && !sale_add(list, len, 5, 3, 40, ZONA_SUR)
    && !sale_add(list, len, 5, 4, 20, ZONA_OESTE)))
    {
        returnValue = 0;
    }

    return returnValue;
}

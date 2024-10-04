#include "koi.h"

#include <stdlib.h>
#include <string.h>

u8 koi_last_err_code = KOI_NO_ERR;

typedef struct String
{
    char* str;
} String;

String* koi_new_string(const char* str)
{
    koi_last_err_code = KOI_NO_ERR;

    if (str == NULL)
    {
        koi_last_err_code = KOI_INVALID_ARGS_ERR;

        return NULL;
    }

    String* s = malloc(sizeof(String));

    if (s == NULL)
    {
        koi_last_err_code = KOI_MEM_ALLOC_ERR;

        return NULL;
    }

    s->str = strdup(str);

    if (s->str == NULL)
    {
        koi_last_err_code = KOI_MEM_ALLOC_ERR;

        free(s);

        return NULL;
    }

    return s;
}

void koi_delete_string(String* s)
{
    koi_last_err_code = KOI_NO_ERR;

    if (s == NULL)
    {
        koi_last_err_code = KOI_INVALID_ARGS_ERR;

        return;
    }

    free(s->str);

    free(s);
}

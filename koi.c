#include "koi.h"

#include <stdlib.h>
#include <string.h>

u8 koi_last_err_code = KOI_NO_ERR;

typedef struct String
{
    char* str;

#if defined(__i386__)
    u32 length;
#elif defined(__x86_64__)
    u64 length;
#endif

#if defined(__i386__)
    u32 extra_characters;
#elif defined(__x86_64__)
    u64 extra_characters;
#endif

#if defined(__i386__)
    u32 size;
#elif defined(__x86_64__)
    u64 size;
#endif
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

    s->length = strlen(str);

#if defined(__i386__)
    s->extra_characters = 4;
#elif defined(__x86_64__)
    s->extra_characters = 8;
#endif

    void* p = realloc(s->str, s->length + 1 + s->extra_characters);

    if (p == NULL)
    {
        koi_last_err_code = KOI_MEM_ALLOC_ERR;

        free(s->str);

        free(s);

        return NULL;
    }

    s->size = s->length + 1 + s->extra_characters;

    s->extra_characters *= 2;

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

const char* koi_get_str(String* s)
{
    koi_last_err_code = KOI_NO_ERR;

    if (s == NULL)
    {
        koi_last_err_code = KOI_INVALID_ARGS_ERR;

        return NULL;
    }

    return s->str;
}

#if defined(__i386__)
u32 koi_get_length(String* s)
{
    koi_last_err_code = KOI_NO_ERR;

    if (s == NULL)
    {
        koi_last_err_code = KOI_INVALID_ARGS_ERR;

        return 0;
    }

    return s->length;
}
#elif defined(__x86_64__)
u64 koi_get_length(String* s)
{
    koi_last_err_code = KOI_NO_ERR;

    if (s == NULL)
    {
        koi_last_err_code = KOI_INVALID_ARGS_ERR;

        return 0;
    }

    return s->length;
}
#endif

#if defined(__i386__)
u32 koi_index_of(String* s, char c)
{
    koi_last_err_code = KOI_NO_ERR;

    if (s == NULL)
    {
        koi_last_err_code = KOI_INVALID_ARGS_ERR;

        return 0;
    }

    for (u32 i = 0; i < s->length; i += 1)
    {
        if (s->str[i] == c)
        {
            return i;
        }
    }

    koi_last_err_code = KOI_NOT_FOUND_ERR;

    return 0;
}
#elif defined(__x86_64__)
u64 koi_index_of(String* s, char c)
{
    koi_last_err_code = KOI_NO_ERR;

    if (s == NULL)
    {
        koi_last_err_code = KOI_INVALID_ARGS_ERR;

        return 0;
    }

    for (u64 i = 0; i < s->length; i += 1)
    {
        if (s->str[i] == c)
        {
            return i;
        }
    }

    koi_last_err_code = KOI_NOT_FOUND_ERR;

    return 0;
}
#endif

bool koi_contains(String* s, char c)
{
    koi_last_err_code = KOI_NO_ERR;

    if (s == NULL)
    {
        koi_last_err_code = KOI_INVALID_ARGS_ERR;

        return false;
    }

#if defined(__i386__)
    u32 i = 0;
#elif defined(__x86_64__)
    u64 i = 0;
#endif

    for (; i < s->length; i += 1)
    {
        if (s->str[i] == c)
        {
            return true;
        }
    }

    return false;
}

void koi_to_upper(String* s)
{
    koi_last_err_code = KOI_NO_ERR;

    if (s == NULL)
    {
        koi_last_err_code = KOI_INVALID_ARGS_ERR;

        return;
    }

#if defined(__i386__)
    u32 i = 0;
#elif defined(__x86_64__)
    u64 i = 0;
#endif

    for (; i < s->length; i += 1)
    {
        if (s->str[i] >= 'a' && s->str[i] < 'z')
        {
            s->str[i] -= 32;
        }
    }
}

void koi_to_lower(String* s)
{
    koi_last_err_code = KOI_NO_ERR;

    if (s == NULL)
    {
        koi_last_err_code = KOI_INVALID_ARGS_ERR;

        return;
    }

#if defined(__i386__)
    u32 i = 0;
#elif defined(__x86_64__)
    u64 i = 0;
#endif

    for (; i < s->length; i += 1)
    {
        if (s->str[i] >= 'A' && s->str[i] < 'Z')
        {
            s->str[i] += 32;
        }
    }
}

typedef struct StringList
{
    String* arr;

#if defined(__i386__)
    u32 arr_length;
#elif defined(__x86_64__)
    u64 arr_length;
#endif

#if defined(__i386__)
    u32 size;
#elif defined(__x86_64__)
    u64 size;
#endif
} StringList;

StringList* koi_new_string_list(void)
{
    koi_last_err_code = KOI_NO_ERR;

    StringList* l = malloc(sizeof(StringList));

    if (l == NULL)
    {
        koi_last_err_code = KOI_MEM_ALLOC_ERR;

        return NULL;
    }

    l->arr = malloc(sizeof(String) * 10);

    if (l->arr == NULL)
    {
        koi_last_err_code = KOI_MEM_ALLOC_ERR;

        free(l);

        return NULL;
    }

    l->arr_length = 0;

    l->size = 10;

    return l;
}

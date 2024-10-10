#include "koi.h"

#include <stdlib.h>
#include <string.h>

//

u8 koi_last_err_code = KOI_NO_ERR;

// String

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

//

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

//

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
u32 koi_get_size(String* s)
{
    koi_last_err_code = KOI_NO_ERR;

    if (s == NULL)
    {
        koi_last_err_code = KOI_INVALID_ARGS_ERR;

        return 0;
    }

    return s->size;
}
#elif defined(__x86_64__)
u64 koi_get_size(String* s)
{
    koi_last_err_code = KOI_NO_ERR;

    if (s == NULL)
    {
        koi_last_err_code = KOI_INVALID_ARGS_ERR;

        return 0;
    }

    return s->size;
}
#endif

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

//

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

bool koi_copy_string(String* s1, String* s2)
{
    koi_last_err_code = KOI_NO_ERR;

    if (s1 == NULL || s2 == NULL)
    {
        koi_last_err_code = KOI_INVALID_ARGS_ERR;

        return false;
    }

    char* temp = malloc(s1->size);

    if (temp == NULL)
    {
        koi_last_err_code = KOI_MEM_ALLOC_ERR;

        return false;
    }

#if defined(__i386__)
    u32 i = 0;
#elif defined(__x86_64__)
    u64 i = 0;
#endif  

    for (; i < s1->length; i += 1)
    {
        temp[i] = s1->str[i];
    }

    temp[s1->length] = '\0';

    free(s2->str);

    s2->str = temp;

    s2->length = s1->length;

    s2->extra_characters = s1->extra_characters;

    s2->size = s1->size;

    return true;
}

bool koi_equals(String* s1, String* s2)
{
    koi_last_err_code = KOI_NO_ERR;

    if (s1 == NULL || s2 == NULL)
    {
        koi_last_err_code = KOI_INVALID_ARGS_ERR;

        return false;
    }

    if (s1->length != s2->length)
    {
        return false;
    }

#if defined(__i386__)
    u32 i = 0;
#elif defined(__x86_64__)
    u64 i = 0;
#endif

    for (; i < s1->length; i += 1)
    {
        if (s1->str[i] != s2->str[i])
        {
            return false;
        }
    }

    return true;
}

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

// StringList

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

//

StringList* koi_new_string_list(void)
{
    koi_last_err_code = KOI_NO_ERR;

    StringList* l = malloc(sizeof(StringList));

    if (l == NULL)
    {
        koi_last_err_code = KOI_MEM_ALLOC_ERR;

        return NULL;
    }

    l->arr = calloc(sizeof(String), 10);

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

void koi_delete_string_list(StringList* l)
{
    koi_last_err_code = KOI_NO_ERR;

    if (l == NULL)
    {
        koi_last_err_code = KOI_INVALID_ARGS_ERR;

        return;
    }

#if defined(__i386__)
    u32 i = 0;
#elif defined(__x86_64__)
    u64 i = 0;
#endif

    for (; i < l->arr_length; i += 1)
    {
        free(l->arr[i].str);
    }

    free(l->arr);

    free(l);
}

//

#if defined(__i386__)
u32 koi_get_list_length(StringList* l)
{
    koi_last_err_code = KOI_NO_ERR;

    if (l == NULL)
    {
        koi_last_err_code = KOI_INVALID_ARGS_ERR;

        return 0;
    }

    return l->arr_length;
}
#elif defined(__x86_64__)
u64 koi_get_list_length(StringList* l)
{
    koi_last_err_code = KOI_NO_ERR;

    if (l == NULL)
    {
        koi_last_err_code = KOI_INVALID_ARGS_ERR;

        return 0;
    }

    return l->arr_length;
}
#endif

//

bool koi_list_contains_string(StringList* l, String* s)
{
    koi_last_err_code = KOI_NO_ERR;

    if (l == NULL || s == NULL)
    {
        koi_last_err_code = KOI_INVALID_ARGS_ERR;

        return false;
    }

#if defined(__i386__)
    u32 i = 0;
#elif defined(__x86_64__)
    u64 i = 0;
#endif

    for (; i < l->arr_length; i += 1)
    {
        if (koi_equals(&l->arr[i], s))
        {
            return true;
        }
    }

    return false;
}

bool koi_add_string(StringList* l, String* s)
{
    koi_last_err_code = KOI_NO_ERR;

    if (l == NULL || s == NULL)
    {
        koi_last_err_code = KOI_INVALID_ARGS_ERR;

        return false;
    }

    if (l->arr_length == l->size)
    {
        void* temp = realloc(l->arr, l->size * 2);

        if (temp == NULL)
        {
            koi_last_err_code = KOI_MEM_ALLOC_ERR;

            return false;
        }

        l->arr = temp;

#if defined(__i386__)
        u32 i = l->arr_length;
#elif defined(__x86_64__)
        u64 i = l->arr_length;
#endif

        for (; i < l->size * 2; i += 1)
        {
            l->arr[i].str = NULL;
        }

        l->size *= 2;
    }

    koi_copy_string(s, &l->arr[l->arr_length]);

    l->arr_length += 1;

    return true;
}

void koi_for_each(StringList* l, void (*f) (String*))
{
    koi_last_err_code = KOI_NO_ERR;

    if (l == NULL || f == NULL)
    {
        koi_last_err_code = KOI_INVALID_ARGS_ERR;

        return;
    }

#if defined(__i386__)
    u32 i = 0;
#elif defined(__x86_64__)
    u64 i = 0;
#endif

    for (; i < l->arr_length; i += 1)
    {
        f(&l->arr[i]);
    }
}

StringList* koi_filter(StringList* l, bool (*f) (String*))
{
    koi_last_err_code = KOI_NO_ERR;

    if (l == NULL || f == NULL)
    {
        koi_last_err_code = KOI_INVALID_ARGS_ERR;

        return NULL;
    }

    if (l->arr_length == 0 || l->arr_length == 1)
    {
        return NULL;
    }

    StringList* result = koi_new_string_list();

    if (result == NULL)
    {
        // koi_last_err_code = KOI_MEM_ALLOC_ERR;

        return NULL;
    }

#if defined(__i386__)
    u32 i = 0;
#elif defined(__x86_64__)
    u64 i = 0;
#endif

    for (; i < l->arr_length; i += 1)
    {
        if (f(&l->arr[i]))
        {
            koi_add_string(result, &l->arr[i]);
        }
    }

    return result;
}

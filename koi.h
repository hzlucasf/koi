#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t u8;

#if defined(__i386__)
typedef uint32_t u32;
#elif defined(__x86_64__)
typedef uint64_t u64;
#endif

#define KOI_NO_ERR           0
#define KOI_INVALID_ARGS_ERR 1
#define KOI_MEM_ALLOC_ERR    2
#define KOI_NOT_FOUND_ERR    3

extern u8 koi_last_err_code;

typedef struct String String;

String* koi_new_string(const char*);

void koi_delete_string(String*);

const char* koi_get_str(String*);

#if defined(__i386__)
u32 koi_get_length(String*);
#elif defined(__x86_64__)
u64 koi_get_length(String*);
#endif

#if defined(__i386__)
u32 koi_index_of(String*, char);
#elif defined(__x86_64__)
u64 koi_index_of(String*, char);
#endif

bool koi_contains(String*, char);

void koi_to_upper(String*);

void koi_to_lower(String*);

typedef struct StringList StringList;

StringList* koi_new_string_list(void);

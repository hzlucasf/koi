#pragma once

#include <stdint.h>

typedef uint8_t u8;

#define KOI_NO_ERR           0
#define KOI_INVALID_ARGS_ERR 1
#define KOI_MEM_ALLOC_ERR    2

extern u8 koi_last_err_code;

typedef struct String String;

String* koi_new_string(const char*);

void koi_delete_string(String*);

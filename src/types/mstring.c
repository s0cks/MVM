#include <types/mstring.h>
#include <string.h>

mstring_t*
mstring_create(){
    mstring_t* ret;
    if((ret = malloc(sizeof(mstring_t))) == NULL){
        return NULL;
    }

    ret->data = malloc(sizeof(byte) * MSTR_INIT_SIZE);
    ret->size = 0;
    ret->asize = MSTR_INIT_SIZE;
    return ret;
}

mstring_t*
mstring_slice(mstring_t* str, size_t offset, size_t len){
    mstring_t* mstr = mstring_create();

    for(size_t i = offset; i < len; i++){
        mstring_putc(mstr, str->data[i]);
    }

    return mstr;
}

mstring_t*
mstring_wrap(byte* str){
    mstring_t* ret = mstring_create();
    mstring_put(ret, str, strlen((const char *) str));
    return ret;
}

const char*
mstring_cstr(mstring_t* str){
    if(str->size < str->asize && str->data[str->size] == 0){
        return (const char*) str->data;
    }

    mstring_grow(str, str->size + 1);
    str->data[str->size] = 0;
    return (const char*) str->data;
}

const char
mstring_getc(mstring_t* str, size_t index){
    if(index > str->size || index < 0){
        return 0;
    }

    return str->data[index];
}

int
mstring_starts_with(mstring_t* str1, mstring_t* str2){
    if(str1->size >= str2->size){
        for(size_t i = 0; i < str2->size; i++){
            if(str1->data[i] != str2->data[i]){
                return 0;
            }
        }

        return 1;
    }

    return 0;
}

int
mstring_equals(mstring_t* str1, mstring_t* str2){
    if(str1->size != str2->size){
        return 0;
    }

    for(size_t i = 0; i < str2->size; i++){
        if(str1->data[i] != str2->data[i]){
            return 0;
        }
    }

    return 1;
}

void
mstring_free(mstring_t* str){
    if(!str){
        return;
    }

    free(str->data);
    free(str);
}

void
mstring_grow(mstring_t* str, size_t nsize){
    if(str->asize > nsize){
        return;
    }

    size_t nasize = str->asize + MSTR_CHUNK_SIZE;
    while(nasize < nsize){
        nasize += MSTR_CHUNK_SIZE;
    }

    byte* ret;
    if((ret = realloc(str->data, nasize)) == NULL){
        return;
    }

    str->data = ret;
    str->asize = nasize;
}

void
mstring_put(mstring_t* str, const byte* data, size_t len){
    if(str->size + len > str->asize){
        mstring_grow(str, str->size + len);
    }

    memcpy(str->data + str->size, data, len);
    str->size += len;
}

void
mstring_putc(mstring_t* str, const byte data){
    if(str->size + 1 >= str->asize){
        mstring_grow(str, str->size + 1);
    }

    str->data[str->size] = data;
    str->size++;
}

void
mstring_putstr(mstring_t* str, mstring_t* data){
    mstring_put(str, data->data, data->size);
}

void
mstring_printf(mstring_t* str, const char* fmt, ...){
    if(str->size + 1 >= str->asize){
        mstring_grow(str, str->size + 1);
    }

    va_list list;
    int len;

    va_start(list, fmt);
    len = vsnprintf((char*) str->data + str->size, str->asize - str->size, fmt, list);
    va_end(list);

    if(len < 0){
        return;
    }

    if(len >= str->asize - str->size){
        mstring_grow(str, str->size + len + 1);
        va_start(list, fmt);
        len = vsnprintf((char*) str->data + str->size, str->asize - str->size, fmt, list);
        va_end(list);
    }

    if(len < 0){
        return;
    }

    str->size += len;
}
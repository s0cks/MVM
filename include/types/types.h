#ifndef MICROVM_TYPES_H
#define MICROVM_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif

#include "../mvm-private.h"
#include "mstring.h"

typedef enum{
    MVM_INTEGER,
    MVM_STRING,
    MVM_DOUBLE,
    MVM_BYTE
} mvm_obj_type;

typedef struct smvm_obj_t{
    byte marked;
    mvm_obj_type type;
    struct smvm_obj_t* next;
} mvm_obj_t;

typedef struct{
    mvm_obj_t obj;
    int value;
} mvm_integer_t;

typedef struct{
    mvm_obj_t obj;
    double value;
} mvm_double_t;

typedef struct{
    mvm_obj_t obj;
    byte value;
} mvm_byte_t;

typedef struct{
    mvm_obj_t obj;
    mstring_t* value;
} mvm_string_t;

#ifndef container_of
#define container_of(ptr_, type_, member_)({ \
    const typeof(((type_*) 0)->member_)* __mbptr = ((void*) ptr_); \
    (type_*)((char*) __mbptr - offsetof(type_, member_)); \
    })
#endif

#define mvm_typeof(mot_) ((mot_)->type)

#define mvm_is_integer(mot_) ((mot_) && mvm_typeof(mot_) == MVM_INTEGER)
#define mvm_is_double(mot_) ((mot_) && mvm_typeof(mot_) == MVM_DOUBLE)
#define mvm_is_byte(mot_) ((mot_) && mvm_typeof(mot_) == MVM_BYTE)
#define mvm_is_string(mot_) ((mot_) && mvm_typeof(mot_) == MVM_STRING)

#define mvm_to_integer(mot_) container_of(mot_, mvm_integer_t, obj)
#define mvm_to_double(mot_) container_of(mot_, mvm_double_t, obj)
#define mvm_to_byte(mot_) container_of(mot_, mvm_byte_t, obj)
#define mvm_to_string(mot_) container_of(mot_, mvm_string_t, obj)

int mvm_integer_value(mvm_obj_t* obj);
double mvm_double_value(mvm_obj_t* obj);
byte mvm_byte_value(mvm_obj_t* obj);
mstring_t* mvm_string_value(mvm_obj_t* obj);

void mvm_type_free(mvm_obj_t* obj);

#ifdef __cplusplus
};
#endif

#endif
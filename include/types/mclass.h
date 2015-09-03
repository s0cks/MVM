#ifndef MICROVM_MCLASS_H
#define MICROVM_MCLASS_H

#ifdef __cplusplus
extern "C"{
#endif

#include "types/types.h"

#ifndef MVM_CLASS_SIZE
#define MVM_CLASS_SIZE 1024
#endif

typedef struct _mvm_class_field_t{
    mstring_t* name;
    mvm_obj_t* value;
    struct _mvm_class_field_t* next;
} mvm_class_field_t;

typedef struct _mvm_class_t{
    mstring_t* name;
    struct _mvm_class_t *super;
    mvm_class_field_t** iv;
} mvm_class_t;

mvm_class_t* mvm_define_class(mstring_t* name, mvm_class_t* super);

byte mvm_class_is_instance(mvm_class_t* klass, mstring_t* sklass);

mvm_class_field_t* mvm_class_define_field(mvm_class_t* klass, mstring_t* name, mvm_obj_t* value);
mvm_obj_t* mvm_class_get_field(mvm_class_t* klass, mstring_t* name);

void mvm_class_spec(mvm_class_t* klass);

#ifdef __cplusplus
};
#endif

#endif
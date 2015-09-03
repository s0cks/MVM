#include <types/mstring.h>
#include <string.h>
#include "types/mclass.h"

unsigned long int
mvm_hash(mstring_t* str){
    unsigned long int h = 0;
    for(size_t i = 0; i < str->size; i++){
        h = (h ^ str->data[i] ^ (str->data[i] << 1) ^ (str->data[i] << 8) + (str->data[i] << (str->data[i] % 7)));
    }
    return h % (MVM_CLASS_SIZE - 1);
}

mvm_class_field_t*
mvm_new_field(mstring_t* str, mvm_class_t* tclass){
    mvm_class_field_t* field;
    if((field = malloc(sizeof(mvm_class_field_t))) == NULL){
        return NULL;
    }

    field->name = str;
    field->tclass = tclass;
    field->next = NULL;
    return field;
}

mvm_class_t*
mvm_define_class(mstring_t* name, mvm_class_t* super){
    mvm_class_t* class;
    if((class = malloc(sizeof(mvm_class_t))) == NULL){
        return NULL;
    }

    if((class->iv = malloc(sizeof(mvm_class_field_t*) * MVM_CLASS_SIZE)) == NULL){
        free(class);
        return NULL;
    }

    for(size_t i = 0; i < MVM_CLASS_SIZE; i++){
        class->iv[i] = NULL;
    }

    class->name = name;
    class->super = super;
    return class;
}

mvm_class_field_t*
mvm_class_define_field(mvm_class_t* klass, mstring_t* name, mvm_class_t* tclass){
    unsigned long int bin = mvm_hash(name);
    mvm_class_field_t* next = klass->iv[bin];
    mvm_class_field_t* last = NULL;

    while(next != NULL && next->name != NULL && mstring_equals(name, next->name) > 0){
        last = next;
        next = next->next;
    }

    if(next != NULL && next->name != NULL && mstring_equals(name, next->name) == 0){
        next->tclass = tclass;
        return next;
    } else{
        mvm_class_field_t* field = mvm_new_field(name, tclass);
        if(next == klass->iv[bin]){
            field->next = next;
            klass->iv[bin] = field;
        } else if(next == NULL){
            last->next = field;
        } else{
            field->next = next;
            last->next = field;
        }

        return field;
    }
}

byte
mvm_class_is_instance(mvm_class_t* klass, mstring_t* sklass){
    mvm_class_t* cklass = klass;
    while(cklass != NULL){
        if(mstring_equals(cklass->name, sklass)){
            return 1;
        }

        cklass = cklass->super;
    }

    return 0;
}

void
mvm_class_spec(mvm_class_t* klass){
    printf("Class: %s\n", mstring_cstr(klass->name));
    printf("SuperClass: %s\n", klass->super == NULL ? "<root>" : (char*) mstring_cstr(klass->super->name));
}
#include <mvm.h>

int main(int argc, char** argv){
    mvm_allocator_t* alloc = mvm_allocator_create(1024);

    mvm_class_t* objclass = mvm_define_class(mstring_wrap((byte*) "Object"), NULL);
    mvm_class_t* numclass = mvm_define_class(mstring_wrap((byte*) "Num"), objclass);
    mvm_class_t* strclass = mvm_define_class(mstring_wrap((byte*) "Str"), objclass);
    mvm_class_t* byteclass = mvm_define_class(mstring_wrap((byte*) "Byte"), numclass);

    printf("Num is Object?: %s\n", mvm_bool_to_str(mvm_class_is_instance(numclass, mstring_wrap((byte*) "Object"))));
    printf("Str is Object?: %s\n", mvm_bool_to_str(mvm_class_is_instance(strclass, mstring_wrap((byte*) "Object"))));
    printf("Byte is Num?: %s\n", mvm_bool_to_str(mvm_class_is_instance(byteclass, mstring_wrap((byte*) "Num"))));
    printf("Num is String? %s\n", mvm_bool_to_str(mvm_class_is_instance(numclass, mstring_wrap((byte*) "String"))));

    mvm_class_define_field(objclass, mstring_wrap((byte*) "Hash"), mvm_alloc_new_string(alloc, (byte*) "0x02837383"));
    mvm_class_define_field(objclass, mstring_wrap((byte*) "Name"), mvm_alloc_new_string(alloc, (byte*) "Object"));

    mvm_class_spec(objclass);
    mvm_class_spec(numclass);
    mvm_class_spec(strclass);
    mvm_class_spec(byteclass);

    printf("Object.Name?: %s\n", mstring_cstr(mvm_string_value(mvm_class_get_field(objclass, mstring_wrap((byte*) "Name")))));
    printf("Object.Hash?: %s\n", mstring_cstr(mvm_string_value(mvm_class_get_field(objclass, mstring_wrap((byte*) "Hash")))));

    printf("Str.Name?: %s\n", mstring_cstr(mvm_string_value(mvm_class_get_field(strclass, mstring_wrap((byte*) "Name")))));
    mvm_class_define_field(strclass, mstring_wrap((byte*) "Name"), mvm_alloc_new_string(alloc, (byte*) "String"));
    printf("Str.Name?: %s\n", mstring_cstr(mvm_string_value(mvm_class_get_field(strclass, mstring_wrap((byte*) "Name")))));

    printf("Byte.Hash?: %s\n", mstring_cstr(mvm_string_value(mvm_class_get_field(byteclass, mstring_wrap((byte*) "Hash")))));
    return 0;
}
#include <mvm.h>

int main(int argc, char** argv){
    mvm_t* mvm = mvm_create();
    mvm_push_integer(mvm, 10);
    mvm_push_integer(mvm, 10);
    mvm_push_byte(mvm, 1);

    if(mvm_byte_value(mvm_pop(mvm)) == 1){
        mvm_push_integer(mvm, mvm_integer_value(mvm_pop(mvm)) + mvm_integer_value(mvm_pop(mvm)));
    }

    mvm_obj_t* res = mvm_pop(mvm);
    printf("%d\n", mvm_integer_value(res));

    mvm_push_integer(mvm, 100);
    mvm_push_integer(mvm, 100);
    mvm_push_byte(mvm, 2);

    if(mvm_byte_value(mvm_pop(mvm)) == 2){
        mvm_push_integer(mvm, mvm_integer_value(mvm_pop(mvm)) - mvm_integer_value(mvm_pop(mvm)));
    }

    res = mvm_pop(mvm);
    printf("%d\n", mvm_integer_value(res));

    mvm_push_integer(mvm, 2);
    mvm_push_integer(mvm, 1000);
    mvm_push_byte(mvm, 3);

    if(mvm_byte_value(mvm_pop(mvm)) == 3){
        mvm_push_integer(mvm, mvm_integer_value(mvm_pop(mvm)) % mvm_integer_value(mvm_pop(mvm)));
    }

    res = mvm_pop(mvm);
    printf("%d\n", mvm_integer_value(res));

    printf("Collected: %lu\n", mvm_gc(mvm));
    mvm_free(mvm);
    return 0;
}
#include <mvm.h>
#include <mvm-debug.h>
#include <string.h>
#include <types/mstringpool.h>

int main(int argc, char** argv){
    mvm_t* mvm = mvm_create();

    mvm_free(mvm);
    return 0;
}
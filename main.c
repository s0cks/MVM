#include <mvm.h>

void
mvm_assert(int exp, char* msg){
    if(!exp){
        fprintf(stderr, "%s\n", msg);
        exit(1);
    }
}

int main(int argc, char** argv){
    return 0;
}
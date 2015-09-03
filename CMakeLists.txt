cmake_minimum_required(VERSION 3.2)
project(MicroVM)

include_directories(include)

add_executable(MicroVM ${SOURCE_FILES} main.c main.c include/mvm.h include/mvm-private.h include/types/types.h include/gc/allocator.h include/gc/collector.h src/types/types.c src/gc/allocator.c src/gc/collector.c include/types/mstring.h src/types/mstring.c src/mvm.c include/opcodes.h include/types/mclass.h src/types/mclass.c)
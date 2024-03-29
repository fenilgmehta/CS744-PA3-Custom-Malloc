cmake_minimum_required(VERSION 3.8)
project("PA_3_handout")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE on)

#--------------------------------------------------------------------------------------------------------------------------------------------------------------------

# REFER: https://stackoverflow.com/questions/4765222/how-do-i-produce-only-an-object-file-o-from-a-cmake-build-target
# REFER: https://cmake.org/cmake/help/latest/command/add_library.html#object-libraries
add_library(MY_all_1.o     OBJECT       clock.c clock.h config.h fcyc.c fcyc.h fsecs.c fsecs.h ftimer.c ftimer.h mdriver.c memlib.c memlib.h mm1.c mm.h)
add_library(MY_all_2.o     OBJECT       clock.c clock.h config.h fcyc.c fcyc.h fsecs.c fsecs.h ftimer.c ftimer.h mdriver.c memlib.c memlib.h mm2.c mm.h)
add_executable(mdriver1 $<TARGET_OBJECTS:MY_all_1.o>)
add_executable(mdriver2 $<TARGET_OBJECTS:MY_all_2.o>)

#add_library(MyObj OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/src/object.c)
#add_library(MyLibrary STATIC $<TARGET_OBJECTS:MyObj> MyClass1.cpp Helpers.cpp)

# add_library(MY_mdriver.o OBJECT mdriver.c fsecs.h fcyc.h clock.h memlib.h config.h mm.h)
# add_library(MY_memlib.o  OBJECT memlib.c memlib.h)
# add_library(MY_mm.o      OBJECT mm.c mm.h memlib.h)
# add_library(MY_mm1.o     OBJECT mm1.c mm.h memlib.h)
# add_library(MY_mm2.o     OBJECT mm2.c mm.h memlib.h)
# add_library(MY_fsecs.o   OBJECT fsecs.c fsecs.h config.h)
# add_library(MY_fcyc.o    OBJECT fcyc.c fcyc.h)
# add_library(MY_ftimer.o  OBJECT ftimer.c ftimer.h config.h)
# add_library(MY_clock.o   OBJECT clock.c clock.h)
# add_executable(
#     mdriver      
#     $<TARGET_OBJECTS:MY_mdriver.o>
#     $<TARGET_OBJECTS:MY_memlib.o>
#     $<TARGET_OBJECTS:MY_mm.o>
#     $<TARGET_OBJECTS:MY_mm1.o>
#     $<TARGET_OBJECTS:MY_mm2.o>
#     $<TARGET_OBJECTS:MY_fsecs.o>
#     $<TARGET_OBJECTS:MY_fcyc.o>
#     $<TARGET_OBJECTS:MY_ftimer.o>
#     $<TARGET_OBJECTS:MY_clock.o>
# )

#--------------------------------------------------------------------------------------------------------------------------------------------------------------------

#file(GLOB sourceFILES *.cpp *.c *.o)
#
#FOREACH (sourceFile ${sourceFILES})
#    get_filename_component(sourceFile_Path ${sourceFile} PATH)
#    MESSAGE(STATUS "Process file, path: ${sourceFile}")
#
#    get_filename_component(sourceFile_Name ${sourceFile} NAME)
#    string(REPLACE " " "_" sourceFile_Name ${sourceFile_Name})
#    string(REPLACE "'" "" sourceFile_Name ${sourceFile_Name})
#    string(REPLACE "\"" "" sourceFile_Name ${sourceFile_Name})
#    string(REPLACE "(" "_" sourceFile_Name ${sourceFile_Name})
#    string(REPLACE ")" "_" sourceFile_Name ${sourceFile_Name})
#    MESSAGE(STATUS "Process file, name: \"${sourceFile_Name}\"")
#
#    add_executable("${sourceFile_Name}" "${sourceFile}")
#
#endforeach (sourceFile)

project(golovolomka)
cmake_minimum_required(VERSION 2.6)

# check libs and packages (headers + lib)

# std C libraries
#find_package(stdlibs REQUIRED)

#check_include_file(argp.h HAVE_ARGP_H)

# additional compiler flags
#add_definitions(-Wall -Wextra -pedantic -Werror)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# compiler switches
# enable gcc specific stuff
# if (CMAKE_COMPILER_IS_GNUCC)
#     set_source_files_properties(${EXAMPLE_SRC} PROPERTIES COMPILE_FLAGS "-std=c99 -Werror -Wall -pedantic")
# endif ()

# install binaries
#install(TARGETS golovolomka RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)

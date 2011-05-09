# include_directories(
#     .
#     ..
#     ${CMAKE_CURRENT_BINARY_DIR}
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     ${CMAKE_SOURCE_DIR}
#     ${CMAKE_BINARY_DIR}
#     ${CMAKE_SOURCE_DIR}/src/
#    )

# define the sources
FILE(GLOB CPPSources *.cpp)

# define executable
add_executable(golovolomka ${CPPSources})
#target_link_libraries(golovolomka ${CMAKE_REQUIRED_LIBRARIES})

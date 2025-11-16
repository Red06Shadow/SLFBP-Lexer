cmake_minimum_required(VERSION 3.10)

option(USINGWCARACTER "Usa los caracteres wchar_t para las rutas de archivos" OFF)
option(TEST "Indica si libme esta en testeo o en compilacion libreria" ON)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

if(TEST)
project(SLFBP-Lexer-Test)
add_executable(SLFBP-Lexer-Test 
${CMAKE_SOURCE_DIR}/main.cpp
${CMAKE_SOURCE_DIR}/lib/lexer/lexer.cpp
)
link_directories(${CMAKE_SOURCE_DIR}/libme/lib)
target_link_libraries(SLFBP-Lexer-Test PRIVATE Pathcch ${CMAKE_SOURCE_DIR}/lib/stda/libstdandart-library-for-me.a)
else()
project(SLFBP-Lexer)
add_library(SLFBP-Lexer STATIC
${CMAKE_SOURCE_DIR}/lib/lexer/lexer.cpp
)
# Configuración por configuración
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/release)

# Para una biblioteca específica
set_target_properties(SLFBP-Lexer PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/debug
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/release
)
link_directories(${CMAKE_SOURCE_DIR}/libme/lib)
target_link_libraries(SLFBP-Lexer PRIVATE Pathcch ${CMAKE_SOURCE_DIR}/lib/stda/libstdandart-library-for-me.a)

endif()


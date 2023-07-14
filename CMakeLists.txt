cmake_minimum_required (VERSION 3.11)
project(app
    LANGUAGES CXX
    VERSION 1.6.0
)

# Definir as variáveis do seu projeto
set(CC g++)
set(CXXFLAGS "-std=c++20")
set(CPPFLAGS "-Wall")
set(LDFLAGS "-lcurl")

set(INCDIR include)
set(SRCDIR src)
set(OBJDIR obj)
set(BINDIR bin)
set(TARGET app)

# Obter a lista de arquivos fonte
file(GLOB_RECURSE SRCS "${SRCDIR}/*.cpp")

# Compilar os arquivos fonte para objetos
foreach(SRC ${SRCS})
    get_filename_component(SRC_NAME ${SRC} NAME_WE)
    set(OBJ "${OBJDIR}/${SRC_NAME}.o")
    set(OBJ_LIST ${OBJ_LIST} ${OBJ})
    add_custom_command(
        OUTPUT ${OBJ}
        COMMAND ${CC} ${CXXFLAGS} ${CPPFLAGS} -I${INCDIR} -c ${SRC} -o ${OBJ}
        DEPENDS ${SRC}
    )
endforeach()

# Compilar o executável
add_executable(${TARGET} ${OBJ_LIST} main.cpp)

# Configurar as dependências do FTXUI
find_package(ftxui REQUIRED)
target_link_libraries(${TARGET} PRIVATE ftxui::screen ftxui::dom)
target_include_directories(${TARGET} PRIVATE ${INCDIR})

# Adiciona as flags de linker
target_link_options(${TARGET} PRIVATE ${LDFLAGS})

# Copiar os arquivos Python para a pasta de saída do executável
add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/setcoordinates.py" "$<TARGET_FILE_DIR:${TARGET}>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/processdata.py" "$<TARGET_FILE_DIR:${TARGET}>"
)

# Definir alvos personalizados para os comandos do Makefile
add_custom_target(build_all
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${TARGET}
    COMMENT "Building all"
)

add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${OBJDIR}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BINDIR}
    COMMENT "Cleaning all"
)

add_custom_target(run
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${TARGET}
    COMMAND ${CMAKE_COMMAND} -E chdir ${BINDIR} ./${TARGET}
    COMMENT "Running the application"
)
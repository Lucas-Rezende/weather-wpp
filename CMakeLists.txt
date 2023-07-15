cmake_minimum_required (VERSION 3.11)
project(app
    LANGUAGES CXX
    VERSION 1.6.0
)

include(FetchContent) 
FetchContent_Declare( 
  ftxui 
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG v4.1.1 # Especifique um GIT_TAG aqui.
) 
FetchContent_MakeAvailable(ftxui)

# Compilar o executável
add_executable(app main.cpp src/weatherdatafetcher.cpp src/getcoordinates.cpp src/gettime.cpp src/hourlydatafilter.cpp)

# Configurar as dependências do FTXUI
set(ftxui::ftxui_DIR ${ftxui_BINARY_DIR})
target_link_libraries(app PRIVATE ftxui::screen ftxui::dom ftxui::component)

# Adicionar as flags de linker
target_link_libraries(app PRIVATE curl)

# Copiar os arquivos Python para a pasta de saída do executável
add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/setcoordinates.py" "$<TARGET_FILE_DIR:app>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/processdata.py" "$<TARGET_FILE_DIR:app>"
)

# Definir alvos personalizados para os comandos do Makefile
add_custom_target(run
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target app
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} ./app
    COMMENT "Running the application"
)

cmake_minimum_required(VERSION 3.14)
project(ArkanoidGame)

set(CMAKE_CXX_STANDARD 17)

# Statik derleme ile devam ediyoruz, en temiz yöntem
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
set(SFML_BUILD_AUDIO OFF CACHE BOOL "Build audio" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "Build network" FORCE)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)

add_executable(Arkanoid main.cpp OyunFonksiyonlari.cpp)

# Grafik modülü bağlı kalıyor (Tuğlalar ve top için), sadece yazı tipini koddan eliyoruz
target_link_libraries(Arkanoid PRIVATE sfml-graphics sfml-window sfml-system)

# Seviye dosyasını build klasörüne kopyalar
file(COPY 
    ${CMAKE_CURRENT_SOURCE_DIR}/seviye1.txt
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)
cmake_minimum_required(VERSION 3.14)
project(ArkanoidGame)

set(CMAKE_CXX_STANDARD 17)

# DLL derdini TAMAMEN bitirir (Statik derleme)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)

# İhtiyacımız olmayan ve hata çıkaran ekstra modülleri kapat
set(SFML_BUILD_AUDIO OFF CACHE BOOL "Build audio" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "Build network" FORCE)

# SFML'i indir ve projeye dahil et
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)

# Çalıştırılabilir dosyayı oluştur
add_executable(Arkanoid main.cpp)

# SFML kütüphanelerini bağla
target_link_libraries(Arkanoid PRIVATE sfml-graphics sfml-window sfml-system)
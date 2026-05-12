cmake_minimum_required(VERSION 3.10)
project(ArkanoidGame)

set(CMAKE_CXX_STANDARD 17)

# SFML kütüphanesini bul
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Çalıştırılabilir dosyayı oluştur
add_executable(Arkanoid main.cpp)

# SFML kütüphanelerini bağla
target_link_libraries(Arkanoid sfml-graphics sfml-window sfml-system)
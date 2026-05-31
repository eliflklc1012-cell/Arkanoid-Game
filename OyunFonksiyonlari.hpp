#ifndef OYUN_FONKSIYONLARI_HPP
#define OYUN_FONKSIYONLARI_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// Tuğla yapısı (1 canı olan pembe, 2 canı olan mor tuğlalar için)
struct Tugla { 
    sf::RectangleShape shape; 
    int can; 
};

// Fonksiyon Prototipleri
// Girdilere göre raketi hareket ettiren fonksiyon
void raketHareketi(sf::RectangleShape& paddle, float paddleSpeed, sf::Time dt);

// Topun hareketi, duvarlardan sekmesi ve aşağı düşme kontrolü (main ile uyumlu bool)
bool topHareketiVeDuvarSekmesi(sf::CircleShape& ball, sf::Vector2f& ballVelocity, sf::Time dt);

// Topun rakete çarpıp sekmesini sağlayan fonksiyon
void topRaketCarpmasi(sf::CircleShape& ball, sf::Vector2f& ballVelocity, const sf::RectangleShape& paddle);

// Txt dosyasından haritayı okuyup blokları hafızaya alan fonksiyon
void seviyeYukle(const std::string& dosyaAdi, std::vector<Tugla>& blocks);

// Topun tuğlaları kırıp sekmesini sağlayan fonksiyon (main.cpp çağrısı ile tamamen eşitlendi)
void topBlokCarpismasi(sf::CircleShape& ball, sf::Vector2f& ballVelocity, std::vector<Tugla>& blocks, int&skor);

// Güç arttırıcı (Power-up) kutularını yönetmek için  bir yapı tanımlıyoruz
struct PowerUp {
    sf::RectangleShape shape;
    int tip; // 1: Raket Genişletme, 2: Top Hızlandırma
    bool aktif = true;
};

#endif // OYUN_FONKSIYONLARI_HPP
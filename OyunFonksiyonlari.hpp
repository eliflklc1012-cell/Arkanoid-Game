#ifndef OYUN_FONKSIYONLARI_HPP
#define OYUN_FONKSIYONLARI_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>


//Fonksiyon Prototipleri (bildirimleri)

void raketHareketi(sf::RectangleShape&paddle, float paddleSpeed, sf::Time dt);
void topHareketiVeDuvarSekmesi(sf::CircleShape& ball,sf::Vector2f& ballVelocity, sf::Time dt);
void topRaketCarpmasi(sf::CircleShape& ball, sf::Vector2f& ballVelocity, const sf::RectangleShape& paddle);

//dosyadan harita yükleme fonksiyonu 
void seviyeYukle(const std :: string&dosyaAdi, std::vector<sf::RectangleShape>&blocks);

//topun tuğlaları kırıp sekmesini sağlayan fonk.
void topBlokCarpismasi(sf::CircleShape& ball, sf::Vector2f& ballVelocity, std::vector<sf::RectangleShape>& blocks);

#endif //OYUN_FONKSİYONLARI_HPP
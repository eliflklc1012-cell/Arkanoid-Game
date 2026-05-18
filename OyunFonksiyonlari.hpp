#ifndef OYUN_FONKSIYONLARI_HPP
#define OYUN_FONKSIYONLARI_HPP

#include <SFML/Graphics.hpp>

//Fonksiyon Prototipleri (bildirimleri)

void raketHareketi(sf::RectangleShape&paddle, float paddleSpeed, sf::Time dt);
void topHareketiVeDuvarSekmesi(sf::CircleShape& ball,sf::Vector2f& ballVelocity, sf::Time dt);
void topRaketCarpmasi(sf::CircleShape& ball, sf::Vector2f& ballVelocity, const sf::RectangleShape& paddle);

#endif //OYUN_FONKSİYONLARI_HPP
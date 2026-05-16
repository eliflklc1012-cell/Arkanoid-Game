#include "OyunFonksiyonlari.hpp"

//raket hareket mantığı

void raketHareketi(sf::RectangleShape& paddle, float paddleSpeed, sf::Time dt)
 {
    if 
    (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && paddle.getPosition().x > 0){ 
        paddle.move(-paddleSpeed * dt.asSeconds(), 0); 
      } 
    
    if
    (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && paddle.getPosition().x + paddle.getSize().x < 800 ){
          paddle.move(paddleSpeed * dt.asSeconds(), 0);
     }
    
}

// topun hareketi ve sınırlardan sekme mantığı

void topHareketiVeDuvarSekmesi(sf::CircleShape& ball, sf::Vector2f & ballVelocity, sf::Time dt) {
    ball.move(ballVelocity * dt.asSeconds());

    //sol ve sağ duvar kontrolü
    if (ball.getPosition().x < 0  || ball.getPosition().x + ball.getRadius() * 2 >800) {
        ballVelocity.x = -ballVelocity.x;
    }
    //üstteki duvarın konrtolü
    if(ball.getPosition().y <0){
        ballVelocity.y= -ballVelocity.y;
    }
}
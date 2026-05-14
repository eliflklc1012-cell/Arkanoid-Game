//sfml grafik kütüphanesi ve standart kütüphaneleri dahil etme
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    std::cout << "1. Adim: Program basladi..." << std::endl;
    
    // Pencere oluşturmayı deniyoruz(pencere boyutunu, adını belirleme)
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid - Seviye 1");
    
    std::cout << "2. Adim: Pencere basariyla olusturuldu!" << std::endl;
    
    window.setFramerateLimit(60);

    //raket tanımladım(boyutunu, rengini ve başlangıç konumunu belirleme)
        sf::RectangleShape 
         paddle(sf::Vector2f(120.f, 20.f));
         paddle.setFillColor(sf::Color::Cyan);
            paddle.setPosition(340.0f, 550.0f);
            
    //oyunun farklı bilgisayarlarda aynı hızda çalışmasını sf::clock kullanarak sağlıyoruz
            sf::Clock clock;
            float paddleSpeed = 600.0f;
    //döngü, pencere açık olduğu sürece kontrolleri çizimleri yapaıcak
         while (window.isOpen()) {
    
    //  geçen süreyi hesaplama ve girdilere göre raketi hareket ettirme kısmı
            sf::Time dt =clock.restart();
            if 
            (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && paddle.getPosition().x> 0) {
                paddle.move(-paddleSpeed * dt.asSeconds(), 0);
            }
            if 
            (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && paddle.getPosition().x +paddle.getSize().x <800)
            {   
                 paddle.move(paddleSpeed * dt.asSeconds(), 0);
            }
            
    //kapatma tuşu gibi olayları kontrol etme 
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

    // ekran temizleme, raketi çizme ve ekrana yansıtma kısmı
        window.clear(sf::Color::Black);
        window.draw(paddle);
        window.display();
    }

    std::cout << "3. Adim: Program kapaniyor." << std::endl;
    return 0;
}
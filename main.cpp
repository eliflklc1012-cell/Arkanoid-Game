//sfml grafik kütüphanesi ve standart kütüphaneleri dahil etme
#include <SFML/Graphics.hpp>
#include <iostream>
#include "OyunFonksiyonlari.hpp" //header dosyası

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

    // top ayarları
        sf::CircleShape ball(10.0f); //sfmlden hazır aldığım top çizme kalıbı , buyukluğu 10
        ball.setFillColor(sf::Color::White); //topun  rengi
        ball.setPosition(400.0f, 300.0f);//ektranın boyutuna göre ortada durması
        sf::Vector2f ballVelocity(300.0f, -300.0f);  //topun yönü
        
        



    //döngü, pencere açık olduğu sürece kontrolleri çizimleri yapaıcak
         while (window.isOpen()) {
    
    //  geçen süreyi hesaplama ve girdilere göre raketi hareket ettirme kısmı
            sf::Time dt =clock.restart();
            
        raketHareketi(paddle, paddleSpeed, dt);
        topHareketiVeDuvarSekmesi(ball, ballVelocity, dt);
        topRaketCarpmasi(ball, ballVelocity, paddle);
            
    //kapatma tuşu gibi olayları kontrol etme 
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

    // ekran temizleme, raketi çizme ve ekrana yansıtma kısmı
        window.clear(sf::Color::Black);
        window.draw(paddle);
        window.draw(ball);
        window.display();
    }

    std::cout << "3. Adim: Program kapaniyor." << std::endl;
    return 0;
}
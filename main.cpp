#include <SFML/Graphics.hpp>

int main() {
    // 800x600 boyutlarında bir oyun penceresi oluştur
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid - Seviye 1");
    window.setFramerateLimit(60); // Oyun saniyede 60 kare (FPS) çalışsın

    // Oyun Döngüsü (Game Loop): Pencere açık kaldığı sürece çalışır
    while (window.isOpen()) {
        sf::Event event;
        
        // Kullanıcı penceredeki çarpı (X) tuşuna basarsa pencereyi kapat
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Ekranı temizle (Siyah arkaplan)
        window.clear(sf::Color::Black);

        

        // 3. Çizilenleri ekranda göster
        window.display();
    }

    return 0;
}
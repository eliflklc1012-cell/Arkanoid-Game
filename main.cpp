#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    std::cout << "1. Adim: Program basladi..." << std::endl;
    
    // Pencere oluşturmayı deniyoruz
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid - Seviye 1");
    
    std::cout << "2. Adim: Pencere basariyla olusturuldu!" << std::endl;
    
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        window.display();
    }

    std::cout << "3. Adim: Program kapaniyor." << std::endl;
    return 0;
}
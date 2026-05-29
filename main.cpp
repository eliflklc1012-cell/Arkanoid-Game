//sfml grafik kütüphanesi ve standart kütüphaneleri dahil etme
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string> // Skor ve canları pencere başlığına metin olarak yazdırmak için ekledik
#include "OyunFonksiyonlari.hpp" //header dosyası

int main() {
    std::cout << "1. Adim: Program basladi..." << std::endl;
    
    // Pencere oluşturmayı deniyoruz(pencere boyutunu, adını belirleme)
    // Başlangıçta seviye, skor ve can bilgisini pencere başlığında gösteriyoruz
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid - Seviye: 1  Skor: 0  Can: 3");
    
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
        
    // oyunun durumunu takip etmek için basit değişkenler (Skor ve can takibi için)
        int skor = 0;
        int can = 3;
        int seviye = 1;
        bool oyunBitti = false;
    
    //blokları tutacak olan vektörümüzü tanımlıyoruz ve dosyadan haritayı okuyup blokları ekrana dizen fonksiyonla ekrana diziyoruzz
        std::vector<Tugla> blocks;
        seviyeYukle("seviye1.txt", blocks); // Döngü başlamadan önce dosyayı bir kez okuyup blokları hafızaya alır

    //döngü, pencere açık olduğu sürece kontrolleri çizimleri yapaıcak
         while (window.isOpen()) {
    
    //  geçen süreyi hesaplama ve girdilere göre raketi hareket ettirme kısmı
            sf::Time dt = clock.restart();
            
        if (!oyunBitti) {
            raketHareketi(paddle, paddleSpeed, dt);
            
            // Topun düşme kontrolünü yapıyoruz
            bool topDustu = topHareketiVeDuvarSekmesi(ball, ballVelocity, dt);
            if (topDustu) {
                can--;
                if (can <= 0) {
                    oyunBitti = true;
                } else {
                    // Can gitirse topu ve raketi merkeze sıfırla
                    ball.setPosition(400.0f, 300.0f);
                    ballVelocity = sf::Vector2f(300.0f, -300.0f);
                    paddle.setPosition(340.0f, 550.0f);
                }
            }
            
            topRaketCarpmasi(ball, ballVelocity, paddle);
            
            // Blok çarpışmasını ve skor artışını yönetiyoruz
            topBlokCarpismasi(ball, ballVelocity, blocks, skor);
            
            // Hata veren font kütüphanesi yerine, skoru pencerenin üstündeki başlığa canlı yazdırıyoruz
            std::string yeniBaslik = "Arkanoid - Seviye: " + std::to_string(seviye) + 
                                     "  Skor: " + std::to_string(skor) + 
                                     "  Can: " + std::to_string(can);
            window.setTitle(yeniBaslik);
            
            // Eğer tüm bloklar temizlenirse seviye bitirme mesajı ver
            if (blocks.empty()) {
                window.setTitle("TEBRIKLER! SEVIYE GECILDI!");
            }
        }
            
    //kapatma tuşu gibi olayları kontrol etme 
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

    // ekran temizleme, raketi çizme ve ekrana yansıtma kısmı
        window.clear(sf::Color::Black);
        
        if (!oyunBitti) {
            window.draw(paddle);
            window.draw(ball);
            
            //listede kalan tuğlaları tek tek çizme
            for (const auto& block : blocks) {
                window.draw(block.shape);
            }
        } else {
            // Oyun bittiğinde başlığı güncelle
            window.setTitle("GAME OVER - Toplam Skor: " + std::to_string(skor));
        }
        
        window.display();
    }

    std::cout << "3. Adim: Program kapaniyor." << std::endl;
    return 0;
}
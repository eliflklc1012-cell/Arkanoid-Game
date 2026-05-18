#include "OyunFonksiyonlari.hpp"
#include <iostream>

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


// topun rakete çarpıp sekmesi mantığı

void topRaketCarpmasi(sf::CircleShape& ball, sf::Vector2f& ballVelocity, const sf::RectangleShape& paddle){
    sf::FloatRect ballBounds = ball.getGlobalBounds(); //topun ekrandaki sınırlarını alma
    sf::FloatRect paddleBounds = paddle.getGlobalBounds(); //raketin ekrandaki sınırlarını alma


    if (ballBounds.intersects(paddleBounds) && ballVelocity.y > 0) { //topun rakete çarpıpı çarpmadığını ve çarpışmanınn sadece aşağı doğru algılamasını sağlar
        ballVelocity.y =  -ballVelocity.y;//temas gerçekleştiği anda topun aynı süratle yukarı doğru sekmesini sağlar
    }
}

//  Dosyadan haritayı okuyup blokları ekrana dizen fonksiyon
void seviyeYukle(const std::string& dosyaAdi, std::vector<sf::RectangleShape>& blocks) {
    blocks.clear(); // Önceki seviyeden kalan bloklar varsa listeyi sıfırlıyoruz

    std::ifstream dosya(dosyaAdi); // Belirtilen txt dosyasını okumak için açıyoruz
    if (!dosya.is_open()) {
        std::cout << "Hata: " <<dosyaAdi<< " dosyasi build klasorunde bulunamadi!" << std::endl;
        return;
    }

    int deger;
    int satir = 0;
    int sutun = 0;

    // Tuğlaların boyutları ve aralarındaki boşluklar
    float blockWidth = 70.f;
    float blockHeight = 25.f;
    float spacingX = 8.f;
    float spacingY = 8.f;
    float startX = 35.f; // İlk tuğlanın soldan başlama mesafesi
    float startY = 50.f; // İlk tuğlanın yukarıdan başlama mesafesi

    // Dosyadaki tüm sayıları tek tek (boşluklara göre) okuyan kısım
    while (dosya >> deger) {
        if (deger == 1) { // Eğer sayı 1 ise orada kırılacak bir tuğla var 
            sf::RectangleShape block(sf::Vector2f(blockWidth, blockHeight));
            
            // Matematiksel olarak her tuğlanın ekrandaki benzersiz konumunu hesaplama
            float x = startX + sutun * (blockWidth + spacingX);
            float y = startY + satir * (blockHeight + spacingY);
            
            block.setPosition(x, y);
            block.setFillColor(sf::Color(255, 105,180)); // Tuğlalarımızın rengi kırmızı olsun
            
            blocks.push_back(block); // Oluşturulan tuğlayı dinamik listemize ekle
        }

        sutun++;
        if (sutun == 10) { // Bizim seviye matrisimiz 10 sütundan oluşuyor, 10 olunca alt satıra geç
            sutun = 0;
            satir++;
        }
    }
    dosya.close(); // Dosya ile işimiz bittiği için kapatıyoruz
}

//Topun tuğlaları kırıp dikey eksende sekmesini sağlar
void topBlokCarpismasi(sf::CircleShape& ball, sf::Vector2f& ballVelocity, std::vector<sf::RectangleShape>& blocks) {
    sf::FloatRect ballBounds = ball.getGlobalBounds();

    // Vektör(liste) içindeki tuğlaları güvenli bir şekilde silerek ilerlemek için iterator kullanıyoruz
    for (auto it = blocks.begin(); it != blocks.end(); ) {
        sf::FloatRect blockBounds = it->getGlobalBounds();

        // Eğer top ile döngüdeki mevcut tuğla ekranda temas ediyorsa
        if (ballBounds.intersects(blockBounds)) {
            ballVelocity.y = -ballVelocity.y; // Topun dikey hızını tersine çeviren kısım
            
            it = blocks.erase(it); //tuğlayı listeden tamamen sil ve listeyi güncelle
            break; // Aynı oyun karesinde(frame) sadece tek bir tuğla kırılsın diye döngüden çık
        } else {
            ++it; // Çarpışma yoksa listedeki bir sonraki tuğlaya geç
        }
    }
}
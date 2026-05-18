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
void seviyeYukle(const std::string& dosyaAdi, std::vector<Tugla>& blocks) {
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
        //eğer sayi 1 veya 2 ise tuğla oluşturulacak, 0 ise boşluk
        if (deger == 1  || deger==2) { 
            Tugla yeniTugla;
            yeniTugla.can = deger; //tuğlanın can degerini dosyadan okunan degere göre(1/2) atıyoruz

            sf::RectangleShape rect(sf::Vector2f(blockWidth, blockHeight));
            
            // Matematiksel olarak her tuğlanın ekrandaki benzersiz konumunu hesaplama
            float x = startX + sutun * (blockWidth + spacingX);
            float y = startY + satir * (blockHeight + spacingY);
            rect.setPosition(x, y);
            
           if(yeniTugla.can ==2){ 
                rect.setFillColor(sf::Color(102, 51, 153)); //canı 2 olan tuglalar mor olucak
            }else{
                rect.setFillColor(sf::Color(255, 105,180)); //canı bir olan pembe
            }


            yeniTugla.shape= rect; // oluşturduğumuz dikdörtgeni tugla yapısının shape uyesine atıyoruz
            blocks.push_back(yeniTugla); // Oluşturulan tuğlayı dinamik listemize ekle
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
void topBlokCarpismasi(sf::CircleShape& ball, sf::Vector2f& ballVelocity, std::vector<Tugla>& blocks) {
    sf::FloatRect ballBounds = ball.getGlobalBounds();

    // Vektör(liste) içindeki tuğlaları güvenli bir şekilde silerek ilerlemek için iterator kullanıyoruz
    for (auto it = blocks.begin(); it != blocks.end(); ) {
        sf::FloatRect blockBounds = it->shape.getGlobalBounds();

        // Eğer top ile döngüdeki mevcut tuğla ekranda temas ediyorsa
        if (ballBounds.intersects(blockBounds)) {
            ballVelocity.y = -ballVelocity.y; 
            
            it->can--;// Topun dikey hızını tersine çeviren kısım
            

          if(it->can <=0){
            it = blocks.erase(it); //tuğlayı listeden tamamen sil ve listeyi güncelle
        } else {
            it->shape.setFillColor(sf::Color(255, 105, 180));//canı kaldıysa pembeye çevir
        }
        break;//çarpışma sonrası döngüden çıkma

        } else{
            ++it;
        }
    }
}
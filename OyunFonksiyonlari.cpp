#include "OyunFonksiyonlari.hpp"
#include <iostream>
#include <fstream>

// Raketin sağa ve sola hareket etmesini sağlar
void raketHareketi(sf::RectangleShape& paddle, float paddleSpeed, sf::Time dt) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && paddle.getPosition().x > 0) {
        paddle.move(-paddleSpeed * dt.asSeconds(), 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && paddle.getPosition().x + paddle.getSize().x < 800) {
        paddle.move(paddleSpeed * dt.asSeconds(), 0);
    }
}





// Topun hareketi ve sınırlardan (duvarlardan) sekmesi
bool topHareketiVeDuvarSekmesi(sf::CircleShape& ball, sf::Vector2f& ballVelocity, sf::Time dt) {
    ball.move(ballVelocity * dt.asSeconds());

    // Sağ ve sol duvardan sekme kontrolü
    if (ball.getPosition().x < 0 || ball.getPosition().x + ball.getRadius() * 2 > 800) {
        ballVelocity.x = -ballVelocity.x;
    }
    // Üstteki duvarın kontrolü
    if (ball.getPosition().y < 0) {
        ballVelocity.y = -ballVelocity.y;
    }

    // Top alt sınıra (tabana) düşerse true döner
    if (ball.getPosition().y > 580) { 
        return true; 
    }
    return false;
}







// Topun rakete çarpıp sekmesini sağlar
void topRaketCarpmasi(sf::CircleShape& ball, sf::Vector2f& ballVelocity, const sf::RectangleShape& paddle) {
    sf::FloatRect ballBounds = ball.getGlobalBounds();//topun ekrandaki sınırlarını alma
    sf::FloatRect paddleBounds = paddle.getGlobalBounds();//raketin ekrandaki sınırlarını alma

    if (ballBounds.intersects(paddleBounds) && ballVelocity.y > 0) {
        ballVelocity.y = -ballVelocity.y;// top rakete çarptığı anda topun aynı süratle yukarı çıkmasını sağlıyoruz
    }
}






// Txt dosyasından seviyeyi yükler
void seviyeYukle(const std::string& dosyaAdi, std::vector<Tugla>& blocks) {

    if (dosyaAdi == "seviye2.txt" && !blocks.empty()) { blocks.clear(); } // seviye-2 yüklenirken önceki seviyeden kalan blok varsa temizleme kontrolü

    blocks.clear();// önceki seviyeden blok varsa liste sıfırlanır
   
    std::ifstream dosya(dosyaAdi); //belirtilen txt dosyasını okumak için açıyoruz

    // eğer dosya ilk denemede açılamazsa, build klasörünün bir üstünde aramaya çalışıyoruz (dosya konumuna göre)
   if(!dosya.is_open()) {
        dosya.open("../" + dosyaAdi); 
   }

    if (!dosya.is_open()) {
     std::cout << "Hata: " 
               << dosyaAdi 
               << " dosyasi build klasorunde bulunamadi!" 
               << std::endl;
        return;
    }

    int deger;
    int satir = 0;
    int sutun = 0;

// tuğlaların boyutları ve aralarındaki boşluklar
    float blockWidth = 70.f;
    float blockHeight = 25.f;

    float spacingX = 8.f;
    float spacingY = 8.f;

    float startX = 35.f;
    float startY = 50.f;

    // dosyadaki tüm sayılartı tek tek (boşluklara göre) okuyarak tuğla oluşturuyoruz
    while (dosya >> deger) {

   //eğer sayi 1 veya 2 ise tuğla oluşturulacak, 0 ise boşluk
        if (deger == 1 || deger == 2) {

            Tugla yeniTugla;
            yeniTugla.can = deger;//tuğlanın can degerini dosyadan okunan degere göre(1/2) atıyoruz

            sf::RectangleShape rect(sf::Vector2f(blockWidth, blockHeight));

    // Matematiksel olarak her tuğlanın ekrandaki  konumunu hesaplama  
            float x = startX + sutun * (blockWidth + spacingX);
            float y = startY + satir * (blockHeight + spacingY);
            rect.setPosition(x, y);

                if (yeniTugla.can == 2) {
                    rect.setFillColor(sf::Color(102, 51, 153)); // canı 2 olan tuğlalar mor 
                } else {
                    rect.setFillColor(sf::Color(255, 105, 180));  //canı 1 olan pembe
                }

            yeniTugla.shape = rect; // oluşturduğumuz dikdörtgeni tugla yapısının shape uyesine atıyoruz
            blocks.push_back(yeniTugla); // Oluşturulan tuğlayı dinamik listemize ekle
        }

        sutun++;
        if (sutun == 10) {// Bizim seviye matrisimiz 10 sütundan oluşuyor, 10 olunca alt satıra geç
            sutun = 0;
            satir++;
        }
    }
    std::cout << "blocks sayisi: " 
              << blocks.size()
              << std::endl;

    dosya.close();// Dosya ile işimiz bittiği için kapatıyoruz
}







// Topun tuğlalarla çarpışmasını kontrol eder( topun tuğlaları kırıp dikey eksende sekmesini sağlar))
void topBlokCarpismasi(sf::CircleShape& ball, sf::Vector2f& ballVelocity, std::vector<Tugla>& blocks, int& skor) {
    sf::FloatRect ballBounds = ball.getGlobalBounds();

// Vektör(liste) içindeki tuğlaları güvenli bir şekilde silerek ilerlemek için iterator kullanıyoruz 
    for (auto it = blocks.begin(); it != blocks.end(); ) {

        sf::FloatRect blockBounds = it->shape.getGlobalBounds();

        if (ballBounds.intersects(blockBounds)) {

            float topMerkezY = ball.getPosition().y + ball.getRadius();

            if (topMerkezY < blockBounds.top || topMerkezY > blockBounds.top + blockBounds.height) {
                ballVelocity.y = -ballVelocity.y;
                ball.move(0, ballVelocity.y * 0.02f);
            } else {
                ballVelocity.x = -ballVelocity.x;
                ball.move(ballVelocity.x * 0.02f, 0);
            }

            it->can--;
            skor += 50;

            if (it->can <= 0) {
                it = blocks.erase(it);//tuğlayı listeden tamamen sil ve listeyi güncelle
            }
             else {
                it->shape.setFillColor(sf::Color(255, 105, 180)); //  canı kaldıysa mordan pembeye dönüş
                ++it;
            }

            break;//çarpışma sonrası döngüden çıkma
        } else {

            ++it;
        }
    }
}